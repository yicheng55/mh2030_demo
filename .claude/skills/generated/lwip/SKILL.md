---
name: lwip
description: "Skill for the Lwip area of mh2030_demo. 39 symbols across 6 files."
---

# Lwip

39 symbols | 6 files | Cohesion: 72%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how dm9051_core_send, dm9051_core_phy_read, dm9051_uip_mh2030a_smoke_send work
- Modifying lwip-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | dm9051_core_hal_status, dm9051_core_read_reg, dm9051_core_write_mem, dm9051_core_phy_read_raw, dm9051_core_tx_pad_len (+12) |
| `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | dm9051_lwip_packet_send, dm9051_lwip_packet_receive, dm9051_lwip_hw_init, dm9051_init, dm9051_if_init (+10) |
| `ModuleDemo/DM9051A/dm9051_driver/examples/uip_mh2030a_demo/dm9051_uip_mh2030a_smoke.c` | dm9051_uip_mh2030a_smoke_send, dm9051_uip_mh2030a_smoke_receive |
| `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_int.c` | dm9051_mh2030a_irq_attach_device, dm9051_mh2030a_irq_count |
| `ModuleDemo/DM9051A/dm9051_driver/examples/uip_mh2030a_demo/main_uip_mh2030a_demo.c` | dm9051_demo_read_link_up, dm9051_demo_handle_link_detection |
| `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | dm9051_mh2030a_default_config |

## Entry Points

Start here when exploring this area:

- **`dm9051_core_send`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c:1117`
- **`dm9051_core_phy_read`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c:1153`
- **`dm9051_uip_mh2030a_smoke_send`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/examples/uip_mh2030a_demo/dm9051_uip_mh2030a_smoke.c:112`
- **`dm9051_core_receive`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c:1046`
- **`dm9051_core_receive_ex`** (Function) — `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c:1060`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `dm9051_core_send` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 1117 |
| `dm9051_core_phy_read` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 1153 |
| `dm9051_uip_mh2030a_smoke_send` | Function | `ModuleDemo/DM9051A/dm9051_driver/examples/uip_mh2030a_demo/dm9051_uip_mh2030a_smoke.c` | 112 |
| `dm9051_core_receive` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 1046 |
| `dm9051_core_receive_ex` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 1060 |
| `dm9051_uip_mh2030a_smoke_receive` | Function | `ModuleDemo/DM9051A/dm9051_driver/examples/uip_mh2030a_demo/dm9051_uip_mh2030a_smoke.c` | 103 |
| `dm9051_init` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 149 |
| `dm9051_if_init` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 206 |
| `dm9051_lwip_init` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 381 |
| `dm9051_core_mac` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 1269 |
| `dm9051_mh2030a_irq_attach_device` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_int.c` | 75 |
| `dm9051_mh2030a_default_config` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | 361 |
| `dm9051_packet_send` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 150 |
| `dm9051_packet_receive` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 151 |
| `dm9051_lwip_input` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 303 |
| `dm9051_lwip_poll` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 387 |
| `dm9051_lwip_link_is_up` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 131 |
| `dm9051_link_is_up` | Function | `ModuleDemo/DM9051A/dm9051_driver/adapters/lwip/dm9051_lwip.c` | 153 |
| `dm9051_core_link_is_up` | Function | `ModuleDemo/DM9051A/dm9051_driver/core/src/dm9051_core.c` | 1182 |
| `dm9051_mh2030a_irq_count` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/dm9051_hal_mh2030a_int.c` | 90 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → Dm9051_link_is_up` | cross_community | 4 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Dm9051_core_ | 6 calls |
| Ppp | 4 calls |
| Mh2030a | 3 calls |
| Dm9051_ | 2 calls |

## How to Explore

1. `context({name: "dm9051_core_send"})` — see callers and callees
2. `query({query: "lwip"})` — find related execution flows
3. Read key files listed above for implementation details
