# Bare-Metal NO_SYS Safety Notes

## Shared ISR/main-loop data

Shared state exists in:

- `dm9051_runtime_t.interrupt_event`: ISR sets, main loop takes/resets.
- `dm9051_runtime_t.bus_busy`: core bus arbitration flag.
- `dm9051_mh2030a_irq_device`: ISR-visible attached device pointer.
- `dm9051_mh2030a_irq_event_count`: ISR counter.
- `mh2030a_uip_elapsed_ms`: SysTick-updated clock value.

The event flag, bus flag, IRQ device pointer, IRQ counter, and uIP elapsed time
are declared volatile where they are shared with ISR. That is necessary, but not
sufficient by itself; multi-step read/modify/write still needs critical
sections.

## Critical sections

The core uses `enter_critical` and `exit_critical` around `bus_busy` acquire and
interrupt flag take/reset. MH2030A maps these hooks to PRIMASK disable/restore.
`dm9051_core_open()` rejects interrupt mode if critical hooks are missing.

## Reentrancy

The driver is not reentrant at adapter level:

- uIP has a single static attached device pointer.
- lwIP has static `tx_buf` and `rx_buf`.
- MH2030A HAL has one static bound config.
- SPI CS and DMA channels are global hardware resources.

Use one main-loop owner per DM9051 device. ISR must only set flags.

## Race conditions to watch

- `dm9051_core_interrupt_set()` writes `interrupt_event` without entering a
  critical section, which is acceptable for a single-byte ISR set on Cortex-M,
  but the main-loop take/reset side must remain critical.
- `dm9051_core_interrupt_reset()` clears `interrupt_event` before reading and
  writing DM9051 ISR/IMR. A new edge during reset can be lost if the chip INT
  line is not still asserted or EXTI pending is cleared too aggressively.
- `dm9051_mh2030a_irq_attach_device()` is not protected. Attach before enabling
  IRQ and detach only after IRQ is disabled.
- `delay.c` uses SysTick as a blocking delay source. uIP and lwIP examples also
  use SysTick for time. This can disturb `clock_time()` or `sys_now()`.

## OS object usage

No mutex, semaphore, or thread API is used in this staged directory. The lwIP
options are consistent with `NO_SYS=1`: sockets and netconn are disabled.

## Device ownership

The staged type header has a compile-time guard against defining both
`DM9051_USE_UIP` and `DM9051_USE_LWIP`. Practically, uIP and lwIP must not poll
the same DM9051 instance simultaneously. Select one stack owner per build or
provide an explicit upper-layer arbiter.

