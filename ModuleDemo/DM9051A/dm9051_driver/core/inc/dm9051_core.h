#ifndef DM9051_CORE_H
#define DM9051_CORE_H

#include <stdint.h>

#include "dm9051_regs.h"
#include "dm9051_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Staging snapshot of the current public DM9051 core API.
 * Current source of truth:
 *   drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051.h
 *
 * This header is intentionally not included by existing targets yet. */

int dm9051_conf(void);
const uint8_t *dm9051_init(const uint8_t *adr);
uint16_t dm9051_rx(uint8_t *buf, uint16_t buf_len);
void dm9051_tx(uint8_t *buf, uint16_t len);
uint16_t cspi_phy_read(uint16_t reg);

void dm9051_interrupt_set(uint32_t exint_line);
int dm9051_interrupt_get(void);
void dm9051_interrupt_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_CORE_H */
