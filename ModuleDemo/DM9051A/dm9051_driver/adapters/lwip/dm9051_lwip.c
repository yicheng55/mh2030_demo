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
/*
 * 底層 DM9051A 驅動 API。
 *
 * 使用者指定這三個函式為穩定、不變動的硬體介面。若實際工程中的函式名稱
 * 不同，只需要在這個區塊改成對應 wrapper，不必碰 lwIP netif 邏輯。
 */
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

/* Bare-metal MCU 上使用靜態 buffer，避免在 driver TX/RX 路徑中動態配置。 */
static uint8_t tx_buf[DM9051_LWIP_ETH_FRAME_SIZE];
static uint8_t rx_buf[DM9051_LWIP_ETH_FRAME_SIZE];

static err_t low_level_output(struct netif *netif, struct pbuf *p);

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
                   NETIF_FLAG_ETHERNET |
                   NETIF_FLAG_LINK_UP;

    /*
     * 應用層應在 netif_add() 前先填好 netif->hwaddr。
     * dm9051_init() 會初始化 SPI/PHY/DM9051A，並將 MAC 寫入晶片。
     */
    dm9051_init(netif->hwaddr);

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
     * pbuf 可能是 chain，例如 header 與 payload 分散在不同 pbuf。
     * DM9051A 底層送封包 API 需要連續記憶體，因此用 pbuf_copy_partial()
     * 從 offset 0 開始複製整包 Ethernet frame。
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
