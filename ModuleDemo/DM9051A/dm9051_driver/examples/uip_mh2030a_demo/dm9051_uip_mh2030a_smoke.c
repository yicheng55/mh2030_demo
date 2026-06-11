/*
 * Staged MH2030A/uIP smoke glue.
 *
 * This file belongs to the example layer. It may bind the MH2030A port to the
 * stack-neutral DM9051 core, but it must not replace the production uIP path.
 */

#include "dm9051_uip_mh2030a_smoke.h"

#include "../../hal/inc/dm9051_hal.h"
#include "../../ports/mh2030a/dm9051_hal_mh2030a.h"

static dm9051_device_t dm9051_uip_mh2030a_smoke_dev;
static dm9051_hal_t dm9051_uip_mh2030a_smoke_hal;
static int dm9051_uip_mh2030a_smoke_status = DM9051_ERR_NOT_READY;

static int dm9051_uip_mh2030a_hal_status_to_core_status(int status)
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

int dm9051_uip_mh2030a_smoke_open(const uint8_t *mac_addr)
{
    dm9051_config_t core_config;
    dm9051_mh2030a_config_t port_config;
    int status;

    dm9051_core_default_config(&core_config);
    core_config.mac_addr = mac_addr;
    core_config.interrupt_mode = DM9051_INPUT_MODE_POLL;
    core_config.flow_control = 0u;

    dm9051_mh2030a_default_config(&port_config);
    port_config.transport = DM9051_MH2030A_TRANSPORT_POLLING;
    port_config.irq_mode = DM9051_MH2030A_IRQ_OFF;

    status = dm9051_mh2030a_hal_bind(&dm9051_uip_mh2030a_smoke_hal,
                                     &port_config);
    if (status != DM9051_HAL_OK) {
        dm9051_uip_mh2030a_smoke_status =
            dm9051_uip_mh2030a_hal_status_to_core_status(status);
        return dm9051_uip_mh2030a_smoke_status;
    }

    dm9051_uip_mh2030a_smoke_status =
        dm9051_core_open(&dm9051_uip_mh2030a_smoke_dev,
                         &core_config,
                         &dm9051_uip_mh2030a_smoke_hal);

    return dm9051_uip_mh2030a_smoke_status;
}

const dm9051_device_t *dm9051_uip_mh2030a_smoke_device(void)
{
    return &dm9051_uip_mh2030a_smoke_dev;
}

dm9051_device_t *dm9051_uip_mh2030a_smoke_mutable_device(void)
{
    return &dm9051_uip_mh2030a_smoke_dev;
}

int dm9051_uip_mh2030a_smoke_last_status(void)
{
    return dm9051_uip_mh2030a_smoke_status;
}

uint16_t dm9051_uip_mh2030a_smoke_receive(uint8_t *buf, uint16_t buf_len)
{
    if (dm9051_uip_mh2030a_smoke_status != DM9051_OK) {
        return 0u;
    }

    return dm9051_core_receive(&dm9051_uip_mh2030a_smoke_dev, buf, buf_len);
}

int dm9051_uip_mh2030a_smoke_send(const uint8_t *buf, uint16_t len)
{
    if (dm9051_uip_mh2030a_smoke_status != DM9051_OK) {
        return DM9051_ERR_NOT_READY;
    }

    return dm9051_core_send(&dm9051_uip_mh2030a_smoke_dev, buf, len);
}
