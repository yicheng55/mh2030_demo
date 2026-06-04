#include "hal_mh2030a.h"
#include "clock-arch.h"
#include "developer_conf.h"
#include <stdio.h>

extern void time_update(void);
extern uint32_t lwip_sys_now;
extern uint32_t g_RunTime;

void mh2030a_uip_tick_init(void)
{
    if (SysTick_Config(SystemCoreClock / (1000u / MH2030A_UIP_TICK_MS)) != 0u) {
        printf("[MH2030A uIP] SysTick config failed\r\n");
    }
}

void mh2030a_uip_tick_isr(void)
{
    time_update();
}

uint32_t mh2030a_uip_millis(void)
{
    return lwip_sys_now;
}

clock_time_t clock_time(void)
{
    return (clock_time_t)lwip_sys_now;
}


