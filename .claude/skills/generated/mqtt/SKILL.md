---
name: mqtt
description: "Skill for the Mqtt area of mh2030_demo. 29 symbols across 1 files."
---

# Mqtt

29 symbols | 1 files | Cohesion: 46%

## When to Use

- Working with code in `middlewares/`
- Understanding how mqtt_client_connect, mqtt_publish, mqtt_sub_unsub work
- Modifying mqtt-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | mqtt_cyclic_timer, mqtt_request_time_elapsed, mqtt_init_requests, mqtt_output_append_u8, mqtt_output_append_fixed_header (+24) |

## Entry Points

Start here when exploring this area:

- **`mqtt_client_connect`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c:1281`
- **`mqtt_publish`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c:1095`
- **`mqtt_sub_unsub`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c:1171`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `mqtt_client_connect` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 1281 |
| `mqtt_publish` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 1095 |
| `mqtt_sub_unsub` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 1171 |
| `mqtt_cyclic_timer` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 124 |
| `mqtt_request_time_elapsed` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 389 |
| `mqtt_init_requests` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 434 |
| `mqtt_output_append_u8` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 449 |
| `mqtt_output_append_fixed_header` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 492 |
| `mqtt_output_check_space` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 512 |
| `mqtt_ringbuf_put` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 182 |
| `mqtt_output_append_u16` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 455 |
| `mqtt_output_append_buf` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 462 |
| `mqtt_output_append_string` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 471 |
| `mqtt_ringbuf_get_ptr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 193 |
| `mqtt_ringbuf_advance_get_idx` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 199 |
| `mqtt_ringbuf_len` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 211 |
| `mqtt_output_send` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 232 |
| `mqtt_tcp_poll_cb` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 1025 |
| `mqtt_msg_type_to_str` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 151 |
| `pub_ack_rec_rel_response` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/mqtt/mqtt.c` | 633 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Http | 10 calls |
| Smtp | 1 calls |
| Altcp_tls | 1 calls |
| Api | 1 calls |
| Sntp | 1 calls |

## How to Explore

1. `context({name: "mqtt_client_connect"})` — see callers and callees
2. `query({query: "mqtt"})` — find related execution flows
3. Read key files listed above for implementation details
