/*
 * Future MH2030A SPI/GPIO/IRQ/delay implementation for DM9051.
 *
 * Current sources:
 *   ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c
 *   ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi_dma.c
 *   ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_int.c
 *
 * This file is intentionally not implemented yet. The current production
 * driver still selects polling/DMA/IRQ through Keil file options and flat
 * hal_* symbols.
 */

#include "dm9051_hal_mh2030a.h"

#include "../../core/inc/dm9051_regs.h"
#include "../../../port/mh2030a/hal_mh2030a.h"

#define DM9051_MH2030A_SPI        SPI1
#define DM9051_MH2030A_CS_PORT    GPIOA
#define DM9051_MH2030A_CS_PIN     GPIO_Pin_15
#define DM9051_MH2030A_SCK_PORT   GPIOB
#define DM9051_MH2030A_SCK_PIN    GPIO_Pin_3
#define DM9051_MH2030A_MOSI_PORT  GPIOB
#define DM9051_MH2030A_MOSI_PIN   GPIO_Pin_5
#define DM9051_MH2030A_MISO_PORT  GPIOB
#define DM9051_MH2030A_MISO_PIN   GPIO_Pin_4
#define DM9051_MH2030A_RST_PORT   GPIOF
#define DM9051_MH2030A_RST_PIN    GPIO_Pin_7

static int dm9051_mh2030a_staging_read_reg(void *ctx,
                                            uint8_t reg,
                                            uint8_t *val)
{
    (void)ctx;
    (void)reg;

    if (val == 0) {
        return DM9051_HAL_ERR_PARAM;
    }

    return DM9051_HAL_ERR_NOT_READY;
}

static int dm9051_mh2030a_staging_write_reg(void *ctx,
                                             uint8_t reg,
                                             uint8_t val)
{
    (void)ctx;
    (void)reg;
    (void)val;
    return DM9051_HAL_ERR_NOT_READY;
}

static int dm9051_mh2030a_staging_read_mem(void *ctx,
                                            uint8_t *buf,
                                            uint16_t len)
{
    (void)ctx;

    if ((buf == 0) && (len != 0u)) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    return DM9051_HAL_ERR_NOT_READY;
}

static int dm9051_mh2030a_staging_write_mem(void *ctx,
                                             const uint8_t *buf,
                                             uint16_t len)
{
    (void)ctx;

    if ((buf == 0) && (len != 0u)) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    return DM9051_HAL_ERR_NOT_READY;
}

static void dm9051_mh2030a_staging_reset(void *ctx)
{
    (void)ctx;
}

static void dm9051_mh2030a_staging_delay_ms(uint32_t ms)
{
    (void)ms;
}

static void dm9051_mh2030a_staging_delay_us(uint32_t us)
{
    (void)us;
}

static void dm9051_mh2030a_staging_irq_enable(void *ctx)
{
    (void)ctx;
}

static void dm9051_mh2030a_staging_irq_disable(void *ctx)
{
    (void)ctx;
}

static const dm9051_hal_ops_t dm9051_mh2030a_staging_ops = {
    dm9051_mh2030a_staging_read_reg,
    dm9051_mh2030a_staging_write_reg,
    dm9051_mh2030a_staging_read_mem,
    dm9051_mh2030a_staging_write_mem,
    dm9051_mh2030a_staging_reset,
    dm9051_mh2030a_staging_delay_ms,
    dm9051_mh2030a_staging_delay_us,
    dm9051_mh2030a_staging_irq_enable,
    dm9051_mh2030a_staging_irq_disable,
    0,
    0
};

static void dm9051_mh2030a_select(void)
{
    GPIO_ResetBits(DM9051_MH2030A_CS_PORT, DM9051_MH2030A_CS_PIN);
}

static void dm9051_mh2030a_deselect(void)
{
    GPIO_SetBits(DM9051_MH2030A_CS_PORT, DM9051_MH2030A_CS_PIN);
}

