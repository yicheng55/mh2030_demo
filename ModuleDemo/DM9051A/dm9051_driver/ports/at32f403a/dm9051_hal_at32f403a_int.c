#include "dm9051_hal_at32f403a_int.h"
#include "dm9051_hal_at32f403a_spi1_priv.h"

#include "../../core/inc/dm9051_core.h"

#if DM9051_AT32F403A_ENABLE_IRQ

static volatile dm9051_device_t *dm9051_at32f403a_irq_device;
static volatile uint32_t dm9051_at32f403a_irq_event_count;

void dm9051_at32f403a_irq_init_if_enabled(const dm9051_at32f403a_config_t *config)
{
    gpio_init_type gpio;
    exint_init_type exti;

    if ((config == 0) || (config->irq_mode != DM9051_AT32F403A_IRQ_EXTI)) {
        return;
    }

    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio);
    gpio.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio.gpio_mode = GPIO_MODE_INPUT;
    gpio.gpio_pull = GPIO_PULL_UP;
    gpio.gpio_pins = DM9051_AT32F403A_INT_PIN;
    gpio_init(DM9051_AT32F403A_INT_PORT, &gpio);

    gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOC, GPIO_PINS_SOURCE7);

    exint_default_para_init(&exti);
    exti.line_enable = TRUE;
    exti.line_mode = EXINT_LINE_INTERRUPUT;
    exti.line_select = DM9051_AT32F403A_INT_LINE;
    exti.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
    exint_init(&exti);
    exint_flag_clear(DM9051_AT32F403A_INT_LINE);

    printf("[AT32F403A] DM9051 interrupt initialized (INT PC7, EXTI line 7, falling edge)\r\n");
}

void dm9051_at32f403a_irq_enable_if_enabled(void *ctx)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;

    if ((config == 0) || (config->irq_mode != DM9051_AT32F403A_IRQ_EXTI)) {
        return;
    }

    exint_flag_clear(DM9051_AT32F403A_INT_LINE);
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    nvic_irq_enable(DM9051_AT32F403A_INT_IRQn, 1, 0);
}

void dm9051_at32f403a_irq_disable_if_enabled(void *ctx)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;

    if ((config == 0) || (config->irq_mode != DM9051_AT32F403A_IRQ_EXTI)) {
        return;
    }

    nvic_irq_disable(DM9051_AT32F403A_INT_IRQn);
    exint_flag_clear(DM9051_AT32F403A_INT_LINE);
}

void dm9051_at32f403a_irq_attach_device(dm9051_device_t *dev)
{
    dm9051_at32f403a_irq_device = dev;
}

void dm9051_at32f403a_irq_detach_device(void)
{
    dm9051_at32f403a_irq_device = 0;
}

uint32_t dm9051_at32f403a_irq_line(void)
{
    return DM9051_AT32F403A_INT_LINE;
}

uint32_t dm9051_at32f403a_irq_count(void)
{
    return dm9051_at32f403a_irq_event_count;
}

void dm9051_at32f403a_irq_handler(void)
{
    dm9051_device_t *dev;

    if (exint_flag_get(DM9051_AT32F403A_INT_LINE) == RESET) {
        return;
    }

    ++dm9051_at32f403a_irq_event_count;

    dev = (dm9051_device_t *)dm9051_at32f403a_irq_device;
    if (dev != 0) {
        dm9051_core_interrupt_set(dev, DM9051_AT32F403A_INT_LINE);
    }

    exint_flag_clear(DM9051_AT32F403A_INT_LINE);
}

#if DM9051_AT32F403A_OWN_EXTI9_5_HANDLER
void EXINT9_5_IRQHandler(void)
{
    dm9051_at32f403a_irq_handler();
}
#endif

#endif /* DM9051_AT32F403A_ENABLE_IRQ */
