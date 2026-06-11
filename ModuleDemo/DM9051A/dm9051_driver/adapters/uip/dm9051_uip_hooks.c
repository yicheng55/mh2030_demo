#include "uip.h"

#include <stdio.h>

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
