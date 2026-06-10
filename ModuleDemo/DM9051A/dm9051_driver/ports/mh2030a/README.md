# MH2030A DM9051 Port

This directory will contain the MH2030A implementation of the portable DM9051
HAL interface.

## Current Pin Mapping

| Signal | Pin |
| --- | --- |
| CS | PA15 |
| SCK | PB3 |
| MISO | PB4 |
| MOSI | PB5 |
| INT | PF6 / EXTI line 6 |
| RST | PF7 |

## Current Build Modes

| Mode | Define | Current source |
| --- | --- | --- |
| Polling SPI | none | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c` |
| SPI DMA | `MH2030A_DM9051_SPI_DMA` | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi_dma.c` |
| Interrupt | `DMPLUG_INT` | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_int.c` |

The current Keil targets select files with per-target file options. The future
portable build should make the transport selection explicit to avoid duplicate
`hal_*` symbols.

See `../../docs/BUILD_SELECTION.md` for the current target matrix.

## Future Port API

The staging header `dm9051_hal_mh2030a.h` defines an explicit config model:

- `dm9051_mh2030a_transport_t`: polling or DMA SPI.
- `dm9051_mh2030a_irq_mode_t`: IRQ off or EXTI IRQ.
- `dm9051_mh2030a_pins_t`: pin assignment for CS/SCK/MISO/MOSI/RST/INT.
- `dm9051_mh2030a_config_t`: transport, IRQ, pins, and timeout.

The future implementation should bind this config into `dm9051_hal_t` with
`dm9051_mh2030a_hal_bind()`. Until that function is implemented and wired into
a target, the production code remains the current flat `hal_*` implementation.

Current staging implementation status:

- `dm9051_mh2030a_default_config()` sets a transport/IRQ/timeout default without
  touching hardware.
- `dm9051_mh2030a_config_is_valid()` validates transport, IRQ mode, and timeout
  without requiring platform headers.
- `dm9051_mh2030a_transport_name()` and `dm9051_mh2030a_irq_name()` are usable
  string helpers.
- `dm9051_mh2030a_hal_bind()` validates parameters, clears the HAL handle, and
  returns `DM9051_HAL_ERR` until real polling/DMA ops are implemented.
