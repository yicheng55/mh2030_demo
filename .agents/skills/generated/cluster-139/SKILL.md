---
name: cluster-139
description: "Skill for the Cluster_139 area of mh2030_demo. 15 symbols across 4 files."
---

# Cluster_139

15 symbols | 4 files | Cohesion: 92%

## When to Use

- Working with code in `middlewares/`
- Understanding how uip_fw_forward, uip_neighbor_add, uip_split_output work
- Modifying cluster_139-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/uip/src/uip.c` | uip_add32, chksum, uip_chksum, uip_ipchksum, upper_layer_chksum (+6) |
| `middlewares/3rd_party/uip/src/uip-fw.c` | time_exceeded, uip_fw_forward |
| `middlewares/3rd_party/uip/src/uip-neighbor.c` | uip_neighbor_add |
| `middlewares/3rd_party/uip/src/uip-split.c` | uip_split_output |

## Entry Points

Start here when exploring this area:

- **`uip_fw_forward`** (Function) — `middlewares/3rd_party/uip/src/uip-fw.c:404`
- **`uip_neighbor_add`** (Function) — `middlewares/3rd_party/uip/src/uip-neighbor.c:83`
- **`uip_split_output`** (Function) — `middlewares/3rd_party/uip/src/uip-split.c:47`
- **`uip_add32`** (Function) — `middlewares/3rd_party/uip/src/uip.c:247`
- **`uip_chksum`** (Function) — `middlewares/3rd_party/uip/src/uip.c:309`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `uip_fw_forward` | Function | `middlewares/3rd_party/uip/src/uip-fw.c` | 404 |
| `uip_neighbor_add` | Function | `middlewares/3rd_party/uip/src/uip-neighbor.c` | 83 |
| `uip_split_output` | Function | `middlewares/3rd_party/uip/src/uip-split.c` | 47 |
| `uip_add32` | Function | `middlewares/3rd_party/uip/src/uip.c` | 247 |
| `uip_chksum` | Function | `middlewares/3rd_party/uip/src/uip.c` | 309 |
| `uip_ipchksum` | Function | `middlewares/3rd_party/uip/src/uip.c` | 316 |
| `uip_icmp6chksum` | Function | `middlewares/3rd_party/uip/src/uip.c` | 354 |
| `uip_tcpchksum` | Function | `middlewares/3rd_party/uip/src/uip.c` | 362 |
| `uip_udpchksum` | Function | `middlewares/3rd_party/uip/src/uip.c` | 369 |
| `uip_process` | Function | `middlewares/3rd_party/uip/src/uip.c` | 680 |
| `time_exceeded` | Function | `middlewares/3rd_party/uip/src/uip-fw.c` | 220 |
| `chksum` | Function | `middlewares/3rd_party/uip/src/uip.c` | 278 |
| `upper_layer_chksum` | Function | `middlewares/3rd_party/uip/src/uip.c` | 327 |
| `uip_reass` | Function | `middlewares/3rd_party/uip/src/uip.c` | 553 |
| `uip_add_rcv_nxt` | Function | `middlewares/3rd_party/uip/src/uip.c` | 670 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Develop | 3 calls |
| Cluster_138 | 1 calls |

## How to Explore

1. `gitnexus_context({name: "uip_fw_forward"})` — see callers and callees
2. `gitnexus_query({query: "cluster_139"})` — find related execution flows
3. Read key files listed above for implementation details
