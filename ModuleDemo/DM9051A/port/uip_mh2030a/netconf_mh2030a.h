#ifndef __MH2030A_UIP_CONF_H
#define __MH2030A_UIP_CONF_H

#include "developer_conf.h"

#define MH2030A_UIP_STATIC_IP0    192
#define MH2030A_UIP_STATIC_IP1    168
#define MH2030A_UIP_STATIC_IP2    249
#define MH2030A_UIP_STATIC_IP3    37

#define MH2030A_UIP_GW_IP0        192
#define MH2030A_UIP_GW_IP1        168
#define MH2030A_UIP_GW_IP2        249
#define MH2030A_UIP_GW_IP3        1

#define MH2030A_UIP_MASK_IP0      255
#define MH2030A_UIP_MASK_IP1      255
#define MH2030A_UIP_MASK_IP2      255
#define MH2030A_UIP_MASK_IP3      0

void mh2030a_uip_net_init(void);
void mh2030a_uip_net_loop(void);
void mh2030a_uip_update_time(void);

#endif
