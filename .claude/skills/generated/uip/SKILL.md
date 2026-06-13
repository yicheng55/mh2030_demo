---
name: uip
description: "Skill for the Uip area of mh2030_demo. 40 symbols across 11 files."
---

# Uip

40 symbols | 11 files | Cohesion: 72%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how dm9051_uip_last_rx_status, dm9051_uip_interrupt_mode, dm9051_uip_stack_poll work
- Modifying uip-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | dm9051_uip_last_rx_status, dm9051_uip_interrupt_mode, dm9051_uip_output, dm9051_uip_init, dm9051_uip_target_mode (+2) |
| `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip_stack.c` | dm9051_uip_stack_rx_pending_from_burst, dm9051_uip_stack_print_rx_burst, dm9051_uip_stack_poll, dm9051_uip_stack_send_if_needed, dm9051_uip_stack_drain_rx (+1) |
| `middlewares/3rd_party/uip/src/uip_arp.c` | uip_arp_timer, uip_arp_update, uip_arp_ipin, uip_arp_arpin, uip_arp_out (+1) |
| `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | dm9051_core_enter_critical, dm9051_core_exit_critical, dm9051_core_imr_value, dm9051_core_interrupt_take, dm9051_core_interrupt_reset |
| `middlewares/3rd_party/uip/src/timer.c` | timer_reset, timer_restart, timer_expired, timer_set |
| `ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.c` | dm9051_uip_adapter_poll, dm9051_netif_target_mode, dm9051_uip_adapter_init, dm9051_netif_open |
| `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c` | mh2030a_uip_target_mode, mh2030a_uip_net_init, mh2030a_uip_net_loop |
| `ModuleDemo/DM9051A/port/uip/clock-arch.c` | mh2030a_uip_update_time, mh2030a_uip_tick_isr |
| `ModuleDemo/DM9051A/USER/main_uip_mh2030a.c` | main |
| `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | dm9051_conf |

## Entry Points

Start here when exploring this area:

- **`dm9051_uip_last_rx_status`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c:63`
- **`dm9051_uip_interrupt_mode`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c:77`
- **`dm9051_uip_stack_poll`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip_stack.c:179`
- **`timer_reset`** (Function) — `middlewares/3rd_party/uip/src/timer.c:82`
- **`timer_restart`** (Function) — `middlewares/3rd_party/uip/src/timer.c:116`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `dm9051_uip_last_rx_status` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 63 |
| `dm9051_uip_interrupt_mode` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 77 |
| `dm9051_uip_stack_poll` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip_stack.c` | 179 |
| `timer_reset` | Function | `middlewares/3rd_party/uip/src/timer.c` | 82 |
| `timer_restart` | Function | `middlewares/3rd_party/uip/src/timer.c` | 116 |
| `timer_expired` | Function | `middlewares/3rd_party/uip/src/timer.c` | 133 |
| `uip_arp_timer` | Function | `middlewares/3rd_party/uip/src/uip_arp.c` | 140 |
| `dm9051_uip_output` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 68 |
| `dm9051_uip_adapter_poll` | Function | `ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.c` | 123 |
| `uip_arp_ipin` | Function | `middlewares/3rd_party/uip/src/uip_arp.c` | 233 |
| `uip_arp_arpin` | Function | `middlewares/3rd_party/uip/src/uip_arp.c` | 276 |
| `uip_arp_out` | Function | `middlewares/3rd_party/uip/src/uip_arp.c` | 352 |
| `main` | Function | `ModuleDemo/DM9051A/USER/main_uip_mh2030a.c` | 5 |
| `dm9051_netif_target_mode` | Function | `ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.c` | 29 |
| `dm9051_uip_adapter_init` | Function | `ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.c` | 116 |
| `mh2030a_uip_target_mode` | Function | `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c` | 9 |
| `mh2030a_uip_net_init` | Function | `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c` | 42 |
| `mh2030a_uip_net_loop` | Function | `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c` | 70 |
| `dm9051_conf` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 39 |
| `dm9051_uip_init` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/uip/dm9051_uip.c` | 17 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Cluster_141 | 2 calls |
| At32f415_dm9051 | 2 calls |
| Develop | 2 calls |
| Lwip | 2 calls |
| Dm9051_ | 2 calls |
| Dm9051_core_ | 1 calls |
| Uip_mh2030a_demo | 1 calls |

## How to Explore

1. `context({name: "dm9051_uip_last_rx_status"})` — see callers and callees
2. `query({query: "uip"})` — find related execution flows
3. Read key files listed above for implementation details
