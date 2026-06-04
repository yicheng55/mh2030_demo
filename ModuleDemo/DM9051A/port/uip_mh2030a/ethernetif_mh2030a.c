#include "uip.h"
#include "uip_arp.h"
#include "developer_conf.h"
#include "ethernetif.h"
#include "core/dm9051.h"

#define EthBuff_rx (&uip_buf[0])
#define EthBuff_tx (&uip_buf[0])

uint16_t ethernetif_input(void)
{
    return dm9051_rx(EthBuff_rx, UIP_BUFSIZE);
}

err_t ethernetif_output(void)
{
    dm9051_tx(EthBuff_tx, uip_len);
    return ERR_OK;
}
