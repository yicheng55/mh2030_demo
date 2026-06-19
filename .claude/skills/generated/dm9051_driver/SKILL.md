---
name: dm9051_driver
description: "Skill for the Dm9051_driver area of mh2030_demo. ~340 symbols across 39 files (18 source). Portable layered DM9051 SPI Ethernet driver for MH2030A."
---

# Dm9051_driver

~340 symbols | 39 files (18 source, 7 docs, 6 plan docs, 8 ancillary) | Architecture: 4-layer

## When to Use

- Working with the new **modular DM9051 driver** under `ModuleDemo/DM9051A/dm9051_driver/`
- Adding/porting DM9051 to a new MCU platform (write a new `ports/<mcu>/`)
- Modifying the core chip driver (RX/TX/PHY/init) in `core/`
- Changing the uIP or lwIP adapter glue in `adapters/`
- Understanding the HAL vtable contract between core and platform port
- Debugging DM9051 init failure, RX/TX hangs, interrupt issues, or link detection
- **DO NOT use** for the legacy monolithic driver in `drivers/dm9051_edriver_v1.6.1a_beta/`

## Architecture

```
Application / uIP / lwIP (examples/)
        |
Network Stack Adapter (adapters/uip/, adapters/lwip/)
        |
DM9051 Core Driver (core/src/, core/inc/)
        |
DM9051 HAL Interface (hal/inc/dm9051_hal.h — vtable contract)
        |
MH2030A Platform Port (ports/mh2030a/ — SPI1, DMA, IRQ, delay, board)
        |
SPI1 / GPIO / IRQ / Delay (hardware)
```

**Rules:**
- `core/` never includes uIP/lwIP/MCU headers
- `adapters/` never includes platform SPI/GPIO headers
- `ports/` never includes uIP/lwIP application logic

## Transports

| Mode | SPI | Registers | FIFO | File |
|------|-----|-----------|------|------|
| Polling | SPI1 polling | byte xfer | byte xfer | `dm9051_hal_mh2030a_spi1.c` |
| DMA | SPI1 + DMA1 CH2/CH3 | byte xfer (polling) | DMA burst | `dm9051_hal_mh2030a_spi1_dma.c` |
| Interrupt | Any + PF6/EXTI6 | byte xfer | byte xfer or DMA | `dm9051_hal_mh2030a_int.c` |

## Key Files

