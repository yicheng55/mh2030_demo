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

int dm9051_mh2030a_hal_bind(dm9051_hal_t *hal,
                             const dm9051_mh2030a_config_t *config)
{
    if ((hal == 0) || (config == 0)) {
        return DM9051_HAL_ERR_PARAM;
    }

    hal->ops = 0;
    hal->ctx = 0;
    return DM9051_HAL_ERR;
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
