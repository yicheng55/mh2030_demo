---
name: altcp-tls
description: "Skill for the Altcp_tls area of mh2030_demo. 50 symbols across 9 files."
---

# Altcp_tls

50 symbols | 9 files | Cohesion: 73%

## When to Use

- Working with code in `middlewares/`
- Understanding how mqtt_disconnect, altcp_new, altcp_arg work
- Modifying altcp_tls-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls.c` | altcp_mbedtls_lower_recv_process, altcp_mbedtls_lower_connected, altcp_mbedtls_lower_recved, altcp_mbedtls_remove_callbacks, altcp_mbedtls_setup_callbacks (+10) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | altcp_new, altcp_arg, altcp_recv, altcp_sent, altcp_poll (+8) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | mqtt_close, mqtt_tcp_err_cb, mqtt_tcp_connect_cb, mqtt_disconnect |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | smtp_tcp_connected, smtp_dns_found, smtp_setup_pcb, smtp_close |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c` | altcp_mbedtls_mem_init, altcp_mbedtls_free_config, altcp_mbedtls_alloc, altcp_mbedtls_free |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/altcp_proxyconnect.c` | altcp_proxyconnect_lower_recv, altcp_proxyconnect_setup_callbacks, altcp_proxyconnect_set_poll |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c` | httpc_free_state, httpc_create_request_string, httpc_init_connection_common |
| `apps/lwip_web2403v2_freelw/httpd.c` | http_close_or_abort_conn, http_accept |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/httpd.c` | http_close_or_abort_conn, http_accept |

## Entry Points

Start here when exploring this area:

- **`mqtt_disconnect`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c:1435`
- **`altcp_new`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c:172`
- **`altcp_arg`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c:211`
- **`altcp_recv`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c:235`
- **`altcp_sent`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c:247`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `mqtt_disconnect` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 1435 |
| `altcp_new` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 172 |
| `altcp_arg` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 211 |
| `altcp_recv` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 235 |
| `altcp_sent` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 247 |
| `altcp_poll` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 259 |
| `altcp_err` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 275 |
| `altcp_abort` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 340 |
| `altcp_close` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 352 |
| `altcp_setprio` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 468 |
| `altcp_default_set_poll` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 516 |
| `altcp_default_setprio` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 626 |
| `altcp_tls_free_config` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls.c` | 877 |
| `altcp_mbedtls_mem_init` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c` | 159 |
| `altcp_mbedtls_free_config` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c` | 201 |
| `altcp_mbedtls_alloc` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c` | 170 |
| `altcp_mbedtls_free` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c` | 180 |
| `altcp_mss` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 404 |
| `altcp_default_mss` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 574 |
| `http_close_or_abort_conn` | Function | `apps/lwip_web2403v2_freelw/httpd.c` | 317 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Http | 12 calls |
| Ppp | 8 calls |
| Lwip_web2403v2_freelw | 5 calls |
| Smtp | 2 calls |
| Api | 2 calls |
| Mqtt | 2 calls |
| Sntp | 1 calls |
| Sockets | 1 calls |

## How to Explore

1. `context({name: "mqtt_disconnect"})` — see callers and callees
2. `query({query: "altcp_tls"})` — find related execution flows
3. Read key files listed above for implementation details
