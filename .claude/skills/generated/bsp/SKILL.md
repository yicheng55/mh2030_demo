---
name: bsp
description: "Skill for the Bsp area of mh2030_demo. 31 symbols across 2 files."
---

# Bsp

31 symbols | 2 files | Cohesion: 85%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how MH2030A_SPI1_Transfer, DM9051A_CS_Low, DM9051A_CS_High work
- Modifying bsp-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/DM9051A/bsp/mh2030a_spi1_dma.c` | DM9051A_DebugPrintPinState, DM9051A_DmaTransfer, MH2030A_SPI1_Transfer, DM9051A_CS_Low, DM9051A_CS_High (+11) |
| `ModuleDemo/DM9051A/bsp/mh2030a_spi1.c` | DM9051A_DebugPrintPinState, MH2030A_SPI1_Transfer, DM9051A_CS_Low, DM9051A_CS_High, DM9051A_DebugDump (+10) |

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
| Mh2030a | 7 calls |

## How to Explore

1. `context({name: "MH2030A_SPI1_Transfer"})` — see callers and callees
2. `query({query: "bsp"})` — find related execution flows
3. Read key files listed above for implementation details
