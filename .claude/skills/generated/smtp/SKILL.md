---
name: smtp
description: "Skill for the Smtp area of mh2030_demo. 34 symbols across 5 files."
---

# Smtp

34 symbols | 5 files | Cohesion: 66%

## When to Use

- Working with code in `middlewares/`
- Understanding how pbuf_strstr, smtp_send_mail, smtp_send_mail_static work
- Modifying smtp-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | smtp_verify, smtp_base64_encode, smtp_prepare_mail, smtp_pbuf_str, smtp_is_response (+21) |
| `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | altcp_connect, altcp_write, altcp_default_write |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls.c` | altcp_mbedtls_connect, altcp_mbedtls_bio_send |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/altcp_proxyconnect.c` | altcp_proxyconnect_connect, altcp_proxyconnect_write |
| `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c` | pbuf_strstr |

## Entry Points

Start here when exploring this area:

- **`pbuf_strstr`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c:1501`
- **`smtp_send_mail`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c:583`
- **`smtp_send_mail_static`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c:638`
- **`smtp_send_mail_int`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c:693`
- **`smtp_send_mail_bodycback`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c:1466`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `pbuf_strstr` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/pbuf.c` | 1501 |
| `smtp_send_mail` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 583 |
| `smtp_send_mail_static` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 638 |
| `smtp_send_mail_int` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 693 |
| `smtp_send_mail_bodycback` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 1466 |
| `altcp_connect` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 314 |
| `altcp_write` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 378 |
| `altcp_default_write` | Function | `middlewares/3rd_party/lwip-2.1.2/src/core/altcp.c` | 556 |
| `smtp_verify` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 295 |
| `smtp_base64_encode` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 306 |
| `smtp_prepare_mail` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 308 |
| `smtp_pbuf_str` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 331 |
| `smtp_is_response` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 953 |
| `smtp_prepare_auth_or_mail` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 1052 |
| `smtp_prepare_auth_login_uname` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 1106 |
| `smtp_prepare_auth_login_pass` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 1122 |
| `smtp_prepare_rcpt` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 1156 |
| `smtp_prepare_header` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 1173 |
| `smtp_prepare_quit` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/smtp/smtp.c` | 1202 |
| `altcp_mbedtls_connect` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/altcp_tls/altcp_tls_mbedtls.c` | 927 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Http | 6 calls |
| Altcp_tls | 6 calls |
| Ppp | 5 calls |
| Lwip_web2403v2_freelw | 2 calls |
| Api | 1 calls |

## How to Explore

1. `context({name: "pbuf_strstr"})` — see callers and callees
2. `query({query: "smtp"})` — find related execution flows
3. Read key files listed above for implementation details
