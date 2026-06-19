#include "at32f403a_lwip_clock.h"
#include "at32f403a_platform.h"

#include <stdio.h>

extern u32_t lwip_sys_now;

void at32f403a_lwip_tick_init(void)
{
    if (SysTick_Config(SystemCoreClock / 1000u) != 0u) {
        printf("[AT32F403A lwIP] SysTick 1ms config failed\r\n");
        while (1);
    }
}

void at32f403a_lwip_tick_isr(void)
{
    ++lwip_sys_now;
}
