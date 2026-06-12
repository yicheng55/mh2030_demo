#ifndef DM9051_HAL_MH2030A_SPI1_H
#define DM9051_HAL_MH2030A_SPI1_H

#include <stdint.h>

#include "../../hal/inc/dm9051_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Future MH2030A port binding for the DM9051 HAL interface.
 *
 * Naming note:
 *   This staging header covers the MH2030A SPI1 polling baseline.
 *   Future split headers should keep the bus/mode visible in the filename:
 *     dm9051_hal_mh2030a_spi1.h
 *     dm9051_hal_mh2030a_spi1_dma.h
 *     dm9051_hal_mh2030a_int.h
 *
 * Current closest source:
 *   ModuleDemo/DM9051A/port/mh2030a/dm9051_hal_mh2030a.h
 *
 * This staging header is not included by existing Keil targets yet.
 */

typedef enum dm9051_mh2030a_transport {
    DM9051_MH2030A_TRANSPORT_POLLING = 0,
    DM9051_MH2030A_TRANSPORT_DMA = 1
} dm9051_mh2030a_transport_t;

typedef enum dm9051_mh2030a_irq_mode {
    DM9051_MH2030A_IRQ_OFF = 0,
    DM9051_MH2030A_IRQ_EXTI = 1
} dm9051_mh2030a_irq_mode_t;

typedef struct dm9051_mh2030a_pins {
    uint32_t cs_port;
    uint16_t cs_pin;
    uint32_t sck_port;
    uint16_t sck_pin;
    uint32_t miso_port;
    uint16_t miso_pin;
    uint32_t mosi_port;
    uint16_t mosi_pin;
    uint32_t rst_port;
    uint16_t rst_pin;
    uint32_t int_port;
    uint16_t int_pin;
} dm9051_mh2030a_pins_t;

typedef struct dm9051_mh2030a_config {
    dm9051_mh2030a_transport_t transport;
    dm9051_mh2030a_irq_mode_t irq_mode;
    dm9051_mh2030a_pins_t pins;
    uint32_t spi_timeout;
} dm9051_mh2030a_config_t;

#define DM9051_MH2030A_DEFAULT_SPI_TIMEOUT 1000000u

void dm9051_mh2030a_default_config(dm9051_mh2030a_config_t *config);
int dm9051_mh2030a_config_is_valid(const dm9051_mh2030a_config_t *config);
int dm9051_mh2030a_hal_bind(dm9051_hal_t *hal,
                             const dm9051_mh2030a_config_t *config);
const char *dm9051_mh2030a_transport_name(dm9051_mh2030a_transport_t transport);
const char *dm9051_mh2030a_irq_name(dm9051_mh2030a_irq_mode_t irq_mode);

#ifdef __cplusplus
}
#endif

#endif /* DM9051_HAL_MH2030A_SPI1_H */
