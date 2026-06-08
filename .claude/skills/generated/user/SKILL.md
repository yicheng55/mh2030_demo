---
name: user
description: "Skill for the USER area of mh2030_demo. 578 symbols across 85 files."
---

# USER

578 symbols | 85 files | Cohesion: 79%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how EXTI_Init, EXTI_StructInit, GPIO_Init work
- Modifying user-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `Libraries/MH20xxLib/src/mh20xx_rtc.c` | RTC_AlarmCmd, RTC_ITConfig, RTC_ByteToBcd2, RTC_DeInit, RTC_Init (+20) |
| `Libraries/MH20xxLib/src/mh20xx_rcc.c` | RCC_USARTCLKConfig, RCC_AHBPeriphClockCmd, RCC_APB2PeriphClockCmd, RCC_DeInit, RCC_HSEConfig (+17) |
| `Libraries/MH20xxLib/src/mh20xx_flash.c` | FLASH_SetLatency, FLASH_Unlock, FLASH_Lock, FLASH_ErasePage, FLASH_EraseAllPages (+14) |
| `Libraries/MH20xxLib/src/mh20xx_adc.c` | ADC_DeInit, ADC_Init, ADC_StructInit, ADC_Cmd, ADC_TempSensorCmd (+11) |
| `Libraries/MH20xxLib/src/mh20xx_tim.c` | TIM_TimeBaseInit, TIM_Cmd, TIM_ITConfig, TIM_RemapConfig, TIM_SetCounter (+11) |
| `Libraries/MH20xxLib/src/mh20xx_usart.c` | USART_Init, USART_StructInit, USART_Cmd, USART_SWAPPinCmd, USART_STOPModeCmd (+9) |
| `Libraries/MH20xxLib/src/mh20xx_dma.c` | DMA_DeInit, DMA_Init, DMA_StructInit, DMA_Cmd, DMA_RemapConfig (+7) |
| `ModuleDemo/PWR/PWR_Stop_Rtc_WakeUp/USER/main.c` | UART_Configuration, WAKEUP_Configuration, RTC_AlarmConfig, main, SER_PutChar (+6) |
| `ModuleDemo/IIS/IIS_CS4344/USER/main.c` | UART_Configuration, IIS_Configuration, GPIO_Configuration, SER_PutChar, fputc (+5) |
| `ModuleDemo/RTC/RTC_TIME/USER/main.c` | UART_Configuration, SER_PutChar, fputc, CLK_Configuration, RTC_Config (+5) |

## Entry Points

Start here when exploring this area:

- **`EXTI_Init`** (Function) — `Libraries/MH20xxLib/src/mh20xx_exti.c:55`
- **`EXTI_StructInit`** (Function) — `Libraries/MH20xxLib/src/mh20xx_exti.c:111`
- **`GPIO_Init`** (Function) — `Libraries/MH20xxLib/src/mh20xx_gpio.c:83`
- **`GPIO_StructInit`** (Function) — `Libraries/MH20xxLib/src/mh20xx_gpio.c:138`
- **`GPIO_PinAFConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_gpio.c:392`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `EXTI_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_exti.c` | 55 |
| `EXTI_StructInit` | Function | `Libraries/MH20xxLib/src/mh20xx_exti.c` | 111 |
| `GPIO_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 83 |
| `GPIO_StructInit` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 138 |
| `GPIO_PinAFConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_gpio.c` | 392 |
| `NVIC_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_misc.c` | 44 |
| `PWR_EnterSleepMode` | Function | `Libraries/MH20xxLib/src/mh20xx_pwr.c` | 322 |
| `PWR_EnterSTOPMode` | Function | `Libraries/MH20xxLib/src/mh20xx_pwr.c` | 362 |
| `RCC_USARTCLKConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_rcc.c` | 829 |
| `RCC_AHBPeriphClockCmd` | Function | `Libraries/MH20xxLib/src/mh20xx_rcc.c` | 1135 |
| `RCC_APB2PeriphClockCmd` | Function | `Libraries/MH20xxLib/src/mh20xx_rcc.c` | 1172 |
| `RTC_AlarmCmd` | Function | `Libraries/MH20xxLib/src/mh20xx_rtc.c` | 988 |
| `RTC_ITConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_rtc.c` | 2078 |
| `SPI_I2S_DeInit` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 70 |
| `SPI_StructInit` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 99 |
| `SPI_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 130 |
| `SPI_Cmd` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 338 |
| `I2S_Cmd` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 395 |
| `SPI_RxFIFOThresholdConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 459 |
| `SPI_I2S_DMACmd` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 876 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → USART_GetFlagStatus` | cross_community | 5 |
| `Main → USART_SendData` | cross_community | 5 |
| `Main → FLASH_GetStatus` | intra_community | 5 |
| `Main → RCC_APB1PeriphClockCmd` | cross_community | 4 |
| `Main → RCC_AHBPeriphClockCmd` | cross_community | 4 |
| `Main → RCC_AHBPeriphClockCmd` | cross_community | 4 |
| `Main → GPIO_Init` | cross_community | 4 |
| `Main → GPIO_PinAFConfig` | cross_community | 4 |
| `Main → RCC_APB2PeriphResetCmd` | cross_community | 4 |
| `Main → RCC_APB2PeriphResetCmd` | cross_community | 4 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Bsp | 7 calls |
| Cluster_26 | 4 calls |
| Cluster_36 | 3 calls |
| Uip_mh2030a | 2 calls |
| At24C02 | 1 calls |
| W25qxx | 1 calls |

## How to Explore

1. `gitnexus_context({name: "EXTI_Init"})` — see callers and callees
2. `gitnexus_query({query: "user"})` — find related execution flows
3. Read key files listed above for implementation details
