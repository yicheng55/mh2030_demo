---
name: mh2030a
description: "Skill for the Mh2030a area of mh2030_demo. 52 symbols across 17 files."
---

# Mh2030a

52 symbols | 17 files | Cohesion: 76%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how SPI_SendData8, SPI_ReceiveData8, hal_read_reg work
- Modifying mh2030a-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | dm9051_mh2030a_select, dm9051_mh2030a_deselect, dm9051_mh2030a_wait_spi_idle, dm9051_mh2030a_transfer_byte, dm9051_mh2030a_finish_transfer (+7) |
| `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi_dma.c` | select_dm9051, deselect_dm9051, wait_for_spi_idle, transfer_spi_byte, finish_spi_transfer (+4) |
| `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c` | select_dm9051, deselect_dm9051, transfer_spi_byte, finish_spi_transfer, hal_read_reg (+3) |
| `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_int.c` | dm9051_mh2030a_irq_handler, EXTI4_15_IRQHandler, dm9051_mh2030a_irq_attach_device, dm9051_mh2030a_irq_detach_device |
| `Libraries/MH20xxLib/src/mh20xx_spi.c` | SPI_SendData8, SPI_ReceiveData8, SPI_I2S_GetFlagStatus |
| `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1_dma.c` | dm9051_mh2030a_dma_read_mem, dm9051_mh2030a_dma_write_mem |
| `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | dm9051_core_interrupt_set, dm9051_core_default_config |
| `ModuleDemo/DM9051A/dm9051_driver/examples/uip_mh2030a_demo/dm9051_uip_mh2030a_smoke.c` | dm9051_uip_mh2030a_hal_status_to_core_status, dm9051_uip_mh2030a_smoke_open |
| `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/mh2030a_uip_clock.c` | mh2030a_uip_tick_isr, mh2030a_uip_update_time |
| `ModuleDemo/SPI/SPI_Int/USER/main.c` | SPI1_IRQHandler |

## Entry Points

Start here when exploring this area:

- **`SPI_SendData8`** (Function) — `Libraries/MH20xxLib/src/mh20xx_spi.c:619`
- **`SPI_ReceiveData8`** (Function) — `Libraries/MH20xxLib/src/mh20xx_spi.c:652`
- **`hal_read_reg`** (Function) — `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c:153`
- **`hal_write_reg`** (Function) — `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c:165`
- **`hal_read_mem`** (Function) — `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c:174`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `SPI_SendData8` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 619 |
| `SPI_ReceiveData8` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 652 |
| `hal_read_reg` | Function | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c` | 153 |
| `hal_write_reg` | Function | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c` | 165 |
| `hal_read_mem` | Function | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c` | 174 |
| `hal_write_mem` | Function | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi.c` | 187 |
| `SPI1_IRQHandler` | Function | `ModuleDemo/SPI/SPI_Int/USER/main.c` | 166 |
| `SPI_I2S_GetFlagStatus` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 1092 |
| `hal_read_reg` | Function | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi_dma.c` | 252 |
| `hal_write_reg` | Function | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi_dma.c` | 264 |
| `hal_read_mem` | Function | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi_dma.c` | 273 |
| `hal_write_mem` | Function | `ModuleDemo/DM9051A/port/mh2030a/mh2030a_dm9051_spi_dma.c` | 282 |
| `dm9051_mh2030a_select` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 26 |
| `dm9051_mh2030a_deselect` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 31 |
| `dm9051_mh2030a_wait_spi_idle` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 36 |
| `dm9051_mh2030a_transfer_byte` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 56 |
| `dm9051_mh2030a_finish_transfer` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 89 |
| `dm9051_mh2030a_polling_read_reg` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 202 |
| `dm9051_mh2030a_polling_write_reg` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 240 |
| `dm9051_mh2030a_polling_read_mem` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 269 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → Dm9051_mh2030a_config_is_valid` | cross_community | 4 |
| `Main → Dm9051_mh2030a_config_is_valid` | cross_community | 4 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 15 calls |
| Dm9051_core_ | 1 calls |

## How to Explore

1. `context({name: "SPI_SendData8"})` — see callers and callees
2. `query({query: "mh2030a"})` — find related execution flows
3. Read key files listed above for implementation details
