/*
 * Future lwIP adapter implementation.
 *
 * This file is intentionally empty until the core/HAL boundary is stable and a
 * concrete lwIP demo target exists.
 */

#include "dm9051_lwip.h"

#include "../../core/inc/dm9051_core.h"

int dm9051_lwip_init(struct netif *netif, const dm9051_netif_device_t *dev)
{
    if ((netif == 0) || !dm9051_netif_device_is_valid(dev)) {
        return DM9051_ERR_PARAM;
    }

    return DM9051_ERR_NOT_READY;
}

void dm9051_lwip_poll(struct netif *netif)
{
    (void)netif;
}
