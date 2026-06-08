---
name: develop
description: "Skill for the Develop area of mh2030_demo. 25 symbols across 12 files."
---

# Develop

25 symbols | 12 files | Cohesion: 84%

## When to Use

- Working with code in `apps/`
- Understanding how uip_log, htons, httpd_fs_strcmp work
- Modifying develop-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c` | httpd_fs_strcmp, update_ajax_fsfile, update_barinfo_fsfile, update_adc_fsfile, update_led_fsfile (+2) |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd.c` | ledflag_of_input, DM9051_DoRXDUMP, next_scriptstate, update_onoff_led, Set_LED_mode_button (+2) |
| `middlewares/3rd_party/uip/src/uip.c` | uip_log, htons |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd-cgi.c` | generate_tcp_stats |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT/httpd-cgi.c` | generate_tcp_stats |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | generate_tcp_stats |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-cgi - EditB.c` | generate_tcp_stats |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-cgi.c` | generate_tcp_stats |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | generate_tcp_stats |
| `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/org/httpd-cgi.c` | generate_tcp_stats |

## Entry Points

Start here when exploring this area:

- **`uip_log`** (Function) — `middlewares/3rd_party/uip/src/uip.c:240`
- **`htons`** (Function) — `middlewares/3rd_party/uip/src/uip.c:1883`
- **`httpd_fs_strcmp`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c:86`
- **`update_ajax_fsfile`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c:128`
- **`update_barinfo_fsfile`** (Function) — `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c:152`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `uip_log` | Function | `middlewares/3rd_party/uip/src/uip.c` | 240 |
| `htons` | Function | `middlewares/3rd_party/uip/src/uip.c` | 1883 |
| `httpd_fs_strcmp` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c` | 86 |
| `update_ajax_fsfile` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c` | 128 |
| `update_barinfo_fsfile` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c` | 152 |
| `update_adc_fsfile` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c` | 167 |
| `update_led_fsfile` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c` | 189 |
| `httpd_fs_open` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c` | 200 |
| `httpd_fs_count` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-fs.c` | 271 |
| `ledflag_of_input` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd.c` | 252 |
| `DM9051_DoRXDUMP` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd.c` | 78 |
| `httpd_appcall` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd.c` | 572 |
| `generate_tcp_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT - do/httpd-cgi.c` | 140 |
| `generate_tcp_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/AT/httpd-cgi.c` | 140 |
| `generate_tcp_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/DM/httpd-cgi-test1.c` | 849 |
| `generate_tcp_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-cgi - EditB.c` | 207 |
| `generate_tcp_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/Develop/httpd-cgi.c` | 288 |
| `generate_tcp_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/IOT/httpd-cgi-test1.c` | 844 |
| `generate_tcp_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/org/httpd-cgi.c` | 140 |
| `generate_tcp_stats` | Function | `apps/uip_dm9051_example_e1/uip_app_src/webserver/src/uip-1-0 - do/httpd-cgi.c` | 140 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 1 calls |

## How to Explore

1. `gitnexus_context({name: "uip_log"})` — see callers and callees
2. `gitnexus_query({query: "develop"})` — find related execution flows
3. Read key files listed above for implementation details
