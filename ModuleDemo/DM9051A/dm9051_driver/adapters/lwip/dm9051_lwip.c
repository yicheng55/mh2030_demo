/**
 * @file dm9051_lwip.c
 * @brief lwIP standard netif adapter for the DM9051A SPI Ethernet controller.
 *
 * The DM9051A low-level driver works with one contiguous Ethernet frame buffer.
 * lwIP, however, may hand the netif driver a pbuf chain.  This adapter performs
 * the required copy/flatten step on transmit and submits received frames back
 * to lwIP through netif->input().
 */

#include "dm9051_lwip.h"

#include <stdint.h>
#include <string.h>

#include "lwip/def.h"
#include "lwip/etharp.h"
#if LWIP_IPV6
#include "lwip/ethip6.h"
#endif
#include "lwip/pbuf.h"
#include "lwip/snmp.h"
#include "lwip/stats.h"
#include "lwip/prot/ethernet.h"
#include "netif/ethernet.h"

/*
 * Driver API binding
 * ------------------
 * Default mode uses the placeholder APIs requested for this adapter:
 *   dm9051_init(), dm9051_packet_send(), dm9051_packet_receive()
 *
 * This repository's current staged core exposes legacy names instead:
 *   dm9051_init(), dm9051_tx(), dm9051_rx()
 *
 * Define DM9051_LWIP_USE_LEGACY_CORE as 1 in the Keil target or before
 * including this file to build against the current staged core names.
 */
#ifndef DM9051_LWIP_USE_LEGACY_CORE
#define DM9051_LWIP_USE_LEGACY_CORE 0
#endif

#if DM9051_LWIP_USE_LEGACY_CORE
#include "../../core/inc/dm9051_core.h"
#define dm9051_packet_receive(packet, max_len) dm9051_rx((packet), (max_len))
static uint16_t dm9051_lwip_packet_send(uint8_t *packet, uint16_t len)
{
    dm9051_tx(packet, len);
    return len;
}
#define dm9051_packet_send(packet, len) dm9051_lwip_packet_send((packet), (len))
#else
void dm9051_init(uint8_t *macaddr);
uint16_t dm9051_packet_send(uint8_t *packet, uint16_t len);
uint16_t dm9051_packet_receive(uint8_t *packet, uint16_t max_len);
#endif

#ifndef DM9051_LWIP_MTU
#define DM9051_LWIP_MTU 1500U
#endif

#ifndef DM9051_LWIP_ETH_FRAME_SIZE
#define DM9051_LWIP_ETH_FRAME_SIZE 1514U
#endif

/* Static buffers are simple and predictable for small bare-metal targets. */
static uint8_t tx_buf[DM9051_LWIP_ETH_FRAME_SIZE];
static uint8_t rx_buf[DM9051_LWIP_ETH_FRAME_SIZE];

static err_t low_level_output(struct netif *netif, struct pbuf *p);

err_t dm9051_if_init(struct netif *netif)
{
    if (netif == NULL) {
        return ERR_ARG;
    }

    netif->name[0] = 'd';
    netif->name[1] = 'm';
    netif->output = etharp_output;
    netif->linkoutput = low_level_output;

#if LWIP_IPV6
    netif->output_ip6 = ethip6_output;
#endif

    netif->hwaddr_len = ETH_HWADDR_LEN;
    netif->mtu = DM9051_LWIP_MTU;
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP |
                   NETIF_FLAG_ETHERNET | NETIF_FLAG_LINK_UP;

    /*
     * The application should set netif->hwaddr before netif_add(), or keep its
     * board default in the low-level driver.  dm9051_init() programs the MAC
     * address and performs the hardware/SPI/PHY initialization.
     */
#if DM9051_LWIP_USE_LEGACY_CORE
    {
        const uint8_t *mac = dm9051_init(netif->hwaddr);
        if (mac == NULL) {
            return ERR_IF;
        }
        memcpy(netif->hwaddr, mac, ETH_HWADDR_LEN);
    }
#else
    dm9051_init(netif->hwaddr);
#endif

    return ERR_OK;
}

static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    uint16_t sent_len;

    (void)netif;

    if (p == NULL) {
        return ERR_ARG;
    }

    if (p->tot_len > sizeof(tx_buf)) {
        LINK_STATS_INC(link.lenerr);
        LINK_STATS_INC(link.drop);
        return ERR_BUF;
    }

    /*
     * lwIP may provide a chained pbuf.  Flatten the full Ethernet frame into a
     * contiguous buffer before passing it to the simple DM9051A TX routine.
     */
    if (pbuf_copy_partial(p, tx_buf, p->tot_len, 0) != p->tot_len) {
        LINK_STATS_INC(link.err);
        return ERR_BUF;
    }

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
    err_t err;

    if ((netif == NULL) || (netif->input == NULL)) {
        return;
    }

    /*
     * Receive into a contiguous temporary buffer first.  PBUF_POOL allocation
     * can return a pbuf chain whose first payload area is smaller than a full
     * Ethernet frame, so direct RX into p->payload is not generally safe.
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