| Layer | File | Role |
|-------|------|------|
| Core | `core/inc/dm9051_types.h` | Shared types, config structs, error codes |
| Core | `core/inc/dm9051_regs.h` | DM9051 register addresses and bit masks |
| Core | `core/inc/dm9051_core.h` | Public core API (context-based + legacy wrappers) |
| Core | `core/src/dm9051_core.c` | Full core implementation: init, probe, RX, TX, PHY, IRQ (~1500 lines) |
| HAL | `hal/inc/dm9051_hal.h` | HAL vtable contract: 11 function pointers |
| Port | `ports/mh2030a/dm9051_hal_mh2030a_spi1.h` | Port public API, config structs, feature flags |
| Port | `ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | SPI1 polling HAL implementation (~497 lines) |
| Port | `ports/mh2030a/dm9051_hal_mh2030a_spi1_priv.h` | Private pin mapping + shared helpers |
| Port | `ports/mh2030a/dm9051_hal_mh2030a_spi1_dma.c` | SPI1 DMA FIFO implementation (~242 lines) |
| Port | `ports/mh2030a/dm9051_hal_mh2030a_int.c` | PF6/EXTI6 IRQ implementation (~121 lines) |
| Port | `ports/mh2030a/mh2030a_board.h / .c` | Board bring-up: clock, UART, printf |
| Port | `ports/mh2030a/delay.h / .c` | SysTick-based delay (ms/us) |
| Port | `ports/mh2030a/mh2030a_uip_clock.h / .c` | uIP 10ms tick clock |
| Port | `ports/mh2030a/mh20xx_it.c` | Interrupt vectors: SysTick, HardFault |
| Adapter | `adapters/uip/dm9051_uip.h / .c` | uIP adapter: attach, input, output |
| Adapter | `adapters/uip/dm9051_uip_stack.h / .c` | uIP stack init + poll loop (~264 lines) |
| Adapter | `adapters/lwip/dm9051_lwip.h / .c` | lwIP netif adapter (~210 lines) |
| Example | `examples/uip_mh2030a_demo/main_uip_mh2030a_smoke.c` | Hardware smoke test |
| Example | `examples/uip_mh2030a_demo/main_uip_mh2030a_demo.c` | Full uIP demo |
| Example | `examples/lwip_mh2030a_demo/main_dm9051_lwip_example.c` | lwIP demo with HTTP server |
| Doc | `docs/PORTING_GUIDE.md` | 8-step porting guide for new MCU |
| Doc | `docs/plan/HAL_CONTRACT.md` | HAL operation semantics |
| Doc | `docs/plan/STATE_MODEL.md` | Device state model |

## Entry Points

Start here when exploring this area:

- **`dm9051_core_open`** (Function) — `core/src/dm9051_core.c` — Main init entry: validate config+HAL, probe chip, reset, init device, enable RX
- **`dm9051_core_send`** (Function) — `core/src/dm9051_core.c` — Transmit frame: set TX len, write FIFO, trigger TXREQ, wait done
- **`dm9051_core_receive_ex`** (Function) — `core/src/dm9051_core.c` — Receive frame: check ready, read header, read payload, ACK ISR
- **`dm9051_mh2030a_hal_bind`** (Function) — `ports/mh2030a/dm9051_hal_mh2030a_spi1.c` — Bind HAL vtable (polling or DMA) to the device
- **`dm9051_uip_stack_init`** (Function) — `adapters/uip/dm9051_uip_stack.c` — Full uIP stack init: driver + uIP + ARP + timers
- **`dm9051_uip_stack_poll`** (Function) — `adapters/uip/dm9051_uip_stack.c` — uIP main poll loop: RX drain + TCP/UDP periodic + ARP timer
- **`dm9051_if_init`** (Function) — `adapters/lwip/dm9051_lwip.c` — lwIP netif init function
- **`mh2030a_uip_board_init`** (Function) — `ports/mh2030a/mh2030a_board.c` — Board bring-up: clock + delay + UART

## Key Symbols

### Core Driver Types

| Symbol | Type | File | Line |
|--------|------|------|------|
| `dm9051_device_t` | Struct | `core/inc/dm9051_types.h` | — |
| `dm9051_config_t` | Struct | `core/inc/dm9051_types.h` | — |
| `dm9051_runtime_t` | Struct | `core/inc/dm9051_types.h` | — |
| `dm9051_netif_device_t` | Struct | `core/inc/dm9051_types.h` | — |
| `dm9051_mac_t` | Type alias | `core/inc/dm9051_types.h` | — |

### Core Public API

| Symbol | Type | File | Line |
|--------|------|------|------|
| `dm9051_core_open` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_close` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_default_config` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_config_is_valid` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_receive` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_receive_ex` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_send` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_tx_poll_done` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_phy_read` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_phy_write` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_link_is_up` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_interrupt_set` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_interrupt_take` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_interrupt_reset` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_netif_device_is_valid` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_mac` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_device_found` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_vendor_id` | Function | `core/src/dm9051_core.c` | — |
| `dm9051_core_product_id` | Function | `core/src/dm9051_core.c` | — |

### HAL Vtable Contract

| Symbol | Type | File | Line |
|--------|------|------|------|
| `dm9051_hal_t` | Struct | `hal/inc/dm9051_hal.h` | — |
| `dm9051_hal_ops_t` | Struct | `hal/inc/dm9051_hal.h` | — |
| `read_reg` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `write_reg` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `read_mem` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `write_mem` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `reset` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `delay_ms` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `delay_us` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `irq_enable` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `irq_disable` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `enter_critical` | Func ptr | `hal/inc/dm9051_hal.h` | — |
| `exit_critical` | Func ptr | `hal/inc/dm9051_hal.h` | — |

### Port Layer (MH2030A)

