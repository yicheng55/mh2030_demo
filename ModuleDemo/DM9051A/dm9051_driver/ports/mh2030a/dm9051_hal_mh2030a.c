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

    hal->ops = &dm9051_mh2030a_staging_ops;
    hal->ctx = 0;
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
