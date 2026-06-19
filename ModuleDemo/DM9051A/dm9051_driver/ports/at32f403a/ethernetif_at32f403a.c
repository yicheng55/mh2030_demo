#include "ethernetif_at32f403a.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/etharp.h"
#include "lwip/ethip6.h"
#include "netif/ethernet.h"

#include "../../core/inc/dm9051_core.h"
#include "../../hal/inc/dm9051_hal.h"
#include "dm9051_hal_at32f403a_spi1.h"

#ifndef ETHERNETIF_DIAG
#define ETHERNETIF_DIAG 1
#endif

#if ETHERNETIF_DIAG
#define ETHERNETIF_PRINTF(...) printf(__VA_ARGS__)
#else
#define ETHERNETIF_PRINTF(...) do { } while (0)
#endif

#ifndef ETHERNETIF_RX_STRIP_FCS
#define ETHERNETIF_RX_STRIP_FCS 0
#endif

#ifndef ETHERNETIF_MTU
#define ETHERNETIF_MTU         1500U
#endif

#define ETHERNETIF_ETH_FRAME_SIZE   1514U

static uint16_t eth_type(const uint8_t *frame, uint16_t len)
{
    if ((frame == NULL) || (len < 14U)) return 0U;
    return (uint16_t)(((uint16_t)frame[12] << 8) | frame[13]);
}

static const char *eth_type_name(uint16_t t)
{
    switch (t) {
    case 0x0800U: return "IPv4";
    case 0x0806U: return "ARP";
    case 0x86DDU: return "IPv6";
    default:      return "ETH";
    }
}

static void low_level_init(struct netif *netif)
{
    struct ethernetif_at32f403a *eth = (struct ethernetif_at32f403a *)netif->state;
    dm9051_config_t core_config;
    dm9051_at32f403a_config_t port_config;
    const uint8_t *active_mac;
    int status;

    dm9051_core_default_config(&core_config);
    core_config.mac_addr = netif->hwaddr;

#if DM9051_AT32F403A_ENABLE_IRQ
    core_config.interrupt_mode = DM9051_INPUT_MODE_INTERRUPT;
#else
    core_config.interrupt_mode = DM9051_INPUT_MODE_POLL;
#endif
    core_config.flow_control = 0U;

    dm9051_at32f403a_default_config(&port_config);
#if DM9051_AT32F403A_ENABLE_DMA
    port_config.transport = DM9051_AT32F403A_TRANSPORT_DMA;
#else
    port_config.transport = DM9051_AT32F403A_TRANSPORT_POLLING;
#endif
#if DM9051_AT32F403A_ENABLE_IRQ
    port_config.irq_mode = DM9051_AT32F403A_IRQ_EXTI;
#else
    port_config.irq_mode = DM9051_AT32F403A_IRQ_OFF;
#endif

    status = dm9051_at32f403a_hal_bind(&eth->hal, &port_config);
    if (status != DM9051_HAL_OK) {
        ETHERNETIF_PRINTF("[etherif] HAL bind failed (%d)\r\n", status);
        return;
    }

#if DM9051_AT32F403A_ENABLE_IRQ
    dm9051_at32f403a_irq_attach_device(&eth->dev);
#endif

    status = dm9051_core_open(&eth->dev, &core_config, &eth->hal);
    if (status != DM9051_OK) {
        ETHERNETIF_PRINTF("[etherif] core_open failed (%d)\r\n", status);
#if DM9051_AT32F403A_ENABLE_IRQ
        dm9051_at32f403a_irq_detach_device();
#endif
        return;
    }

    active_mac = dm9051_core_mac(&eth->dev);
    if (active_mac != NULL) {
        memcpy(netif->hwaddr, active_mac, ETH_HWADDR_LEN);
    }

    netif->hwaddr_len = ETH_HWADDR_LEN;
    netif->mtu        = ETHERNETIF_MTU;
    netif->flags      = NETIF_FLAG_BROADCAST |
                        NETIF_FLAG_ETHARP |
                        NETIF_FLAG_ETHERNET;

#if LWIP_IPV6
    netif->output_ip6 = ethip6_output;
#endif

    ETHERNETIF_PRINTF("[etherif] hw MAC=%02X:%02X:%02X:%02X:%02X:%02X "
                      "mtu=%u flags=0x%02X\r\n",
                      netif->hwaddr[0], netif->hwaddr[1],
                      netif->hwaddr[2], netif->hwaddr[3],
                      netif->hwaddr[4], netif->hwaddr[5],
                      (unsigned)netif->mtu,
                      (unsigned)netif->flags);
}

