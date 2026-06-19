#include "dm9051_at32f403a_smoke.h"

#include "../../hal/inc/dm9051_hal.h"
#include "../../ports/at32f403a/dm9051_hal_at32f403a_spi1.h"
#if DM9051_AT32F403A_USE_IRQ
#include "../../ports/at32f403a/dm9051_hal_at32f403a_int.h"
#endif

static dm9051_device_t dm9051_at32f403a_smoke_dev;
static dm9051_hal_t dm9051_at32f403a_smoke_hal;
static int dm9051_at32f403a_smoke_status = DM9051_ERR_NOT_READY;

static int dm9051_at32f403a_hal_status_to_core_status(int status)
{
    if (status == DM9051_HAL_OK) {
        return DM9051_OK;
    }

    if (status == DM9051_HAL_ERR_TIMEOUT) {
        return DM9051_ERR_TIMEOUT;
    }

    if (status == DM9051_HAL_ERR_PARAM) {
        return DM9051_ERR_PARAM;
    }

    return DM9051_ERR_NOT_READY;
}

int dm9051_at32f403a_smoke_open(const uint8_t *mac_addr)
{
    dm9051_config_t core_config;
    dm9051_at32f403a_config_t port_config;
    int status;

    dm9051_core_default_config(&core_config);
    core_config.mac_addr = mac_addr;
#if DM9051_AT32F403A_USE_IRQ
    core_config.interrupt_mode = DM9051_INPUT_MODE_INTERRUPT;
#else
    core_config.interrupt_mode = DM9051_INPUT_MODE_POLL;
#endif
    core_config.flow_control = 0u;

    dm9051_at32f403a_default_config(&port_config);
#if DM9051_AT32F403A_USE_DMA
    port_config.transport = DM9051_AT32F403A_TRANSPORT_DMA;
#else
    port_config.transport = DM9051_AT32F403A_TRANSPORT_POLLING;
#endif
#if DM9051_AT32F403A_USE_IRQ
    port_config.irq_mode = DM9051_AT32F403A_IRQ_EXTI;
#else
    port_config.irq_mode = DM9051_AT32F403A_IRQ_OFF;
#endif

    status = dm9051_at32f403a_hal_bind(&dm9051_at32f403a_smoke_hal,
                                       &port_config);
    if (status != DM9051_HAL_OK) {
        dm9051_at32f403a_smoke_status =
            dm9051_at32f403a_hal_status_to_core_status(status);
        return dm9051_at32f403a_smoke_status;
    }

#if DM9051_AT32F403A_USE_IRQ
    dm9051_at32f403a_irq_attach_device(&dm9051_at32f403a_smoke_dev);
#endif

    dm9051_at32f403a_smoke_status =
        dm9051_core_open(&dm9051_at32f403a_smoke_dev,
                         &core_config,
                         &dm9051_at32f403a_smoke_hal);
#if DM9051_AT32F403A_USE_IRQ
    if (dm9051_at32f403a_smoke_status != DM9051_OK) {
        dm9051_at32f403a_irq_detach_device();
    }
#endif

    return dm9051_at32f403a_smoke_status;
}

const dm9051_device_t *dm9051_at32f403a_smoke_device(void)
{
    return &dm9051_at32f403a_smoke_dev;
}

dm9051_device_t *dm9051_at32f403a_smoke_mutable_device(void)
{
    return &dm9051_at32f403a_smoke_dev;
}

int dm9051_at32f403a_smoke_last_status(void)
{
    return dm9051_at32f403a_smoke_status;
}

uint16_t dm9051_at32f403a_smoke_receive(uint8_t *buf, uint16_t buf_len)
{
    if (dm9051_at32f403a_smoke_status != DM9051_OK) {
        return 0u;
    }

    return dm9051_core_receive(&dm9051_at32f403a_smoke_dev, buf, buf_len);
}

int dm9051_at32f403a_smoke_send(const uint8_t *buf, uint16_t len)
{
    if (dm9051_at32f403a_smoke_status != DM9051_OK) {
        return DM9051_ERR_NOT_READY;
    }

    return dm9051_core_send(&dm9051_at32f403a_smoke_dev, buf, len);
}
