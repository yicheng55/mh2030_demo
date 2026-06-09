---
name: lwiperf
description: "Skill for the Lwiperf area of mh2030_demo. 48 symbols across 7 files."
---

# Lwiperf

48 symbols | 7 files | Cohesion: 82%

## When to Use

- Working with code in `middlewares/`
- Understanding how netconn_alloc, lwip_netconn_do_listen, lwiperf_start_tcp_server_default work
- Modifying lwiperf-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c` | lwiperf_tcp_err, lwiperf_start_tcp_server_impl, lwiperf_list_add, lwiperf_list_remove, lwiperf_list_find (+13) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | tcp_backlog_delayed, tcp_close, tcp_listen_with_backlog, tcp_listen_with_backlog_and_err, tcp_new_ip_type (+6) |
| `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c` | lwip_netconn_do_writemore, lwip_netconn_do_close_internal, lwip_netconn_err_to_msg, setup_tcp, accept_function (+4) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp_tcp.c` | altcp_tcp_setup, altcp_tcp_accept, altcp_tcp_remove_callbacks, altcp_tcp_setup_callbacks, altcp_tcp_set_poll (+2) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls.c` | altcp_mbedtls_lower_accept |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | altcp_alloc |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/tcp/test_tcp.c` | test_tcp_recv_expectclose |

## Entry Points

Start here when exploring this area:

- **`netconn_alloc`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c:703`
- **`lwip_netconn_do_listen`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c:1447`
- **`lwiperf_start_tcp_server_default`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c:653`
- **`lwiperf_start_tcp_server`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c:668`
- **`lwiperf_start_tcp_client_default`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c:743`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `netconn_alloc` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c` | 703 |
| `lwip_netconn_do_listen` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c` | 1447 |
| `lwiperf_start_tcp_server_default` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c` | 653 |
| `lwiperf_start_tcp_server` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c` | 668 |
| `lwiperf_start_tcp_client_default` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c` | 743 |
| `lwiperf_start_tcp_client` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c` | 757 |
| `lwiperf_abort` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/lwiperf/lwiperf.c` | 818 |
| `altcp_alloc` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 134 |
| `tcp_backlog_delayed` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 292 |
| `tcp_close` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 482 |
| `tcp_listen_with_backlog` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 823 |
| `tcp_listen_with_backlog_and_err` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 846 |
| `tcp_new_ip_type` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1960 |
| `tcp_arg` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 1986 |
| `tcp_recv` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2009 |
| `tcp_sent` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2029 |
| `tcp_err` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2055 |
| `tcp_accept` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2074 |
| `tcp_poll` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2103 |
| `lwip_netconn_do_writemore` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c` | 82 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Tcp | 8 calls |
| Api | 4 calls |
| Http | 4 calls |
| Cluster_233 | 2 calls |
| Ppp | 1 calls |
| Ipv4 | 1 calls |
| Altcp_tls | 1 calls |

## How to Explore

1. `context({name: "netconn_alloc"})` — see callers and callees
2. `query({query: "lwiperf"})` — find related execution flows
3. Read key files listed above for implementation details
