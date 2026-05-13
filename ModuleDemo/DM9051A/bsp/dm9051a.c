/**
 * @file    dm9051a.c
 * @brief   DM9051A protocol layer – register read/write and bring-up.
 *
 * SPI transaction format (DM9051A / DM9058):
 *   Write: CS_L | (reg | OPC_REG_W) | data_byte | CS_H
 *   Read : CS_L | (reg | OPC_REG_R) | dummy_byte | CS_H  → data_byte
 */

#include "dm9051a.h"
#include "mh2030a_spi2.h"

/* -----------------------------------------------------------------------
 * Low-level helpers
 * ----------------------------------------------------------------------- */

uint8_t DM9051A_ReadReg(uint8_t reg)
{
    uint8_t val;
    DM9051A_CS_L();
    MH2030A_SPI2_ReadWriteByte((uint8_t)(reg | OPC_REG_R));
    val = MH2030A_SPI2_ReadWriteByte(0xFFu);
    DM9051A_CS_H();
    return val;
}

void DM9051A_WriteReg(uint8_t reg, uint8_t val)
{
    DM9051A_CS_L();
    MH2030A_SPI2_ReadWriteByte((uint8_t)(reg | OPC_REG_W));
    MH2030A_SPI2_ReadWriteByte(val);
    DM9051A_CS_H();
}

/* -----------------------------------------------------------------------
 * DM9051A_ReadVidPid
 * ----------------------------------------------------------------------- */
void DM9051A_ReadVidPid(uint16_t *pVid, uint16_t *pPid)
{
    uint8_t vidl, vidh, pidl, pidh;

    vidl = DM9051A_ReadReg(DM9051A_VIDL);
    vidh = DM9051A_ReadReg(DM9051A_VIDH);
    pidl = DM9051A_ReadReg(DM9051A_PIDL);
    pidh = DM9051A_ReadReg(DM9051A_PIDH);

    if (pVid) *pVid = (uint16_t)((vidh << 8) | vidl);
    if (pPid) *pPid = (uint16_t)((pidh << 8) | pidl);
}

/* -----------------------------------------------------------------------
 * DM9051A_CheckID
 * ----------------------------------------------------------------------- */
DM9051A_Status DM9051A_CheckID(void)
{
    uint16_t vid, pid;
    DM9051A_ReadVidPid(&vid, &pid);
    if ((vid == DM9051A_EXPECTED_VID) && (pid == DM9051A_EXPECTED_PID)) {
        return DM9051A_OK;
    }
    return DM9051A_ERR;
}

/* -----------------------------------------------------------------------
 * DM9051A_Reset
 * ----------------------------------------------------------------------- */
void DM9051A_Reset(void (*delay_ms)(uint16_t))
{
    /* Hardware reset: hold RST low ≥ 10 ms, then release */
    DM9051A_RST_L();
    delay_ms(20u);
    DM9051A_RST_H();
    delay_ms(20u);

    /* Software reset via NCR[0] */
    DM9051A_WriteReg(DM9051A_NCR, NCR_RST);
    delay_ms(2u);
    /* NCR_RST auto-clears; verify it is cleared */
    /* (no action needed, just allow settling time) */
}

/* -----------------------------------------------------------------------
 * DM9051A_BasicInit
 * ----------------------------------------------------------------------- */
void DM9051A_BasicInit(void)
{
    /* Power on PHY (clear PHY power-down bit in GPR) */
    DM9051A_WriteReg(DM9051A_GPCR, 0x01u); /* GPCR bit0 = GPO direction */
    DM9051A_WriteReg(DM9051A_GPR,  0x00u); /* GPR bit1=0 → PHY power on */

    /* Clear any pending interrupt flags */
    DM9051A_WriteReg(DM9051A_ISR, ISR_CLR_ALL);

    /* Enable RX: receive broadcast + multicast + unicast, no promiscuous */
    DM9051A_WriteReg(DM9051A_RCR, RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN);

    /* Enable RX interrupt + pointer auto-return */
    DM9051A_WriteReg(DM9051A_IMR, IMR_PAR | IMR_PR);
}
