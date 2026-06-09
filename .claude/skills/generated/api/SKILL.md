---
name: api
description: "Skill for the Api area of mh2030_demo. 239 symbols across 44 files."
---

# Api

239 symbols | 44 files | Cohesion: 69%

## When to Use

- Working with code in `middlewares/`
- Understanding how netconn_new_with_proto_and_callback, netconn_prepare_delete, netconn_delete work
- Modifying api-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | lwip_socket_register_membership, lwip_socket_unregister_membership, lwip_socket_drop_registered_memberships, lwip_socket_register_mld6_membership, lwip_socket_unregister_mld6_membership (+63) |
| `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c` | netconn_new_with_proto_and_callback, netconn_prepare_delete, netconn_delete, netconn_getaddr, netconn_recv_udp_raw_netbuf_flags (+29) |
| `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c` | lwip_netconn_do_bind, lwip_netconn_do_connect, lwip_netconn_do_accepted, netconn_drain, lwip_netconn_is_deallocated_msg (+10) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | tcp_free, tcp_backlog_accepted, tcp_process_refused_data, tcp_pcb_purge, tcp_pcb_remove (+9) |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/api/test_sockets.c` | test_sockets_get_used_count, sockets_teardown, test_sockets_alloc_socket_nonblocking, test_sockets_allfunctions_basic_domain, test_sockets_init_loopback_addr (+6) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/udp.c` | udp_new_port, udp_bind, udp_connect, udp_recv, udp_remove (+6) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/dns.c` | dns_init_local, dns_init, dns_alloc_random_port, dns_lookup, dns_alloc_pcb (+3) |
| `middlewares/3rd_party/lwip-2.1.2/src/api/tcpip.c` | tcpip_thread_poll_one, tcpip_callback, tcpip_send_msg_wait_sem, tcpip_callbackmsg_delete, tcpip_thread_handle_msg (+2) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/raw.c` | raw_bind, raw_connect, raw_remove, raw_sendto, raw_send (+1) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/netif.c` | netif_name_to_index, netif_find, netif_add_ext_callback, netif_index_to_name, netif_get_by_index |

## Entry Points

Start here when exploring this area:

- **`netconn_new_with_proto_and_callback`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c:147`
- **`netconn_prepare_delete`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c:190`
- **`netconn_delete`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c:231`
- **`netconn_getaddr`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c:267`
- **`netconn_recv_udp_raw_netbuf_flags`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c:840`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `netconn_new_with_proto_and_callback` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c` | 147 |
| `netconn_prepare_delete` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c` | 190 |
| `netconn_delete` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c` | 231 |
| `netconn_getaddr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c` | 267 |
| `netconn_recv_udp_raw_netbuf_flags` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_lib.c` | 840 |
| `err_to_errno` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/err.c` | 67 |
| `lwip_strerr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/err.c` | 105 |
| `lwip_socket_dbg_get_socket` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 420 |
| `lwip_accept` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 618 |
| `lwip_bind` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 716 |
| `lwip_close` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 770 |
| `lwip_connect` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 811 |
| `lwip_listen` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 879 |
| `lwip_recvfrom` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1197 |
| `lwip_read` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1250 |
| `lwip_readv` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1256 |
| `lwip_recvmsg` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1279 |
| `lwip_send` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1380 |
| `lwip_sendto` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1583 |
| `lwip_socket` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1683 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Ipcp_up → Memp_sanity` | cross_community | 9 |
| `Nd6_input → Memp_sanity` | cross_community | 5 |
| `Zepif_init → Mem_overflow_init_raw` | cross_community | 4 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 30 calls |
| Ipv4 | 9 calls |
| Tcp | 9 calls |
| Sntp | 8 calls |
| Http | 8 calls |
| Tcp_ | 8 calls |
| Sockets | 6 calls |
| Lwiperf | 3 calls |

## How to Explore

1. `context({name: "netconn_new_with_proto_and_callback"})` — see callers and callees
2. `query({query: "api"})` — find related execution flows
3. Read key files listed above for implementation details
