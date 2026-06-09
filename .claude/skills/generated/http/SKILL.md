---
name: http
description: "Skill for the Http area of mh2030_demo. 174 symbols across 25 files."
---

# Http

174 symbols | 25 files | Cohesion: 65%

## When to Use

- Working with code in `middlewares/`
- Understanding how httpc_get_file, mqtt_disconnect, altcp_new work
- Modifying http-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/httpd.c` | http_close_or_abort_conn, http_accept, http_check_eof, http_write, http_send_headers (+34) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | altcp_new, altcp_arg, altcp_recv, altcp_sent, altcp_poll (+26) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c` | httpc_free_state, httpc_create_request_string, httpc_init_connection_common, httpc_init_connection_addr, httpc_get_file (+18) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/altcp_proxyconnect.c` | altcp_proxyconnect_lower_recv, altcp_proxyconnect_setup_callbacks, altcp_proxyconnect_set_poll, altcp_proxyconnect_format_request, altcp_proxyconnect_send_request (+10) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls.c` | altcp_mbedtls_lower_recv_process, altcp_mbedtls_lower_connected, altcp_mbedtls_lower_recved, altcp_mbedtls_remove_callbacks, altcp_mbedtls_setup_callbacks (+8) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/fs.c` | fs_canread_custom, fs_wait_read_custom, fs_read_async, fs_read, fs_is_file_ready (+7) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | mqtt_close, mqtt_tcp_err_cb, mqtt_tcp_connect_cb, mqtt_disconnect, mqtt_client_new (+1) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | smtp_tcp_connected, smtp_dns_found, smtp_setup_pcb, smtp_close, smtp_prepare_helo (+1) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c` | pbuf_free_header, pbuf_get_at, pbuf_memcmp, pbuf_memfind |
| `middlewares/3rd_party/lwip-2.1.2/src/core/def.c` | lwip_strnstr, lwip_stricmp, lwip_itoa |

## Entry Points

Start here when exploring this area:

- **`httpc_get_file`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c:630`
- **`mqtt_disconnect`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c:1435`
- **`altcp_new`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c:172`
- **`altcp_arg`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c:211`
- **`altcp_recv`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c:235`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `httpc_get_file` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c` | 630 |
| `mqtt_disconnect` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 1435 |
| `altcp_new` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 172 |
| `altcp_arg` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 211 |
| `altcp_recv` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 235 |
| `altcp_sent` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 247 |
| `altcp_poll` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 259 |
| `altcp_err` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 275 |
| `altcp_abort` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 340 |
| `altcp_close` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 352 |
| `altcp_default_set_poll` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 516 |
| `fs_canread_custom` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/fs.c` | 46 |
| `fs_wait_read_custom` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/fs.c` | 47 |
| `fs_read_async` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/fs.c` | 110 |
| `fs_read` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/fs.c` | 113 |
| `fs_is_file_ready` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/fs.c` | 148 |
| `fs_bytes_left` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/fs.c` | 169 |
| `altcp_sndbuf` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 417 |
| `altcp_sndqueuelen` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 430 |
| `altcp_nagle_enable` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 447 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Ipcp_up → Mem_overflow_check_raw` | cross_community | 9 |
| `Ipcp_up → Mem_to_ptr` | cross_community | 9 |
| `Nd6_input → Mem_overflow_check_raw` | cross_community | 5 |
| `Nd6_input → Mem_to_ptr` | cross_community | 5 |
| `Nd6_input → Ptr_to_mem` | cross_community | 5 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 21 calls |
| Api | 11 calls |
| Sockets | 5 calls |
| Smtp | 4 calls |
| Altcp_tls | 3 calls |
| Sntp | 2 calls |
| Cluster_251 | 2 calls |
| Mqtt | 2 calls |

## How to Explore

1. `context({name: "httpc_get_file"})` — see callers and callees
2. `query({query: "http"})` — find related execution flows
3. Read key files listed above for implementation details
