---
name: udp-app
description: "Skill for the Udp_app area of mh2030_demo. 9 symbols across 5 files."
---

# Udp_app

9 symbols | 5 files | Cohesion: 80%

## When to Use

- Working with code in `apps/`
- Understanding how udp_server_connected, udp_ServerSendEndCallBack, dhcpc_init work
- Modifying udp_app-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/udp_app/udp_app.c` | udp_send_data, udp_recv_appcall, udp_recv_connect, udp_send_connect |
| `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/UDP/udp_t.c` | udp_server_connected, udp_ServerSendEndCallBack |
| `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | dhcpc_init |
| `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/resolv/resolv.c` | resolv_conf |
| `middlewares/3rd_party/uip/src/uip.c` | uip_udp_new |

## Entry Points

Start here when exploring this area:

- **`udp_server_connected`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/UDP/udp_t.c:33`
- **`udp_ServerSendEndCallBack`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/UDP/udp_t.c:172`
- **`dhcpc_init`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c:321`
- **`resolv_conf`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/resolv/resolv.c:436`
- **`udp_send_data`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/udp_app/udp_app.c:19`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `udp_server_connected` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/UDP/udp_t.c` | 33 |
| `udp_ServerSendEndCallBack` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/UDP/udp_t.c` | 172 |
| `dhcpc_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/dhcpc/dhcpc.c` | 321 |
| `resolv_conf` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/resolv/resolv.c` | 436 |
| `udp_send_data` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/udp_app/udp_app.c` | 19 |
| `udp_recv_appcall` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/udp_app/udp_app.c` | 31 |
| `udp_recv_connect` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/udp_app/udp_app.c` | 67 |
| `udp_send_connect` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/udp_app/udp_app.c` | 106 |
| `uip_udp_new` | Function | `middlewares/3rd_party/uip/src/uip.c` | 471 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Develop | 2 calls |
| AT - do | 1 calls |

## How to Explore

1. `gitnexus_context({name: "udp_server_connected"})` — see callers and callees
2. `gitnexus_query({query: "udp_app"})` — find related execution flows
3. Read key files listed above for implementation details
