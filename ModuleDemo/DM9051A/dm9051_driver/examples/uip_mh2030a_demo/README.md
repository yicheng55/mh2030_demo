# uIP MH2030A Demo

Future location for a reusable DM9051 + uIP MH2030A example.

Current sources:

- `ModuleDemo/DM9051A/USER/main_uip_mh2030a.c`
- `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c`
- `ModuleDemo/DM9051A/port/uip/clock-arch.c`
- `apps/uip_dm9051_example_e1/uip_conf_inc/uip-conf.h`

This example should remain an application layer user of `adapters/uip`, not a
direct user of MH2030A SPI/GPIO functions.

## Current Staging Smoke Glue

`dm9051_uip_mh2030a_smoke.c` is an incremental validation helper for the new
`ModuleDemo/DM9051A/USER/DM9051A_uip.uvprojx` project.

It currently:

- Creates one static `dm9051_hal_t`.
- Creates one static `dm9051_device_t`.
- Binds the MH2030A polling HAL with `dm9051_mh2030a_hal_bind()`.
- Calls `dm9051_core_open()` to run the staged chip-ID probe.

`main_uip_mh2030a_smoke.c` is the current staging entry point selected by
`DM9051A_uip.uvprojx`. It initializes the board/tick, runs the smoke open path,
prints the probe status and ID fields, then stays in an idle loop.

It does not call uIP, process RX packets, or replace the production
`netconf_mh2030a.c` / `dm9051_uip_adapter.c` flow.
