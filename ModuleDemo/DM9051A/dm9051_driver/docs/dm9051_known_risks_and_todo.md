# Known Risks and TODO

## Risks

1. HIGH: staged directory is not the production Keil target source of truth yet.
   Validate the exact linked files before relying on this driver in firmware.
2. HIGH: uIP and lwIP must not share one DM9051 instance concurrently. The
   staged header blocks simultaneous stack macros, but default lwIP external
   APIs could still link to another global driver instance.
3. HIGH: `delay.c` reuses SysTick for blocking delays while uIP/lwIP examples
   use SysTick for time. This can break timers.
4. MEDIUM: TX timeout returns an error but has no explicit TX FIFO recovery.
5. MEDIUM: DMA timeout can busy-wait for `spi_timeout * len`, which may stall
   the main loop for too long on full-size packets.
6. MEDIUM: static adapter buffers and static HAL binding make the current
   implementation single-instance and non-reentrant.
7. MEDIUM: `dm9051_core_interrupt_reset()` may lose a new interrupt edge if an
   event arrives while reset clears software state and EXTI pending.
8. LOW: RX discard uses 32-byte polling chunks; safe but not optimal.
9. LOW: default lwIP link status reports link up when no hardware link API is
   enabled.

## Recommended changes

1. Replace SysTick busy-wait delay with a timer that does not disturb uIP/lwIP
   time, or make delay use a cycle counter/peripheral timer.
2. Add explicit TX recovery on `DM9051_ERR_TIMEOUT`, such as reading TCR/TSR and
   resetting/restarting TX/RX when needed.
3. Convert SPI and DMA timeout constants to calibrated microsecond or
   millisecond budgets.
4. Add a build-level stack-owner selection rule: exactly one of uIP or lwIP owns
   a DM9051 instance.
5. Protect IRQ attach/detach with IRQ disable or critical section.
6. Consider disabling DM9051/MCU IRQ around interrupt reset, then re-check chip
   ISR before reenabling.
7. Add optional counters for RX discard, SPI timeout, DMA timeout, TX timeout,
   and chip reset.
8. For lwIP default external API mode, require a real link-status wrapper before
   enabling link callbacks in production.
9. Add tests or smoke scripts for init fail, bad MAC/IP config, RX short frame,
   RX overlength, TX overlength, SPI timeout, and interrupt event take/reset.

