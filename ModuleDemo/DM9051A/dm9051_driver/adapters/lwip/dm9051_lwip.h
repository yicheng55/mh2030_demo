#ifndef DM9051_LWIP_H
#define DM9051_LWIP_H

/**
 * @file dm9051_lwip.h
 * @brief lwIP netif adapter for the DM9051A SPI Ethernet controller.
 *
 * This adapter keeps lwIP-facing code separate from the DM9051A low-level
 * driver.  Add the interface with lwIP's netif_add(), using dm9051_if_init()
 * as the init callback, then call dm9051_lwip_input() from the main loop or
 * from an interrupt-deferred RX handler.
 */

#include "lwip/err.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize one lwIP netif instance for the DM9051A.
 *
 * Expected usage:
 *   netif_add(&netif, &ip, &mask, &gw, NULL, dm9051_if_init, netif_input);
 */
err_t dm9051_if_init(struct netif *netif);

/**
 * @brief Poll/read one received Ethernet frame and submit it to lwIP.
 *
 * Call this from the main loop, an RTOS task, or a deferred interrupt handler.
 * The function returns immediately when no frame is pending.
 */
void dm9051_lwip_input(struct netif *netif);

/* Compatibility wrappers for the earlier staging API. */
int dm9051_lwip_init(struct netif *netif, const void *dev);
void dm9051_lwip_poll(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_LWIP_H */
