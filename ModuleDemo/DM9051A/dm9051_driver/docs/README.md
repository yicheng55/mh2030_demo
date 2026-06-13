# DM9051 Driver Documentation

## Files read before analysis

GitNexus context was read first, but GitNexus query was unavailable because the
local LadybugDB storage version did not match the current reader. The analysis
below is therefore based on these source files read directly from this
directory:

- `README.md`, `Makefile`
- `core/inc/dm9051_core.h`, `core/inc/dm9051_regs.h`, `core/inc/dm9051_types.h`
- `core/src/dm9051_core.c`, `core/src/dm9051_debug.c`
- `hal/inc/dm9051_hal.h`
- `adapters/uip/dm9051_uip.c`, `adapters/uip/dm9051_uip.h`
- `adapters/uip/dm9051_uip_stack.c`, `adapters/uip/dm9051_uip_stack.h`
- `adapters/lwip/dm9051_lwip.c`, `adapters/lwip/dm9051_lwip.h`
- `adapters/lwip/lwipopts.h`
- `ports/mh2030a/dm9051_hal_mh2030a_spi1.c`
- `ports/mh2030a/dm9051_hal_mh2030a_spi1.h`
- `ports/mh2030a/dm9051_hal_mh2030a_spi1_priv.h`
- `ports/mh2030a/dm9051_hal_mh2030a_spi1_dma.c`
- `ports/mh2030a/dm9051_hal_mh2030a_spi1_dma.h`
- `ports/mh2030a/dm9051_hal_mh2030a_int.c`
- `ports/mh2030a/dm9051_hal_mh2030a_int.h`
- `ports/mh2030a/mh20xx_it.c`
- `ports/mh2030a/mh2030a_board.c`, `ports/mh2030a/mh2030a_board.h`
- `ports/mh2030a/mh2030a_platform.h`
- `ports/mh2030a/mh2030a_uip_clock.c`, `ports/mh2030a/mh2030a_uip_clock.h`
- `ports/mh2030a/delay.c`, `ports/mh2030a/delay.h`
- `ports/mh2030a/README.md`
- `examples/uip_mh2030a_demo/dm9051_uip_mh2030a_smoke.c`
- `examples/uip_mh2030a_demo/dm9051_uip_mh2030a_smoke.h`
- `examples/uip_mh2030a_demo/main_uip_mh2030a_demo.c`
- `examples/uip_mh2030a_demo/main_uip_mh2030a_smoke.c`
- `examples/uip_mh2030a_demo/README.md`
- `examples/lwip_mh2030a_demo/main_dm9051_lwip_example.c`
- `examples/lwip_mh2030a_demo/README.md`
- `docs/plan/ADAPTER_STAGING.md`, `docs/plan/API_BOUNDARY.md`
- `docs/plan/BUILD_SELECTION.md`, `docs/plan/CORE_API_PLAN.md`
- `docs/plan/CORE_SPLIT_MAP.md`, `docs/plan/HAL_CONTRACT.md`
- `docs/plan/STATE_MODEL.md`

## Document map

- `dm9051_driver_architecture.md`: layers, ownership, and major flows.
- `dm9051_api_manual.md`: core, uIP, lwIP, HAL, and port APIs.
- `dm9051_uip_porting_guide.md`: uIP bare-metal integration path.
- `dm9051_lwip_porting_guide.md`: lwIP `NO_SYS=1` integration path.
- `dm9051_baremetal_no_os_notes.md`: ISR/main-loop safety review.
- `dm9051_isr_spi_timeout_review.md`: SPI, DMA, timeout, and recovery review.
- `dm9051_known_risks_and_todo.md`: risk list and recommended fixes.

## SVG flowcharts

- `dm9051_architecture.svg`
- `dm9051_init_flow.svg`
- `dm9051_tx_flow.svg`
- `dm9051_rx_flow.svg`
- `dm9051_isr_mainloop_flow.svg`
- `uip_lwip_adapter_flow.svg`

