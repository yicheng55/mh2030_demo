---
name: tcp-2
description: "Skill for the Tcp_ area of mh2030_demo. 27 symbols across 3 files."
---

# Tcp_

27 symbols | 3 files | Cohesion: 55%

## When to Use

- Working with code in `middlewares/`
- Understanding how tcp_rst, tcp_send_empty_ack, tcp_keepalive work
- Modifying tcp_-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | tcp_get_num_sacks, tcp_build_sack_option, tcp_output_alloc_header_common, tcp_output_alloc_header, tcp_output_fill_options (+11) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_in.c` | tcp_timewait_input, tcp_receive, tcp_add_sack, tcp_remove_sacks_lt, tcp_remove_sacks_gt (+2) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | tcp_segs_free, tcp_seg_free, tcp_seg_copy, tcp_eff_send_mss_netif |

## Entry Points

Start here when exploring this area:

- **`tcp_rst`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c:1978`
- **`tcp_send_empty_ack`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c:2017`
- **`tcp_keepalive`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c:2076`
- **`tcp_zero_window_probe`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c:2114`
- **`tcp_segs_free`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c:1606`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `tcp_rst` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1978 |
| `tcp_send_empty_ack` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 2017 |
| `tcp_keepalive` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 2076 |
| `tcp_zero_window_probe` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 2114 |
| `tcp_segs_free` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1606 |
| `tcp_seg_free` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1621 |
| `tcp_seg_copy` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1660 |
| `tcp_eff_send_mss_netif` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2236 |
| `tcp_rexmit` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1722 |
| `tcp_rexmit_fast` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1781 |
| `tcp_timewait_input` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_in.c` | 95 |
| `tcp_get_num_sacks` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1160 |
| `tcp_build_sack_option` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1191 |
| `tcp_output_alloc_header_common` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1816 |
| `tcp_output_alloc_header` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1851 |
| `tcp_output_fill_options` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1870 |
| `tcp_output_control_segment` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1919 |
| `tcp_receive` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_in.c` | 91 |
| `tcp_add_sack` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_in.c` | 100 |
| `tcp_remove_sacks_lt` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_in.c` | 101 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 16 calls |
| Ipv4 | 7 calls |
| Api | 3 calls |
| Cluster_242 | 1 calls |
| Tcp | 1 calls |

## How to Explore

1. `context({name: "tcp_rst"})` — see callers and callees
2. `query({query: "tcp_"})` — find related execution flows
3. Read key files listed above for implementation details