| Symbol | Type | File | Line |
|--------|------|------|------|
| `dm9051_mh2030a_config_t` | Struct | `ports/mh2030a/dm9051_hal_mh2030a_spi1.h` | — |
| `dm9051_mh2030a_pins_t` | Struct | `ports/mh2030a/dm9051_hal_mh2030a_spi1.h` | — |
| `dm9051_mh2030a_default_config` | Function | `ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | — |
| `dm9051_mh2030a_config_is_valid` | Function | `ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | — |
| `dm9051_mh2030a_hal_bind` | Function | `ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | — |
| `dm9051_mh2030a_polling_ops` | Vtable | `ports/mh2030a/dm9051_hal_mh2030a_spi1.c` | — |
| `dm9051_mh2030a_dma_ops` | Vtable | `ports/mh2030a/dm9051_hal_mh2030a_spi1_dma.c` | — |
| `dm9051_mh2030a_irq_handler` | Function | `ports/mh2030a/dm9051_hal_mh2030a_int.c` | — |
| `dm9051_mh2030a_irq_attach_device` | Function | `ports/mh2030a/dm9051_hal_mh2030a_int.c` | — |
| `mh2030a_uip_board_init` | Function | `ports/mh2030a/mh2030a_board.c` | — |
| `mh2030a_uip_tick_init` | Function | `ports/mh2030a/mh2030a_uip_clock.c` | — |
| `Delay_Init` | Function | `ports/mh2030a/delay.c` | — |
| `Delay_Ms` | Function | `ports/mh2030a/delay.c` | — |
| `Delay_Us` | Function | `ports/mh2030a/delay.c` | — |

### Stack Adapters

| Symbol | Type | File | Line |
|--------|------|------|------|
| `dm9051_uip_init` | Function | `adapters/uip/dm9051_uip.c` | — |
| `dm9051_uip_attach` | Function | `adapters/uip/dm9051_uip.c` | — |
| `dm9051_uip_input` | Function | `adapters/uip/dm9051_uip.c` | — |
| `dm9051_uip_output` | Function | `adapters/uip/dm9051_uip.c` | — |
| `dm9051_uip_poll` | Function | `adapters/uip/dm9051_uip.c` | — |
| `dm9051_uip_stack_init` | Function | `adapters/uip/dm9051_uip_stack.c` | — |
| `dm9051_uip_stack_poll` | Function | `adapters/uip/dm9051_uip_stack.c` | — |
| `dm9051_if_init` | Function | `adapters/lwip/dm9051_lwip.c` | — |
| `dm9051_lwip_input` | Function | `adapters/lwip/dm9051_lwip.c` | — |
| `dm9051_lwip_simple_init` | Function | `adapters/lwip/dm9051_lwip.c` | — |
| `dm9051_lwip_simple_poll` | Function | `adapters/lwip/dm9051_lwip.c` | — |
| `dm9051_lwip_link_poll` | Function | `adapters/lwip/dm9051_lwip.c` | — |

### Key Register Defines

| Symbol | Value | Description |
|--------|-------|-------------|
| `DM9051_VENDOR_ID` | `0x0A46` | Expected vendor ID |
| `DM9051_PRODUCT_ID` | `0x9051` | Expected product ID |
| `DM9051_OPC_REG_R` | `0x00` | SPI register read opcode |
| `DM9051_OPC_REG_W` | `0x80` | SPI register write opcode |
| `DM9051_ISR_PR` | `bit 0` | Packet received interrupt |
| `DM9051_ISR_CLEAR_RX` | `bit 7` | RX clear command |
| `DM9051_PKT_RDY` | `0x01` | Packet ready marker |
| `DM9051_NCR_RESET` | `bit 0` | Software reset bit |
| `DM9051_TCR_TXREQ` | `bit 0` | TX request bit |
| `DM9051_NSR_LINKST` | `bit 6` | Link status |

### Key Configuration Macros

| Macro | Default | Description |
|-------|---------|-------------|
| `DM9051_TX_WAIT_DONE` | `1` | Blocking TX wait (0 = non-blocking) |
| `DM9051_TX_WAIT_TIMEOUT_US` | `100000` | TX timeout (100ms) |
| `DM9051_RXB_RESET_THRESHOLD` | `10` | RXB error count before chip reset |
| `DM9051_MH2030A_ENABLE_DMA` | `0` | Compile DMA transport support |
| `DM9051_MH2030A_ENABLE_IRQ` | `0` | Compile IRQ transport support |
| `DM9051_MH2030A_DIAG` | `1` | Diagnostic printf output |

## Execution Flows

### 1. Initialization Flow

```
mh2030a_uip_board_init(115200)       // Clock (72MHz) + SysTick delay + UART printf
  dm9051_core_default_config(&cfg)   // Set safe defaults (checksums, flow ctrl)
  dm9051_mh2030a_default_config(&p)  // Set port config (polling, no IRQ)
  dm9051_mh2030a_hal_bind(&hal, &p)  // Validate + select polling_ops or dma_ops
  dm9051_core_open(&dev, &cfg, &hal)
    1. Validate config + HAL vtable (6 mandatory ops)
    2. hal->reset → GPIO/SPI1 init + RST pulse (2ms low, 10ms high)
    3. dm9051_core_probe → read VID/PID/CHIPR, verify 0x0A46/0x9051
    4. dm9051_core_reset_and_start
       a. GPR=0x00 (wake), NCR reset, delay
       b. Soft default: MBNDRY, PPCR, LMCR, INTR, checksum, PHY
       c. Write MAC to PAR registers
       d. Enable RX: MAR, flow control, IMR, RCR
