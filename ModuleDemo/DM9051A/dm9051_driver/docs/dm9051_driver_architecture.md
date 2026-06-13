# DM9051 Driver Architecture

## Overall structure

This directory is a staged, reusable DM9051 driver layout. The top-level
`README.md` says it is not wired into the original Keil targets yet, but the
staged core and MH2030A polling HAL already contain real init, RX, TX, PHY,
interrupt-flag, SPI polling, and optional DMA FIFO paths.

Layer ownership:

- Application/example: board init, IP/MAC selection, main loop, link polling.
- uIP adapter: attaches one opened `dm9051_device_t`, uses `uip_buf`, ARP,
  `uip_input`, `uip_periodic`, and `uip_udp_periodic`.
- lwIP adapter: implements standard `struct netif`, `linkoutput`, pbuf copy,
  RX pbuf allocation, and `netif->input`.
- Core driver: stack-neutral DM9051 reset, chip ID probe, register policy, PHY
  access, RX FIFO framing, TX FIFO framing, link status, interrupt event flag,
  and bus arbitration.
- HAL contract: `read_reg`, `write_reg`, `read_mem`, `write_mem`, reset,
  delay, IRQ gating, and critical-section hooks.
- MH2030A port: SPI1/GPIO/reset/delay, optional DMA FIFO transport, optional
  PF6/EXTI6 interrupt handoff.
- Chip: DM9051 registers and RX/TX FIFO.

## Directory purpose

- `core/inc`: public core API, portable types, register constants.
- `core/src`: staged core behavior and diagnostics.
- `hal/inc`: portable HAL vtable contract.
- `ports/mh2030a`: concrete SPI1, GPIO, reset, delay, IRQ, and DMA binding.
- `adapters/uip`: uIP bridge and optional uIP poll loop.
- `adapters/lwip`: lwIP `netif` bridge and bare-metal lwIP options.
- `examples/uip_mh2030a_demo`: staged uIP smoke and full poll-loop examples.
- `examples/lwip_mh2030a_demo`: staged lwIP `NO_SYS=1` main-loop example.
- `docs/plan`: earlier staging notes used as context for this review.

## Initialization flow

`dm9051_uip_mh2030a_smoke_open()` and the optional lwIP core mode both build a
`dm9051_config_t`, bind `dm9051_hal_t` with `dm9051_mh2030a_hal_bind()`, then
call `dm9051_core_open()`.

`dm9051_core_open()` validates config and HAL, requires critical-section hooks
when interrupt mode is selected, copies MAC/config state, optionally calls HAL
reset, probes `VIDL/VIDH/PIDL/PIDH/CHIPR`, resets the chip, writes soft
defaults, programs PAR/MAR/checksum/flow-control registers, sets IMR, then
enables RX through RCR.

## SPI read/write flow

Polling register access asserts CS, sends `reg | read/write opcode`, transfers
one data byte, waits for SPI idle, drains RXNE if needed, then deasserts CS.
FIFO access uses one MRCMD/MWCMD command followed by a contiguous byte loop.
DMA mode keeps register access as polling and accelerates only FIFO
`read_mem`/`write_mem`.

## TX flow

Core TX validates `buf` and `len <= 1514`, acquires `runtime.bus_busy`, writes
`TXPLL/TXPLH`, writes the Ethernet frame to TX FIFO with MWCMD, sets
`TCR_TXREQ`, then by default waits up to `DM9051_TX_WAIT_TIMEOUT_US` while
polling TCR. It releases the bus and returns `DM9051_OK`, timeout, parameter,
or bus/HAL error.

## RX flow

Core RX acquires the bus, reads MRCMDX twice to check packet-ready, reads the
4-byte RX header through MRCMD, validates RX status and frame length, discards
malformed or too-large frames, reads the payload into the caller buffer, clears
RX interrupt status by writing ISR, releases the bus, and returns length through
`dm9051_core_receive_ex()`.

## ISR and main loop flow

The optional EXTI handler in `dm9051_hal_mh2030a_int.c` only increments a
volatile event counter and calls `dm9051_core_interrupt_set()`. The actual RX
drain is deferred to `dm9051_uip_stack_poll()` or `dm9051_lwip_input()` in the
main loop. This is the right shape for bare-metal main-loop + ISR systems.

## uIP and lwIP coupling

`core/inc/dm9051_types.h` rejects simultaneous `DM9051_USE_UIP` and
`DM9051_USE_LWIP`, which is good for one physical device. uIP currently keeps a
single static attached device pointer. lwIP default mode uses external
`dm9051_init`, `dm9051_packet_send`, and `dm9051_packet_receive` names, while
`DM9051_LWIP_USE_LEGACY_CORE=1` binds the staged core directly. Do not run uIP
and lwIP against the same chip instance at the same time.

