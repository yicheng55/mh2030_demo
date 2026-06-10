# DM9051 Driver Refactor Staging Area

This directory is a staging layout for a reusable DM9051 driver. It is not
connected to the existing Keil targets yet, so the current project behavior is
unchanged.

## Layering

```text
USER / uIP / lwIP
        |
network stack adapter
        |
DM9051 core driver
        |
DM9051 HAL interface
        |
MH2030A SPI / GPIO / IRQ / delay
```

## Current Source Mapping

| New location | Current source | Role |
| --- | --- | --- |
| `core/inc/dm9051_core.h` | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051.h` | Public DM9051 API. |
| `core/inc/dm9051_regs.h` | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_internal.h` | Register and bit definitions. |
| `core/inc/dm9051_types.h` | `drivers/.../include/dm9051_hal.h`, `drivers/.../include/dm9051_netif.h`, `dm9051_internal.h` | Shared types, status codes, config. |
| `core/src/dm9051_core.c` | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | Core init, RX, TX, PHY, interrupt state. |
| `hal/inc/dm9051_hal.h` | `drivers/dm9051_edriver_v1.6.1a_beta/include/dm9051_hal.h` | Portable HAL vtable contract. |
| `adapters/uip/dm9051_uip.*` | `ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.*` | uIP stack adapter. |
| `adapters/lwip/dm9051_lwip.*` | none yet | Future lwIP adapter. |
| `ports/mh2030a/dm9051_hal_mh2030a.*` | `ModuleDemo/DM9051A/port/mh2030a/*` | MH2030A SPI/GPIO/IRQ/delay implementation. |
| `examples/uip_mh2030a_demo/` | `ModuleDemo/DM9051A/USER/main_uip_mh2030a.c`, `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c` | Current uIP demo shape. |
| `examples/lwip_mh2030a_demo/` | none yet | Future lwIP demo. |

## Compatibility Rule

The existing project remains the source of truth until a later phase explicitly
switches a target to this directory. Do not remove, rename, or redirect existing
files as part of the staging step.

## Refactor Phases

1. Add this staging layout and document file ownership.
2. Move pure definitions into `dm9051_regs.h` and `dm9051_types.h` in a
   compatibility-preserving copy.
3. Wrap the existing flat `hal_*` functions behind `dm9051_hal_t`.
4. Split core implementation into stable init, RX, TX, PHY, and IRQ sections.
5. Move uIP-only logic into `adapters/uip` and keep core stack-neutral.
6. Add lwIP adapter and examples after the core/HAL boundary is stable.

