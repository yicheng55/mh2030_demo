#ifndef __DM9051_HAL_H
#define __DM9051_HAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DM9051_HAL_OK             0
#define DM9051_HAL_ERR           -1
#define DM9051_HAL_ERR_TIMEOUT   -2
#define DM9051_HAL_ERR_PARAM     -3

typedef struct dm9051_hal_ops {
    int (*read_reg)(void *ctx, uint8_t reg, uint8_t *val);
    int (*write_reg)(void *ctx, uint8_t reg, uint8_t val);
    int (*read_mem)(void *ctx, uint8_t *buf, uint16_t len);
    int (*write_mem)(void *ctx, const uint8_t *buf, uint16_t len);
    void (*reset)(void *ctx);
    void (*delay_ms)(uint32_t ms);
    void (*delay_us)(uint32_t us);
    void (*irq_enable)(void *ctx);
    void (*irq_disable)(void *ctx);
    uint32_t (*enter_critical)(void *ctx);
    void (*exit_critical)(void *ctx, uint32_t state);
} dm9051_hal_ops_t;

typedef struct dm9051_hal {
    const dm9051_hal_ops_t *ops;
    void *ctx;
} dm9051_hal_t;

#ifdef __cplusplus
}
#endif

#endif /* __DM9051_HAL_H */
