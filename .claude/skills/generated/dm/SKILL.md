---
name: dm
description: "Skill for the DM area of mh2030_demo. 13 symbols across 3 files."
---

# DM

13 symbols | 3 files | Cohesion: 100%

## When to Use

- Working with code in `apps/`
- Understanding how Read_AT_DataFlash, show_role_msg, httpd_fs_open work
- Modifying dm-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | Read_AT_DataFlash, show_role_msg, generate_gipconfig_stats, generate_mipconfig_stats, generate_hipconfig_stats (+2) |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-fs.c` | httpd_fs_strcmp, result_true_print, httpd_fs_open, httpd_fs_count |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd.c` | handle_connection, httpd_appcall |

## Entry Points

Start here when exploring this area:

- **`Read_AT_DataFlash`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c:167`
- **`show_role_msg`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c:172`
- **`httpd_fs_open`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-fs.c:94`
- **`httpd_fs_count`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-fs.c:140`
- **`httpd_appcall`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd.c:390`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `Read_AT_DataFlash` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | 167 |
| `show_role_msg` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | 172 |
| `httpd_fs_open` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-fs.c` | 94 |
| `httpd_fs_count` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-fs.c` | 140 |
| `httpd_appcall` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd.c` | 390 |
| `generate_gipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | 353 |
| `generate_mipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | 399 |
| `generate_hipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | 445 |
| `generate_parameter1_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | 599 |
| `generate_current_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | 667 |
| `httpd_fs_strcmp` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-fs.c` | 62 |
| `result_true_print` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-fs.c` | 89 |
| `handle_connection` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd.c` | 381 |

## How to Explore

1. `gitnexus_context({name: "Read_AT_DataFlash"})` — see callers and callees
2. `gitnexus_query({query: "dm"})` — find related execution flows
3. Read key files listed above for implementation details
