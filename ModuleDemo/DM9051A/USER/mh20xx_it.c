#include "mh20xx_it.h"
#include "hal_mh2030a.h"

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
    while (1) {
    }
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
    mh2030a_uip_tick_isr();
}
