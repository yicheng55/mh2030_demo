#ifndef AT32F403A_LWIP_CLOCK_H
#define AT32F403A_LWIP_CLOCK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void at32f403a_lwip_tick_init(void);
void at32f403a_lwip_tick_isr(void);

#ifdef __cplusplus
}
#endif

#endif
