---
name: delay
description: "Skill for the Delay area of mh2030_demo. 55 symbols across 55 files."
---

# Delay

55 symbols | 55 files | Cohesion: 100%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how SysTick_CLKSourceConfig, Delay_Init, Delay_Init work
- Modifying delay-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `Libraries/MH20xxLib/src/mh20xx_misc.c` | SysTick_CLKSourceConfig |
| `ModuleDemo/ADC/ADC_DMA/SYSTEM/delay/delay.c` | Delay_Init |
| `ModuleDemo/ADC/ADC_Int/SYSTEM/delay/delay.c` | Delay_Init |
| `ModuleDemo/ADC/ADC_Single/SYSTEM/delay/delay.c` | Delay_Init |
| `ModuleDemo/ADC/ADC_VrefintTemper/SYSTEM/delay/delay.c` | Delay_Init |
| `ModuleDemo/COMP/COMP_Int/SYSTEM/delay/delay.c` | Delay_Init |
| `ModuleDemo/COMP/COMP_Out/SYSTEM/delay/delay.c` | Delay_Init |
| `ModuleDemo/CRC/CRC/SYSTEM/delay/delay.c` | Delay_Init |
| `ModuleDemo/DIVSQRT/Division/SYSTEM/delay/delay.c` | Delay_Init |
| `ModuleDemo/DIVSQRT/Sqrt/SYSTEM/delay/delay.c` | Delay_Init |

## Entry Points

Start here when exploring this area:

- **`SysTick_CLKSourceConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_misc.c:107`
- **`Delay_Init`** (Function) — `ModuleDemo/ADC/ADC_DMA/SYSTEM/delay/delay.c:5`
- **`Delay_Init`** (Function) — `ModuleDemo/ADC/ADC_Int/SYSTEM/delay/delay.c:5`
- **`Delay_Init`** (Function) — `ModuleDemo/ADC/ADC_Single/SYSTEM/delay/delay.c:5`
- **`Delay_Init`** (Function) — `ModuleDemo/ADC/ADC_VrefintTemper/SYSTEM/delay/delay.c:5`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `SysTick_CLKSourceConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_misc.c` | 107 |
| `Delay_Init` | Function | `ModuleDemo/ADC/ADC_DMA/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/ADC/ADC_Int/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/ADC/ADC_Single/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/ADC/ADC_VrefintTemper/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/COMP/COMP_Int/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/COMP/COMP_Out/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/CRC/CRC/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/DIVSQRT/Division/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/DIVSQRT/Sqrt/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/DM9051A/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/DM9051A/dm9051_driver/ports/mh2030a/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/FLASH/FLASH_EraseProgram/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/GPIO/GPIO_BEEP/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/GPIO/GPIO_IOInput/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/GPIO/GPIO_IOOut/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/GPIO/GPIO_IO_DSConfig/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/GPIO/GPIO_KEY/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/GPIO/GPIO_LED/SYSTEM/delay/delay.c` | 5 |
| `Delay_Init` | Function | `ModuleDemo/IAP/App/SYSTEM/delay/delay.c` | 5 |

## How to Explore

1. `context({name: "SysTick_CLKSourceConfig"})` — see callers and callees
2. `query({query: "delay"})` — find related execution flows
3. Read key files listed above for implementation details
