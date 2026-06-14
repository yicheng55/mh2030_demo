# DM9051 uIP Porting Guide

## Recommended ownership

Keep board and hardware opening in the example or board layer, then attach the
opened device to uIP. The adapter should not include MH2030A SPI/GPIO headers.

## Startup sequence

1. Initialize board clock, delay, UART, and SysTick policy.
2. Create one `dm9051_device_t` and one `dm9051_hal_t`.
3. Bind MH2030A HAL with polling or DMA transport.
4. Open core with `dm9051_core_open()`.
5. Call `dm9051_uip_attach()`.
6. Fill `dm9051_netif_device_t` with MAC, IP, gateway, and netmask.
7. Call `dm9051_uip_stack_init()`.
8. In the main loop, call `dm9051_uip_stack_poll()`.

## Main loop

`dm9051_uip_stack_poll()` drains up to `DM9051_UIP_RX_BURST_MAX` frames per
entry, handles IP and ARP packets from `uip_buf`, sends any response through
`dm9051_uip_output()`, and runs periodic TCP/UDP/ARP timers when enabled.

## Interrupt mode

In interrupt mode, the ISR only sets `runtime.interrupt_event`. The main loop
calls `dm9051_uip_interrupt_take()`, drains RX, and calls
`dm9051_uip_interrupt_reset()` after the burst is empty. This avoids running
SPI and uIP from the ISR.

## Safety notes

- `uip_buf` is global and must only be used by the main loop, not by ISR.
- `dm9051_uip_attached_dev` is a single static pointer. Do not attach multiple
  devices without adding explicit ownership.
- `DM9051_UIP_RX_BURST_MAX` prevents one poll call from starving the rest of
  the application, but heavy traffic can leave `rx_drain_pending` set.
- The current `delay.c` uses SysTick directly; avoid using it after SysTick has
  been configured as the uIP timer unless the delay implementation is changed.

