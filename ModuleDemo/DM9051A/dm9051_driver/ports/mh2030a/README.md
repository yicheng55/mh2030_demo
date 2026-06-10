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

