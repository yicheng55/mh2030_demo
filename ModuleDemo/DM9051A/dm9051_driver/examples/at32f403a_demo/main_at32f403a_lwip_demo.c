#include "at32f403a_board.h"
#include "at32f403a_lwip_clock.h"
#include "ethernetif_at32f403a.h"

#include "lwip/init.h"
#include "lwip/ip4_addr.h"
#include "lwip/netif.h"
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"
#include "netif/ethernet.h"

#include "lwip_web2403v2_freelw.h"

#include <stdio.h>
#include <string.h>

static struct netif g_dm9051_netif;

#define DM9051_LINK_POLL_INTERVAL_MS 500U

void SysTick_Handler(void)
{
    at32f403a_lwip_tick_isr();
}

static void dm9051_lwip_link_poll_wrapper(struct netif *netif)
{
    static u32_t last_link_poll_ms;
    u32_t now_ms;

    if (netif == NULL) {
        return;
    }

    now_ms = sys_now();
    if ((u32_t)(now_ms - last_link_poll_ms) < DM9051_LINK_POLL_INTERVAL_MS) {
        return;
    }
    last_link_poll_ms = now_ms;

    ethernetif_at32f403a_update_config(netif);
}

static void platform_init(void)
{
    at32f403a_uip_board_init(115200U);
    at32f403a_lwip_tick_init();
}

static void network_init(void)
{
    ip4_addr_t ipaddr;
    ip4_addr_t netmask;
    ip4_addr_t gateway;
    struct netif *added_netif;
    err_t err;

    static const uint8_t mac_addr[6] = {
        0x00U, 0x60U, 0x6EU, 0x90U, 0x51U, 0x02U
    };

    IP4_ADDR(&ipaddr, 192, 168, 249, 37);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
    IP4_ADDR(&gateway, 192, 168, 249, 1);

    lwip_init();

    memset(&g_dm9051_netif, 0, sizeof(g_dm9051_netif));
    memcpy(g_dm9051_netif.hwaddr, mac_addr, sizeof(mac_addr));

    added_netif = netif_add(&g_dm9051_netif,
                            &ipaddr,
                            &netmask,
                            &gateway,
                            NULL,
                            ethernetif_at32f403a_init,
                            ethernet_input);
    if (added_netif == NULL) {
        printf("[DM9051 lwIP] netif_add failed\r\n");
        while (1);
    }

    netif_set_link_callback(&g_dm9051_netif, ethernetif_at32f403a_update_config);
    netif_set_default(&g_dm9051_netif);
    dm9051_lwip_link_poll_wrapper(&g_dm9051_netif);
    netif_set_up(&g_dm9051_netif);

    printf("[DM9051 lwIP] netif up IP=%u.%u.%u.%u mask=%u.%u.%u.%u gw=%u.%u.%u.%u\r\n",
           ip4_addr1(&ipaddr),
           ip4_addr2(&ipaddr),
           ip4_addr3(&ipaddr),
           ip4_addr4(&ipaddr),
           ip4_addr1(&netmask),
           ip4_addr2(&netmask),
           ip4_addr3(&netmask),
           ip4_addr4(&netmask),
           ip4_addr1(&gateway),
           ip4_addr2(&gateway),
           ip4_addr3(&gateway),
           ip4_addr4(&gateway));

    err = lwip_web2403v2_freelw_init(&g_dm9051_netif);
    if (err != ERR_OK) {
        printf("[DM9051 lwIP] HTTP server init failed (%d)\r\n", err);
        while (1);
    }
}

int main(void)
{
    platform_init();
    network_init();

    while (1) {
        dm9051_lwip_link_poll_wrapper(&g_dm9051_netif);
        ethernetif_at32f403a_input(&g_dm9051_netif);
#if LWIP_TIMERS
        sys_check_timeouts();
#endif
        lwip_web2403v2_freelw_poll();
    }
}
