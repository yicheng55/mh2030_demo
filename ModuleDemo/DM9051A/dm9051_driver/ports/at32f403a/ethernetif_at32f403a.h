#ifndef ETHERNETIF_AT32F403A_H
#define ETHERNETIF_AT32F403A_H

#include <stdint.h>

#include "lwip/err.h"
#include "lwip/netif.h"

#include "../../core/inc/dm9051_types.h"
#include "../../hal/inc/dm9051_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ethernetif_at32f403a {
    dm9051_device_t dev;
    dm9051_hal_t    hal;
    uint8_t         rx_buf[1514];
    uint8_t         tx_buf[1514];
};

err_t ethernetif_at32f403a_init(struct netif *netif);
err_t ethernetif_at32f403a_input(struct netif *netif);
void ethernetif_at32f403a_update_config(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif
