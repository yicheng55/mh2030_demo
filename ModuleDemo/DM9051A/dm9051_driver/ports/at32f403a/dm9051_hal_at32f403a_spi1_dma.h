#ifndef DM9051_HAL_AT32F403A_SPI1_DMA_H
#define DM9051_HAL_AT32F403A_SPI1_DMA_H

#include "dm9051_hal_at32f403a_spi1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Compile this file with DM9051_AT32F403A_ENABLE_DMA=1.
 *
 * DMA mapping (AT32F403A, DEFAULT — no remap needed):
 *   SPI1 RX: DMA1 Channel 2
 *   SPI1 TX: DMA1 Channel 3
 */
extern const dm9051_hal_ops_t dm9051_at32f403a_dma_ops;

#ifdef __cplusplus
}
#endif

#endif
