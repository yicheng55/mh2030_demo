#ifndef __DM9051_HAL_MH2030A_H
#define __DM9051_HAL_MH2030A_H

#include "../include/dm9051_hal.h"
#include "hal_mh2030a.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_boards_initialize_spi  hal_spi_initialize
#define HAL_boards_initialize_int  hal_int_initialize
#define HAL_read_reg               hal_read_reg
#define HAL_write_reg              hal_write_reg
#define HAL_read_mem               hal_read_mem
#define HAL_write_mem              hal_write_mem
#define HAL_enable_mcu_irq         hal_enable_mcu_irq

#ifdef __cplusplus
}
#endif

#endif
