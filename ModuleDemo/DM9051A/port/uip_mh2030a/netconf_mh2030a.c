#include "netconf_mh2030a.h"
#include "hal_mh2030a.h"
#include "uip.h"
#include "uip_arp.h"
#include "timer.h"
#include "ethernetif.h"
#include "core/dm9051.h"
#include <stdio.h>
#include <string.h>

uint32_t lwip_sys_now = 0;
uint32_t g_RunTime = 0;
volatile uint32_t all_local_time = 0;

static struct timer periodic_timer;
static struct timer arp_timer;
static int input_mode;

void uip_log(char *msg)
{
    printf("[uIP] %s\r\n", msg);
}

void resolv_found(char *name, u16_t *ipaddr)
{
    if (ipaddr == NULL) {
        printf("[uIP DNS] %s not found\r\n", name);
        return;
    }

    printf("[uIP DNS] %s resolved to %u.%u.%u.%u\r\n",
           name,
           (unsigned int)(ntohs(ipaddr[0]) >> 8),
           (unsigned int)(ntohs(ipaddr[0]) & 0xffu),
           (unsigned int)(ntohs(ipaddr[1]) >> 8),
           (unsigned int)(ntohs(ipaddr[1]) & 0xffu));
}

void time_update(void)
{
    lwip_sys_now += SYSTEMTICK_PERIOD_MS10;
    g_RunTime += SYSTEMTICK_PERIOD_MS10;
    all_local_time += SYSTEMTICK_PERIOD_MS10;
}

void mh2030a_uip_net_init(void)
{
    const uint8_t *mac;
    struct uip_eth_addr ethaddr;
    uip_ipaddr_t ipaddr;

    printf("[MH2030A uIP] network init\r\n");
    timer_set(&periodic_timer, CLOCK_SECOND / 2);
    timer_set(&arp_timer, CLOCK_SECOND * 10);

    uip_init();
    uip_arp_init();

    input_mode = dm9051_conf();
    mac = dm9051_init(NULL);
    if (mac == NULL) {
        printf("[MH2030A uIP] DM9051 init failed: no MAC\r\n");
        while (1) {
        }
    }

    memcpy(ethaddr.addr, mac, sizeof(ethaddr.addr));
    uip_setethaddr(ethaddr);

    uip_ipaddr(ipaddr, MH2030A_UIP_STATIC_IP0, MH2030A_UIP_STATIC_IP1,
               MH2030A_UIP_STATIC_IP2, MH2030A_UIP_STATIC_IP3);
    uip_sethostaddr(ipaddr);
    uip_ipaddr(ipaddr, MH2030A_UIP_GW_IP0, MH2030A_UIP_GW_IP1,
               MH2030A_UIP_GW_IP2, MH2030A_UIP_GW_IP3);
    uip_setdraddr(ipaddr);
    uip_ipaddr(ipaddr, MH2030A_UIP_MASK_IP0, MH2030A_UIP_MASK_IP1,
               MH2030A_UIP_MASK_IP2, MH2030A_UIP_MASK_IP3);
    uip_setnetmask(ipaddr);

    printf("[MH2030A uIP] mode=%s\r\n", input_mode == INPUT_MODE_POLL ? "poll" : "interrupt");
    printf("[MH2030A uIP] MAC %02X:%02X:%02X:%02X:%02X:%02X\r\n",
           uip_ethaddr.addr[0], uip_ethaddr.addr[1], uip_ethaddr.addr[2],
           uip_ethaddr.addr[3], uip_ethaddr.addr[4], uip_ethaddr.addr[5]);
    printf("[MH2030A uIP] static IP %u.%u.%u.%u\r\n",
           MH2030A_UIP_STATIC_IP0, MH2030A_UIP_STATIC_IP1,
           MH2030A_UIP_STATIC_IP2, MH2030A_UIP_STATIC_IP3);
}

static void uip_process_input(void)
{
    uip_len = ethernetif_input();
    if (uip_len == 0) {
        return;
    }

    if (((struct uip_eth_hdr *)&uip_buf[0])->type == htons(UIP_ETHTYPE_IP)) {
        uip_arp_ipin();
        uip_input();
        if (uip_len > 0) {
            uip_arp_out();
            ethernetif_output();
        }
    } else if (((struct uip_eth_hdr *)&uip_buf[0])->type == htons(UIP_ETHTYPE_ARP)) {
        uip_arp_arpin();
        if (uip_len > 0) {
            ethernetif_output();
        }
    }
}

static void uip_process_timers(void)
{
    int i;

    if (!timer_expired(&periodic_timer)) {
        return;
    }
    timer_reset(&periodic_timer);

    for (i = 0; i < UIP_CONNS; ++i) {
        uip_periodic(i);
        if (uip_len > 0) {
            uip_arp_out();
            ethernetif_output();
        }
    }

#if UIP_UDP
    for (i = 0; i < UIP_UDP_CONNS; ++i) {
        uip_udp_periodic(i);
        if (uip_len > 0) {
            uip_arp_out();
            ethernetif_output();
        }
    }
#endif

    if (timer_expired(&arp_timer)) {
        timer_reset(&arp_timer);
        uip_arp_timer();
    }
}

void mh2030a_uip_net_loop(void)
{
    if (dm9051_interrupt_get()) {
        uip_process_input();
        dm9051_interrupt_reset();
    }
    uip_process_timers();
}
