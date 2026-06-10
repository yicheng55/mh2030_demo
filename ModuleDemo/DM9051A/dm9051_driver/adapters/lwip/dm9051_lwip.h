#ifndef DM9051_LWIP_H
#define DM9051_LWIP_H

#include "../../core/inc/dm9051_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Staging lwIP adapter API.
 *
 * No current MH2030A lwIP implementation is wired into the reviewed targets.
 * Keep lwIP types forward-declared here so the DM9051 core never includes lwIP
 * headers directly.
 */

struct netif;

int dm9051_lwip_init(struct netif *netif, const dm9051_netif_device_t *dev);
void dm9051_lwip_poll(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_LWIP_H */
