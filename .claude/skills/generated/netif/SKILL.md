---
name: netif
description: "Skill for the Netif area of mh2030_demo. 33 symbols across 8 files."
---

# Netif

33 symbols | 8 files | Cohesion: 83%

## When to Use

- Working with code in `middlewares/`
- Understanding how bridgeif_fdb_update_src, bridgeif_fdb_get_dst_ports, lowpan6_tmr work
- Modifying netif-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif.c` | bridgeif_find_dst_ports, bridgeif_is_local_mac, bridgeif_send_to_port, bridgeif_send_to_ports, bridgeif_output (+2) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_ble.c` | ble_addr_to_eui64, rfc7668_set_addr, rfc7668_set_local_addr_eui64, rfc7668_set_local_addr_mac48, rfc7668_set_peer_addr_eui64 (+2) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6.c` | lowpan6_parse_iee802154_header, free_reass_datagram, dequeue_datagram, lowpan6_tmr, lowpan6_input (+1) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_common.c` | lowpan6_decompress, lowpan6_get_address_mode, lowpan6_get_address_mode_mc, lowpan6_context_lookup, lowpan6_compress_headers |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/slipif.c` | slipif_output, slipif_output_v4, slipif_output_v6 |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif_fdb.c` | bridgeif_fdb_update_src, bridgeif_fdb_get_dst_ports |
| `middlewares/3rd_party/lwip-2.1.2/src/api/tcpip.c` | tcpip_inpkt, tcpip_input |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/zepif.c` | zep_lowpan_timer |

## Entry Points

Start here when exploring this area:

- **`bridgeif_fdb_update_src`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif_fdb.c:74`
- **`bridgeif_fdb_get_dst_ports`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif_fdb.c:126`
- **`lowpan6_tmr`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6.c:318`
- **`lowpan6_input`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6.c:644`
- **`lowpan6_decompress`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_common.c:777`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `bridgeif_fdb_update_src` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif_fdb.c` | 74 |
| `bridgeif_fdb_get_dst_ports` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif_fdb.c` | 126 |
| `lowpan6_tmr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6.c` | 318 |
| `lowpan6_input` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6.c` | 644 |
| `lowpan6_decompress` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_common.c` | 777 |
| `ble_addr_to_eui64` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_ble.c` | 108 |
| `rfc7668_set_local_addr_eui64` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_ble.c` | 174 |
| `rfc7668_set_local_addr_mac48` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_ble.c` | 185 |
| `rfc7668_set_peer_addr_eui64` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_ble.c` | 196 |
| `rfc7668_set_peer_addr_mac48` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_ble.c` | 207 |
| `tcpip_inpkt` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/tcpip.c` | 238 |
| `tcpip_input` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/tcpip.c` | 281 |
| `tcpip_6lowpan_input` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6.c` | 912 |
| `tcpip_rfc7668_input` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_ble.c` | 438 |
| `lowpan6_get_address_mode` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_common.c` | 63 |
| `lowpan6_compress_headers` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/lowpan6_common.c` | 130 |
| `bridgeif_find_dst_ports` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif.c` | 194 |
| `bridgeif_is_local_mac` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif.c` | 224 |
| `bridgeif_send_to_port` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif.c` | 247 |
| `bridgeif_send_to_ports` | Function | `middlewares/3rd_party/lwip-2.1.2/src/netif/bridgeif.c` | 272 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 5 calls |
| Http | 2 calls |
| Sntp | 1 calls |
| Sockets | 1 calls |
| Api | 1 calls |

## How to Explore

1. `context({name: "bridgeif_fdb_update_src"})` — see callers and callees
2. `query({query: "netif"})` — find related execution flows
3. Read key files listed above for implementation details
