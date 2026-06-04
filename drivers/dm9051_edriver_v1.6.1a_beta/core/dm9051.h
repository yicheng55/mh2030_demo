/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __DM9051_H
#define __DM9051_H

#include "../hal/dm9051_hal_mh2030a.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PHY_STATUS_REG            (0x01)           /*!< basic mode status register */
#define DM9051_VIDL               (0x28)
#define DM9051_VIDH               (0x29)
#define DM9051_PIDL               (0x2A)
#define DM9051_PIDH               (0x2B)
#define DM9051_CHIPR              (0x2C)
#define DM9051_MRCMD              (0x72)
#define DM9051_MWCMD              (0x78)
#define OPC_REG_W                 0x80             // Register Write
#define OPC_REG_R                 0x00             // Register Read

#define INPUT_MODE_POLL 0
#define INPUT_MODE_INTERRUPT 1
#define INPUT_MODE_INTERRUPT_CLKOUT 2

int dm9051_conf(void);
const uint8_t *dm9051_init(const uint8_t *adr);
uint16_t dm9051_rx(uint8_t *buf, uint16_t buf_len);
void dm9051_tx(uint8_t *buf, uint16_t len);
uint16_t cspi_phy_read(uint16_t uReg);

void dm9051_interrupt_set(uint32_t exint_line);
int dm9051_interrupt_get(void);
void dm9051_interrupt_reset(void);

#define HAL_IRQLine			hal_irqline
uint32_t hal_irqline(void);

#define MAC_ADDR_LENGTH         (6)
typedef uint8_t mac_t[MAC_ADDR_LENGTH];

#ifdef __cplusplus
}
#endif

#endif //__DM9051_H
