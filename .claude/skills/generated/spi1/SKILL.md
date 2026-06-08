---
name: spi1
description: "Skill for the SPI1 area of mh2030_demo. 15 symbols across 1 files."
---

# SPI1

15 symbols | 1 files | Cohesion: 100%

## When to Use

- Working with code in `drivers/`
- Understanding how hal_read_reg, hal_write_reg, hal_read_mem work
- Modifying spi1-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | hal_stdpin_lo, hal_stdpin_hi, hal_spi_wait_flag, hal_spi_clear_rx, hal_spi_finish (+10) |

## Entry Points

Start here when exploring this area:

- **`hal_read_reg`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c:293`
- **`hal_write_reg`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c:308`
- **`hal_read_mem`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c:321`
- **`hal_write_mem`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c:334`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `hal_read_reg` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 293 |
| `hal_write_reg` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 308 |
| `hal_read_mem` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 321 |
| `hal_write_mem` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 334 |
| `hal_stdpin_lo` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 135 |
| `hal_stdpin_hi` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 144 |
| `hal_spi_wait_flag` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 149 |
| `hal_spi_clear_rx` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 161 |
| `hal_spi_finish` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 176 |
| `hal_spi_writexfer` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 188 |
| `hal_spi_readxfer` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 213 |
| `hal_spi_data_read` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 239 |
| `hal_spi_data_write` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 250 |
| `hal_spi_mem_read` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 262 |
| `hal_spi_mem_write` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/hal/SPI1/at32f403a_spi1.c` | 277 |

## How to Explore

1. `gitnexus_context({name: "hal_read_reg"})` — see callers and callees
2. `gitnexus_query({query: "spi1"})` — find related execution flows
3. Read key files listed above for implementation details