```

### 2. Transmit Flow

```
dm9051_core_send(&dev, buf, len)
  1. bus_acquire (critical section, set bus_busy flag)
  2. tx_set_len → write TXPLL/TXPLH registers
  3. write_mem → [Polling] byte xfer or [DMA] SPI1+DMA burst
  4. write_reg(TCR, TXREQ) → trigger transmission
  5. tx_wait_done → poll TCR.TXREQ until 0 (100ms timeout)
  6. bus_release
```

### 3. Receive Flow

```
dm9051_core_receive_ex(&dev, buf, buf_len, &rx_len)
  1. bus_acquire
  2. rx_ready → double-read MRCMDX (erratum workaround), check PKT_RDY
  3. rx_header → read_mem 4 bytes: status + length
  4. Validate status (check error bits), validate length
  5. read_mem → read RX payload into buf
  6. write_reg(ISR, ISR_CLEAR_RX) → ACK interrupt
  7. bus_release
```

### 4. Interrupt Flow (IRQ mode)

```
DM9051 INT(PF6) → EXTI6 falling edge
  EXTI4_15_IRQHandler
    dm9051_mh2030a_irq_handler
      1. Check EXTI_Line6 pending
      2. Increment event count
      3. dm9051_core_interrupt_set → set interrupt_event=1
      4. Clear EXTI pending

Main loop:
  dm9051_uip_stack_poll
    dm9051_uip_interrupt_take()
      dm9051_core_interrupt_take → atomically read & clear event
    dm9051_uip_stack_drain_rx → up to 8 frames per burst
    dm9051_uip_interrupt_reset → re-arm IRQ
```

### 5. Link Detection Flow

```
dm9051_core_link_is_up(&dev)
  read_reg(NSR) → return (NSR & NSR_LINKST) != 0

lwIP: dm9051_lwip_link_poll(netif) → netif_set_link_up/down
uIP:  Application polls every 500ms, prints state changes
```

### 6. uIP Stack Periodic Flow

```
dm9051_uip_stack_poll() [called from main loop]
  1. RX drain: up to DM9051_UIP_RX_BURST_MAX (8) frames
     - dm9051_uip_input → check EtherType
       - IP:  uip_arp_ipin → uip_input → uip_arp_out → dm9051_uip_output
       - ARP: uip_arp_arpin → dm9051_uip_output if response needed
  2. TCP periodic (every 0.5s): uip_periodic for each connection
  3. UDP periodic (every 0.5s): uip_udp_periodic for each connection
  4. ARP timer (every 10s): uip_arp_timer
  5. Re-check RX after periodic processing
