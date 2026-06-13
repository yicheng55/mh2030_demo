---
name: uip
description: "Skill for the Uip area of mh2030_demo. 58 symbols across 13 files."
---

# Uip

58 symbols | 13 files | Cohesion: 76%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how dm9051_uip_interrupt_reset, dm9051_core_phy_write, dm9051_core_interrupt_reset work
- Modifying uip-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | dm9051_core_write_reg, dm9051_core_set_par, dm9051_core_set_mar, dm9051_core_imr_value, dm9051_core_rcr_value (+16) |
| `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | dm9051_uip_interrupt_reset, dm9051_uip_interrupt_mode, dm9051_uip_interrupt_take, dm9051_uip_init, dm9051_uip_target_mode (+2) |
| `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip_stack.c` | dm9051_uip_stack_rx_pending_from_burst, dm9051_uip_stack_print_rx_burst, dm9051_uip_stack_poll, dm9051_uip_stack_init, dm9051_uip_stack_send_if_needed (+1) |
| `middlewares/3rd_party/uip/src/uip_arp.c` | uip_arp_timer, uip_arp_init, uip_arp_update, uip_arp_ipin, uip_arp_arpin (+1) |
| `middlewares/3rd_party/uip/src/timer.c` | timer_reset, timer_restart, timer_expired, timer_set |
| `ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.c` | dm9051_netif_open, dm9051_uip_adapter_poll, dm9051_netif_target_mode, dm9051_uip_adapter_init |
| `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c` | mh2030a_uip_target_mode, mh2030a_uip_net_init, mh2030a_uip_net_loop |
| `ModuleDemo/DM9051A/port/uip/clock-arch.c` | mh2030a_uip_update_time, mh2030a_uip_tick_isr |
| `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | dm9051_lwip_init |
| `middlewares/3rd_party/uip/src/uip.c` | uip_init |

## Entry Points

Start here when exploring this area:

- **`dm9051_uip_interrupt_reset`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c:79`
- **`dm9051_core_phy_write`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c:962`
- **`dm9051_core_interrupt_reset`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c:1014`
- **`dm9051_uip_interrupt_mode`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c:57`
- **`dm9051_uip_interrupt_take`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c:66`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `dm9051_uip_interrupt_reset` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 79 |
| `dm9051_core_phy_write` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 962 |
| `dm9051_core_interrupt_reset` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 1014 |
| `dm9051_uip_interrupt_mode` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 57 |
| `dm9051_uip_interrupt_take` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 66 |
| `dm9051_uip_stack_poll` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip_stack.c` | 163 |
| `dm9051_core_interrupt_take` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 1000 |
| `timer_reset` | Function | `middlewares/3rd_party/uip/src/timer.c` | 82 |
| `timer_restart` | Function | `middlewares/3rd_party/uip/src/timer.c` | 116 |
| `timer_expired` | Function | `middlewares/3rd_party/uip/src/timer.c` | 133 |
| `uip_arp_timer` | Function | `middlewares/3rd_party/uip/src/uip_arp.c` | 140 |
| `dm9051_lwip_init` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 11 |
| `dm9051_uip_init` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 16 |
| `dm9051_uip_target_mode` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 92 |
| `dm9051_uip_stack_init` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip_stack.c` | 108 |
| `dm9051_netif_device_is_valid` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 802 |
| `dm9051_netif_open` | Function | `ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.c` | 49 |
| `timer_set` | Function | `middlewares/3rd_party/uip/src/timer.c` | 62 |
| `uip_init` | Function | `middlewares/3rd_party/uip/src/uip.c` | 377 |
| `uip_arp_init` | Function | `middlewares/3rd_party/uip/src/uip_arp.c` | 123 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Uip_mh2030a_demo | 5 calls |
| Cluster_119 | 2 calls |
| At32f415_dm9051 | 2 calls |
| Develop | 2 calls |
| Cluster_120 | 1 calls |
| Dm9051_ | 1 calls |

## How to Explore

1. `context({name: "dm9051_uip_interrupt_reset"})` — see callers and callees
2. `query({query: "uip"})` — find related execution flows
3. Read key files listed above for implementation details
