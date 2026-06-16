<!-- gitnexus:start -->
# GitNexus — Code Intelligence

This project is indexed by GitNexus as **mh2030_demo** (24814 symbols, 39332 relationships, 300 execution flows). Use the GitNexus MCP tools to understand code, assess impact, and navigate safely.

> Index stale? Run `node .gitnexus/run.cjs analyze` from the project root — it auto-selects an available runner. No `.gitnexus/run.cjs` yet? `npx gitnexus analyze` (npm 11 crash → `npm i -g gitnexus`; #1939).

## Always Do

- **MUST run impact analysis before editing any symbol.** Before modifying a function, class, or method, run `impact({target: "symbolName", direction: "upstream"})` and report the blast radius (direct callers, affected processes, risk level) to the user.
- **MUST run `detect_changes()` before committing** to verify your changes only affect expected symbols and execution flows. For regression review, compare against the default branch: `detect_changes({scope: "compare", base_ref: "master"})`.
- **MUST warn the user** if impact analysis returns HIGH or CRITICAL risk before proceeding with edits.
- When exploring unfamiliar code, use `query({query: "concept"})` to find execution flows instead of grepping. It returns process-grouped results ranked by relevance.
- When you need full context on a specific symbol — callers, callees, which execution flows it participates in — use `context({name: "symbolName"})`.

## Never Do

- NEVER edit a function, class, or method without first running `impact` on it.
- NEVER ignore HIGH or CRITICAL risk warnings from impact analysis.
- NEVER rename symbols with find-and-replace — use `rename` which understands the call graph.
- NEVER commit changes without running `detect_changes()` to check affected scope.

## Resources

| Resource | Use for |
|----------|---------|
| `gitnexus://repo/mh2030_demo/context` | Codebase overview, check index freshness |
| `gitnexus://repo/mh2030_demo/clusters` | All functional areas |
| `gitnexus://repo/mh2030_demo/processes` | All execution flows |
| `gitnexus://repo/mh2030_demo/process/{name}` | Step-by-step execution trace |

## CLI

| Task | Read this skill file |
|------|---------------------|
| Understand architecture / "How does X work?" | `.claude/skills/gitnexus/gitnexus-exploring/SKILL.md` |
| Blast radius / "What breaks if I change X?" | `.claude/skills/gitnexus/gitnexus-impact-analysis/SKILL.md` |
| Trace bugs / "Why is X failing?" | `.claude/skills/gitnexus/gitnexus-debugging/SKILL.md` |
| Rename / extract / split / refactor | `.claude/skills/gitnexus/gitnexus-refactoring/SKILL.md` |
| Tools, resources, schema reference | `.claude/skills/gitnexus/gitnexus-guide/SKILL.md` |
| Index, status, clean, wiki CLI commands | `.claude/skills/gitnexus/gitnexus-cli/SKILL.md` |

<!-- gitnexus:end -->

# mh2030_demo — Repo Guide

## What it is

Davicom **MH2030A** (ARM Cortex-M0) firmware SDK + **DM9051A SPI Ethernet** driver demo. C, bare-metal (1 FreeRTOS example), built with **Keil MDK uVision 5** (`.uvprojx`, not Makefile/CMake). Secondary IAR template exists.

## Build (Keil MDK)

Three Keil projects under `ModuleDemo/DM9051A/USER/`:

| Project file | Purpose |
|---|---|
| `DM9051A.uvprojx` | Bare DM9051 function test (no TCP/IP) |
| `DM9051A_uip.uvprojx` | uIP + DM9051 integration |
| `DM9051A_lwip.uvprojx` | lwIP + DM9051 integration |

**5 target configurations** (switchable in Keil uVision):

| Target | Purpose | Entrypoint | Output dir |
|---|---|---|---|
| `DM9051A` | Polling SPI, no DMA | `main.c` | `..\OBJ\` |
| `DM9051A_SPI_DMA` | DMA SPI | `main.c` | `..\OBJ\` |
| `MH2030A_DM9051_uIP` | uIP + polling SPI | `main_uip_mh2030a.c` | `..\OBJ_UIP\` |
| `MH2030A_DM9051_uIP_dma` | uIP + DMA SPI | `main_uip_mh2030a.c` | `..\OBJ_UIP\` |
| `MH2030A_DM9051_uIP_int` | uIP + interrupt | `main_uip_mh2030a.c` | `..\OBJ_UIP_INT\` |

Key preprocessor defines vary by target: `USE_STDPERIPH_DRIVER`, `MH2030A_UIP_PORT`, `MH2030A_DM9051_SPI_DMA`, `DMPLUG_INT`.

## Validate Keil project targets

```powershell
pwsh tools/keil/validate-dm9051-targets.ps1
```
Validates output dirs, defines, and file inclusion/exclusion per target. Fails if mismatched.

## Project structure

| Path | Role |
|---|---|
| `ModuleDemo/DM9051A/` | **Primary development area** — DM9051 driver + Keil projects |
| `ModuleDemo/DM9051A/dm9051_driver/` | **New refactored driver** (layered architecture) |
| `ModuleDemo/DM9051A/bsp/` + `port/` | **Old** board-support / port layer (being replaced) |
| `ModuleDemo/X/` | Other peripheral demos (GPIO, SPI, I2C, USART, etc.) |
| `drivers/` | **Old** monolithic DM9051 driver v1.6.1a (do NOT edit unless targeting legacy) |
| `middlewares/` | uIP + lwIP 2.1.2 source (upstream, ported) |
| `apps/` | Application-level demo (lwIP web server, uIP example) |
| `Libraries/` | CMSIS, startup code `startup_mh20xx.s`, MH20xxLib peripheral HAL |
| `tools/keil/` | Validation script only |

## DM9051 driver — two versions coexist

| Version | Path | Style |
|---|---|---|
| **Old (legacy)** | `drivers/dm9051_edriver_v1.6.1a_beta/` | Monolithic, single-file style |
| **New (active)** | `ModuleDemo/DM9051A/dm9051_driver/` | Layered: Core → HAL → Platform Port → Stack Adapter |

Edit the **new** driver unless specifically asked to fix the old one. The `port/` and `bsp/` directories under `ModuleDemo/DM9051A/` contain older port code that the new driver's `ports/mh2030a/` is superseding.

## New driver layering

```
Application / uIP / lwIP
        |
Network Stack Adapter  (adapters/uip/, adapters/lwip/)
        |
DM9051 Core Driver    (core/src/, core/inc/)
        |
DM9051 HAL Interface  (hal/inc/dm9051_hal.h — vtable contract)
        |
MH2030A Platform Port (ports/mh2030a/ — SPI1, DMA, IRQ, delay, board)
        |
SPI1 / GPIO / IRQ / Delay
```

- Core driver is platform-agnostic (no GPIO/SPI/delay calls).
- HAL is a function-pointer vtable in `dm9051_hal.h`.
- Platform port binds MH2030A SPI1, DMA, EXTI, SysTick.

## Hardware pin mapping (MH2030A + DM9051A)

| Signal | Pin |
|---|---|
| CS | PA15 |
| SCK | PB3 |
| MISO | PB4 |
| MOSI | PB5 |
| INT | PF6 / EXTI6 |
| RST | PF7 |

## Conventions

- Language: C (C99-ish, Keil ARMCC). No C++.
- All Keil `.uvprojx` and `.uvoptx` tracked in git (except `.uvguix.*` per `.gitignore`).
- Do NOT write Makefile/CMake — the project builds only in Keil MDK.
- `AGENTS.md` is identical to this file — keep both in sync.
