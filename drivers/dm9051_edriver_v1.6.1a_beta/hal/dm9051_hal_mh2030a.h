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
#define HAL_disable_mcu_irq        hal_disable_mcu_irq
#define HAL_enable_mcu_irq         hal_enable_mcu_irq

static __inline int dm9051_hal_mh2030a_read_reg(void *ctx, uint8_t reg, uint8_t *val)
{
    (void)ctx;
    if (val == 0) {
        return DM9051_HAL_ERR_PARAM;
    }
    *val = hal_read_reg(reg);
    return DM9051_HAL_OK;
}

static __inline int dm9051_hal_mh2030a_write_reg(void *ctx, uint8_t reg, uint8_t val)
{
    (void)ctx;
    hal_write_reg(reg, val);
    return DM9051_HAL_OK;
}

static __inline int dm9051_hal_mh2030a_read_mem(void *ctx, uint8_t *buf, uint16_t len)
{
    (void)ctx;
    if ((buf == 0) && (len != 0u)) {
        return DM9051_HAL_ERR_PARAM;
    }
    hal_read_mem(buf, len);
    return DM9051_HAL_OK;
}

static __inline int dm9051_hal_mh2030a_write_mem(void *ctx, const uint8_t *buf, uint16_t len)
{
    (void)ctx;
    if ((buf == 0) && (len != 0u)) {
        return DM9051_HAL_ERR_PARAM;
    }
    hal_write_mem(buf, len);
    return DM9051_HAL_OK;
}

static __inline void dm9051_hal_mh2030a_delay_ms(uint32_t ms)
{
    while (ms > 0xffffu) {
        Delay_Ms(0xffffu);
        ms -= 0xffffu;
    }
    if (ms != 0u) {
        Delay_Ms((uint16_t)ms);
    }
}

static __inline void dm9051_hal_mh2030a_delay_us(uint32_t us)
{
    Delay_Us(us);
}

static __inline void dm9051_hal_mh2030a_irq_enable(void *ctx)
{
    (void)ctx;
    hal_enable_mcu_irq();
}

static __inline void dm9051_hal_mh2030a_irq_disable(void *ctx)
{
    (void)ctx;
    hal_disable_mcu_irq();
}

static __inline uint32_t dm9051_hal_mh2030a_enter_critical(void *ctx)
{
    uint32_t primask;

    (void)ctx;
    primask = __get_PRIMASK();
    __disable_irq();
    return primask;
}

static __inline void dm9051_hal_mh2030a_exit_critical(void *ctx, uint32_t state)
{
    (void)ctx;
    __set_PRIMASK(state);
}

static __inline void dm9051_hal_mh2030a_bind(dm9051_hal_t *hal, void *ctx)
{
    static const dm9051_hal_ops_t ops = {
        dm9051_hal_mh2030a_read_reg,
        dm9051_hal_mh2030a_write_reg,
        dm9051_hal_mh2030a_read_mem,
        dm9051_hal_mh2030a_write_mem,
        0,
        dm9051_hal_mh2030a_delay_ms,
        dm9051_hal_mh2030a_delay_us,
        dm9051_hal_mh2030a_irq_enable,
        dm9051_hal_mh2030a_irq_disable,
        dm9051_hal_mh2030a_enter_critical,
        dm9051_hal_mh2030a_exit_critical
    };

    if (hal != 0) {
        hal->ops = &ops;
        hal->ctx = ctx;
    }
}

#ifdef __cplusplus
}
#endif

#endif
