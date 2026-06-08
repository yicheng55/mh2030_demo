---
name: at-do
description: "Skill for the AT - do area of mh2030_demo. 16 symbols across 11 files."
---

# AT - do

16 symbols | 11 files | Cohesion: 97%

## When to Use

- Working with code in `apps/`
- Understanding how tcp_server_init, httpd_report_filename, httpd_init work
- Modifying at - do-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd.c` | httpd_report_filename, httpd_init, handle_connection, httpd_appcall |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd-fs.c` | httpd_fs_strcmp, httpd_fs_open, httpd_fs_count |
| `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/tcp_app/tcp_app.c` | tcp_server_init |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT/httpd.c` | httpd_init |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd.c` | httpd_init |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd.c` | httpd_init |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd.c` | httpd_init |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/org/httpd.c` | httpd_init |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/uip-1-0 - do/httpd.c` | httpd_init |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/uip-1-0 - org/httpd.c` | httpd_init |

## Entry Points

Start here when exploring this area:

- **`tcp_server_init`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/tcp_app/tcp_app.c:117`
- **`httpd_report_filename`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd.c:77`
- **`httpd_init`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd.c:336`
- **`httpd_init`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT/httpd.c:331`
- **`httpd_init`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd.c:425`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `tcp_server_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/Eth_app/tcp_app/tcp_app.c` | 117 |
| `httpd_report_filename` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd.c` | 77 |
| `httpd_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd.c` | 336 |
| `httpd_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT/httpd.c` | 331 |
| `httpd_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd.c` | 425 |
| `httpd_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd.c` | 607 |
| `httpd_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd.c` | 419 |
| `httpd_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/org/httpd.c` | 331 |
| `httpd_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/uip-1-0 - do/httpd.c` | 330 |
| `httpd_init` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/uip-1-0 - org/httpd.c` | 331 |
| `uip_listen` | Function | `middlewares/3rd_party/uip/src/uip.c` | 527 |
| `httpd_fs_open` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd-fs.c` | 79 |
| `httpd_fs_count` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd-fs.c` | 119 |
| `httpd_appcall` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd.c` | 301 |
| `httpd_fs_strcmp` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd-fs.c` | 57 |
| `handle_connection` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd.c` | 292 |

## How to Explore

1. `gitnexus_context({name: "tcp_server_init"})` — see callers and callees
2. `gitnexus_query({query: "at - do"})` — find related execution flows
3. Read key files listed above for implementation details
