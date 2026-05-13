/**
 * @file    dm9051a_regs.h
 * @brief   DM9051A register map, bit definitions and SPI opcodes.
 *          Register layout is identical to DM9058.
 */
#ifndef __DM9051A_REGS_H
#define __DM9051A_REGS_H

/* -----------------------------------------------------------------------
 * SPI opcode / command byte (OR-ed with register address)
 * ----------------------------------------------------------------------- */
#define OPC_REG_W       0x80u   /* Register write */
#define OPC_REG_R       0x00u   /* Register read  */
#define OPC_MEM_W       0xA0u   /* MWCMD write    */
#define OPC_MEM_R       0x72u   /* MRCMD read     */

/* -----------------------------------------------------------------------
 * Network control / status
 * ----------------------------------------------------------------------- */
#define DM9051A_NCR     0x00u   /* Network Control Register */
#define NCR_EXT_PHY     (1u<<7)
#define NCR_WAKEEN      (1u<<6)
#define NCR_FCOL        (1u<<4)
#define NCR_FDX         (1u<<3)
#define NCR_LBK_MAC     (1u<<1)
#define NCR_RST         (1u<<0) /* Software reset */

#define DM9051A_NSR     0x01u   /* Network Status Register */
#define NSR_SPEED       (1u<<7)
#define NSR_LINKST      (1u<<6)
#define NSR_WAKEST      (1u<<5)
#define NSR_TX2END      (1u<<3)
#define NSR_TX1END      (1u<<2)
#define NSR_RXOV        (1u<<1)
#define NSR_RXRDY       (1u<<0)

/* -----------------------------------------------------------------------
 * TX / RX control
 * ----------------------------------------------------------------------- */
#define DM9051A_TCR     0x02u   /* TX Control Register */
#define TCR_TJDIS       (1u<<6)
#define TCR_EXCECM      (1u<<5)
#define TCR_PAD_DIS2    (1u<<4)
#define TCR_CRC_DIS2    (1u<<3)
#define TCR_PAD_DIS1    (1u<<2)
#define TCR_CRC_DIS1    (1u<<1)
#define TCR_TXREQ       (1u<<0) /* TX request */

#define DM9051A_TSR1    0x03u   /* TX Status Register 1 */
#define DM9051A_TSR2    0x04u   /* TX Status Register 2 */

#define DM9051A_RCR     0x05u   /* RX Control Register */
#define RCR_WTDIS       (1u<<6)
#define RCR_DIS_LONG    (1u<<5)
#define RCR_DIS_CRC     (1u<<4)
#define RCR_ALL         (1u<<3)
#define RCR_RUNT        (1u<<2)
#define RCR_PRMSC       (1u<<1) /* Promiscuous mode */
#define RCR_RXEN        (1u<<0) /* RX enable */

#define DM9051A_RSR     0x06u   /* RX Status Register */
#define DM9051A_ROCR    0x07u   /* Receive Overflow Counter */
#define DM9051A_BPTR    0x08u   /* Back Pressure Threshold */
#define DM9051A_FCTR    0x09u   /* Flow Control Threshold */
#define DM9051A_FCR     0x0Au   /* TX/RX Flow Control */
#define DM9051A_EPCR    0x0Bu   /* EEPROM/PHY Control */
#define DM9051A_EPAR    0x0Cu   /* EEPROM/PHY Address */
#define DM9051A_EPDRL   0x0Du   /* EEPROM/PHY Low Byte Data */
#define DM9051A_EPDRH   0x0Eu   /* EEPROM/PHY High Byte Data */
#define DM9051A_WCR     0x0Fu   /* Wake-up Control */

/* -----------------------------------------------------------------------
 * MAC address (physical address)
 * ----------------------------------------------------------------------- */
#define DM9051A_PAR     0x10u   /* Physical Address Register (6 bytes: 0x10-0x15) */
#define DM9051A_MAR     0x16u   /* Multicast Address Register (8 bytes: 0x16-0x1D) */

/* -----------------------------------------------------------------------
 * GPCR / GPR
 * ----------------------------------------------------------------------- */
#define DM9051A_GPCR    0x1Eu   /* General-Purpose Control */
#define DM9051A_GPR     0x1Fu   /* General-Purpose Register (PHY power down bit1) */
#define GPR_PHY_PWROFF  (1u<<0) /* 1=PHY power off */

/* -----------------------------------------------------------------------
 * TX/RX FIFO pointers, counter
 * ----------------------------------------------------------------------- */
#define DM9051A_TRPAL   0x22u
#define DM9051A_TRPAH   0x23u
#define DM9051A_RWPAL   0x24u
#define DM9051A_RWPAH   0x25u
#define DM9051A_TXPLL   0x7Cu
#define DM9051A_TXPLH   0x7Du

/* -----------------------------------------------------------------------
 * Vendor / Product ID
 * ----------------------------------------------------------------------- */
#define DM9051A_VIDL    0x28u   /* Vendor ID Low  Byte  (expected 0x46) */
#define DM9051A_VIDH    0x29u   /* Vendor ID High Byte  (expected 0x0A) */
#define DM9051A_PIDL    0x2Au   /* Product ID Low  Byte (expected 0x51) */
#define DM9051A_PIDH    0x2Bu   /* Product ID High Byte (expected 0x90) */

#define DM9051A_EXPECTED_VID    0x0A46u
#define DM9051A_EXPECTED_PID    0x9051u

/* -----------------------------------------------------------------------
 * Chip revision
 * ----------------------------------------------------------------------- */
#define DM9051A_CHIPR   0x2Cu   /* Chip Revision */

/* -----------------------------------------------------------------------
 * TX memory: 4K (0x0000–0x0FFF), RX memory: 12K (0x1000–0x3FFF)
 * ----------------------------------------------------------------------- */
#define DM9051A_TX_FIFO_SZ  (4u * 1024u)
#define DM9051A_RX_FIFO_SZ  (12u * 1024u)

/* -----------------------------------------------------------------------
 * Interrupt mask / status
 * ----------------------------------------------------------------------- */
#define DM9051A_IMR     0x7Fu   /* Interrupt Mask Register */
#define DM9051A_ISR     0x7Eu   /* Interrupt Status Register */
#define IMR_PAR         (1u<<7) /* Pointer auto-return (set this bit!) */
#define IMR_LNKCHGI     (1u<<5)
#define IMR_UDRUN       (1u<<4)
#define IMR_ROOM        (1u<<3)
#define IMR_ROO         (1u<<2)
#define IMR_PT          (1u<<1) /* TX complete interrupt */
#define IMR_PR          (1u<<0) /* RX complete interrupt */

#define ISR_LNKCHG      (1u<<5)
#define ISR_UDRUN       (1u<<4)
#define ISR_ROOM        (1u<<3)
#define ISR_ROO         (1u<<2)
#define ISR_PT          (1u<<1)
#define ISR_PR          (1u<<0)
#define ISR_CLR_ALL     0x3Fu

/* -----------------------------------------------------------------------
 * Receive memory read command (MRCMD) address
 * ----------------------------------------------------------------------- */
#define DM9051A_MRCMDX  0x70u   /* Memory Read Command w/o address incr */
#define DM9051A_MRCMD   0x72u   /* Memory Read Command */
#define DM9051A_MRRL    0x74u
#define DM9051A_MRRH    0x75u
#define DM9051A_MWCMD   0x78u   /* Memory Write Command */
#define DM9051A_MWRL    0x7Au
#define DM9051A_MWRH    0x7Bu
#define DM9051A_TXPLL2  0x7Cu
#define DM9051A_TXPLH2  0x7Du

#endif /* __DM9051A_REGS_H */
