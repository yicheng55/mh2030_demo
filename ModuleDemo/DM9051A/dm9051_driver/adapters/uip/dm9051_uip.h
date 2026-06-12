#ifndef DM9051_UIP_H
#define DM9051_UIP_H

#include "../../core/inc/dm9051_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Staging uIP adapter API.
 *
 * Current source of truth:
 *   ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.h
 *
 * This header is intentionally stack-facing, not platform-facing. It must not
 * include MH2030A SPI/GPIO/IRQ headers.
 */

int dm9051_uip_init(const dm9051_netif_device_t *dev);
int dm9051_uip_attach(dm9051_device_t *dev);
uint16_t dm9051_uip_input(uint8_t *buf, uint16_t buf_len);
int dm9051_uip_output(const uint8_t *buf, uint16_t len);
int dm9051_uip_interrupt_mode(void);
int dm9051_uip_interrupt_take(void);
void dm9051_uip_interrupt_reset(void);
void dm9051_uip_poll(void);
const char *dm9051_uip_target_mode(void);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_UIP_H */
