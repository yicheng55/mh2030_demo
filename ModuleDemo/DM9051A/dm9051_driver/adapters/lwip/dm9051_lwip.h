#ifndef DM9051_LWIP_H
#define DM9051_LWIP_H

/**
 * @file dm9051_lwip.h
 * @brief DM9051A SPI Ethernet 控制器的 lwIP standard netif 適配層。
 *
 * 使用方式：
 *   1. 應用程式先設定 struct netif 的 MAC 位址欄位。
 *   2. 呼叫 netif_add()，並把 dm9051_if_init() 當作 init callback。
 *   3. 在 bare-metal main loop 或中斷延後處理中呼叫 dm9051_lwip_input()。
 */

#include "lwip/err.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化 DM9051A 對應的 lwIP netif。
 *
 * dm9051_if_init() 會設定 netif name/output/linkoutput/MTU/flags，
 * 並呼叫底層 dm9051_init(netif->hwaddr) 完成硬體初始化與 MAC 設定。
 */
err_t dm9051_if_init(struct netif *netif);

/**
 * @brief 從 DM9051A 收一包 Ethernet frame，並送進 lwIP。
 *
 * 此函式適合在 NO_SYS=1 的 bare-metal 主迴圈中輪詢呼叫。
 * 若硬體目前沒有封包，函式會立即返回。
 */
void dm9051_lwip_input(struct netif *netif);

/* 舊 staging API 的相容 wrapper，方便既有工程逐步切換。 */
int dm9051_lwip_init(struct netif *netif, const void *dev);
void dm9051_lwip_poll(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_LWIP_H */
