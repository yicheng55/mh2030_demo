/**
 * @file    dm9051a.h
 * @brief   DM9051A protocol layer – register read/write and bring-up API.
 *          Depends on mh2030a_spi2.h for the hardware bus.
 */
#ifndef __DM9051A_H
#define __DM9051A_H

#include "mh20xx.h"
#include "dm9051a_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
 * Return codes
 * ----------------------------------------------------------------------- */
typedef enum {
    DM9051A_OK   = 0,
    DM9051A_ERR  = 1
} DM9051A_Status;

/* -----------------------------------------------------------------------
 * Public API
 * ----------------------------------------------------------------------- */

/**
 * @brief Hardware reset (RST pin toggle) + software reset of DM9051A.
 *        Caller must have called MH2030A_SPI2_Init() first.
 * @param delay_ms  Function pointer to a millisecond delay, e.g. Delay_Ms.
 */
void DM9051A_Reset(void (*delay_ms)(uint16_t));

/**
 * @brief Read one register byte.
 */
uint8_t DM9051A_ReadReg(uint8_t reg);

/**
 * @brief Write one register byte.
 */
void DM9051A_WriteReg(uint8_t reg, uint8_t val);

/**
 * @brief Read Vendor ID and Product ID.
 * @param pVid  Pointer to store 16-bit VID (little-endian, LSB first).
 * @param pPid  Pointer to store 16-bit PID.
 */
void DM9051A_ReadVidPid(uint16_t *pVid, uint16_t *pPid);

/**
 * @brief Verify VID/PID against expected values.
 * @return DM9051A_OK if chip found, DM9051A_ERR otherwise.
 */
DM9051A_Status DM9051A_CheckID(void);

/**
 * @brief Minimal initialisation: power-on PHY, configure RX, clear ISR,
 *        set interrupt mask.  Call after DM9051A_Reset().
 */
void DM9051A_BasicInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __DM9051A_H */
