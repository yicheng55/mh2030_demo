---
name: uip-mh2030a
description: "Skill for the Uip_mh2030a area of mh2030_demo. 56 symbols across 14 files."
---

# Uip_mh2030a

56 symbols | 14 files | Cohesion: 77%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how mh2030a_uip_net_loop, conf_ext_line, hal_active_interrupt_mode work
- Modifying uip_mh2030a-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | conf_ext_line, hal_active_interrupt_mode, cspi_soft_default, dm9051_interrupt_get, dm9051_interrupt_reset (+7) |
| `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi_dma.c` | select_dm9051, deselect_dm9051, wait_for_spi_idle, transfer_spi_byte, finish_spi_transfer (+4) |
| `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | select_dm9051, deselect_dm9051, transfer_spi_byte, finish_spi_transfer, hal_read_reg (+3) |
| `middlewares/3rd_party/uip/src/uip_arp.c` | uip_arp_init, uip_arp_timer, uip_arp_update, uip_arp_ipin, uip_arp_arpin (+1) |
| `ModuleDemo/DM9051A/port/uip_mh2030a/netconf_mh2030a.c` | mh2030a_uip_net_loop, mh2030a_uip_net_init, process_uip_periodic_timers, process_received_ethernet_frame |
| `ModuleDemo/DM9051A/port/uip_mh2030a/clock-arch.c` | mh2030a_uip_tick_init, clock_time, mh2030a_uip_update_time, mh2030a_uip_tick_isr |
| `middlewares/3rd_party/uip/src/timer.c` | timer_set, timer_reset, timer_restart, timer_expired |
| `Libraries/MH20xxLib/src/mh20xx_spi.c` | SPI_SendData8, SPI_ReceiveData8, SPI_I2S_GetFlagStatus |
| `ModuleDemo/SPI/SPI_Int/USER/main.c` | SPI1_IRQHandler |
| `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | DM9051A_WaitSpiIdle |

## Entry Points

Start here when exploring this area:

- **`mh2030a_uip_net_loop`** (Function) — `ModuleDemo/DM9051A/port/uip_mh2030a/netconf_mh2030a.c:153`
- **`conf_ext_line`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:42`
- **`hal_active_interrupt_mode`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:176`
- **`cspi_soft_default`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:355`
- **`dm9051_interrupt_get`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:498`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `mh2030a_uip_net_loop` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/netconf_mh2030a.c` | 153 |
| `conf_ext_line` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 42 |
| `hal_active_interrupt_mode` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 176 |
| `cspi_soft_default` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 355 |
| `dm9051_interrupt_get` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 498 |
| `dm9051_interrupt_reset` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 510 |
| `dm9051_isr_enab` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 588 |
| `dm9051_imr_disab` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 595 |
| `dm9051_imr_enab` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 600 |
| `cspi_set_imr` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 605 |
| `cspi_disble_irq` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 610 |
| `cspi_enable_irq` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 615 |
| `SPI_SendData8` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 619 |
| `SPI_ReceiveData8` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 652 |
| `hal_read_reg` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | 153 |
| `hal_write_reg` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | 165 |
| `hal_read_mem` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | 174 |
| `hal_write_mem` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi.c` | 187 |
| `SPI1_IRQHandler` | Function | `ModuleDemo/SPI/SPI_Int/USER/main.c` | 166 |
| `SPI_I2S_GetFlagStatus` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 1092 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 9 calls |
| Cluster_115 | 1 calls |
| Develop | 1 calls |

## How to Explore

1. `context({name: "mh2030a_uip_net_loop"})` — see callers and callees
2. `query({query: "uip_mh2030a"})` — find related execution flows
3. Read key files listed above for implementation details
