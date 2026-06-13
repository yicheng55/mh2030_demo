/**
 * @file dm9051_lwip.c
 * @brief DM9051A SPI Ethernet 控制器的 lwIP standard netif 適配層。
 *
 * 設計重點：
 *   - DM9051A 底層驅動只處理「連續記憶體」中的完整 Ethernet frame。
 *   - lwIP TX 可能給出不連續的 pbuf chain，因此送出前必須先整理成 tx_buf。
 *   - RX 先從硬體讀到 rx_buf，再配置 PBUF_POOL pbuf 並交給 netif->input()。
 */

#include "dm9051_lwip.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lwip/def.h"
#include "lwip/etharp.h"
#if LWIP_IPV6
#include "lwip/ethip6.h"
#endif
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/prot/ethernet.h"

#ifndef DM9051_LWIP_USE_LEGACY_CORE
#define DM9051_LWIP_USE_LEGACY_CORE 0
#endif

#ifndef DM9051_LWIP_DIAG
#define DM9051_LWIP_DIAG 1
#endif

#ifndef DM9051_LWIP_RX_STRIP_FCS
#define DM9051_LWIP_RX_STRIP_FCS 1
#endif

#ifndef DM9051_LWIP_HAS_LINK_STATUS
#define DM9051_LWIP_HAS_LINK_STATUS 0
#endif

#if DM9051_LWIP_DIAG
#define DM9051_LWIP_DIAG_PRINTF(...) printf(__VA_ARGS__)
#else
#define DM9051_LWIP_DIAG_PRINTF(...) do { } while (0)
#endif

#if DM9051_LWIP_USE_LEGACY_CORE
#include "../../core/inc/dm9051_core.h"
#include "../../hal/inc/dm9051_hal.h"
#include "../../ports/mh2030a/dm9051_hal_mh2030a_spi1.h"

static dm9051_device_t dm9051_lwip_dev;
static dm9051_hal_t dm9051_lwip_hal;
static int dm9051_lwip_status = DM9051_ERR_NOT_READY;

static err_t dm9051_lwip_hw_init(uint8_t *macaddr)
{
    dm9051_config_t core_config;
    dm9051_mh2030a_config_t port_config;
    const uint8_t *active_mac;
    int status;

    dm9051_core_default_config(&core_config);
    core_config.mac_addr = macaddr;
#if DM9051_MH2030A_USE_IRQ
    core_config.interrupt_mode = DM9051_INPUT_MODE_INTERRUPT;
#else
    core_config.interrupt_mode = DM9051_INPUT_MODE_POLL;
#endif
    core_config.flow_control = 0u;

    dm9051_mh2030a_default_config(&port_config);
#if DM9051_MH2030A_USE_DMA
    port_config.transport = DM9051_MH2030A_TRANSPORT_DMA;
#else
    port_config.transport = DM9051_MH2030A_TRANSPORT_POLLING;
#endif
#if DM9051_MH2030A_USE_IRQ
    port_config.irq_mode = DM9051_MH2030A_IRQ_EXTI;
#else
    port_config.irq_mode = DM9051_MH2030A_IRQ_OFF;
#endif

    status = dm9051_mh2030a_hal_bind(&dm9051_lwip_hal, &port_config);
    if (status != DM9051_HAL_OK) {
        dm9051_lwip_status = DM9051_ERR_NOT_READY;
        return ERR_IF;
    }

#if DM9051_MH2030A_USE_IRQ
    dm9051_mh2030a_irq_attach_device(&dm9051_lwip_dev);
#endif

    dm9051_lwip_status = dm9051_core_open(&dm9051_lwip_dev,
                                          &core_config,
                                          &dm9051_lwip_hal);
    if (dm9051_lwip_status != DM9051_OK) {
#if DM9051_MH2030A_USE_IRQ
        dm9051_mh2030a_irq_detach_device();
#endif
        return ERR_IF;
    }

    active_mac = dm9051_core_mac(&dm9051_lwip_dev);
    if (active_mac != NULL) {
        memcpy(macaddr, active_mac, ETH_HWADDR_LEN);
    }

    return ERR_OK;
}

static uint16_t dm9051_lwip_packet_receive(uint8_t *packet, uint16_t max_len)
{
    if (dm9051_lwip_status != DM9051_OK) {
        return 0u;
    }

    return dm9051_core_receive(&dm9051_lwip_dev, packet, max_len);
}

