#ifndef DM9051_HAL_AT32F403A_SPI1_PRIV_H
#define DM9051_HAL_AT32F403A_SPI1_PRIV_H

#include "dm9051_hal_at32f403a_spi1.h"
#include "at32f403a_platform.h"

#include "../../core/inc/dm9051_regs.h"

#include <stdio.h>

/* SPI1 pins: SCK=PA5, MOSI=PA7, MISO=PA6, CS=PA15 */
#define DM9051_AT32F403A_SPI            SPI1
#define DM9051_AT32F403A_CS_PORT        GPIOA
#define DM9051_AT32F403A_CS_PIN         GPIO_PINS_15
#define DM9051_AT32F403A_SCK_PORT       GPIOA
#define DM9051_AT32F403A_SCK_PIN        GPIO_PINS_5
#define DM9051_AT32F403A_MOSI_PORT      GPIOA
#define DM9051_AT32F403A_MOSI_PIN       GPIO_PINS_7
#define DM9051_AT32F403A_MISO_PORT      GPIOA
#define DM9051_AT32F403A_MISO_PIN       GPIO_PINS_6
#define DM9051_AT32F403A_RST_PORT       GPIOF
#define DM9051_AT32F403A_RST_PIN        GPIO_PINS_7
/* INT pin: PC7 / EXTI Line 7 / EXTI9_5_IRQn */
#define DM9051_AT32F403A_INT_PORT       GPIOC
#define DM9051_AT32F403A_INT_PIN        GPIO_PINS_7
#define DM9051_AT32F403A_INT_LINE       EXINT_LINE_7
#define DM9051_AT32F403A_INT_IRQn       EXINT9_5_IRQn

#if DM9051_AT32F403A_DIAG
#define DM9051_AT32F403A_DIAG_PRINTF(...) printf(__VA_ARGS__)
#else
#define DM9051_AT32F403A_DIAG_PRINTF(...) do { } while (0)
#endif

#if DM9051_AT32F403A_TRACE
#define DM9051_AT32F403A_TRACE_PRINTF(...) printf(__VA_ARGS__)
#else
#define DM9051_AT32F403A_TRACE_PRINTF(...) do { } while (0)
#endif

extern const dm9051_hal_ops_t dm9051_at32f403a_polling_ops;

void dm9051_at32f403a_select(void);
void dm9051_at32f403a_deselect(void);
int dm9051_at32f403a_wait_spi_idle(const dm9051_at32f403a_config_t *config);
int dm9051_at32f403a_transfer_byte(const dm9051_at32f403a_config_t *config,
                                   uint8_t tx,
                                   uint8_t *rx);
int dm9051_at32f403a_finish_transfer(const dm9051_at32f403a_config_t *config);
void dm9051_at32f403a_spi1_polling_bus_init(void);
void dm9051_at32f403a_spi1_bus_init_common(void);
void dm9051_at32f403a_reset_gpio_sequence(void);
void dm9051_at32f403a_delay_ms(uint32_t ms);
void dm9051_at32f403a_delay_us(uint32_t us);
uint32_t dm9051_at32f403a_enter_critical(void *ctx);
void dm9051_at32f403a_exit_critical(void *ctx, uint32_t state);
void dm9051_at32f403a_polling_reset(void *ctx);
int dm9051_at32f403a_polling_read_reg(void *ctx, uint8_t reg, uint8_t *val);
int dm9051_at32f403a_polling_write_reg(void *ctx, uint8_t reg, uint8_t val);
int dm9051_at32f403a_polling_read_mem(void *ctx, uint8_t *buf, uint16_t len);
int dm9051_at32f403a_polling_write_mem(void *ctx,
                                       const uint8_t *buf,
                                       uint16_t len);

#if DM9051_AT32F403A_ENABLE_DMA
extern const dm9051_hal_ops_t dm9051_at32f403a_dma_ops;
#endif

#if DM9051_AT32F403A_ENABLE_IRQ
void dm9051_at32f403a_irq_init_if_enabled(const dm9051_at32f403a_config_t *config);
void dm9051_at32f403a_irq_enable_if_enabled(void *ctx);
void dm9051_at32f403a_irq_disable_if_enabled(void *ctx);
#else
static void dm9051_at32f403a_irq_init_if_enabled(const dm9051_at32f403a_config_t *config)
{
    (void)config;
}

static void dm9051_at32f403a_irq_enable_if_enabled(void *ctx)
{
    (void)ctx;
}

static void dm9051_at32f403a_irq_disable_if_enabled(void *ctx)
{
    (void)ctx;
}
#endif

#endif
