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

/* Implementation plan:
 * 1. Add static polling transport ops copied from mh2030a_dm9051_spi.c.
 * 2. Add static DMA transport ops copied from mh2030a_dm9051_spi_dma.c.
 * 3. Add IRQ setup copied from mh2030a_dm9051_int.c.
 * 4. Select transport via dm9051_mh2030a_config_t instead of IncludeInBuild.
 * 5. Bind the selected ops into dm9051_hal_t.
 */
