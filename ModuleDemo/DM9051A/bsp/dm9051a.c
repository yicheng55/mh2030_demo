/**
 * @file    dm9051a.c
 * @brief   DM9051A protocol layer – register read/write and bring-up.
 *
 * SPI transaction format (DM9051A / DM9058):
 *   Write: CS_L | (reg | OPC_REG_W) | data_byte | CS_H
 *   Read : CS_L | (reg | OPC_REG_R) | dummy_byte | CS_H  → data_byte
 */

#include <stddef.h>
#include "dm9051a.h"
#include "mh2030a_spi2.h"

/* -----------------------------------------------------------------------
 * Low-level helpers
 * ----------------------------------------------------------------------- */

static DM9051A_Status DM9051A_ReadRegChecked(uint8_t reg, uint8_t *pVal)
{
    MH2030A_SPI2_Status spi_status;

    DM9051A_CS_L();
    spi_status = MH2030A_SPI2_ReadWriteByteChecked((uint8_t)(reg | OPC_REG_R), NULL);
    if (spi_status != MH2030A_SPI2_OK) {
        DM9051A_CS_H();
        return DM9051A_SPI_ERR;
    }

    spi_status = MH2030A_SPI2_ReadWriteByteChecked(0x00u, pVal);
    DM9051A_CS_H();

    return (spi_status == MH2030A_SPI2_OK) ? DM9051A_OK : DM9051A_SPI_ERR;
}

static DM9051A_Status DM9051A_WriteRegChecked(uint8_t reg, uint8_t val)
{
    MH2030A_SPI2_Status spi_status;

    DM9051A_CS_L();
    spi_status = MH2030A_SPI2_ReadWriteByteChecked((uint8_t)(reg | OPC_REG_W), NULL);
    if (spi_status != MH2030A_SPI2_OK) {
        DM9051A_CS_H();
        return DM9051A_SPI_ERR;
    }

    spi_status = MH2030A_SPI2_ReadWriteByteChecked(val, NULL);
    DM9051A_CS_H();

    return (spi_status == MH2030A_SPI2_OK) ? DM9051A_OK : DM9051A_SPI_ERR;
}

uint8_t DM9051A_ReadReg(uint8_t reg)
{
    uint8_t val = 0xFFu;

    (void)DM9051A_ReadRegChecked(reg, &val);
    return val;
}

void DM9051A_WriteReg(uint8_t reg, uint8_t val)
{
    (void)DM9051A_WriteRegChecked(reg, val);
}

/* -----------------------------------------------------------------------
 * DM9051A_ReadVidPid
 * ----------------------------------------------------------------------- */
DM9051A_Status DM9051A_ReadVidPid(uint16_t *pVid, uint16_t *pPid)
{
    uint8_t vidl, vidh, pidl, pidh;

    if (DM9051A_ReadRegChecked(DM9051A_VIDL, &vidl) != DM9051A_OK) return DM9051A_SPI_ERR;
    if (DM9051A_ReadRegChecked(DM9051A_VIDH, &vidh) != DM9051A_OK) return DM9051A_SPI_ERR;
    if (DM9051A_ReadRegChecked(DM9051A_PIDL, &pidl) != DM9051A_OK) return DM9051A_SPI_ERR;
    if (DM9051A_ReadRegChecked(DM9051A_PIDH, &pidh) != DM9051A_OK) return DM9051A_SPI_ERR;

    if (pVid) *pVid = (uint16_t)((vidh << 8) | vidl);
    if (pPid) *pPid = (uint16_t)((pidh << 8) | pidl);

    return DM9051A_OK;
}

/* -----------------------------------------------------------------------
 * DM9051A_CheckID
 * ----------------------------------------------------------------------- */
DM9051A_Status DM9051A_CheckID(void)
{
    uint16_t vid, pid;
    DM9051A_Status status;

    status = DM9051A_ReadVidPid(&vid, &pid);
    if (status != DM9051A_OK) {
        return status;
    }

    if ((vid == DM9051A_EXPECTED_VID) && (pid == DM9051A_EXPECTED_PID)) {
        return DM9051A_OK;
    }
    return DM9051A_ERR;
}

/* -----------------------------------------------------------------------
 * DM9051A_Reset
 * ----------------------------------------------------------------------- */
DM9051A_Status DM9051A_Reset(void (*delay_ms)(uint16_t))
{
    /* Hardware reset: hold RST low ≥ 10 ms, then release */
    DM9051A_RST_L();
    delay_ms(20u);
    DM9051A_RST_H();
    delay_ms(20u);

    /* Software reset via NCR[0] */
    if (DM9051A_WriteRegChecked(DM9051A_NCR, NCR_RST) != DM9051A_OK) {
        return DM9051A_SPI_ERR;
    }
    delay_ms(2u);
    /* NCR_RST auto-clears; verify it is cleared */
    /* (no action needed, just allow settling time) */
    return DM9051A_OK;
}

/* -----------------------------------------------------------------------
 * DM9051A_BasicInit
 * ----------------------------------------------------------------------- */
DM9051A_Status DM9051A_BasicInit(void)
{
    /* Power on PHY (clear PHY power-down bit in GPR) */
    if (DM9051A_WriteRegChecked(DM9051A_GPCR, 0x01u) != DM9051A_OK) return DM9051A_SPI_ERR;
    if (DM9051A_WriteRegChecked(DM9051A_GPR,  0x00u) != DM9051A_OK) return DM9051A_SPI_ERR;

    /* Clear any pending interrupt flags */
    if (DM9051A_WriteRegChecked(DM9051A_ISR, ISR_CLR_ALL) != DM9051A_OK) return DM9051A_SPI_ERR;

    /* Enable RX: receive broadcast + multicast + unicast, no promiscuous */
    if (DM9051A_WriteRegChecked(DM9051A_RCR, RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN) != DM9051A_OK) return DM9051A_SPI_ERR;

    /* Enable RX interrupt + pointer auto-return */
    if (DM9051A_WriteRegChecked(DM9051A_IMR, IMR_PAR | IMR_PR) != DM9051A_OK) return DM9051A_SPI_ERR;

    return DM9051A_OK;
}
