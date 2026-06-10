# uIP MH2030A Demo

Future location for a reusable DM9051 + uIP MH2030A example.

Current sources:

- `ModuleDemo/DM9051A/USER/main_uip_mh2030a.c`
- `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c`
- `ModuleDemo/DM9051A/port/uip/clock-arch.c`
- `apps/uip_dm9051_example_e1/uip_conf_inc/uip-conf.h`

This example should remain an application layer user of `adapters/uip`, not a
direct user of MH2030A SPI/GPIO functions.

