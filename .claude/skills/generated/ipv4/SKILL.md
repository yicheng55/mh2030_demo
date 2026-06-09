---
name: ipv4
description: "Skill for the Ipv4 area of mh2030_demo. 105 symbols across 20 files."
---

# Ipv4

105 symbols | 20 files | Cohesion: 62%

## When to Use

- Working with code in `middlewares/`
- Understanding how autoip_start, autoip_network_changed, autoip_stop work
- Modifying ipv4-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c` | dhcp_discover, dhcp_bind, dhcp_set_state, dhcp_recv, dhcp_timeout (+27) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/autoip.c` | autoip_start_probing, autoip_start, autoip_network_changed, autoip_stop, autoip_create_addr (+8) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/igmp.c` | igmp_lookup_group, igmp_remove_group, igmp_start_timer, igmp_delaying_member, igmp_start (+7) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/etharp.c` | etharp_request_dst, etharp_find_entry, etharp_find_addr, etharp_output_to_arp_index, etharp_output (+6) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/ipv6/mld6.c` | mld6_new_group, mld6_remove_group, mld6_delayed_report, mld6_report_groups, mld6_lookfor_group (+5) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/netif.c` | netif_do_set_netmask, netif_do_set_gw, netif_set_addr, netif_get_ip6_addr_match, netif_add_ip6_address |
| `middlewares/3rd_party/lwip-2.1.2/src/core/udp.c` | udp_sendto_if, udp_sendto_if_chksum, udp_sendto_if_src |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/ppp/ipcp.c` | ipcp_nakci, ipcp_rejci, ipcp_reqci |
| `middlewares/3rd_party/lwip-2.1.2/src/api/netifapi.c` | netifapi_do_netif_set_addr, netifapi_arp_remove |
| `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c` | lwip_netconn_do_join_leave_group_netif, lwip_netconn_do_join_leave_group |

## Entry Points

Start here when exploring this area:

- **`autoip_start`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/autoip.c:253`
- **`autoip_network_changed`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/autoip.c:331`
- **`autoip_stop`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/autoip.c:347`
- **`dhcp_coarse_tmr`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c:428`
- **`dhcp_start`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c:735`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `autoip_start` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/autoip.c` | 253 |
| `autoip_network_changed` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/autoip.c` | 331 |
| `autoip_stop` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/autoip.c` | 347 |
| `dhcp_coarse_tmr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c` | 428 |
| `dhcp_start` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c` | 735 |
| `dhcp_network_changed` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c` | 856 |
| `dhcp_release_and_stop` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c` | 1316 |
| `dhcp_release` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c` | 1392 |
| `dhcp_supplied_address` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/dhcp.c` | 1978 |
| `netif_set_addr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/netif.c` | 656 |
| `lwip_netconn_do_join_leave_group_netif` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/api_msg.c` | 2058 |
| `mdns_resp_add_netif` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2058 |
| `mdns_resp_remove_netif` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mdns/mdns.c` | 2110 |
| `igmp_start` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/igmp.c` | 126 |
| `igmp_report_groups` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/igmp.c` | 190 |
| `igmp_lookfor_group` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/igmp.c` | 216 |
| `igmp_input` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/igmp.c` | 321 |
| `igmp_joingroup_netif` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/igmp.c` | 483 |
| `igmp_leavegroup_netif` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/igmp.c` | 579 |
| `mld6_report_groups` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv6/mld6.c` | 123 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → Mld6_lookfor_group` | cross_community | 6 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 36 calls |
| Api | 10 calls |
| Http | 4 calls |
| Sockets | 1 calls |
| Sntp | 1 calls |
| Mdns | 1 calls |
| Lwiperf | 1 calls |

## How to Explore

1. `context({name: "autoip_start"})` — see callers and callees
2. `query({query: "ipv4"})` — find related execution flows
3. Read key files listed above for implementation details
