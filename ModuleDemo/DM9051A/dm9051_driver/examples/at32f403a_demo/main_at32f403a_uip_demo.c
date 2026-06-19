#include "at32f403a_board.h"
#include "at32f403a_uip_clock.h"
#include "dm9051_at32f403a_smoke.h"

#include "../../adapters/uip/dm9051_uip.h"
#include "../../adapters/uip/dm9051_uip_stack.h"

#if DM9051_AT32F403A_USE_IRQ
#include "../../ports/at32f403a/dm9051_hal_at32f403a_int.h"
#endif

#include <stdio.h>

#define LINK_DETECTION                   1
#define DM9051_LINK_DETECTION_INTERVAL   500u
#define DM9051_LINK_POLL_LOOP_FALLBACK   20000u
#define DM9051_LINKUP_STATUS_PRINT_COUNT 5u
#define DM9051_STATUS_PRINT_LIMIT        50u
#define DM9051_STATUS_PRINT_STEP         10u

#if !DM9051_AT32F403A_USE_IRQ
#define dm9051_at32f403a_irq_count()     0u
#endif

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
    0x00u, 0x60u, 0x6Eu, 0x90u, 0x51u, 0x02u
};

static volatile uint32_t dm9051_demo_link_timer;

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

static int dm9051_demo_read_link_up(dm9051_device_t *dev)
{
    return dm9051_core_link_is_up(dev);
}

static int dm9051_demo_handle_link_detection(dm9051_device_t *dev,
                                             const dm9051_netif_device_t *netif,
                                             volatile uint32_t localtime)
{
    static int last_link_state = -1;
    static int first_link_check = 1;
    static uint32_t fallback_poll_count = 0u;
    static uint32_t status_timer = 0u;
    static uint32_t linkup_print_count = 0u;
    int poll_due;
    int on_linkup;
    int on_dhcp;

#if (LINK_DETECTION > 0)
    ++fallback_poll_count;
    poll_due = (first_link_check != 0) ||
               ((uint32_t)(localtime - dm9051_demo_link_timer) >=
                DM9051_LINK_DETECTION_INTERVAL) ||
               (localtime < dm9051_demo_link_timer) ||
               (fallback_poll_count >= DM9051_LINK_POLL_LOOP_FALLBACK);

    if (poll_due != 0) {
        first_link_check = 0;
        fallback_poll_count = 0u;
        dm9051_demo_link_timer = localtime;

        on_linkup = dm9051_demo_read_link_up(dev);
        if (on_linkup != last_link_state) {
            printf("[DM9051 uIP] Link: State changed from %s to %s\r\n",
                   (last_link_state == 1) ? "UP" :
                   (last_link_state == 0) ? "DOWN" : "UNKNOWN",
                   on_linkup ? "UP" : "DOWN");

            if ((last_link_state == 0) && (on_linkup == 1)) {
                status_timer = 0u;
                linkup_print_count = DM9051_LINKUP_STATUS_PRINT_COUNT;
                printf("[DM9051 uIP] Link UP detected: Will print Network Status %lu times\r\n",
                       (unsigned long)linkup_print_count);
            }

            last_link_state = on_linkup;
        }

        on_dhcp = 0;
        if (linkup_print_count > 0u) {
            printf("[DM9051 uIP] Network Status: Link=%s, DHCP=%s, IP=%u.%u.%u.%u, IRQ=%lu (LinkUp count: %lu)\r\n",
                   on_linkup ? "UP" : "DOWN",
                   on_dhcp ? "ON" : "OFF",
                   netif->static_ip[0], netif->static_ip[1],
                   netif->static_ip[2], netif->static_ip[3],
                   (unsigned long)dm9051_at32f403a_irq_count(),
                   (unsigned long)linkup_print_count);
            linkup_print_count--;
        } else if (status_timer <= DM9051_STATUS_PRINT_LIMIT) {
            if ((status_timer % DM9051_STATUS_PRINT_STEP) == 0u) {
                printf("[DM9051 uIP] Network Status: Link=%s, DHCP=%s, IP=%u.%u.%u.%u, IRQ=%lu\r\n",
                       on_linkup ? "UP" : "DOWN",
                       on_dhcp ? "ON" : "OFF",
                       netif->static_ip[0], netif->static_ip[1],
                       netif->static_ip[2], netif->static_ip[3],
                       (unsigned long)dm9051_at32f403a_irq_count());
            }
            status_timer++;
        }
    }
#endif

    return (last_link_state == 1) ? 1 : 0;
}

int main(void)
{
    dm9051_netif_device_t netif;
    const dm9051_device_t *dev;
    dm9051_device_t *mutable_dev;
    int status;

    at32f403a_uip_board_init(115200);
    at32f403a_uip_tick_init();

    printf("[DM9051 uIP] AT32F403A staged uIP demo start\r\n");

    status = dm9051_at32f403a_smoke_open(dm9051_demo_mac);
    dev = dm9051_at32f403a_smoke_device();
    printf("[DM9051 uIP] open status=%d found=%d VID=0x%04X PID=0x%04X CHIPR=0x%02X\r\n",
           status,
           dm9051_core_device_found(dev),
           dm9051_core_vendor_id(dev),
           dm9051_core_product_id(dev),
           dm9051_core_chip_revision(dev));

    mutable_dev = dm9051_at32f403a_smoke_mutable_device();

    status = dm9051_uip_attach(mutable_dev);
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
        (void)dm9051_demo_handle_link_detection(mutable_dev,
                                                &netif,
                                                at32f403a_uip_millis());
        dm9051_uip_stack_poll();
    }
}
