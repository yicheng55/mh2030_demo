/**
 * @file    mh2030a_spi2.h
 * @brief   SPI2 bus driver for MH2030A — hardware layer for DM9051A.
 *
 * Pin assignment:
 *   PA9   – CS  (GPIO output, software-controlled)
 *   PA11  – SCK (SPI2 AF0)
 *   PA12  – MISO(SPI2 AF0)
 *   PA8   – MOSI(SPI2 AF0)
 *   PF7   – RST (GPIO output, active-low)
 *   PF6   – INT (GPIO input, EXTI falling edge)
 */
#ifndef __MH2030A_SPI2_H
#define __MH2030A_SPI2_H

#include "mh20xx.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	MH2030A_SPI2_OK = 0,
	MH2030A_SPI2_ERR_TXE_TIMEOUT,
	MH2030A_SPI2_ERR_RX_TIMEOUT
} MH2030A_SPI2_Status;

/* -----------------------------------------------------------------------
 * Chip-select helpers (active-low)
 * ----------------------------------------------------------------------- */
#define DM9051A_CS_L()   GPIO_ResetBits(GPIOA, GPIO_Pin_9)
#define DM9051A_CS_H()   GPIO_SetBits  (GPIOA, GPIO_Pin_9)

/* -----------------------------------------------------------------------
 * Reset helpers (active-low)
 * ----------------------------------------------------------------------- */
#define DM9051A_RST_L()  GPIO_ResetBits(GPIOF, GPIO_Pin_7)
#define DM9051A_RST_H()  GPIO_SetBits  (GPIOF, GPIO_Pin_7)

/* -----------------------------------------------------------------------
 * Public API
 * ----------------------------------------------------------------------- */

/**
 * @brief Initialise SPI2, associated GPIO (CS/SCK/MISO/MOSI/RST/INT)
 *        and DMA channels 4 (RX) / 5 (TX) for SPI2.
 *        Also configures PF6 EXTI falling-edge interrupt.
 */
void MH2030A_SPI2_Init(void);

/**
 * @brief Exchange one byte over SPI2 (polling mode).
 * @param data  Byte to transmit.
 * @return Byte received.
 */
uint8_t MH2030A_SPI2_ReadWriteByte(uint8_t data);

/**
 * @brief Exchange one byte over SPI2 with a bounded wait.
 * @param data  Byte to transmit.
 * @param pRx   Pointer to store received byte.
 * @return Transfer status.
 */
MH2030A_SPI2_Status MH2030A_SPI2_ReadWriteByteChecked(uint8_t data, uint8_t *pRx);

/**
 * @brief DMA-based full-duplex transfer over SPI2.
 *        Blocks until both TX and RX DMA complete.
 * @param pTx   Pointer to transmit buffer (NULL → send 0xFF).
 * @param pRx   Pointer to receive  buffer (NULL → discard).
 * @param len   Number of bytes.
 */
void MH2030A_SPI2_DMATransfer(const uint8_t *pTx, uint8_t *pRx, uint16_t len);

/**
 * @brief Change SPI2 baud-rate prescaler at run-time.
 * @param prescaler  SPI_BaudRatePrescaler_x constant.
 */
void MH2030A_SPI2_SetSpeed(uint8_t prescaler);

/**
 * @brief Get the status from the most recent bounded SPI transfer.
 */
MH2030A_SPI2_Status MH2030A_SPI2_GetLastStatus(void);

/**
 * @brief Clear the sticky last-status register.
 */
void MH2030A_SPI2_ClearLastStatus(void);

#ifdef __cplusplus
}
#endif

#endif /* __MH2030A_SPI2_H */
