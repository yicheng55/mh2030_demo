---
name: lwip-web2403v2-freelw
description: "Skill for the Lwip_web2403v2_freelw area of mh2030_demo. 78 symbols across 12 files."
---

# Lwip_web2403v2_freelw

78 symbols | 12 files | Cohesion: 66%

## When to Use

- Working with code in `apps/`
- Understanding how httpd_init, httpd_init_with_netif, httpd_init work
- Modifying lwip_web2403v2_freelw-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `apps/lwip_web2403v2_freelw/httpd.c` | httpd_init_pcb, httpd_init, httpd_init_with_netif, http_check_eof, http_write (+32) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | altcp_accept, altcp_bind, altcp_listen_with_backlog_and_err, altcp_default_bind, altcp_sndbuf (+5) |
| `apps/lwip_web2403v2_freelw/fs_jjdynamic.c` | fs_open_custom, fs_read_async_custom, fs_read_custom, fs_open, fs_canread_custom (+4) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/httpd.c` | httpd_init_pcb, httpd_init, httpd_inits, get_http_headers, get_http_content_length (+2) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls.c` | altcp_mbedtls_listen, altcp_mbedtls_sndbuf, altcp_mbedtls_write |
| `middlewares/3rd_party/lwip-2.1.2/src/core/def.c` | lwip_strnstr, lwip_stricmp, lwip_itoa |
| `middlewares/3rd_party/lwip-2.1.2/src/core/dns.c` | dns_lookup_local, dns_local_lookup, dns_local_removehost |
| `middlewares/3rd_party/lwip-2.1.2/test/unit/core/test_def.c` | def_check_range_untouched, test_def_itoa |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp_alloc.c` | altcp_tls_new |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp_tcp.c` | altcp_tcp_new_ip_type |

## Entry Points

Start here when exploring this area:

- **`httpd_init`** (Function) — `apps/lwip_web2403v2_freelw/httpd.c:2676`
- **`httpd_init_with_netif`** (Function) — `apps/lwip_web2403v2_freelw/httpd.c:2790`
- **`httpd_init`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/httpd.c:2657`
- **`httpd_inits`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/httpd.c:2683`
- **`altcp_accept`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c:223`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `httpd_init` | Function | `apps/lwip_web2403v2_freelw/httpd.c` | 2676 |
| `httpd_init_with_netif` | Function | `apps/lwip_web2403v2_freelw/httpd.c` | 2790 |
| `httpd_init` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/httpd.c` | 2657 |
| `httpd_inits` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/httpd.c` | 2683 |
| `altcp_accept` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 223 |
| `altcp_bind` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 301 |
| `altcp_listen_with_backlog_and_err` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 327 |
| `altcp_default_bind` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 532 |
| `altcp_tls_new` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp_alloc.c` | 59 |
| `altcp_tcp_new_ip_type` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp_tcp.c` | 187 |
| `altcp_sndbuf` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 417 |
| `altcp_default_sndbuf` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 583 |
| `lwip_strnstr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/def.c` | 103 |
| `lwip_stricmp` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/def.c` | 126 |
| `dns_local_lookup` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/dns.c` | 475 |
| `dns_local_removehost` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/dns.c` | 524 |
| `lwip_itoa` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/def.c` | 197 |
| `altcp_dbg_get_tcp_state` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 504 |
| `altcp_default_dbg_get_tcp_state` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 669 |
| `tcp_debug_state_str` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/tcp.c` | 2352 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 9 calls |
| Http | 8 calls |
| Altcp_tls | 7 calls |
| Api | 4 calls |
| Smtp | 1 calls |
| Sockets | 1 calls |
| Mdns | 1 calls |

## How to Explore

1. `context({name: "httpd_init"})` — see callers and callees
2. `query({query: "lwip_web2403v2_freelw"})` — find related execution flows
3. Read key files listed above for implementation details
