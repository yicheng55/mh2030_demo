#ifndef DM9051_UIP_MH2030A_SMOKE_H
#define DM9051_UIP_MH2030A_SMOKE_H

#include "../../core/inc/dm9051_core.h"

#ifdef __cplusplus
extern "C" {
#endif

int dm9051_uip_mh2030a_smoke_open(const uint8_t *mac_addr);
const dm9051_device_t *dm9051_uip_mh2030a_smoke_device(void);
int dm9051_uip_mh2030a_smoke_last_status(void);
uint16_t dm9051_uip_mh2030a_smoke_receive(uint8_t *buf, uint16_t buf_len);
int dm9051_uip_mh2030a_smoke_send(const uint8_t *buf, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_UIP_MH2030A_SMOKE_H */
