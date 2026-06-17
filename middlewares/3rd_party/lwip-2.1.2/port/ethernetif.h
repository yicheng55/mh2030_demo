#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__

/**
 * @file ethernetif.h
 * @brief DM9051 SPI Ethernet lwIP netif 移植層介面。
 *
 * 與 ethernetif.c 成對，提供標準的 lwIP netif init / input 函式，
 * 以及一組便捷註冊輔助函式供 demo / 快速原型使用。
 */

#include "lwip/err.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------
 * 標準 netif 介面 (適用於進階用法: 自行管理 netif 實例)
 *
 * 用法:
 *   struct netif my_netif;
 *   netif_add(&my_netif, &ip, &mask, &gw, NULL,
 *             ethernetif_init, ethernet_input);
 *   netif_set_link_callback(my_netif, ethernetif_update_config);
 *   netif_set_default(&my_netif);
 *   netif_set_up(&my_netif);
 *
 *   之後在主迴圈定期呼叫 ethernetif_input(&my_netif) 收封包。
 * ------------------------------------------------------------------------ */

/** @brief netif_add 的 init callback: 初始化硬體並設定 netif 屬性。 */
err_t ethernetif_init(struct netif *netif);

/** @brief 從 DM9051 輪詢一幀並餵入 lwIP。若收到封包回傳 ERR_OK。 */
err_t ethernetif_input(struct netif *netif);

/** @brief Link 狀態變更回呼。透過 netif_set_link_callback 註冊。 */
void ethernetif_update_config(struct netif *netif);

/* ---------------------------------------------------------------------------
 * 便捷輔助 API (適用於簡單 demo)
 *
 * 管理一個內部靜態 netif 實例，無需自行宣告 netif 變數。
 * ------------------------------------------------------------------------ */

/** @brief 註冊一個預設 netif (IP=0.0.0.0, 使用 DHCP 或後續手動設定)。 */
struct netif *ethernetif_register(void);

/** @brief 在 ethernetif_register() 之前呼叫，自訂 MAC 位址。 */
void lwip_set_mac_address(unsigned char *macadd);

/** @brief 便捷輪詢：呼叫 ethernetif_input 作用於內部 netif。回傳 0 表示成功。 */
int ethernetif_poll(void);

/* ---------------------------------------------------------------------------
 * PTP 硬體時間戳 (預留 / 視晶片支援啟用)
 * ------------------------------------------------------------------------ */
#if LWIP_PTP
struct ptptime_t {
    s32_t tv_sec;
    s32_t tv_nsec;
};

void emac_ptptime_settime(struct ptptime_t *timestamp);
void emac_ptptime_gettime(struct ptptime_t *timestamp);
void emac_ptptime_updateoffset(struct ptptime_t *timeoffset);
void emac_ptptime_adjfreq(int32_t Adj);
u32_t emac_ptpsubsecond2nanosecond(u32_t subsecondvalue);
#endif /* LWIP_PTP */

#ifdef __cplusplus
}
#endif

#endif /* __ETHERNETIF_H__ */

