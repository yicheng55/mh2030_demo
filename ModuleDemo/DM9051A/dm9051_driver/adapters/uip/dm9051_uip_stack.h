#ifndef DM9051_UIP_STACK_H
#define DM9051_UIP_STACK_H

#include "dm9051_uip.h"

#ifdef __cplusplus
extern "C" {
#endif

int dm9051_uip_stack_init(const dm9051_netif_device_t *dev);
void dm9051_uip_stack_poll(void);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_UIP_STACK_H */
