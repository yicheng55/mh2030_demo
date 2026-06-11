#include "mh2030a_board.h"
#include "mh2030a_uip_clock.h"
#include "dm9051_uip_mh2030a_smoke.h"

#include "../../adapters/uip/dm9051_uip.h"
#include "../../adapters/uip/dm9051_uip_stack.h"

#include <stdio.h>

#define DM9051_UIP_IP0    192u
#define DM9051_UIP_IP1    168u
#define DM9051_UIP_IP2    249u
#define DM9051_UIP_IP3    37u

#define DM9051_UIP_GW0    192u
#define DM9051_UIP_GW1    168u
#define DM9051_UIP_GW2    249u
#define DM9051_UIP_GW3    1u

#define DM9051_UIP_MASK0  255u
#define DM9051_UIP_MASK1  255u
#define DM9051_UIP_MASK2  255u
#define DM9051_UIP_MASK3  0u

static const uint8_t dm9051_demo_mac[DM9051_MAC_ADDR_LENGTH] = {
    0x00u, 0x60u, 0x6Eu, 0x90u, 0x51u, 0x01u
};

static void dm9051_demo_netif_config(dm9051_netif_device_t *dev)
{
    dev->mac_addr = dm9051_demo_mac;

    dev->static_ip[0] = DM9051_UIP_IP0;
    dev->static_ip[1] = DM9051_UIP_IP1;
    dev->static_ip[2] = DM9051_UIP_IP2;
    dev->static_ip[3] = DM9051_UIP_IP3;

    dev->gateway_ip[0] = DM9051_UIP_GW0;
    dev->gateway_ip[1] = DM9051_UIP_GW1;
    dev->gateway_ip[2] = DM9051_UIP_GW2;
    dev->gateway_ip[3] = DM9051_UIP_GW3;

    dev->netmask_ip[0] = DM9051_UIP_MASK0;
    dev->netmask_ip[1] = DM9051_UIP_MASK1;
    dev->netmask_ip[2] = DM9051_UIP_MASK2;
    dev->netmask_ip[3] = DM9051_UIP_MASK3;
}

int main(void)
{
    dm9051_netif_device_t netif;
    const dm9051_device_t *dev;
    int status;

    mh2030a_uip_board_init(115200);
    mh2030a_uip_tick_init();

    printf("[DM9051 uIP] MH2030A staged uIP demo start\r\n");

    status = dm9051_uip_mh2030a_smoke_open(dm9051_demo_mac);
    dev = dm9051_uip_mh2030a_smoke_device();
    printf("[DM9051 uIP] open status=%d found=%d VID=0x%04X PID=0x%04X CHIPR=0x%02X\r\n",
           status,
           dm9051_core_device_found(dev),
           dm9051_core_vendor_id(dev),
           dm9051_core_product_id(dev),
           dm9051_core_chip_revision(dev));

    status = dm9051_uip_attach(dm9051_uip_mh2030a_smoke_mutable_device());
    printf("[DM9051 uIP] attach status=%d\r\n", status);
    if (status != DM9051_OK) {
        while (1) {
        }
    }

    dm9051_demo_netif_config(&netif);
    status = dm9051_uip_stack_init(&netif);
    printf("[DM9051 uIP] stack status=%d\r\n", status);
    if (status != DM9051_OK) {
        while (1) {
        }
    }

    while (1) {
        dm9051_uip_stack_poll();
    }
}
