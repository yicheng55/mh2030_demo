#include "hal_mh2030a.h"
#include "netconf_mh2030a.h"
#include "app_call.h"
#include "core/dm9051.h"
#include <stdio.h>

int main(void)
{
    uint16_t vid;
    uint16_t pid;

    mh2030a_uip_board_init(115200);
    mh2030a_uip_tick_init();

    printf("[MH2030A uIP] DM9051 + uIP polling bring-up\r\n");
    hal_spi_initialize();

    vid = (uint16_t)hal_read_reg(DM9051_VIDL) | ((uint16_t)hal_read_reg(DM9051_VIDH) << 8);
    pid = (uint16_t)hal_read_reg(DM9051_PIDL) | ((uint16_t)hal_read_reg(DM9051_PIDH) << 8);
    printf("[MH2030A uIP] DM9051 VID=0x%04X PID=0x%04X CHIPR=0x%02X\r\n",
           vid, pid, hal_read_reg(DM9051_CHIPR));

    mh2030a_uip_net_init();

#if WEB_EN
    httpd_init();
#endif

    while (1) {
        mh2030a_uip_net_loop();
    }
}


