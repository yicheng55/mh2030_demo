---
name: uip-mh2030a
description: "Skill for the Uip_mh2030a area of mh2030_demo. 43 symbols across 12 files."
---

# Uip_mh2030a

43 symbols | 12 files | Cohesion: 75%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how SPI_ReceiveData8, hal_read_reg, hal_write_reg work
- Modifying uip_mh2030a-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | dm9051_cs_low, dm9051_cs_high, spi_xfer, spi_finish, hal_read_reg (+3) |
| `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi_dma.c` | dm9051_cs_low, dm9051_cs_high, spi_xfer, spi_finish, hal_read_reg (+3) |
| `middlewares/3rd_party/uip/src/uip_arp.c` | uip_arp_init, uip_arp_timer, uip_arp_update, uip_arp_ipin, uip_arp_arpin (+1) |
| `ModuleDemo/DM9051A/port/uip_mh2030a/clock-arch.c` | mh2030a_uip_tick_init, clock_time, time_update, mh2030a_uip_tick_isr |
| `ModuleDemo/DM9051A/port/uip_mh2030a/netconf_mh2030a.c` | mh2030a_uip_net_init, uip_process_timers, uip_process_input, mh2030a_uip_net_loop |
| `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | dm9051_conf, dm9051_interrupt_get, dm9051_imr_disab, cspi_disble_irq |
| `middlewares/3rd_party/uip/src/timer.c` | timer_set, timer_reset, timer_restart, timer_expired |
| `Libraries/MH20xxLib/src/mh20xx_spi.c` | SPI_ReceiveData8 |
| `ModuleDemo/DM9051A/USER/main_uip_mh2030a.c` | main |
| `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_board.c` | mh2030a_uip_board_init |

## Entry Points

Start here when exploring this area:

- **`SPI_ReceiveData8`** (Function) — `Libraries/MH20xxLib/src/mh20xx_spi.c:652`
- **`hal_read_reg`** (Function) — `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c:153`
- **`hal_write_reg`** (Function) — `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c:165`
- **`hal_read_mem`** (Function) — `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c:174`
- **`hal_write_mem`** (Function) — `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c:187`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `SPI_ReceiveData8` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 652 |
| `hal_read_reg` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | 153 |
| `hal_write_reg` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | 165 |
| `hal_read_mem` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | 174 |
| `hal_write_mem` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | 187 |
| `hal_read_reg` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi_dma.c` | 252 |
| `hal_write_reg` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi_dma.c` | 264 |
| `hal_read_mem` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi_dma.c` | 273 |
| `hal_write_mem` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi_dma.c` | 282 |
| `main` | Function | `ModuleDemo/DM9051A/USER/main_uip_mh2030a.c` | 5 |
| `mh2030a_uip_tick_init` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/clock-arch.c` | 9 |
| `mh2030a_uip_board_init` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_board.c` | 67 |
| `mh2030a_uip_net_init` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/netconf_mh2030a.c` | 45 |
| `dm9051_conf` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 39 |
| `uip_init` | Function | `middlewares/3rd_party/uip/src/uip.c` | 377 |
| `uip_arp_init` | Function | `middlewares/3rd_party/uip/src/uip_arp.c` | 123 |
| `clock_time` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/clock-arch.c` | 26 |
| `timer_set` | Function | `middlewares/3rd_party/uip/src/timer.c` | 62 |
| `timer_reset` | Function | `middlewares/3rd_party/uip/src/timer.c` | 82 |
| `timer_restart` | Function | `middlewares/3rd_party/uip/src/timer.c` | 116 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 9 calls |
| Bsp | 7 calls |
| Cluster_115 | 2 calls |
| Cluster_116 | 1 calls |
| Develop | 1 calls |

## How to Explore

1. `gitnexus_context({name: "SPI_ReceiveData8"})` — see callers and callees
2. `gitnexus_query({query: "uip_mh2030a"})` — find related execution flows
3. Read key files listed above for implementation details
