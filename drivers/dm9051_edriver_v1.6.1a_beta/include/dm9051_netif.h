/**
 * @file  dm9051_netif.h
 * @brief DM9051 network-stack adapter interface.
 *
 * This header defines the boundary between the DM9051 core driver and any
 * network stack adapter (uIP, lwIP, bare-metal poll loop, etc.).
 *
 * Adapters MUST:
 *   - Call only dm9051_netif_* functions (or dm9051_init / dm9051_rx /
 *     dm9051_tx from dm9051.h) to interact with the DM9051 core driver.
 *   - NOT include hal_mh2030a.h or any platform-specific header directly.
 *   - NOT call hal_read_reg / hal_write_reg / hal_spi_initialize directly.
 *
 * uIP adapter implementation : ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.c
 * lwIP adapter (future)       : ModuleDemo/DM9051A/port/lwip/dm9051_lwip_adapter.c
 */

#ifndef __DM9051_NETIF_H
#define __DM9051_NETIF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Device handle
 * Passed to every dm9051_netif_* function so that future multi-instance
 * support can be added without API changes.
 * ---------------------------------------------------------------------- */
typedef struct dm9051_netif_device {
    const uint8_t *mac_addr;        /**< NULL = use chip/random MAC         */
    uint8_t        static_ip[4];    /**< Static IP address                  */
    uint8_t        gateway_ip[4];   /**< Default gateway                    */
    uint8_t        netmask_ip[4];   /**< Subnet mask                        */
} dm9051_netif_device_t;

/* -------------------------------------------------------------------------
 * Lifecycle
 * ---------------------------------------------------------------------- */

/**
 * @brief  Initialise DM9051 and configure network parameters.
 * @param  dev  Pointer to device config.  Must remain valid for the lifetime
 *              of the driver session.
 * @return 0 on success, negative on error.
 */
int dm9051_netif_open(const dm9051_netif_device_t *dev);

/* -------------------------------------------------------------------------
 * Data path
 * ---------------------------------------------------------------------- */

/**
 * @brief  Receive one Ethernet frame from DM9051 RX FIFO.
 * @param  buf      Destination buffer.
 * @param  buf_len  Maximum number of bytes to receive.
 * @return Frame length in bytes, or 0 if no frame is available.
 */
uint16_t dm9051_netif_input(uint8_t *buf, uint16_t buf_len);

/**
 * @brief  Transmit one Ethernet frame via DM9051.
 * @param  buf  Frame data.
 * @param  len  Frame length in bytes.
 * @return 0 on success, negative on error.
 */
int dm9051_netif_output(const uint8_t *buf, uint16_t len);

/* -------------------------------------------------------------------------
 * Status / control
 * ---------------------------------------------------------------------- */

/**
 * @brief  Return the current build-time target mode string.
 *         Identical to mh2030a_uip_target_mode() but exposed here so any
 *         adapter can report the mode without coupling to the MH2030A port.
 * @return "polling", "spi dma", or "interrupt" (static string, do not free).
 */
const char *dm9051_netif_target_mode(void);

#ifdef __cplusplus
}
#endif

#endif /* __DM9051_NETIF_H */