static int dm9051_mh2030a_wait_spi_idle(const dm9051_mh2030a_config_t *config)
{
    uint32_t timeout = config->spi_timeout;

    while (SPI_I2S_GetFlagStatus(DM9051_MH2030A_SPI, SPI_I2S_FLAG_BSY) == SET) {
        if (timeout == 0u) {
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }

    return DM9051_HAL_OK;
}

static int dm9051_mh2030a_transfer_byte(const dm9051_mh2030a_config_t *config,
                                        uint8_t tx,
                                        uint8_t *rx)
{
    uint32_t timeout;

    if (rx == 0) {
        return DM9051_HAL_ERR_PARAM;
    }

    timeout = config->spi_timeout;
    while (SPI_I2S_GetFlagStatus(DM9051_MH2030A_SPI, SPI_I2S_FLAG_TXE) == RESET) {
        if (timeout == 0u) {
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }
    SPI_SendData8(DM9051_MH2030A_SPI, tx);

    timeout = config->spi_timeout;
    while (SPI_I2S_GetFlagStatus(DM9051_MH2030A_SPI, SPI_I2S_FLAG_RXNE) == RESET) {
        if (timeout == 0u) {
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }

    *rx = SPI_ReceiveData8(DM9051_MH2030A_SPI);
    return DM9051_HAL_OK;
}

static int dm9051_mh2030a_finish_transfer(const dm9051_mh2030a_config_t *config)
{
    int status;

    status = dm9051_mh2030a_wait_spi_idle(config);
    while (SPI_I2S_GetFlagStatus(DM9051_MH2030A_SPI, SPI_I2S_FLAG_RXNE) == SET) {
        (void)SPI_ReceiveData8(DM9051_MH2030A_SPI);
    }

    return status;
}

static void dm9051_mh2030a_polling_reset(void *ctx)
{
    (void)ctx;
    GPIO_ResetBits(DM9051_MH2030A_RST_PORT, DM9051_MH2030A_RST_PIN);
    Delay_Ms(2u);
    GPIO_SetBits(DM9051_MH2030A_RST_PORT, DM9051_MH2030A_RST_PIN);
    Delay_Ms(10u);
}

static void dm9051_mh2030a_polling_delay_ms(uint32_t ms)
{
    while (ms > 0xffffu) {
        Delay_Ms(0xffffu);
        ms -= 0xffffu;
    }

    Delay_Ms((uint16_t)ms);
}

static void dm9051_mh2030a_polling_delay_us(uint32_t us)
{
    Delay_Us(us);
}

static void dm9051_mh2030a_polling_irq_enable(void *ctx)
{
    (void)ctx;
}

static void dm9051_mh2030a_polling_irq_disable(void *ctx)
{
    (void)ctx;
}

static int dm9051_mh2030a_polling_read_reg(void *ctx,
                                           uint8_t reg,
                                           uint8_t *val)
{
    const dm9051_mh2030a_config_t *config = (const dm9051_mh2030a_config_t *)ctx;
    uint8_t dummy;
    int status;

    if ((config == 0) || (val == 0)) {
        return DM9051_HAL_ERR_PARAM;
    }

    dm9051_mh2030a_select();
    status = dm9051_mh2030a_transfer_byte(config,
                                          (uint8_t)(reg | DM9051_OPC_REG_R),
                                          &dummy);
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_transfer_byte(config, 0x00u, val);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_finish_transfer(config);
    } else {
        (void)dm9051_mh2030a_finish_transfer(config);
    }
    dm9051_mh2030a_deselect();

    return status;
}

static int dm9051_mh2030a_polling_write_reg(void *ctx,
                                            uint8_t reg,
                                            uint8_t val)
{
    const dm9051_mh2030a_config_t *config = (const dm9051_mh2030a_config_t *)ctx;
    uint8_t dummy;
    int status;

    if (config == 0) {
        return DM9051_HAL_ERR_PARAM;
    }

    dm9051_mh2030a_select();
    status = dm9051_mh2030a_transfer_byte(config,
                                          (uint8_t)(reg | DM9051_OPC_REG_W),
                                          &dummy);
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_transfer_byte(config, val, &dummy);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_finish_transfer(config);
    } else {
        (void)dm9051_mh2030a_finish_transfer(config);
    }
    dm9051_mh2030a_deselect();

    return status;
}

static int dm9051_mh2030a_polling_read_mem(void *ctx,
                                           uint8_t *buf,
                                           uint16_t len)
{
    const dm9051_mh2030a_config_t *config = (const dm9051_mh2030a_config_t *)ctx;
    uint8_t dummy;
    uint16_t i;
    int status;

    if ((config == 0) || ((buf == 0) && (len != 0u))) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    dm9051_mh2030a_select();
    status = dm9051_mh2030a_transfer_byte(config,
                                          (uint8_t)(DM9051_MRCMD | DM9051_OPC_REG_R),
                                          &dummy);
    for (i = 0u; (i < len) && (status == DM9051_HAL_OK); ++i) {
        status = dm9051_mh2030a_transfer_byte(config, 0x00u, &buf[i]);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_finish_transfer(config);
    } else {
        (void)dm9051_mh2030a_finish_transfer(config);
    }
    dm9051_mh2030a_deselect();

    return status;
}

static int dm9051_mh2030a_polling_write_mem(void *ctx,
                                            const uint8_t *buf,
                                            uint16_t len)
{
    const dm9051_mh2030a_config_t *config = (const dm9051_mh2030a_config_t *)ctx;
    uint8_t dummy;
    uint16_t i;
    int status;

    if ((config == 0) || ((buf == 0) && (len != 0u))) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    dm9051_mh2030a_select();
    status = dm9051_mh2030a_transfer_byte(config,
                                          (uint8_t)(DM9051_MWCMD | DM9051_OPC_REG_W),
                                          &dummy);
    for (i = 0u; (i < len) && (status == DM9051_HAL_OK); ++i) {
        status = dm9051_mh2030a_transfer_byte(config, buf[i], &dummy);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_finish_transfer(config);
    } else {
        (void)dm9051_mh2030a_finish_transfer(config);
    }
    dm9051_mh2030a_deselect();

    return status;
}

static const dm9051_hal_ops_t dm9051_mh2030a_polling_ops = {
    dm9051_mh2030a_polling_read_reg,
    dm9051_mh2030a_polling_write_reg,
    dm9051_mh2030a_polling_read_mem,
    dm9051_mh2030a_polling_write_mem,
    dm9051_mh2030a_polling_reset,
    dm9051_mh2030a_polling_delay_ms,
    dm9051_mh2030a_polling_delay_us,
    dm9051_mh2030a_polling_irq_enable,
    dm9051_mh2030a_polling_irq_disable,
    0,
    0
};

static dm9051_mh2030a_config_t dm9051_mh2030a_bound_config;

void dm9051_mh2030a_default_config(dm9051_mh2030a_config_t *config)
{
    if (config == 0) {
        return;
    }

    config->transport = DM9051_MH2030A_TRANSPORT_POLLING;
    config->irq_mode = DM9051_MH2030A_IRQ_OFF;
    config->pins.cs_port = 0u;
    config->pins.cs_pin = 0u;
    config->pins.sck_port = 0u;
    config->pins.sck_pin = 0u;
    config->pins.miso_port = 0u;
    config->pins.miso_pin = 0u;
    config->pins.mosi_port = 0u;
    config->pins.mosi_pin = 0u;
    config->pins.rst_port = 0u;
    config->pins.rst_pin = 0u;
    config->pins.int_port = 0u;
    config->pins.int_pin = 0u;
    config->spi_timeout = DM9051_MH2030A_DEFAULT_SPI_TIMEOUT;
}

int dm9051_mh2030a_config_is_valid(const dm9051_mh2030a_config_t *config)
{
    if (config == 0) {
        return 0;
    }

    switch (config->transport) {
    case DM9051_MH2030A_TRANSPORT_POLLING:
    case DM9051_MH2030A_TRANSPORT_DMA:
        break;
    default:
        return 0;
    }

    switch (config->irq_mode) {
    case DM9051_MH2030A_IRQ_OFF:
    case DM9051_MH2030A_IRQ_EXTI:
        break;
    default:
        return 0;
    }

    if (config->spi_timeout == 0u) {
        return 0;
    }

    return 1;
}

int dm9051_mh2030a_hal_bind(dm9051_hal_t *hal,
                             const dm9051_mh2030a_config_t *config)
{
    if ((hal == 0) || !dm9051_mh2030a_config_is_valid(config)) {
        return DM9051_HAL_ERR_PARAM;
    }

    dm9051_mh2030a_bound_config = *config;
    hal->ctx = &dm9051_mh2030a_bound_config;

    if (config->transport == DM9051_MH2030A_TRANSPORT_POLLING) {
        hal->ops = &dm9051_mh2030a_polling_ops;
        return DM9051_HAL_OK;
    }

    hal->ops = &dm9051_mh2030a_staging_ops;
    return DM9051_HAL_ERR_NOT_READY;
}

const char *dm9051_mh2030a_transport_name(dm9051_mh2030a_transport_t transport)
{
    switch (transport) {
    case DM9051_MH2030A_TRANSPORT_POLLING:
        return "polling";
    case DM9051_MH2030A_TRANSPORT_DMA:
        return "dma";
    default:
        return "unknown";
    }
}

const char *dm9051_mh2030a_irq_name(dm9051_mh2030a_irq_mode_t irq_mode)
{
    switch (irq_mode) {
    case DM9051_MH2030A_IRQ_OFF:
        return "off";
    case DM9051_MH2030A_IRQ_EXTI:
        return "exti";
    default:
        return "unknown";
    }
}

/* Implementation plan:
 * 1. Add static polling transport ops copied from mh2030a_dm9051_spi.c.
 * 2. Add static DMA transport ops copied from mh2030a_dm9051_spi_dma.c.
 * 3. Add IRQ setup copied from mh2030a_dm9051_int.c.
 * 4. Select transport via dm9051_mh2030a_config_t instead of IncludeInBuild.
 * 5. Bind the selected ops into dm9051_hal_t.
 */
