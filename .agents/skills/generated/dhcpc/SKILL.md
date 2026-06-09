---
name: dhcpc
description: "Skill for the Dhcpc area of mh2030_demo. 10 symbols across 1 files."
---

# Dhcpc

10 symbols | 1 files | Cohesion: 68%

## When to Use

- Working with code in `apps/`
- Understanding how add_msg_type, add_req_options, create_msg work
- Modifying dhcpc-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | add_msg_type, add_req_options, create_msg, send_discover, add_server_id (+5) |

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `add_msg_type` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 96 |
| `add_req_options` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 123 |
| `create_msg` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 141 |
| `send_discover` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 166 |
| `add_server_id` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 105 |
| `add_req_ipaddr` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 114 |
| `add_end` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 134 |
| `send_request` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 181 |
| `parse_options` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 197 |
| `parse_msg` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 232 |

## Connected Areas

| Area | Connections |
|------|-------------|
| UDP | 2 calls |

## How to Explore

1. `gitnexus_context({name: "add_msg_type"})` — see callers and callees
2. `gitnexus_query({query: "dhcpc"})` — find related execution flows
3. Read key files listed above for implementation details
