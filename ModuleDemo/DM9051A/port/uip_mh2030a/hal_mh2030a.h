#ifndef __HAL_MH2030A_H
#define __HAL_MH2030A_H

#include <stdint.h>
#ifndef USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#include "mh20xx.h"
#include "delay.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MH2030A_UIP_TICK_MS      10u

void mh2030a_uip_board_init(uint32_t baudrate);
void mh2030a_uip_clock_init(void);
void mh2030a_uip_tick_init(void);
void mh2030a_uip_tick_isr(void);
uint32_t mh2030a_uip_millis(void);

void hal_spi_initialize(void);
char *hal_spi_info(int index);
uint8_t hal_read_reg(uint8_t reg);
void hal_write_reg(uint8_t reg, uint8_t val);
void hal_read_mem(uint8_t *buf, uint16_t len);
void hal_write_mem(uint8_t *buf, uint16_t len);

uint32_t hal_int_initialize(void);
void hal_enable_mcu_irq(void);
void hal_disable_mcu_irq(void);
uint32_t hal_irqline(void);
char *hal_int_info(int index);

#ifdef __cplusplus
}
#endif

#endif
