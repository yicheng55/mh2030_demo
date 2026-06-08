---
name: cluster-124
description: "Skill for the Cluster_124 area of mh2030_demo. 10 symbols across 1 files."
---

# Cluster_124

10 symbols | 1 files | Cohesion: 90%

## When to Use

- Working with code in `drivers/`
- Understanding how cspi_read_rxb, cspi_get_rwpa, cspi_get_mrrl work
- Modifying cluster_124-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | cspi_read_rxb, cspi_get_rwpa, cspi_get_mrrl, dm9051_read_rx_pointers, rx_pointers_equ (+5) |

## Entry Points

Start here when exploring this area:

- **`cspi_read_rxb`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:671`
- **`cspi_get_rwpa`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:677`
- **`cspi_get_mrrl`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:683`
- **`dm9051_read_rx_pointers`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:695`
- **`rx_pointers_equ`** (Function) — `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c:701`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `cspi_read_rxb` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 671 |
| `cspi_get_rwpa` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 677 |
| `cspi_get_mrrl` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 683 |
| `dm9051_read_rx_pointers` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 695 |
| `rx_pointers_equ` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 701 |
| `env_evaluate_rxb` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 770 |
| `env_evaluate_rxb_zero` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 794 |
| `cspi_rx_ready` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 876 |
| `dm9051_show_rxbstatistic` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 712 |
| `ret_fire_time` | Function | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | 747 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Cluster_123 | 1 calls |

## How to Explore

1. `gitnexus_context({name: "cspi_read_rxb"})` — see callers and callees
2. `gitnexus_query({query: "cluster_124"})` — find related execution flows
3. Read key files listed above for implementation details
