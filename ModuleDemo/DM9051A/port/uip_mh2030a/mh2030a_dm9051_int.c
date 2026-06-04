#include "hal_mh2030a.h"

static char *int_info[] = {
    "MH2030A DM9051 interrupt disabled",
    "polling mode bring-up",
};

char *hal_int_info(int index)
{
    return int_info[index & 1];
}

uint32_t hal_int_initialize(void)
{
    return 0u;
}

void hal_enable_mcu_irq(void)
{
}

void hal_disable_mcu_irq(void)
{
}

uint32_t hal_irqline(void)
{
    return 0u;
}
