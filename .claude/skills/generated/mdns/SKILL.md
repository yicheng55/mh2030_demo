---
name: mdns
description: "Skill for the Mdns area of mh2030_demo. 44 symbols across 2 files."
---

# Mdns

44 symbols | 2 files | Cohesion: 62%

## When to Use

- Working with code in `middlewares/`
- Understanding how mdns_resp_announce, mdns_readname, mdns_domain_eq work
- Modifying mdns-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | mdns_send_outpacket, mdns_probe, mdns_build_host_domain, mdns_add_answer, mdns_add_a_answer (+38) |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/mdns/test_mdns.c` | START_TEST |

## Entry Points

Start here when exploring this area:

- **`mdns_resp_announce`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c:2315`
- **`mdns_readname`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c:419`
- **`mdns_domain_eq`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c:453`
- **`mdns_compress_domain`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c:786`
- **`START_TEST`** (Function) — `middlewares/3rd_party/lwip-2.1.2/test/unit/mdns/test_mdns.c:55`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `mdns_resp_announce` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2315 |
| `mdns_readname` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 419 |
| `mdns_domain_eq` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 453 |
| `mdns_compress_domain` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 786 |
| `START_TEST` | Function | `middlewares/3rd_party/lwip-2.1.2/test/unit/mdns/test_mdns.c` | 55 |
| `mdns_domain_add_label` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 314 |
| `mdns_resp_add_service_txtitem` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2300 |
| `mdns_resp_rename_netif` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2154 |
| `mdns_resp_add_service` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2190 |
| `mdns_resp_rename_service` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2265 |
| `mdns_resp_restart` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2354 |
| `mdns_send_outpacket` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 286 |
| `mdns_probe` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 287 |
| `mdns_build_host_domain` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 601 |
| `mdns_add_answer` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 966 |
| `mdns_add_a_answer` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 1169 |
| `mdns_add_hostv4_ptr_answer` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 1179 |
| `mdns_add_aaaa_answer` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 1192 |
| `mdns_add_hostv6_ptr_answer` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 1202 |
| `mdns_add_servicename_ptr_answer` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 1225 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 22 calls |
| Http | 5 calls |
| Api | 3 calls |
| Ipv4 | 2 calls |
| Sntp | 2 calls |

## How to Explore

1. `context({name: "mdns_resp_announce"})` — see callers and callees
2. `query({query: "mdns"})` — find related execution flows
3. Read key files listed above for implementation details
