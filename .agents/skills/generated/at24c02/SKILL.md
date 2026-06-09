---
name: at24c02
description: "Skill for the At24C02 area of mh2030_demo. 19 symbols across 6 files."
---

# At24C02

19 symbols | 6 files | Cohesion: 75%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how I2C_TransferHandling, I2C_SendData, I2C_ReceiveData work
- Modifying at24c02-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `Libraries/MH20xxLib/src/mh20xx_i2c.c` | I2C_TransferHandling, I2C_SendData, I2C_ReceiveData, I2C_GetFlagStatus, I2C_ClearFlag (+3) |
| `ModuleDemo/IIC/IIC_AT24C02/SYSTEM/at24C02/at24cxx.c` | AT24Cxx_TIMEOUT_UserCallback, AT24Cxx_WaitEepromStandbyState, AT24Cxx_WritePage, AT24Cxx_WriteBuffer, AT24Cxx_ReadBuffer (+2) |
| `ModuleDemo/IIC/IIC_AT24C02/USER/main.c` | main |
| `ModuleDemo/IIC/IIC_Int/USER/main.c` | I2C1_IRQHandler |
| `Libraries/MH20xxLib/src/mh20xx_rcc.c` | RCC_I2CCLKConfig |
| `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | OLED_Init |

## Entry Points

Start here when exploring this area:

- **`I2C_TransferHandling`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:798`
- **`I2C_SendData`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:1162`
- **`I2C_ReceiveData`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:1176`
- **`I2C_GetFlagStatus`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:1339`
- **`I2C_ClearFlag`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:1383`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `I2C_TransferHandling` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 798 |
| `I2C_SendData` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 1162 |
| `I2C_ReceiveData` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 1176 |
| `I2C_GetFlagStatus` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 1339 |
| `I2C_ClearFlag` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 1383 |
| `AT24Cxx_TIMEOUT_UserCallback` | Function | `ModuleDemo/IIC/IIC_AT24C02/SYSTEM/at24C02/at24cxx.c` | 16 |
| `AT24Cxx_WaitEepromStandbyState` | Function | `ModuleDemo/IIC/IIC_AT24C02/SYSTEM/at24C02/at24cxx.c` | 61 |
| `AT24Cxx_WritePage` | Function | `ModuleDemo/IIC/IIC_AT24C02/SYSTEM/at24C02/at24cxx.c` | 104 |
| `AT24Cxx_WriteBuffer` | Function | `ModuleDemo/IIC/IIC_AT24C02/SYSTEM/at24C02/at24cxx.c` | 191 |
| `AT24Cxx_ReadBuffer` | Function | `ModuleDemo/IIC/IIC_AT24C02/SYSTEM/at24C02/at24cxx.c` | 305 |
| `main` | Function | `ModuleDemo/IIC/IIC_AT24C02/USER/main.c` | 17 |
| `I2C1_IRQHandler` | Function | `ModuleDemo/IIC/IIC_Int/USER/main.c` | 169 |
| `I2C_DeInit` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 63 |
| `I2C_Init` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 92 |
| `I2C_Cmd` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 197 |
| `RCC_I2CCLKConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_rcc.c` | 807 |
| `I2C2_Init` | Function | `ModuleDemo/IIC/IIC_AT24C02/SYSTEM/at24C02/at24cxx.c` | 26 |
| `AT24CXX_Init` | Function | `ModuleDemo/IIC/IIC_AT24C02/SYSTEM/at24C02/at24cxx.c` | 55 |
| `OLED_Init` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 387 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → RCC_APB1PeriphResetCmd` | cross_community | 5 |
| `Main → RCC_APB1PeriphResetCmd` | cross_community | 4 |
| `Main → RCC_AHBPeriphClockCmd` | cross_community | 4 |
| `Main → GPIO_Init` | cross_community | 4 |
| `Main → GPIO_PinAFConfig` | cross_community | 4 |
| `Main → GPIO_SetBits` | cross_community | 3 |
| `Main → RCC_DeInit` | cross_community | 3 |
| `Main → RCC_HSEConfig` | cross_community | 3 |
| `Main → RCC_GetFlagStatus` | cross_community | 3 |
| `Main → RCC_PLLCmd` | cross_community | 3 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 12 calls |
| Oled | 3 calls |
| Cluster_26 | 1 calls |

## How to Explore

1. `gitnexus_context({name: "I2C_TransferHandling"})` — see callers and callees
2. `gitnexus_query({query: "at24c02"})` — find related execution flows
3. Read key files listed above for implementation details