static uint16_t dm9051_lwip_packet_send(uint8_t *packet, uint16_t len)
{
    if (dm9051_lwip_status != DM9051_OK) {
        return 0u;
    }

    return (dm9051_core_send(&dm9051_lwip_dev, packet, len) == DM9051_OK) ?
           len : 0u;
}

int dm9051_lwip_link_is_up(void)
{
    if (dm9051_lwip_status != DM9051_OK) {
        return 0;
    }

    return dm9051_core_link_is_up(&dm9051_lwip_dev);
}

#define dm9051_packet_receive(packet, max_len) dm9051_lwip_packet_receive((packet), (max_len))
#define dm9051_packet_send(packet, len) dm9051_lwip_packet_send((packet), (len))
#else
/*
 * 底層 DM9051A 驅動 API。
 *
 * 使用者指定這三個函式為穩定、不變動的硬體介面。若實際工程中的函式名稱
 * 不同，只需要在這個區塊改成對應 wrapper，不必碰 lwIP netif 邏輯。
 */
void dm9051_init(uint8_t *macaddr);
uint16_t dm9051_packet_send(uint8_t *packet, uint16_t len);
uint16_t dm9051_packet_receive(uint8_t *packet, uint16_t max_len);
#if DM9051_LWIP_HAS_LINK_STATUS
int dm9051_link_is_up(void);
#endif
static err_t dm9051_lwip_hw_init(uint8_t *macaddr)
{
    dm9051_init(macaddr);
    return ERR_OK;
}

int dm9051_lwip_link_is_up(void)
{
#if DM9051_LWIP_HAS_LINK_STATUS
    return dm9051_link_is_up() ? 1 : 0;
#else
    return 1;
#endif
}
#endif

#ifndef DM9051_LWIP_MTU
#define DM9051_LWIP_MTU 1500U
#endif

#ifndef DM9051_LWIP_ETH_FRAME_SIZE
#define DM9051_LWIP_ETH_FRAME_SIZE 1514U
#endif

/* Bare-metal MCU 上使用靜態 buffer，避免在 driver TX/RX 路徑中動態配置。 */
static uint8_t tx_buf[DM9051_LWIP_ETH_FRAME_SIZE];
static uint8_t rx_buf[DM9051_LWIP_ETH_FRAME_SIZE];

static err_t low_level_output(struct netif *netif, struct pbuf *p);

static uint16_t dm9051_lwip_eth_type(const uint8_t *frame, uint16_t len)
{
    if ((frame == NULL) || (len < 14U)) {
        return 0U;
    }

    return (uint16_t)(((uint16_t)frame[12] << 8) | frame[13]);
}

static const char *dm9051_lwip_eth_type_name(uint16_t eth_type)
{
    switch (eth_type) {
    case 0x0800U:
        return "IPv4";
    case 0x0806U:
        return "ARP";
    default:
        return "ETH";
    }
}

err_t dm9051_if_init(struct netif *netif)
{
    if (netif == NULL) {
        return ERR_ARG;
    }

    /*
     * lwIP 會用 name[0..1] 作為介面名稱前綴；這裡使用 "dm"
     * 表示 Davicom/DM9051A。
     */
    netif->name[0] = 'd';
    netif->name[1] = 'm';

    /*
     * IPv4 走 ARP output，最後會呼叫 netif->linkoutput。
     * linkoutput 則是本檔提供的 low_level_output()。
     */
    netif->output = etharp_output;
    netif->linkoutput = low_level_output;

#if LWIP_IPV6
    netif->output_ip6 = ethip6_output;
#endif

    netif->hwaddr_len = ETH_HWADDR_LEN;
    netif->mtu = DM9051_LWIP_MTU;
    netif->flags = NETIF_FLAG_BROADCAST |
                   NETIF_FLAG_ETHARP |
                   NETIF_FLAG_ETHERNET;

    /*
     * 應用層應在 netif_add() 前先填好 netif->hwaddr。
     * dm9051_lwip_hw_init() 會初始化 SPI/PHY/DM9051A，並將 MAC 寫入晶片。
     */
    if (dm9051_lwip_hw_init(netif->hwaddr) != ERR_OK) {
        return ERR_IF;
    }

    DM9051_LWIP_DIAG_PRINTF("[DM9051 lwIP] if init MAC=%02X:%02X:%02X:%02X:%02X:%02X mtu=%u flags=0x%02X\r\n",
                            netif->hwaddr[0],
                            netif->hwaddr[1],
                            netif->hwaddr[2],
                            netif->hwaddr[3],
                            netif->hwaddr[4],
                            netif->hwaddr[5],
                            (unsigned)netif->mtu,
                            (unsigned)netif->flags);

    return ERR_OK;
}

