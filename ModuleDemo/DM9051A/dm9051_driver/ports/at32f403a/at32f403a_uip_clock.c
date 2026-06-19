#include "at32f403a_uip_clock.h"
#include "at32f403a_platform.h"

#include "clock.h"

#include <stdio.h>

static volatile uint32_t at32f403a_uip_elapsed_ms;

void at32f403a_uip_tick_init(void)
{
    if (SysTick_Config(SystemCoreClock / (1000u / AT32F403A_UIP_TICK_MS)) != 0u) {
        printf("[AT32F403A uIP] SysTick config failed\r\n");
    }
}

void at32f403a_uip_tick_isr(void)
{
    at32f403a_uip_update_time();
}

void at32f403a_uip_update_time(void)
{
    at32f403a_uip_elapsed_ms += AT32F403A_UIP_TICK_MS;
}

uint32_t at32f403a_uip_millis(void)
{
    return at32f403a_uip_elapsed_ms;
}

clock_time_t clock_time(void)
{
    return (clock_time_t)at32f403a_uip_elapsed_ms;
}
