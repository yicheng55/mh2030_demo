#include "hal_mh2030a.h"
#include "netconf_mh2030a.h"
#include "app_call.h"
#include <stdio.h>

static void mh2030a_uip_print_target_mode(void)
{
#if defined(DMPLUG_INT)
    printf("[MH2030A uIP] target mode: interrupt\r\n");
#elif defined(MH2030A_DM9051_SPI_DMA)
    printf("[MH2030A uIP] target mode: spi dma\r\n");
#else
    printf("[MH2030A uIP] target mode: polling\r\n");
#endif
}

int main(void)
{
    mh2030a_uip_board_init(115200);
    mh2030a_uip_tick_init();

    printf("[MH2030A uIP] DM9051 + uIP bring-up\r\n");
    mh2030a_uip_print_target_mode();
    mh2030a_uip_net_init();

#if WEB_EN
    httpd_init();
#endif

    while (1) {
        mh2030a_uip_net_loop();
    }
}


