---
name: ppp
description: "Skill for the Ppp area of mh2030_demo. 687 symbols across 82 files."
---

# Ppp

687 symbols | 82 files | Cohesion: 74%

## When to Use

- Working with code in `middlewares/`
- Understanding how eth_mac_irq, eth_rx_irq, netbuf_alloc work
- Modifying ppp-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/netif/ppp/ppp.c` | ppp_netif_output_ip4, ppp_netif_output_ip6, ppp_netif_output, ppp_input, ppp_write (+42) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/ppp/auth.c` | auth_check_passwd, auth_peer_fail, auth_peer_success, auth_withpeer_success, auth_number (+36) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/ppp/eap.c` | eap_input, eap_server_timeout, eap_state_name, eap_send_failure, eap_send_success (+28) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/ipv6/nd6.c` | nd6_find_neighbor_cache_entry, nd6_new_neighbor_cache_entry, nd6_free_neighbor_cache_entry, nd6_find_destination_cache_entry, nd6_new_destination_cache_entry (+23) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c` | pbuf_skip_const, pbuf_init_alloced_pbuf, pbuf_alloc, pbuf_alloc_reference, pbuf_alloced_custom (+23) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/ppp/lcp.c` | lcp_delayed_up, lcp_extcode, lcp_rprotrej, lcp_received_echo_reply, lcp_addci (+22) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/netif.c` | netif_loop_output_ipv4, netif_loop_output_ipv6, netif_loop_output, netif_issue_reports, netif_init (+19) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/ppp/utils.c` | ppp_logit, ppp_warn, ppp_info, ppp_dbglog, ppp_dump_packet (+18) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/ppp/ccp.c` | ccp_open, ccp_close, ccp_input, ccp_protrej, ccp_datainput (+18) |
| `middlewares/3rd_party/lwip-2.1.2/src/netif/ppp/chap_ms.c` | chapms2_check_success, chapms_handle_failure, ascii2unicode, NTPasswordHash, ChallengeHash (+16) |

## Entry Points

Start here when exploring this area:

- **`eth_mac_irq`** (Function) — `middlewares/3rd_party/lwip-2.1.2/doc/NO_SYS_SampleCode.c:0`
- **`eth_rx_irq`** (Function) — `middlewares/3rd_party/lwip-2.1.2/doc/ZeroCopyRx.c:24`
- **`netbuf_alloc`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/netbuf.c:100`
- **`netbuf_free`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/netbuf.c:125`
- **`netbuf_ref`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/api/netbuf.c:149`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `eth_mac_irq` | Function | `middlewares/3rd_party/lwip-2.1.2/doc/NO_SYS_SampleCode.c` | 0 |
| `eth_rx_irq` | Function | `middlewares/3rd_party/lwip-2.1.2/doc/ZeroCopyRx.c` | 24 |
| `netbuf_alloc` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/netbuf.c` | 100 |
| `netbuf_free` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/netbuf.c` | 125 |
| `netbuf_ref` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/netbuf.c` | 149 |
| `netifapi_arp_add` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/netifapi.c` | 161 |
| `lwip_sendmsg` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1420 |
| `lwip_writev` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/sockets.c` | 1750 |
| `tcpip_try_callback` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/tcpip.c` | 343 |
| `pbuf_free_callback` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/tcpip.c` | 638 |
| `mem_free_callback` | Function | `middlewares/3rd_party/lwip-2.1.2/src/api/tcpip.c` | 651 |
| `snmp_sendto` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_raw.c` | 55 |
| `lwip_htons` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/def.c` | 74 |
| `dns_tmr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/dns.c` | 393 |
| `lwip_standard_chksum` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/inet_chksum.c` | 60 |
| `inet_chksum_pseudo` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/inet_chksum.c` | 308 |
| `ip6_chksum_pseudo` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/inet_chksum.c` | 341 |
| `ip_chksum_pseudo` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/inet_chksum.c` | 377 |
| `inet_chksum` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/inet_chksum.c` | 553 |
| `inet_chksum_pbuf` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/inet_chksum.c` | 566 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Ipcp_up → Memp_sanity` | cross_community | 9 |
| `Ipcp_up → Mem_overflow_check_raw` | cross_community | 9 |
| `Ipcp_up → Mem_to_ptr` | cross_community | 9 |
| `Ipcp_up → Ppp_print_string` | cross_community | 7 |
| `Main → Mem_overflow_init_raw` | cross_community | 6 |
| `Main → Mem_overflow_check_raw` | cross_community | 6 |
| `Main → Mld6_lookfor_group` | cross_community | 6 |
| `Ipcp_up → Pbuf_alloc` | cross_community | 6 |
| `Main → Udp_netif_ip_addr_changed` | intra_community | 5 |
| `Main → Raw_netif_ip_addr_changed` | intra_community | 5 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ipv4 | 40 calls |
| Api | 39 calls |
| Sntp | 15 calls |
| Http | 14 calls |
| Netif | 5 calls |
| Tcp | 3 calls |
| Ipv6 | 3 calls |
| Altcp_tls | 3 calls |

## How to Explore

1. `context({name: "eth_mac_irq"})` — see callers and callees
2. `query({query: "ppp"})` — find related execution flows
3. Read key files listed above for implementation details
