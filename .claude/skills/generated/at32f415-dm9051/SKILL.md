---
name: at32f415-dm9051
description: "Skill for the At32f415_dm9051 area of mh2030_demo. 13 symbols across 3 files."
---

# At32f415_dm9051

13 symbols | 3 files | Cohesion: 88%

## When to Use

- Working with code in `drivers/`
- Understanding how ethernetif_output, dm9051_tx, cspi_tx_packet_len work
- Modifying at32f415_dm9051-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | dm9051_tx, cspi_tx_packet_len, cspi_tx_write, cspi_tx_req, dm9051_rx (+2) |
| `middlewares/3rd_party/uip/port/at32f415_dm9051/ethernetif.c` | low_level_output, ethernetif_output, low_level_input, ethernetif_input |
| `ModuleDemo/DM9051A/port/uip_mh2030a/ethernetif_mh2030a.c` | ethernetif_output, ethernetif_input |

## Entry Points

Start here when exploring this area:

- **`ethernetif_output`** (Function) — `ModuleDemo/DM9051A/port/uip_mh2030a/ethernetif_mh2030a.c:14`
- **`dm9051_tx`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:110`
- **`cspi_tx_packet_len`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:912`
- **`cspi_tx_write`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:919`
- **`cspi_tx_req`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:925`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `ethernetif_output` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/ethernetif_mh2030a.c` | 14 |
| `dm9051_tx` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 110 |
| `cspi_tx_packet_len` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 912 |
| `cspi_tx_write` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 919 |
| `cspi_tx_req` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 925 |
| `ethernetif_output` | Function | `middlewares/3rd_party/uip/port/at32f415_dm9051/ethernetif.c` | 155 |
| `ethernetif_input` | Function | `ModuleDemo/DM9051A/port/uip_mh2030a/ethernetif_mh2030a.c` | 9 |
| `dm9051_rx` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 84 |
| `cspi_rx_read` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 847 |
| `cspi_rx_discard` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 861 |
| `ethernetif_input` | Function | `middlewares/3rd_party/uip/port/at32f415_dm9051/ethernetif.c` | 134 |
| `low_level_output` | Function | `middlewares/3rd_party/uip/port/at32f415_dm9051/ethernetif.c` | 117 |
| `low_level_input` | Function | `middlewares/3rd_party/uip/port/at32f415_dm9051/ethernetif.c` | 98 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Cluster_123 | 2 calls |
| Cluster_124 | 1 calls |

## How to Explore

1. `gitnexus_context({name: "ethernetif_output"})` — see callers and callees
2. `gitnexus_query({query: "at32f415_dm9051"})` — find related execution flows
3. Read key files listed above for implementation details
