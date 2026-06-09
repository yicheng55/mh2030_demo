---
name: w25qxx
description: "Skill for the W25qxx area of mh2030_demo. 17 symbols across 3 files."
---

# W25qxx

17 symbols | 3 files | Cohesion: 57%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how W25QXX_ReadSR, W25QXX_Write_Enable, W25QXX_Write_Page work
- Modifying w25qxx-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | W25QXX_ReadSR, W25QXX_Write_Enable, W25QXX_Write_Page, W25QXX_Write_NoCheck, W25QXX_Erase_Chip (+10) |
| `Libraries/MH20xxLib/src/mh20xx_spi.c` | SPI_GetReceptionFIFOStatus |
| `ModuleDemo/SPI/SPI_W25Q64/USER/main.c` | main |

## Entry Points

Start here when exploring this area:

- **`W25QXX_ReadSR`** (Function) — `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c:106`
- **`W25QXX_Write_Enable`** (Function) — `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c:126`
- **`W25QXX_Write_Page`** (Function) — `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c:184`
- **`W25QXX_Write_NoCheck`** (Function) — `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c:205`
- **`W25QXX_Erase_Chip`** (Function) — `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c:278`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `W25QXX_ReadSR` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 106 |
| `W25QXX_Write_Enable` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 126 |
| `W25QXX_Write_Page` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 184 |
| `W25QXX_Write_NoCheck` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 205 |
| `W25QXX_Erase_Chip` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 278 |
| `W25QXX_Erase_Sector` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 290 |
| `W25QXX_Wait_Busy` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 305 |
| `SPI_GetReceptionFIFOStatus` | Function | `Libraries/MH20xxLib/src/mh20xx_spi.c` | 1069 |
| `SPI_ReadWriteByte` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 9 |
| `W25QXX_Write_SR` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 117 |
| `W25QXX_Write_Disable` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 134 |
| `W25QXX_PowerDown` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 310 |
| `W25QXX_WAKEUP` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 318 |
| `W25QXX_ReadID` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 147 |
| `W25QXX_Read` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 165 |
| `W25QXX_Write` | Function | `ModuleDemo/SPI/SPI_W25Q64/SYSTEM/w25qxx/w25qxx.c` | 232 |
| `main` | Function | `ModuleDemo/SPI/SPI_W25Q64/USER/main.c` | 20 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → RCC_APB1PeriphClockCmd` | cross_community | 4 |
| `Main → RCC_AHBPeriphClockCmd` | cross_community | 4 |
| `Main → RCC_DeInit` | cross_community | 3 |
| `Main → RCC_HSEConfig` | cross_community | 3 |
| `Main → RCC_GetFlagStatus` | cross_community | 3 |
| `Main → RCC_PLLCmd` | cross_community | 3 |
| `Main → RCC_APB2PeriphClockCmd` | cross_community | 3 |
| `Main → GPIO_PinAFConfig` | cross_community | 3 |
| `Main → GPIO_Init` | cross_community | 3 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 4 calls |
| Bsp | 2 calls |
| Uip_mh2030a | 1 calls |

## How to Explore

1. `gitnexus_context({name: "W25QXX_ReadSR"})` — see callers and callees
2. `gitnexus_query({query: "w25qxx"})` — find related execution flows
3. Read key files listed above for implementation details
