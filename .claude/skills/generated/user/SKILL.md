---
name: user
description: "Skill for the USER area of mh2030_demo. 603 symbols across 89 files."
---

# USER

603 symbols | 89 files | Cohesion: 85%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how COMP_Init, COMP_Cmd, COMP_WindowCmd work
- Modifying user-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `Libraries/MH20xxLib/src/mh20xx_rtc.c` | RTC_SetAlarm, RTC_AlarmCmd, RTC_ITConfig, RTC_ClearFlag, RTC_GetITStatus (+20) |
| `Libraries/MH20xxLib/src/mh20xx_rcc.c` | RCC_MCOConfig, RCC_USARTCLKConfig, RCC_GetClocksFreq, RCC_AHBPeriphClockCmd, RCC_APB2PeriphClockCmd (+17) |
| `Libraries/MH20xxLib/src/mh20xx_flash.c` | FLASH_SetLatency, FLASH_Unlock, FLASH_Lock, FLASH_ErasePage, FLASH_EraseAllPages (+14) |
| `Libraries/MH20xxLib/src/mh20xx_tim.c` | TIM_TimeBaseInit, TIM_ARRPreloadConfig, TIM_Cmd, TIM_CtrlPWMOutputs, TIM_OC1Init (+11) |
| `Libraries/MH20xxLib/src/mh20xx_adc.c` | ADC_DeInit, ADC_Init, ADC_StructInit, ADC_Cmd, ADC_TempSensorCmd (+11) |
| `Libraries/MH20xxLib/src/mh20xx_usart.c` | USART_Init, USART_StructInit, USART_Cmd, USART_SWAPPinCmd, USART_STOPModeCmd (+9) |
| `Libraries/MH20xxLib/src/mh20xx_dma.c` | DMA_RemapConfig, DMA_DeInit, DMA_Init, DMA_StructInit, DMA_Cmd (+7) |
| `ModuleDemo/PWR/PWR_Stop_Rtc_WakeUp/USER/main.c` | UART_Configuration, WAKEUP_Configuration, RTC_AlarmConfig, main, RTC_IRQHandler (+6) |
| `ModuleDemo/IIS/IIS_CS4344/USER/main.c` | UART_Configuration, IIS_Configuration, NVIC_Configuration, GPIO_Configuration, main (+5) |
| `ModuleDemo/RTC/RTC_TIME/USER/main.c` | UART_Configuration, SER_PutChar, fputc, CLK_Configuration, RTC_Config (+5) |

## Entry Points

Start here when exploring this area:

- **`COMP_Init`** (Function) — `Libraries/MH20xxLib/src/mh20xx_comp.c:65`
- **`COMP_Cmd`** (Function) — `Libraries/MH20xxLib/src/mh20xx_comp.c:133`
- **`COMP_WindowCmd`** (Function) — `Libraries/MH20xxLib/src/mh20xx_comp.c:279`
- **`DIVQSRT_SetRadicand`** (Function) — `Libraries/MH20xxLib/src/mh20xx_divqsrt.c:37`
- **`DIVQSRT_GetSqrtres`** (Function) — `Libraries/MH20xxLib/src/mh20xx_divqsrt.c:42`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `COMP_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_comp.c` | 65 |
| `COMP_Cmd` | Function | `Libraries/MH20xxLib/src/mh20xx_comp.c` | 133 |
| `COMP_WindowCmd` | Function | `Libraries/MH20xxLib/src/mh20xx_comp.c` | 279 |
| `DIVQSRT_SetRadicand` | Function | `Libraries/MH20xxLib/src/mh20xx_divqsrt.c` | 37 |
| `DIVQSRT_GetSqrtres` | Function | `Libraries/MH20xxLib/src/mh20xx_divqsrt.c` | 42 |
| `DMA_RemapConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_dma.c` | 350 |
| `EXTI_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_exti.c` | 55 |
| `EXTI_StructInit` | Function | `Libraries/MH20xxLib/src/mh20xx_exti.c` | 111 |
| `EXTI_ClearITPendingBit` | Function | `Libraries/MH20xxLib/src/mh20xx_exti.c` | 217 |
| `GPIO_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 83 |
| `GPIO_StructInit` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 138 |
| `GPIO_SetBits` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 284 |
| `GPIO_ResetBits` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 301 |
| `GPIO_PinAFConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 392 |
| `GPIO_DsConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 408 |
| `NVIC_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_misc.c` | 44 |
| `PWR_PVDLevelConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_pwr.c` | 119 |
| `PWR_PVDCmd` | Function | `Libraries/MH20xxLib/src/mh20xx_pwr.c` | 144 |
| `PWR_EnterSleepMode` | Function | `Libraries/MH20xxLib/src/mh20xx_pwr.c` | 322 |
| `PWR_EnterSTOPMode` | Function | `Libraries/MH20xxLib/src/mh20xx_pwr.c` | 362 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → USART_GetFlagStatus` | cross_community | 5 |
| `Main → USART_SendData` | cross_community | 5 |
| `Main → FLASH_GetStatus` | cross_community | 5 |
| `Main → RCC_APB1PeriphClockCmd` | intra_community | 4 |
| `Main → RCC_AHBPeriphClockCmd` | intra_community | 4 |
| `Main → RCC_AHBPeriphClockCmd` | cross_community | 4 |
| `Main → GPIO_Init` | cross_community | 4 |
| `Main → GPIO_PinAFConfig` | cross_community | 4 |
| `Main → RCC_APB2PeriphResetCmd` | cross_community | 4 |
| `Main → RCC_APB2PeriphResetCmd` | cross_community | 4 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Mh2030a | 5 calls |
| Bsp | 4 calls |
| Cluster_24 | 4 calls |
| Cluster_34 | 3 calls |
| W25qxx | 3 calls |
| Touch | 2 calls |
| At24C02 | 1 calls |

## How to Explore

1. `context({name: "COMP_Init"})` — see callers and callees
2. `query({query: "user"})` — find related execution flows
3. Read key files listed above for implementation details
