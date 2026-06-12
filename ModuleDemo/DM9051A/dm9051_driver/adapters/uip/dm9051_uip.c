/*
 * Future uIP adapter implementation.
 *
 * Current source of truth:
 *   ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.c
 *
 * This staging file remains intentionally empty until the production adapter is
 * copied behind compatibility-preserving wrappers.
 */

#include "dm9051_uip.h"

#include "../../core/inc/dm9051_core.h"

static dm9051_device_t *dm9051_uip_attached_dev;

int dm9051_uip_init(const dm9051_netif_device_t *dev)
{
    if (!dm9051_netif_device_is_valid(dev)) {
        return DM9051_ERR_PARAM;
    }

    if (dm9051_uip_attached_dev == 0) {
        return DM9051_ERR_NOT_READY;
    }

    return DM9051_OK;
}

int dm9051_uip_attach(dm9051_device_t *dev)
{
    if ((dev == 0) || !dm9051_core_device_found(dev)) {
        return DM9051_ERR_PARAM;
    }

    dm9051_uip_attached_dev = dev;
    return DM9051_OK;
}

uint16_t dm9051_uip_input(uint8_t *buf, uint16_t buf_len)
{
    if (dm9051_uip_attached_dev == 0) {
        return 0u;
    }

    return dm9051_core_receive(dm9051_uip_attached_dev, buf, buf_len);
}

int dm9051_uip_output(const uint8_t *buf, uint16_t len)
{
    if (dm9051_uip_attached_dev == 0) {
        return DM9051_ERR_NOT_READY;
    }

    return dm9051_core_send(dm9051_uip_attached_dev, buf, len);
}

int dm9051_uip_interrupt_mode(void)
{
    if (dm9051_uip_attached_dev == 0) {
        return DM9051_INPUT_MODE_POLL;
    }

    return dm9051_uip_attached_dev->runtime.config.interrupt_mode;
}

int dm9051_uip_interrupt_take(void)
{
    if (dm9051_uip_attached_dev == 0) {
        return 0;
    }

    if (dm9051_uip_attached_dev->runtime.config.interrupt_mode == DM9051_INPUT_MODE_POLL) {
        return 1;
    }

    return dm9051_core_interrupt_take(dm9051_uip_attached_dev);
}

void dm9051_uip_interrupt_reset(void)
{
    if (dm9051_uip_attached_dev == 0) {
        return;
    }

    dm9051_core_interrupt_reset(dm9051_uip_attached_dev);
}

void dm9051_uip_poll(void)
{
}

const char *dm9051_uip_target_mode(void)
{
    return "staging";
}
