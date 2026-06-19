#ifndef DM9051_AT32F403A_BOARD_H
#define DM9051_AT32F403A_BOARD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void at32f403a_uip_board_init(uint32_t baudrate);
void at32f403a_uip_clock_init(void);
void at32f403a_uip_tick_isr(void);

#ifdef __cplusplus
}
#endif

#endif
