---
name: iot
description: "Skill for the IOT area of mh2030_demo. 20 symbols across 4 files."
---

# IOT

20 symbols | 4 files | Cohesion: 100%

## When to Use

- Working with code in `apps/`
- Understanding how Read_AT_DataFlash, show_role_msg, Read_AT_DataFlash work
- Modifying iot-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | Read_AT_DataFlash, show_role_msg, generate_gipconfig_stats, generate_mipconfig_stats, generate_hipconfig_stats (+2) |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c` | Read_AT_DataFlash, show_role_msg, generate_gipconfig_stats, generate_mipconfig_stats, generate_hipconfig_stats (+2) |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-fs.c` | httpd_fs_strcmp, result_true_print, httpd_fs_open, httpd_fs_count |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd.c` | handle_connection, httpd_appcall |

## Entry Points

Start here when exploring this area:

- **`Read_AT_DataFlash`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c:162`
- **`show_role_msg`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c:167`
- **`Read_AT_DataFlash`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c:162`
- **`show_role_msg`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c:167`
- **`httpd_fs_open`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-fs.c:89`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `Read_AT_DataFlash` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | 162 |
| `show_role_msg` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | 167 |
| `Read_AT_DataFlash` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c` | 162 |
| `show_role_msg` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c` | 167 |
| `httpd_fs_open` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-fs.c` | 89 |
| `httpd_fs_count` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-fs.c` | 135 |
| `httpd_appcall` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd.c` | 384 |
| `generate_gipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | 348 |
| `generate_mipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | 394 |
| `generate_hipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | 440 |
| `generate_parameter1_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | 594 |
| `generate_current_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | 662 |
| `generate_gipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c` | 322 |
| `generate_mipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c` | 359 |
| `generate_hipconfig_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c` | 396 |
| `generate_parameter1_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c` | 532 |
| `generate_current_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi.c` | 591 |
| `httpd_fs_strcmp` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-fs.c` | 57 |
| `result_true_print` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-fs.c` | 84 |
| `handle_connection` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd.c` | 375 |

## How to Explore

1. `gitnexus_context({name: "Read_AT_DataFlash"})` — see callers and callees
2. `gitnexus_query({query: "iot"})` — find related execution flows
3. Read key files listed above for implementation details
