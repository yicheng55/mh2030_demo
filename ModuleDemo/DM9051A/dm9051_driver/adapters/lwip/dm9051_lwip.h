#ifndef DM9051_LWIP_H
#define DM9051_LWIP_H

/**
 * @file dm9051_lwip.h
 * @brief DM9051A SPI Ethernet lwIP 適配層標頭 — 相容 API。
 *
 * 此 API 包裝 lwip-2.1.2/port/ethernetif.c 的標準介面，
 * 提供專案既有程式碼習慣使用的 dm9051_lwip_* 函式名稱。
 *
 * 使用方式 (建議)：
 *   1. 自行宣告 struct netif，填入 MAC
 *   2. netif_add(&n, &ip, &mask, &gw, NULL,
 *                dm9051_if_init, ethernet_input)
 *   3. 主迴圈中呼叫 dm9051_lwip_input(&n) 收封包
 *
 * 快速入門 (simple API)：
 *   1. dm9051_lwip_simple_init()
 *   2. while(1) { dm9051_lwip_simple_poll(); ... }
 */

#include "lwip/err.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------
 * 標準 netif 介面 (與 ethernetif_init)
 * ------------------------------------------------------------------------ */

/** @brief netif_add init callback。等同 ethernetif_init。 */
err_t dm9051_if_init(struct netif *netif);

/** @brief 輪詢 DM9051 RX 並餵入 lwIP (等同 ethernetif_input)。 */
void dm9051_lwip_input(struct netif *netif);

/** @brief 查詢 link 狀態 (1 = UP, 0 = DOWN)。 */
int dm9051_lwip_link_is_up(void);

/* ---------------------------------------------------------------------------
 * 舊式 staging API (相容既有程式碼)
 * ------------------------------------------------------------------------ */

/** @brief 完整初始化：lwip_init + netif_add + set_up + set_default。 */
int dm9051_lwip_init(struct netif *netif, const void *dev);

/** @brief 單次輪詢：收 RX 封包 + TX done poll。 */
void dm9051_lwip_poll(struct netif *netif);

/** @brief 輪詢 PHY link 狀態並同步 lwIP 旗標 (建議 100-500ms 週期呼叫)。 */
void dm9051_lwip_link_poll(struct netif *netif);

/* ---------------------------------------------------------------------------
 * 簡易無參數 API — 操作內部靜態 netif 實例
 * ------------------------------------------------------------------------ */

/** @brief 初始化內部靜態 netif 並註冊至 lwIP。回傳 0 表示成功。 */
int dm9051_lwip_simple_init(void);

/** @brief 輪詢內部靜態 netif (等同於 dm9051_lwip_poll)。 */
void dm9051_lwip_simple_poll(void);

/** @brief 簡易版 link poll：輪詢內部靜態 netif 的 PHY link 狀態。 */
void dm9051_lwip_simple_link_poll(void);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_LWIP_H */
