/**
 * @file dm9051_lwip.c
 * @brief DM9051A SPI Ethernet 的 lwIP 適配層 — 相容包裝。
 *
 * 此檔是 `ethernetif.c` (lwip-2.1.2/port/) 的上層相容包裝，
 * 提供專案中既有程式碼習慣使用的 dm9051_lwip_* API。
 *
 * 對接模型：
 *   dm9051_lwip_xxx()            ← 既有程式碼呼叫此層
 *       ↓ 委託
 *   ethernetif_init / input     ← 標準 lwIP netif 模板 (port/ethernetif.c)
 *       ↓ 呼叫
 *   dm9051_core_*                ← DM9051 核心驅動 (core/src/)
 *       ↓ 透過 vtable
 *   dm9051_hal_mh2030a_*        ← MH2030A 平台移植 (ports/mh2030a/)
 */

#include "dm9051_lwip.h"

#include <stdint.h>
#include <string.h>

#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/etharp.h"
#include "lwip/ethip6.h"
#include "netif/ethernet.h"

#include "ethernetif.h"

/* ---------------------------------------------------------------------------
 * 靜態 netif 實例 — 供既有 dm9051_lwip_poll() 等無參數 API 使用
 * ------------------------------------------------------------------------ */
static struct netif dm9051_netif;
static struct netif *g_active_netif;

/* ---------------------------------------------------------------------------
 * dm9051_if_init — netif_add() 的 init callback
 *
 * 直接委託 ethernetif_init()，由標準 ethernetif.c 完成所有初始化。
 * 相容既有 netif_add(&n, ..., dm9051_if_init, ethernet_input) 的用法。
 * ------------------------------------------------------------------------ */
err_t dm9051_if_init(struct netif *netif)
{
    g_active_netif = netif;
    return ethernetif_init(netif);
}

/* ---------------------------------------------------------------------------
 * dm9051_lwip_link_is_up — 查詢 PHY link 狀態
 *
 * 透過 g_active_netif->state (ethernetif 私有資料) 關聯的 DM9051 裝置
 * 讀取 PHY 暫存器判斷實體線路狀態。
 * 若 g_active_netif 未設定則使用內部靜態 dm9051_netif。
 * ------------------------------------------------------------------------ */
int dm9051_lwip_link_is_up(void)
{
    struct netif *n = (g_active_netif != NULL) ? g_active_netif : &dm9051_netif;

    if (n->state == NULL) {
        return 0;
    }
    return netif_is_link_up(n) ? 1 : 0;
}

/* ---------------------------------------------------------------------------
 * dm9051_lwip_input — 輪詢 RX 並餵入 lwIP
 *
 * 委託 ethernetif_input()。
 * ------------------------------------------------------------------------ */
void dm9051_lwip_input(struct netif *netif)
{
    ethernetif_input(netif);
}

/* ---------------------------------------------------------------------------
 * dm9051_lwip_init — 舊式 staging API 相容包裝
 *
 * 1. 設定 MAC
 * 2. 呼叫 lwip_init()
 * 3. netif_add() 使用 dm9051_if_init / ethernet_input
 * 4. netif_set_up, netif_set_default
 *
 * dev 參數保留但未使用 (為舊 API 簽名相容)。
 * ------------------------------------------------------------------------ */
int dm9051_lwip_init(struct netif *netif, const void *dev)
{
    ip4_addr_t ipaddr, netmask, gateway;

    (void)dev;

    if (netif == NULL) {
        return -1;
    }

    IP4_ADDR(&ipaddr,  0, 0, 0, 0);
    IP4_ADDR(&netmask, 0, 0, 0, 0);
    IP4_ADDR(&gateway, 0, 0, 0, 0);

    /* 若 netif 尚未設定 MAC，給予預設值 */
    {
        int i, all_zero = 1;
        for (i = 0; i < ETH_HWADDR_LEN; i++) {
            if (netif->hwaddr[i] != 0) { all_zero = 0; break; }
        }
        if (all_zero) {
            netif->hwaddr[0] = 0x00;
            netif->hwaddr[1] = 0x60;
            netif->hwaddr[2] = 0x6E;
            netif->hwaddr[3] = 0x11;
            netif->hwaddr[4] = 0x22;
            netif->hwaddr[5] = 0x33;
        }
    }

    lwip_init();

    if (netif_add(netif, &ipaddr, &netmask, &gateway,
                  NULL, dm9051_if_init, ethernet_input) == NULL) {
        return -1;
    }

    netif_set_default(netif);
    netif_set_up(netif);

    g_active_netif = netif;

    return 0;
}

/* ---------------------------------------------------------------------------
 * dm9051_lwip_poll — 單次輪詢：收封包 + TX done poll
 *
 * 主迴圈中定期呼叫即可。
 * ------------------------------------------------------------------------ */
void dm9051_lwip_poll(struct netif *netif)
{
    if (netif != NULL) {
        ethernetif_input(netif);
    }
}

/* ===========================================================================
 * 以下為向後相容的簡易入口 — 操作預設靜態 netif
 * ======================================================================== */

int dm9051_lwip_simple_init(void)
{
    memset(&dm9051_netif, 0, sizeof(dm9051_netif));

    dm9051_netif.hwaddr[0] = 0x00;
    dm9051_netif.hwaddr[1] = 0x60;
    dm9051_netif.hwaddr[2] = 0x6E;
    dm9051_netif.hwaddr[3] = 0x11;
    dm9051_netif.hwaddr[4] = 0x22;
    dm9051_netif.hwaddr[5] = 0x33;

    return dm9051_lwip_init(&dm9051_netif, NULL);
}

void dm9051_lwip_simple_poll(void)
{
    dm9051_lwip_poll(&dm9051_netif);
}
