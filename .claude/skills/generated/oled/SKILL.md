---
name: oled
description: "Skill for the Oled area of mh2030_demo. 28 symbols across 4 files."
---

# Oled

28 symbols | 4 files | Cohesion: 80%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how I2C_ITConfig, I2C_SlaveAddressConfig, I2C_AutoEndCmd work
- Modifying oled-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | OLED_ColorTurn, OLED_DisplayTurn, OLED_WR_Byte, OLED_DisPlay_On, OLED_DisPlay_Off (+14) |
| `Libraries/MH20xxLib/src/mh20xx_i2c.c` | I2C_ITConfig, I2C_SlaveAddressConfig, I2C_AutoEndCmd, I2C_NumberOfBytesConfig, I2C_MasterRequestConfig (+1) |
| `ModuleDemo/IIC/IIC_Int/USER/main.c` | GetCmd, main |
| `ModuleDemo/IIC/IIC_OLED/USER/main.c` | main |

## Entry Points

Start here when exploring this area:

- **`I2C_ITConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:252`
- **`I2C_SlaveAddressConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:442`
- **`I2C_AutoEndCmd`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:536`
- **`I2C_NumberOfBytesConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:585`
- **`I2C_MasterRequestConfig`** (Function) — `Libraries/MH20xxLib/src/mh20xx_i2c.c:614`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `I2C_ITConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 252 |
| `I2C_SlaveAddressConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 442 |
| `I2C_AutoEndCmd` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 536 |
| `I2C_NumberOfBytesConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 585 |
| `I2C_MasterRequestConfig` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 614 |
| `I2C_GenerateSTART` | Function | `Libraries/MH20xxLib/src/mh20xx_i2c.c` | 640 |
| `GetCmd` | Function | `ModuleDemo/IIC/IIC_Int/USER/main.c` | 12 |
| `main` | Function | `ModuleDemo/IIC/IIC_Int/USER/main.c` | 21 |
| `OLED_ColorTurn` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 7 |
| `OLED_DisplayTurn` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 20 |
| `OLED_WR_Byte` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 35 |
| `OLED_DisPlay_On` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 66 |
| `OLED_DisPlay_Off` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 74 |
| `OLED_WR_BP` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 364 |
| `OLED_ShowPicture` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 374 |
| `OLED_Refresh` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 82 |
| `OLED_Clear` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 95 |
| `OLED_DrawPoint` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 111 |
| `OLED_ClearPoint` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 123 |
| `OLED_DrawLine` | Function | `ModuleDemo/IIC/IIC_OLED/SYSTEM/oled/oled.c` | 137 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → RCC_APB1PeriphResetCmd` | cross_community | 4 |
| `Main → RCC_DeInit` | cross_community | 3 |
| `Main → RCC_HSEConfig` | cross_community | 3 |
| `Main → RCC_GetFlagStatus` | cross_community | 3 |
| `Main → RCC_PLLCmd` | cross_community | 3 |
| `Main → RCC_APB2PeriphClockCmd` | cross_community | 3 |
| `Main → RCC_AHBPeriphClockCmd` | cross_community | 3 |
| `Main → GPIO_PinAFConfig` | cross_community | 3 |
| `Main → GPIO_Init` | cross_community | 3 |
| `Main → GPIO_SetBits` | cross_community | 3 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 9 calls |
| At24C02 | 3 calls |

## How to Explore

1. `gitnexus_context({name: "I2C_ITConfig"})` — see callers and callees
2. `gitnexus_query({query: "oled"})` — find related execution flows
3. Read key files listed above for implementation details
