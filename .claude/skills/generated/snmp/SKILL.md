---
name: snmp
description: "Skill for the Snmp area of mh2030_demo. 142 symbols across 20 files."
---

# Snmp

142 symbols | 20 files | Cohesion: 83%

## When to Use

- Working with code in `middlewares/`
- Understanding how snmp_oid_to_ip4, snmp_ip4_to_oid, snmp_ip6_to_oid work
- Modifying snmp-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | snmp_oid_to_ip4, snmp_ip4_to_oid, snmp_ip6_to_oid, snmp_ip_port_to_oid, snmp_ip_to_oid (+21) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_msg.c` | snmp_parse_inbound_frame, snmp_prepare_outbound_frame, snmp_complete_outbound_frame, snmp_varbind_length, snmp_append_outbound_varbind (+18) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | snmp_ans1_enc_tlv, snmp_asn1_enc_raw, snmp_asn1_enc_u32t, snmp_asn1_enc_s32t, snmp_asn1_enc_oid (+12) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_traps.c` | snmp_trap_varbind_sum, snmp_trap_header_sum, snmp_trap_header_enc, snmp_trap_varbind_enc, snmp_send_trap (+6) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_mib2_ip.c` | ip_AddrTable_get_cell_value_core, ip_AddrTable_get_cell_value, ip_AddrTable_get_next_cell_instance_and_value, ip_RouteTable_get_cell_value_core, ip_RouteTable_get_cell_value (+4) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_mib2_tcp.c` | tcp_ConnTable_get_cell_value_core, tcp_ConnTable_get_cell_value, tcp_ConnTable_get_next_cell_instance_and_value, tcp_ConnectionTable_get_cell_value_core, tcp_ConnectionTable_get_next_cell_instance_and_value (+4) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_snmpv2_usm.c` | snmp_engineid_to_oid, snmp_oid_to_name, snmp_name_to_oid, usmusertable_get_instance, usmusertable_get_next_instance (+3) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_threadsync.c` | call_synced_function, threadsync_get_value, threadsync_set_test, threadsync_set_value, threadsync_release_instance (+3) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_pbuf_stream.c` | snmp_pbuf_stream_init, snmp_pbuf_stream_write, snmp_pbuf_stream_writebuf, snmp_pbuf_stream_writeto, snmp_pbuf_stream_seek (+2) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_mib2_udp.c` | udp_endpointTable_get_next_cell_instance_and_value, udp_Table_get_cell_value_core, udp_Table_get_cell_value, udp_Table_get_next_cell_instance_and_value, udp_endpointTable_get_cell_value_core (+1) |

## Entry Points

Start here when exploring this area:

- **`snmp_oid_to_ip4`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c:284`
- **`snmp_ip4_to_oid`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c:304`
- **`snmp_ip6_to_oid`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c:355`
- **`snmp_ip_port_to_oid`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c:385`
- **`snmp_ip_to_oid`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c:403`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `snmp_oid_to_ip4` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 284 |
| `snmp_ip4_to_oid` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 304 |
| `snmp_ip6_to_oid` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 355 |
| `snmp_ip_port_to_oid` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 385 |
| `snmp_ip_to_oid` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 403 |
| `snmp_oid_assign` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 546 |
| `snmp_oid_equal` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 662 |
| `netif_to_num` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 673 |
| `snmp_next_oid_init` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 1111 |
| `snmp_next_oid_check` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 1147 |
| `snmp_oid_in_range` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_core.c` | 1173 |
| `etharp_get_entry` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/ipv4/etharp.c` | 610 |
| `snmp_ans1_enc_tlv` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | 55 |
| `snmp_asn1_enc_raw` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | 131 |
| `snmp_asn1_enc_u32t` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | 149 |
| `snmp_asn1_enc_s32t` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | 181 |
| `snmp_asn1_enc_oid` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | 204 |
| `snmp_asn1_enc_length_cnt` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | 251 |
| `snmp_asn1_enc_u32t_cnt` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | 273 |
| `snmp_asn1_enc_s32t_cnt` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/snmp/snmp_asn1.c` | 297 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 9 calls |

## How to Explore

1. `context({name: "snmp_oid_to_ip4"})` — see callers and callees
2. `query({query: "snmp"})` — find related execution flows
3. Read key files listed above for implementation details
