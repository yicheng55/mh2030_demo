#ifndef DM9051_AT32F403A_UIP_CLOCK_H
#define DM9051_AT32F403A_UIP_CLOCK_H

#include <stdint.h>

#ifndef AT32F403A_UIP_TICK_MS
#define AT32F403A_UIP_TICK_MS 10u
#endif

#ifdef __cplusplus
extern "C" {
#endif

void at32f403a_uip_tick_init(void);
void at32f403a_uip_update_time(void);
uint32_t at32f403a_uip_millis(void);

#ifdef __cplusplus
}
#endif

#endif
