#ifndef __HAL_MH2030A_H
#define __HAL_MH2030A_H

#include <stdint.h>
#ifndef USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#include "mh20xx.h"
#include "delay.h"

/* HAL function declarations (SPI bus + interrupt line) are now centralised
 * in dm9051_hal_api.h.  Include it here so platform implementation files
 * only need to include hal_mh2030a.h without also listing the drivers path. */
#include "include/dm9051_hal_api.h"

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

/* NOTE: hal_spi_initialize, hal_read_reg, hal_write_reg, hal_read_mem,
 *       hal_write_mem, hal_int_initialize, hal_enable_mcu_irq,
 *       hal_disable_mcu_irq, hal_irqline, hal_int_info are declared in
 *       include/dm9051_hal_api.h (included above).  Do NOT redeclare them
 *       here to avoid duplicate-declaration warnings. */

#ifdef __cplusplus
}
#endif

#endif /* __HAL_MH2030A_H */
