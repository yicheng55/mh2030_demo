#include "hal_mh2030a.h"
#include "dm9051_uip_mh2030a_smoke.h"

#include <stdio.h>

static const uint8_t dm9051_smoke_mac[DM9051_MAC_ADDR_LENGTH] = {
    0x00u, 0x60u, 0x6Eu, 0x90u, 0x51u, 0x01u
};

void mh2030a_uip_tick_isr(void)
{
}

int main(void)
{
    const dm9051_device_t *dev;
    int status;

    mh2030a_uip_board_init(115200);

    printf("[DM9051 staging] MH2030A polling smoke start\r\n");

    status = dm9051_uip_mh2030a_smoke_open(dm9051_smoke_mac);
    dev = dm9051_uip_mh2030a_smoke_device();

    printf("[DM9051 staging] open status=%d found=%d VID=0x%04X PID=0x%04X CHIPR=0x%02X\r\n",
           status,
           dm9051_core_device_found(dev),
           dm9051_core_vendor_id(dev),
           dm9051_core_product_id(dev),
           dm9051_core_chip_revision(dev));

    while (1) {
    }
}