static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    struct ethernetif_at32f403a *eth = (struct ethernetif_at32f403a *)netif->state;

    if (p == NULL) return ERR_ARG;

    if (!netif_is_link_up(netif)) {
        LINK_STATS_INC(link.drop);
        return ERR_RTE;
    }

    if (p->tot_len > sizeof(eth->tx_buf)) {
        LINK_STATS_INC(link.lenerr);
        LINK_STATS_INC(link.drop);
        return ERR_BUF;
    }

    if (pbuf_copy_partial(p, eth->tx_buf, p->tot_len, 0) != p->tot_len) {
        LINK_STATS_INC(link.err);
        return ERR_BUF;
    }

    ETHERNETIF_PRINTF("[etherif] TX len=%u type=%s(0x%04X)\r\n",
                      (unsigned)p->tot_len,
                      eth_type_name(eth_type(eth->tx_buf, p->tot_len)),
                      eth_type(eth->tx_buf, p->tot_len));

    if (dm9051_core_send(&eth->dev, eth->tx_buf, p->tot_len) != DM9051_OK) {
        LINK_STATS_INC(link.err);
        return ERR_IF;
    }

    LINK_STATS_INC(link.xmit);
    return ERR_OK;
}

static struct pbuf *low_level_input(struct netif *netif)
{
    struct ethernetif_at32f403a *eth = (struct ethernetif_at32f403a *)netif->state;
    struct pbuf *p;
    uint16_t len;
    uint16_t raw_len;

    len = dm9051_core_receive(&eth->dev, eth->rx_buf, sizeof(eth->rx_buf));
    if (len == 0U) return NULL;

    if (len > sizeof(eth->rx_buf)) {
        LINK_STATS_INC(link.lenerr);
        LINK_STATS_INC(link.drop);
        return NULL;
    }

    raw_len = len;
#if ETHERNETIF_RX_STRIP_FCS
    if (len > 4U) len = (uint16_t)(len - 4U);
#endif

    if (len < 14U) {
        LINK_STATS_INC(link.lenerr);
        LINK_STATS_INC(link.drop);
        return NULL;
    }

    ETHERNETIF_PRINTF("[etherif] RX raw=%u len=%u type=%s(0x%04X) "
                      "dst=%02X:%02X:%02X:%02X:%02X:%02X "
                      "src=%02X:%02X:%02X:%02X:%02X:%02X\r\n",
                      (unsigned)raw_len, (unsigned)len,
                      eth_type_name(eth_type(eth->rx_buf, len)),
                      eth_type(eth->rx_buf, len),
                      eth->rx_buf[0], eth->rx_buf[1],
                      eth->rx_buf[2], eth->rx_buf[3],
                      eth->rx_buf[4], eth->rx_buf[5],
                      eth->rx_buf[6], eth->rx_buf[7],
                      eth->rx_buf[8], eth->rx_buf[9],
                      eth->rx_buf[10], eth->rx_buf[11]);

    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    if (p == NULL) {
        LINK_STATS_INC(link.memerr);
        LINK_STATS_INC(link.drop);
        return NULL;
    }

    if (pbuf_take(p, eth->rx_buf, len) != ERR_OK) {
        pbuf_free(p);
        LINK_STATS_INC(link.err);
        return NULL;
    }

    return p;
}

err_t ethernetif_at32f403a_init(struct netif *netif)
{
    struct ethernetif_at32f403a *eth;
    LWIP_ASSERT("netif != NULL", netif != NULL);

    if (netif->state == NULL) {
        eth = (struct ethernetif_at32f403a *)mem_malloc(sizeof(struct ethernetif_at32f403a));
        if (eth == NULL) {
            ETHERNETIF_PRINTF("[etherif] malloc failed\r\n");
            return ERR_MEM;
        }
        memset(eth, 0, sizeof(struct ethernetif_at32f403a));
        netif->state = eth;
    } else {
        eth = (struct ethernetif_at32f403a *)netif->state;
    }

    netif->name[0] = 'd';
    netif->name[1] = 'm';

    netif->output     = etharp_output;
    netif->linkoutput = low_level_output;

    low_level_init(netif);

    ETHERNETIF_PRINTF("[etherif] init done\r\n");
    return ERR_OK;
}

err_t ethernetif_at32f403a_input(struct netif *netif)
{
    struct pbuf *p;

    if ((netif == NULL) || (netif->input == NULL)) return ERR_ARG;

    p = low_level_input(netif);
    if (p == NULL) return ERR_INPROGRESS;

    if (!netif_is_link_up(netif)) {
        netif_set_link_up(netif);
    }

    if (netif->input(p, netif) != ERR_OK) {
        pbuf_free(p);
        LINK_STATS_INC(link.drop);
        return ERR_IF;
    }

    LINK_STATS_INC(link.recv);
    return ERR_OK;
}

void ethernetif_at32f403a_update_config(struct netif *netif)
{
    struct ethernetif_at32f403a *eth = (struct ethernetif_at32f403a *)netif->state;
    int link_up = 0;

    if (eth != NULL) {
        link_up = dm9051_core_link_is_up(&eth->dev);
    }

    if (link_up) {
        if (!netif_is_link_up(netif)) {
            netif_set_link_up(netif);
            ETHERNETIF_PRINTF("[etherif] Link UP (PHY polled)\r\n");
        }
    } else {
        if (netif_is_link_up(netif)) {
            netif_set_link_down(netif);
            ETHERNETIF_PRINTF("[etherif] Link DOWN (PHY polled)\r\n");
        }
    }
}
