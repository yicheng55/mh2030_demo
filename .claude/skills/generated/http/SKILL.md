---
name: http
description: "Skill for the Http area of mh2030_demo. 102 symbols across 23 files."
---

# Http

102 symbols | 23 files | Cohesion: 61%

## When to Use

- Working with code in `middlewares/`
- Understanding how httpc_get_file, httpc_get_file_dns, httpc_get_file_to_disk work
- Modifying http-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/httpd.c` | http_check_eof, http_write, http_send_headers, http_send_data_nonssi, http_send_data_ssi (+20) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c` | httpc_get_internal_addr, httpc_dns_found, httpc_get_internal_dns, httpc_init_connection, httpc_init_connection_addr (+15) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | altcp_sndqueuelen, altcp_nagle_enable, altcp_default_sndqueuelen, altcp_default_nagle_enable, altcp_get_ip (+6) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/altcp_proxyconnect.c` | altcp_proxyconnect_format_request, altcp_proxyconnect_send_request, altcp_proxyconnect_lower_connected, altcp_proxyconnect_state_free, altcp_proxyconnect_dealloc (+6) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/fs.c` | fs_open_custom, fs_read_async_custom, fs_read_custom, fs_open, fs_canread_custom (+4) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c` | pbuf_free_header, pbuf_get_at, pbuf_memcmp, pbuf_memfind |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | smtp_prepare_helo, smtp_is_response_finished |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c` | tls_free, altcp_mbedtls_alloc_config |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | mqtt_client_free, mqtt_client_new |
| `middlewares/3rd_party/lwip-2.1.2/src/core/mem.c` | mem_free, mem_calloc |

## Entry Points

Start here when exploring this area:

- **`httpc_get_file`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c:630`
- **`httpc_get_file_dns`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c:675`
- **`httpc_get_file_to_disk`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c:816`
- **`httpc_get_file_dns_to_disk`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c:868`
- **`dns_gethostbyname`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/dns.c:1524`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `httpc_get_file` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c` | 630 |
| `httpc_get_file_dns` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c` | 675 |
| `httpc_get_file_to_disk` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c` | 816 |
| `httpc_get_file_dns_to_disk` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/http_client.c` | 868 |
| `dns_gethostbyname` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/dns.c` | 1524 |
| `altcp_sndqueuelen` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 430 |
| `altcp_nagle_enable` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 447 |
| `altcp_default_sndqueuelen` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 592 |
| `altcp_default_nagle_enable` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 609 |
| `altcp_get_ip` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 485 |
| `altcp_default_get_ip` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 650 |
| `ipaddr_ntoa` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ip.c` | 78 |
| `ip4addr_ntoa` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/ip4_addr.c` | 265 |
| `mdns_resp_del_service` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2240 |
| `mqtt_client_free` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 1264 |
| `dhcp6_cleanup` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv6/dhcp6.c` | 205 |
| `mem_free` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/mem.c` | 226 |
| `altcp_mbedtls_alloc_config` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c` | 188 |
| `mqtt_client_new` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 1252 |
| `mem_calloc` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/mem.c` | 980 |

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
| Altcp_tls | 12 calls |
| Lwip_web2403v2_freelw | 11 calls |
| Ppp | 10 calls |
| Api | 8 calls |
| Sockets | 4 calls |
| Smtp | 4 calls |
| Cluster_270 | 2 calls |
| Sntp | 1 calls |

## How to Explore

1. `context({name: "httpc_get_file"})` — see callers and callees
2. `query({query: "http"})` — find related execution flows
3. Read key files listed above for implementation details
