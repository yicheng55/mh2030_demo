/**
 * @file  dm9051_hal_api.h
 * @brief DM9051 HAL flat-function API declarations.
 *
 * This header defines the platform-agnostic HAL contract that every target
 * platform must implement.  The DM9051 core driver (#include "dm9051.h")
 * depends only on this header — it does NOT include any platform-specific
 * code.
 *
 * Platform implementation files:
 *   Polling  : ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c
 *   DMA      : ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi_dma.c
 *   Interrupt: ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_int.c
 *
 * Build selection is controlled by Keil target defines:
 *   - (none)                   → polling  (MH2030A_DM9051_uIP)
 *   - MH2030A_DM9051_SPI_DMA   → DMA      (MH2030A_DM9051_uIP_dma)
 *   - DMPLUG_INT               → interrupt(MH2030A_DM9051_uIP_int)
 */

#ifndef __DM9051_HAL_API_H
#define __DM9051_HAL_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Macro aliases used by dm9051_beta.c (backward compatible shim layer).
 * These keep the core driver source unchanged while allowing the underlying
 * implementations to be selected per target.
 * ---------------------------------------------------------------------- */
#define HAL_boards_initialize_spi   hal_spi_initialize
#define HAL_boards_initialize_int   hal_int_initialize
#define HAL_read_reg                hal_read_reg
#define HAL_write_reg               hal_write_reg
#define HAL_read_mem                hal_read_mem
#define HAL_write_mem               hal_write_mem
#define HAL_disable_mcu_irq         hal_disable_mcu_irq
#define HAL_enable_mcu_irq          hal_enable_mcu_irq

/* -------------------------------------------------------------------------
 * SPI / Bus HAL
 * ---------------------------------------------------------------------- */

/**
 * @brief  Initialise the SPI bus and supporting GPIO (CS, RST).
 *         Must be called once before any hal_read_reg / hal_write_reg.
 */
void     hal_spi_initialize(void);

/**
 * @brief  Return a human-readable description string for the SPI bus.
 * @param  index  0 = bus name, 1 = pin assignment string.
 * @return Pointer to a static string (must not be freed).
 */
char    *hal_spi_info(int index);

/**
 * @brief  Read a single DM9051 register.
 * @param  reg  Register address (7-bit, OPC_REG_R applied internally).
 * @return Register value.
 */
uint8_t  hal_read_reg(uint8_t reg);

/**
 * @brief  Write a single DM9051 register.
 * @param  reg  Register address (7-bit, OPC_REG_W applied internally).
 * @param  val  Value to write.
 */
void     hal_write_reg(uint8_t reg, uint8_t val);

/**
 * @brief  Burst-read from DM9051 RX FIFO (MRCMD sequence).
 * @param  buf  Destination buffer; must be at least @p len bytes.
 * @param  len  Number of bytes to read.
 */
void     hal_read_mem(uint8_t *buf, uint16_t len);

/**
 * @brief  Burst-write to DM9051 TX FIFO (MWCMD sequence).
 * @param  buf  Source buffer.
 * @param  len  Number of bytes to write.
 */
void     hal_write_mem(const uint8_t *buf, uint16_t len);

/* -------------------------------------------------------------------------
 * Interrupt / GPIO HAL
 * ---------------------------------------------------------------------- */

/**
 * @brief  Configure the external interrupt line connected to DM9051 INT pin.
 * @return EXTI line value (e.g. EXTI_Line6); 0 when DMPLUG_INT not defined.
 */
uint32_t hal_int_initialize(void);

/**
 * @brief  Enable the MCU IRQ channel for the DM9051 INT line.
 */
void     hal_enable_mcu_irq(void);

/**
 * @brief  Disable the MCU IRQ channel for the DM9051 INT line.
 */
void     hal_disable_mcu_irq(void);

/**
 * @brief  Return the EXTI line value used for the DM9051 interrupt.
 * @return EXTI line constant; 0 in polling mode.
 */
uint32_t hal_irqline(void);

/**
 * @brief  Return a human-readable description of the interrupt configuration.
 * @param  index  0 = mode string, 1 = pin/line string.
 * @return Pointer to a static string (must not be freed).
 */
char    *hal_int_info(int index);

#ifdef __cplusplus
}
#endif

#endif /* __DM9051_HAL_API_H */