```

## Design Patterns

1. **Vtable pattern**: Hardware ops abstracted through `dm9051_hal_ops_t` function pointers
2. **Opaque context**: Core casts `dev->hal` to `dm9051_hal_t*` — never includes HAL header directly
3. **Bus acquire/release**: Critical-section-protected mutual exclusion for register/FIFO access
4. **Double-read erratum**: MRCMDX register read twice (known DM9051 silicon issue, first read may be stale)
5. **RXB error histogram**: Tracks per-RXB error count; auto-resets chip at threshold (`DM9051_RXB_RESET_THRESHOLD`)
6. **Configurable blocking TX**: `DM9051_TX_WAIT_DONE` switches between blocking and non-blocking transmit
7. **Feature flags**: `ENABLE_*` = compile-time, `USE_*` = runtime selection
8. **Forward declaration**: `struct dm9051_hal` in `dm9051_core.h` avoids HAL header dependency in core header

## Porting to a New MCU

Follow `docs/PORTING_GUIDE.md` — 8 steps:

1. Copy `ports/mh2030a/` → `ports/<your_mcu>/`
2. Implement `dm9051_hal.h` mandatory ops: `read_reg`, `write_reg`, `read_mem`, `write_mem`, `delay_ms`, `delay_us`
3. Implement optional ops: `reset`, `irq_enable/disable`, `enter/exit_critical`
4. Provide `dm9051_<mcu>_hal_bind()` that populates `dm9051_hal_ops_t` + `ctx`
5. Implement board init (clock, UART, delay)
6. Test with smoke test `examples/uip_mh2030a_demo/main_uip_mh2030a_smoke.c`
7. Verify probe reads VID=0x0A46, PID=0x9051
8. Enable DMA/IRQ features as needed via feature flags

## Risk Areas

- **MRCMDX double-read**: First read can be stale — missing the second read corrupts RX path
- **RX FIFO sync**: Any mismatch between header read, payload read, and discard breaks RX permanently until reset
- **TX timeout** (`DM9051_TX_WAIT_TIMEOUT_US`=100ms): Hangs polling for 100ms if chip hangs; set `DM9051_TX_WAIT_DONE=0` for non-blocking
- **DMA alignment**: DMA buffers must be 4-byte aligned (compiler-specific macros handle this)
- **IRQ vs Polling**: Interrupt mode requires `enter_critical`/`exit_critical` hooks; polling can leave them NULL
- **RXB auto-reset**: After 10 errors, chip resets destructively losing pending frames
- **Legacy coexistence**: Legacy API (`dm9051_conf`, `dm9051_init`) is declared but not yet implemented in staged driver — only context-based API works

## Hardware Pin Mapping (MH2030A + DM9051A)

| Signal | Pin | Peripheral |
|--------|-----|------------|
| CS | PA15 | GPIO, active low |
| SCK | PB3 | SPI1, AF0 |
| MISO | PB4 | SPI1, AF0, pull-up |
| MOSI | PB5 | SPI1, AF0 |
| INT | PF6 | EXTI6, falling edge |
| RST | PF7 | GPIO, active low pulse |

## Connected Areas

| Area | Connection |
|------|------------|
| `user` | Examples include headers from MH20xxLib and board support |
| `mh2030a` | Shared port-layer symbols (SPI1, GPIO, EXTI, delay) |
| `uip-mh2030a` | Legacy uIP port (being replaced by new adapter) |
| `spi1` | SPI1 hardware abstraction (polling/DMA) |
| `freertos` | Optional RTOS integration (future) |

## How to Explore

1. `gitnexus_context({name: "dm9051_core_open"})` — see callers and callees
2. `gitnexus_query({query: "dm9051_driver"})` — find related execution flows
3. Read `docs/readme.md` (Chinese) or `docs/PORTING_GUIDE.md` for porting
4. Read key files listed above for implementation details
5. Before editing any symbol: run `gitnexus_impact({target: "<symbol>", direction: "upstream"})`