static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    uint16_t sent_len;

    (void)netif;

    if (p == NULL) {
        return ERR_ARG;
    }

    if (!netif_is_link_up(netif)) {
        LINK_STATS_INC(link.drop);
        return ERR_RTE;
    }

    if (p->tot_len > sizeof(tx_buf)) {
        LINK_STATS_INC(link.lenerr);
        LINK_STATS_INC(link.drop);
        return ERR_BUF;
    }

    /*
     * pbuf 可能是 chain，例如 header 與 payload 分散在不同 pbuf。
     * DM9051A 底層送封包 API 需要連續記憶體，因此用 pbuf_copy_partial()
     * 從 offset 0 開始複製整包 Ethernet frame。
     */
    if (pbuf_copy_partial(p, tx_buf, p->tot_len, 0) != p->tot_len) {
        LINK_STATS_INC(link.err);
        return ERR_BUF;
    }

    DM9051_LWIP_DIAG_PRINTF("[DM9051 lwIP] TX len=%u type=%s(0x%04X)\r\n",
                            (unsigned)p->tot_len,
                            dm9051_lwip_eth_type_name(dm9051_lwip_eth_type(tx_buf, p->tot_len)),
                            dm9051_lwip_eth_type(tx_buf, p->tot_len));

    sent_len = dm9051_packet_send(tx_buf, p->tot_len);
    if (sent_len != p->tot_len) {
        LINK_STATS_INC(link.err);
        return ERR_IF;
    }

    LINK_STATS_INC(link.xmit);
    return ERR_OK;
}

void dm9051_lwip_input(struct netif *netif)
{
    struct pbuf *p;
    uint16_t len;
    uint16_t raw_len;
    err_t err;

    if ((netif == NULL) || (netif->input == NULL)) {
        return;
    }

    /*
     * 先讀到 rx_buf，而不是直接讀到 pbuf->payload。
     * 原因是 PBUF_POOL 可能配置出 pbuf chain，第一個 payload 未必能容納整包。
     */
    len = dm9051_packet_receive(rx_buf, sizeof(rx_buf));
    if (len == 0U) {
        return;
    }

    if (len > sizeof(rx_buf)) {
        LINK_STATS_INC(link.lenerr);
        LINK_STATS_INC(link.drop);
        return;
    }

    raw_len = len;
#if DM9051_LWIP_RX_STRIP_FCS
    if (len > 4U) {
        len = (uint16_t)(len - 4U);
    }
#endif

    DM9051_LWIP_DIAG_PRINTF("[DM9051 lwIP] RX raw=%u len=%u type=%s(0x%04X) dst=%02X:%02X:%02X:%02X:%02X:%02X src=%02X:%02X:%02X:%02X:%02X:%02X\r\n",
                            (unsigned)raw_len,
                            (unsigned)len,
                            dm9051_lwip_eth_type_name(dm9051_lwip_eth_type(rx_buf, len)),
                            dm9051_lwip_eth_type(rx_buf, len),
                            rx_buf[0],
                            rx_buf[1],
                            rx_buf[2],
                            rx_buf[3],
                            rx_buf[4],
                            rx_buf[5],
                            rx_buf[6],
                            rx_buf[7],
                            rx_buf[8],
                            rx_buf[9],
                            rx_buf[10],
                            rx_buf[11]);

    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    if (p == NULL) {
        LINK_STATS_INC(link.memerr);
        LINK_STATS_INC(link.drop);
        return;
    }

    if (pbuf_take(p, rx_buf, len) != ERR_OK) {
        pbuf_free(p);
        LINK_STATS_INC(link.err);
        return;
    }

    /*
     * netif_add() 時建議把 input callback 設為 ethernet_input，
     * 因為這裡交出去的是完整 Ethernet frame。
     */
    err = netif->input(p, netif);
    if (err != ERR_OK) {
        pbuf_free(p);
        LINK_STATS_INC(link.drop);
        return;
    }

    LINK_STATS_INC(link.recv);
}

int dm9051_lwip_init(struct netif *netif, const void *dev)
{
    (void)dev;
    return (dm9051_if_init(netif) == ERR_OK) ? 0 : -1;
}

void dm9051_lwip_poll(struct netif *netif)
{
    dm9051_lwip_input(netif);
}
