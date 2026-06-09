---
name: tcp
description: "Skill for the Tcp area of mh2030_demo. 76 symbols across 22 files."
---

# Tcp

76 symbols | 22 files | Cohesion: 80%

## When to Use

- Working with code in `middlewares/`
- Understanding how pbuf_header, tcp_abandon, tcp_abort work
- Modifying tcp-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | tcp_new_port, tcp_close_shutdown_fin, tcp_abandon, tcp_abort, tcp_bind (+12) |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/test_tcp.c` | test_tcp_tmr, START_TEST, test_tcp_recv_expect1byte, check_seqnos, test_tcp_tx_full_window_lost (+6) |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/test_tcp_oos.c` | tcp_oos_count, tcp_oos_pbuf_count, tcp_oos_seg_seqno, tcp_oos_seg_tcplen, tcp_oos_tcplen (+6) |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/tcp_helper.c` | tcp_create_segment, tcp_create_rx_segment, tcp_create_rx_segment_wnd, tcp_set_state, test_tcp_new_counters_pcb (+4) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | tcp_pbuf_prealloc, tcp_seg_add_chksum, tcp_write_checks, tcp_write, tcp_send_fin (+2) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp_tcp.c` | altcp_tcp_bind, altcp_tcp_connect, altcp_tcp_abort, altcp_tcp_write, altcp_tcp_output |
| `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c` | pbuf_header |
| `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_in.c` | tcp_listen_input |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/api/test_sockets.c` | sockets_suite |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/core/test_def.c` | def_suite |

## Entry Points

Start here when exploring this area:

- **`pbuf_header`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c:644`
- **`tcp_abandon`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c:561`
- **`tcp_abort`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c:636`
- **`tcp_bind`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c:659`
- **`tcp_connect`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c:1065`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `pbuf_header` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c` | 644 |
| `tcp_abandon` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 561 |
| `tcp_abort` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 636 |
| `tcp_bind` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 659 |
| `tcp_connect` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1065 |
| `tcp_fasttmr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1477 |
| `tcp_txnow` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1524 |
| `tcp_alloc` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1832 |
| `tcp_new` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1943 |
| `tcp_next_iss` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2213 |
| `tcp_ext_arg_invoke_callbacks_passive_open` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2664 |
| `tcp_write` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 388 |
| `tcp_send_fin` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 999 |
| `tcp_enqueue_flags` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1030 |
| `tcp_output` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp_out.c` | 1235 |
| `tcp_create_segment` | Function | `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/tcp_helper.c` | 110 |
| `tcp_create_rx_segment` | Function | `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/tcp_helper.c` | 123 |
| `tcp_create_rx_segment_wnd` | Function | `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/tcp_helper.c` | 136 |
| `tcp_set_state` | Function | `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/tcp_helper.c` | 144 |
| `test_tcp_new_counters_pcb` | Function | `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/tcp_helper.c` | 237 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 22 calls |
| Api | 8 calls |
| Tcp_ | 6 calls |
| Ip6 | 4 calls |
| Lwiperf | 3 calls |
| Cluster_253 | 1 calls |
| Ipv4 | 1 calls |

## How to Explore

1. `context({name: "pbuf_header"})` — see callers and callees
2. `query({query: "tcp"})` — find related execution flows
3. Read key files listed above for implementation details
