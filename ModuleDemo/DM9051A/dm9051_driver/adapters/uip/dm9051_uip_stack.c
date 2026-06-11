/*
 * Optional uIP loop for the staged DM9051 adapter.
 *
 * This file is intentionally separate from dm9051_uip.c so the hardware smoke
 * target can keep building without pulling in uIP core objects.
 */

#include "dm9051_uip_stack.h"

#include "uip.h"
#include "uip_arp.h"
#include "timer.h"

#include <stdio.h>
#include <string.h>

#define DM9051_UIP_RX_BURST_MAX 8u

static struct timer dm9051_uip_periodic_timer;
static struct timer dm9051_uip_arp_timer;

static void dm9051_uip_stack_send_if_needed(void)
{
    if (uip_len > 0u) {
        uip_arp_out();
        (void)dm9051_uip_output(uip_buf, uip_len);
    }
}

int dm9051_uip_stack_init(const dm9051_netif_device_t *dev)
{
    struct uip_eth_addr ethaddr;
    uip_ipaddr_t ipaddr;
    int status;

    if (!dm9051_netif_device_is_valid(dev) || (dev->mac_addr == 0)) {
        return DM9051_ERR_PARAM;
    }

    status = dm9051_uip_init(dev);
    if (status != DM9051_OK) {
        return status;
    }

    uip_init();
    uip_arp_init();

    (void)memcpy(ethaddr.addr, dev->mac_addr, sizeof(ethaddr.addr));
    uip_setethaddr(ethaddr);

    uip_ipaddr(ipaddr,
               dev->static_ip[0], dev->static_ip[1],
               dev->static_ip[2], dev->static_ip[3]);
    uip_sethostaddr(ipaddr);

    uip_ipaddr(ipaddr,
               dev->gateway_ip[0], dev->gateway_ip[1],
               dev->gateway_ip[2], dev->gateway_ip[3]);
    uip_setdraddr(ipaddr);

    uip_ipaddr(ipaddr,
               dev->netmask_ip[0], dev->netmask_ip[1],
               dev->netmask_ip[2], dev->netmask_ip[3]);
    uip_setnetmask(ipaddr);

    timer_set(&dm9051_uip_periodic_timer, CLOCK_SECOND / 2);
    timer_set(&dm9051_uip_arp_timer, CLOCK_SECOND * 10);
    printf("[DM9051 uIP] stack init mode=%s\r\n", dm9051_uip_target_mode());
    printf("[DM9051 uIP] MAC %02X:%02X:%02X:%02X:%02X:%02X\r\n",
           ethaddr.addr[0], ethaddr.addr[1], ethaddr.addr[2],
           ethaddr.addr[3], ethaddr.addr[4], ethaddr.addr[5]);
    printf("[DM9051 uIP] IP  %u.%u.%u.%u\r\n",
           dev->static_ip[0], dev->static_ip[1],
           dev->static_ip[2], dev->static_ip[3]);

    return DM9051_OK;
}

void dm9051_uip_stack_poll(void)
{
    int i;
    uint8_t rx_burst;

    rx_burst = 0u;

    while (rx_burst < DM9051_UIP_RX_BURST_MAX) {
        uip_len = dm9051_uip_input(uip_buf, UIP_BUFSIZE);
        if (uip_len == 0u) {
            break;
        }

        if (((struct uip_eth_hdr *)&uip_buf[0])->type == htons(UIP_ETHTYPE_IP)) {
            uip_arp_ipin();
            uip_input();
            dm9051_uip_stack_send_if_needed();
        } else if (((struct uip_eth_hdr *)&uip_buf[0])->type == htons(UIP_ETHTYPE_ARP)) {
            uip_arp_arpin();
            if (uip_len > 0u) {
                (void)dm9051_uip_output(uip_buf, uip_len);
            }
        }

        ++rx_burst;
    }

    if (timer_expired(&dm9051_uip_periodic_timer)) {
        timer_reset(&dm9051_uip_periodic_timer);

        for (i = 0; i < UIP_CONNS; ++i) {
            uip_periodic(i);
            dm9051_uip_stack_send_if_needed();
        }

#if UIP_UDP
        for (i = 0; i < UIP_UDP_CONNS; ++i) {
            uip_udp_periodic(i);
            dm9051_uip_stack_send_if_needed();
        }
#endif
    }

    if (timer_expired(&dm9051_uip_arp_timer)) {
        timer_reset(&dm9051_uip_arp_timer);
        uip_arp_timer();
    }
}
