/**
 * @file  hal_mh2030a.h
 * @brief MH2030A platform HAL entry-point header.
 *
 * Port files (mh2030a_dm9051_spi.c, mh2030a_dm9051_spi_dma.c,
 * mh2030a_dm9051_int.c) need only include THIS header.  It re-exports
 * dm9051_hal_api.h (HAL function declarations) and the board-level API
 * from mh2030a_board.h.
 */

#ifndef __HAL_MH2030A_PORT_H
#define __HAL_MH2030A_PORT_H

#include <stdint.h>
#ifndef USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#include "mh20xx.h"
#include "delay.h"

/* HAL function declarations (SPI bus + interrupt line). */
#include "../../../drivers/dm9051_edriver_v1.6.1a_beta/include/dm9051_hal_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MH2030A_UIP_TICK_MS      10u

/* ---- MH2030A board-level API ------------------------------------------ */
void     mh2030a_uip_board_init(uint32_t baudrate);
void     mh2030a_uip_clock_init(void);
void     mh2030a_uip_tick_init(void);
void     mh2030a_uip_tick_isr(void);
uint32_t mh2030a_uip_millis(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_MH2030A_PORT_H */
