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

int dm9051_uip_init(const dm9051_netif_device_t *dev)
{
    if (!dm9051_netif_device_is_valid(dev)) {
        return DM9051_ERR_PARAM;
    }

    return DM9051_ERR_NOT_READY;
}

void dm9051_uip_poll(void)
{
}

const char *dm9051_uip_target_mode(void)
{
    return "staging";
}
