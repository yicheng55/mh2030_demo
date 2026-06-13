---
name: include
description: "Skill for the Include area of mh2030_demo. 30 symbols across 5 files."
---

# Include

30 symbols | 5 files | Cohesion: 100%

## When to Use

- Working with code in `Libraries/`
- Understanding how __disable_irq, NVIC_SetPriority, NVIC_SystemReset work
- Modifying include-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `Libraries/CMSIS/Include/arm_math.h` | clip_q63_to_q31, __CLZ, arm_recip_q31, arm_recip_q15, __QADD (+16) |
| `Libraries/CMSIS/Include/core_cmFunc.h` | __get_PRIMASK, __disable_irq, __set_PRIMASK |
| `Libraries/CMSIS/Include/core_cm0.h` | NVIC_SetPriority, SysTick_Config, NVIC_SystemReset |
| `ModuleDemo/DM9051A/port/mh2030a/dm9051_hal_mh2030a.h` | dm9051_hal_mh2030a_enter_critical, dm9051_hal_mh2030a_exit_critical |
| `Libraries/CMSIS/Include/core_cmInstr.h` | __DSB |

## Entry Points

Start here when exploring this area:

- **`__disable_irq`** (Function) — `Libraries/CMSIS/Include/core_cmFunc.h:339`
- **`NVIC_SetPriority`** (Function) — `Libraries/CMSIS/Include/core_cm0.h:581`
- **`NVIC_SystemReset`** (Function) — `Libraries/CMSIS/Include/core_cm0.h:617`
- **`__DSB`** (Function) — `Libraries/CMSIS/Include/core_cmInstr.h:379`
- **`__set_PRIMASK`** (Function) — `Libraries/CMSIS/Include/core_cmFunc.h:193`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `__disable_irq` | Function | `Libraries/CMSIS/Include/core_cmFunc.h` | 339 |
| `NVIC_SetPriority` | Function | `Libraries/CMSIS/Include/core_cm0.h` | 581 |
| `NVIC_SystemReset` | Function | `Libraries/CMSIS/Include/core_cm0.h` | 617 |
| `__DSB` | Function | `Libraries/CMSIS/Include/core_cmInstr.h` | 379 |
| `__set_PRIMASK` | Function | `Libraries/CMSIS/Include/core_cmFunc.h` | 193 |
| `__get_PRIMASK` | Method | `Libraries/CMSIS/Include/core_cmFunc.h` | 180 |
| `SysTick_Config` | Method | `Libraries/CMSIS/Include/core_cm0.h` | 655 |
| `clip_q63_to_q31` | Function | `Libraries/CMSIS/Include/arm_math.h` | 433 |
| `__QADD` | Function | `Libraries/CMSIS/Include/arm_math.h` | 919 |
| `__QSUB` | Function | `Libraries/CMSIS/Include/arm_math.h` | 929 |
| `arm_clarke_q31` | Function | `Libraries/CMSIS/Include/arm_math.h` | 5098 |
| `arm_inv_clarke_q31` | Function | `Libraries/CMSIS/Include/arm_math.h` | 5202 |
| `arm_park_q31` | Function | `Libraries/CMSIS/Include/arm_math.h` | 5323 |
| `arm_inv_park_q31` | Function | `Libraries/CMSIS/Include/arm_math.h` | 5443 |
| `__SSAT` | Function | `Libraries/CMSIS/Include/arm_math.h` | 619 |
| `__QADD8` | Function | `Libraries/CMSIS/Include/arm_math.h` | 667 |
| `__QSUB8` | Function | `Libraries/CMSIS/Include/arm_math.h` | 694 |
| `__QADD16` | Function | `Libraries/CMSIS/Include/arm_math.h` | 724 |
| `__QSUB16` | Function | `Libraries/CMSIS/Include/arm_math.h` | 770 |
| `__SMLALD` | Function | `Libraries/CMSIS/Include/arm_math.h` | 978 |

## How to Explore

1. `context({name: "__disable_irq"})` — see callers and callees
2. `query({query: "include"})` — find related execution flows
3. Read key files listed above for implementation details
