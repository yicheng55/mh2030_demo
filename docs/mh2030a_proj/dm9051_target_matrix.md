# DM9051 Keil Target Matrix

Date: 2026-06-09
Project: ModuleDemo/DM9051A/USER/DM9051A.uvprojx

## Purpose

This matrix documents the expected differences between DM9051 targets and provides one command to validate drift after uvprojx changes.

## Target Matrix

| Target | OutputDir | Define | main.c | main_uip_mh2030a.c | mh2030a_dm9051_spi.c | mh2030a_dm9051_spi_dma.c | mh2030a_dm9051_int.c |
| --- | --- | --- | --- | --- | --- | --- | --- |
| DM9051A | ..\OBJ\ | USE_STDPERIPH_DRIVER | 1 | 0 | 1 | 1 | 1 |
| DM9051A_SPI_DMA | ..\OBJ\ | USE_STDPERIPH_DRIVER | 1 | 0 | 0 | 1 | 1 |
| MH2030A_DM9051_uIP | ..\OBJ_UIP\ | USE_STDPERIPH_DRIVER,MH2030A_UIP_PORT | 0 | 1 | 1 | 0 | 1 |
| MH2030A_DM9051_uIP_dma | ..\OBJ_UIP\ | USE_STDPERIPH_DRIVER,MH2030A_UIP_PORT,MH2030A_DM9051_SPI_DMA | 0 | 1 | 0 | 1 | 1 |
| MH2030A_DM9051_uIP_int | ..\OBJ_UIP_INT\ | USE_STDPERIPH_DRIVER,MH2030A_UIP_PORT,DMPLUG_INT | 0 | 1 | 1 | 0 | 1 |

Notes:
- IncludeInBuild value 1 means enabled. Value 0 means disabled.
- If IncludeInBuild is missing in uvprojx, Keil treats it as enabled.
- uIP target mode macros:
  - polling: no DMPLUG_INT and no MH2030A_DM9051_SPI_DMA
  - dma: MH2030A_DM9051_SPI_DMA
  - interrupt: DMPLUG_INT

## Validation Command

Run from repository root:

powershell -ExecutionPolicy Bypass -File tools/keil/validate-dm9051-targets.ps1

Expected output on success:

DM9051 target validation PASSED.
