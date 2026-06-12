# MH2030A DM9051 Port

This directory will contain the MH2030A implementation of the portable DM9051
HAL interface.

## Files

| File | Role |
| --- | --- |
| `dm9051_hal_mh2030a_spi1.c/.h` | Staging DM9051 HAL binding for MH2030A SPI1 polling, GPIO, IRQ mode selection, and delay. |
| `mh2030a_platform.h` | Local MH2030A platform include shim for `mh20xx.h` and `delay.h`. |
| `mh2030a_board.c/.h` | MH2030A board bring-up helpers for clock, debug UART, and printf retargeting. |

## Port File Naming Plan

Use names that expose both the platform and the bus. The current staging
implementation is the SPI1 polling baseline; later transports should be added
as separate files instead of hiding the mode behind a generic filename:

| Planned file class | Responsibility |
| --- | --- |
| `dm9051_hal_mh2030a_spi1.c/.h` | SPI1 polling transfer, CS control, reset GPIO, and delay binding. |
| `dm9051_hal_mh2030a_spi1_dma.c/.h` | SPI1 DMA transfer implementation selected by `DM9051_MH2030A_TRANSPORT_DMA`. |
| `dm9051_hal_mh2030a_int.c/.h` | DM9051 INT pin / EXTI setup, enable, disable, and ISR handoff helpers. |

This mirrors the current production split under `ModuleDemo/DM9051A/port/mh2030a`
while making the SPI instance explicit for future ports that may use another
SPI peripheral.

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

The staging header `dm9051_hal_mh2030a_spi1.h` defines an explicit config model:

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
- `dm9051_mh2030a_hal_bind()` validates parameters and copies config into an
  internal HAL context.
- Polling transport binds real SPI register/FIFO operations based on the
  current `mh2030a_dm9051_spi.c` behavior.
- DMA transport still binds the staging vtable and returns
  `DM9051_HAL_ERR_NOT_READY`.
- The staging vtable implements argument checks and zero-length FIFO success,
  but its real register/FIFO transfers return `DM9051_HAL_ERR_NOT_READY`.
