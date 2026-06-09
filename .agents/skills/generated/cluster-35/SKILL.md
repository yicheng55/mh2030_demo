---
name: cluster-35
description: "Skill for the Cluster_35 area of mh2030_demo. 8 symbols across 1 files."
---

# Cluster_35

8 symbols | 1 files | Cohesion: 80%

## When to Use

- Working with code in `Libraries/`
- Understanding how TIM_PWMIConfig, TIM_SetIC1Prescaler, TIM_SetIC2Prescaler work
- Modifying cluster_35-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `Libraries/MH20xxLib/src/mh20xx_tim.c` | TI1_Config, TI2_Config, TIM_PWMIConfig, TIM_SetIC1Prescaler, TIM_SetIC2Prescaler (+3) |

## Entry Points

Start here when exploring this area:

- **`TIM_PWMIConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_tim.c:1920`
- **`TIM_SetIC1Prescaler`** (Function) — `Libraries/MH20xxLib/src/mh20xx_tim.c:2037`
- **`TIM_SetIC2Prescaler`** (Function) — `Libraries/MH20xxLib/src/mh20xx_tim.c:2060`
- **`TIM_ITRxExternalClockConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_tim.c:2504`
- **`TIM_TIxExternalClockConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_tim.c:2531`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `TIM_PWMIConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_tim.c` | 1920 |
| `TIM_SetIC1Prescaler` | Function | `Libraries/MH20xxLib/src/mh20xx_tim.c` | 2037 |
| `TIM_SetIC2Prescaler` | Function | `Libraries/MH20xxLib/src/mh20xx_tim.c` | 2060 |
| `TIM_ITRxExternalClockConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_tim.c` | 2504 |
| `TIM_TIxExternalClockConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_tim.c` | 2531 |
| `TIM_SelectInputTrigger` | Function | `Libraries/MH20xxLib/src/mh20xx_tim.c` | 2680 |
| `TI1_Config` | Function | `Libraries/MH20xxLib/src/mh20xx_tim.c` | 22 |
| `TI2_Config` | Function | `Libraries/MH20xxLib/src/mh20xx_tim.c` | 24 |

## How to Explore

1. `gitnexus_context({name: "TIM_PWMIConfig"})` — see callers and callees
2. `gitnexus_query({query: "cluster_35"})` — find related execution flows
3. Read key files listed above for implementation details
