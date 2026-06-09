---
name: bsp
description: "Skill for the Bsp area of mh2030_demo. 38 symbols across 5 files."
---

# Bsp

38 symbols | 5 files | Cohesion: 77%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how MH2030A_SPI1_Transfer, DM9051A_CS_Low, DM9051A_CS_High work
- Modifying bsp-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | DM9051A_DebugPrintPinState, DM9051A_DebugPrintSpiState, DM9051A_DmaTransfer, MH2030A_SPI1_Transfer, DM9051A_CS_Low (+13) |
| `ModuleDemo/DM9051A/bsp/mh2030a_spi1.c` | DM9051A_DebugPrintPinState, DM9051A_DebugPrintSpiState, MH2030A_SPI1_Transfer, DM9051A_CS_Low, DM9051A_CS_High (+11) |
| `Libraries/MH20xxLib/src/mh20xx_spi.c` | SPI_SendData8, SPI_I2S_GetFlagStatus |
| `ModuleDemo/DM9051A/port/uip_mh2030a/mh2030a_dm9051_spi_dma.c` | spi_wait_idle |
| `ModuleDemo/SPI/SPI_Int/USER/main.c` | SPI1_IRQHandler |

## Entry Points

Start here when exploring this area:

- **`MH2030A_SPI1_Transfer`** (Function) — `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c:259`
- **`DM9051A_CS_Low`** (Function) — `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c:287`
- **`DM9051A_CS_High`** (Function) — `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c:292`
- **`DM9051A_DebugDump`** (Function) — `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c:312`
- **`DM9051A_ReadReg`** (Function) — `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c:355`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `MH2030A_SPI1_Transfer` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 259 |
| `DM9051A_CS_Low` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 287 |
| `DM9051A_CS_High` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 292 |
| `DM9051A_DebugDump` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 312 |
| `DM9051A_ReadReg` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 355 |
| `DM9051A_WriteReg` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 367 |
| `DM9051A_ReadRegBuf` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 375 |
| `DM9051A_WriteRegBuf` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 383 |
| `DM9051A_ReadMem` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 391 |
| `DM9051A_WriteMem` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 399 |
| `DM9051A_ReadVID` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 407 |
| `DM9051A_ReadPID` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 413 |
| `DM9051A_ReadMac` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 419 |
| `DM9051A_WriteMac` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | 424 |
| `MH2030A_SPI1_Transfer` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1.c` | 145 |
| `DM9051A_CS_Low` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1.c` | 173 |
| `DM9051A_CS_High` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1.c` | 178 |
| `DM9051A_DebugDump` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1.c` | 198 |
| `DM9051A_ReadReg` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1.c` | 241 |
| `DM9051A_WriteReg` | Function | `ModuleDemo/DM9051A/bsp/mh2030a_spi1.c` | 253 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 10 calls |
| Uip_mh2030a | 3 calls |

## How to Explore

1. `gitnexus_context({name: "MH2030A_SPI1_Transfer"})` — see callers and callees
2. `gitnexus_query({query: "bsp"})` — find related execution flows
3. Read key files listed above for implementation details
