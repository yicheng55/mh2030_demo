# DM9051 Driver Refactor Staging Area

This directory is a staging layout for a reusable DM9051 driver under the
`ModuleDemo/DM9051A` demo project. It is not connected to the existing Keil
targets yet, so the current project behavior is unchanged.

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
| `core/src/dm9051_debug.c` | `drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c` | Diagnostics and optional debug helpers. |
| `hal/inc/dm9051_hal.h` | `drivers/dm9051_edriver_v1.6.1a_beta/include/dm9051_hal.h` | Portable HAL vtable contract. |
| `adapters/uip/dm9051_uip.*` | `ModuleDemo/DM9051A/port/uip/dm9051_uip_adapter.*` | uIP stack adapter. |
| `adapters/lwip/dm9051_lwip.*` | none yet | Future lwIP adapter. |
| `ports/mh2030a/dm9051_hal_mh2030a_spi1.*` | `ModuleDemo/DM9051A/port/mh2030a/*` | MH2030A SPI1/GPIO/IRQ/delay implementation. |
| `examples/uip_mh2030a_demo/` | `ModuleDemo/DM9051A/USER/main_uip_mh2030a.c`, `ModuleDemo/DM9051A/port/uip/netconf_mh2030a.c` | Current uIP demo shape. |
| `examples/lwip_mh2030a_demo/` | `main_dm9051_lwip_example.c` | MH2030A lwIP demo. |

## Compatibility Rule

The existing project remains the source of truth until a later phase explicitly
switches a target to this directory. Do not remove, rename, or redirect existing
files as part of the staging step.

## Build Selection

The current Keil target transport selection is documented in
`docs/BUILD_SELECTION.md`. The staged driver is not wired into those targets.

The separate `ModuleDemo/DM9051A/USER/DM9051A_uip.uvprojx` project includes
the staged uIP/polling-driver files for incremental validation. The original
`DM9051A.uvprojx` remains unchanged.

## API Boundary

The intended dependency direction and adapter/core/HAL ownership rules are
documented in `docs/API_BOUNDARY.md`.

## Core Split Map

The current `dm9051_beta.c` responsibilities and future extraction order are
documented in `docs/CORE_SPLIT_MAP.md`.

## State Model

The current global state and the staged `dm9051_device_t` runtime model are
documented in `docs/STATE_MODEL.md`.

## Core API Plan

The future context-based core API and legacy wrapper mapping are documented in
`docs/CORE_API_PLAN.md`.

## HAL Contract

The staged HAL operation semantics are documented in `docs/HAL_CONTRACT.md`.

## Adapter Staging

The current uIP/lwIP staging behavior is documented in
`docs/ADAPTER_STAGING.md`.

## Refactor Phases

1. Add this staging layout and document file ownership.
2. Move pure definitions into `dm9051_regs.h` and `dm9051_types.h` in a
   compatibility-preserving copy.
3. Wrap the existing flat `hal_*` functions behind `dm9051_hal_t`.
4. Split core implementation into stable init, RX, TX, PHY, and IRQ sections.
5. Move uIP-only logic into `adapters/uip` and keep core stack-neutral.
6. Add lwIP adapter and examples after the core/HAL boundary is stable.

## Current Staging Status

- `hal/inc/dm9051_hal.h` contains a staging copy of the vtable HAL contract.
- `core/inc/dm9051_types.h` contains portable MAC, buffer, mode, config, and
  netif/device runtime types.
- `core/inc/dm9051_regs.h` contains a staging subset of register and bit
  definitions used by the current core.
- `core/inc/dm9051_core.h` contains a staging snapshot of the current public
  core API.
- `core/src/dm9051_core.c` and `core/src/dm9051_debug.c` are the only planned
  core source files at this stage.
- `core/src/dm9051_core.c` currently provides staging-only config/netif
  validation, minimum HAL binding validation, MAC state copy, chip-ID probe,
  interrupt event state, and neutral not-ready RX/TX/PHY behavior.
- `ports/mh2030a/dm9051_hal_mh2030a_spi1.h` contains the future MH2030A transport
  and IRQ config model.
- `ports/mh2030a/dm9051_hal_mh2030a_spi1.c` binds the MH2030A SPI1 polling HAL to
  the staged vtable; DMA transport still reports `DM9051_HAL_ERR_NOT_READY`.
- `examples/uip_mh2030a_demo/dm9051_uip_mh2030a_smoke.c` binds one staged
  MH2030A polling HAL/device pair and runs `dm9051_core_open()` for chip-ID
  smoke validation only.

These files are not included by the original `DM9051A.uvprojx` project. Use
`DM9051A_uip.uvprojx` for staged validation.
