# DM9051 lwIP Porting Guide

## NO_SYS=1 mode

`adapters/lwip/lwipopts.h` uses `NO_SYS=1`, disables netconn/socket APIs, and
expects the raw API. The main loop must call `sys_check_timeouts()` when
`LWIP_TIMERS=1`.

## Startup sequence

1. Initialize board, SPI pins, UART, and the millisecond timer used by
   `sys_now()`.
2. Call `lwip_init()`.
3. Fill `struct netif.hwaddr`.
4. Call `netif_add(..., dm9051_if_init, ethernet_input)`.
5. Call `netif_set_default()`.
6. Update physical link with `dm9051_lwip_link_is_up()` and
   `netif_set_link_up/down()`.
7. Call `netif_set_up()`.
8. In the main loop call `dm9051_lwip_input()`, `sys_check_timeouts()`, and the
   application poll hook.

## TX path

lwIP may pass a pbuf chain. `low_level_output()` copies the full Ethernet frame
into a static `tx_buf`, validates total length, then sends it through the
staged core/HAL wrapper.

## RX path

`dm9051_lwip_input()` reads one hardware frame into static `rx_buf`, optionally
strips FCS when configured, rejects short frames, allocates `PBUF_RAW` from
`PBUF_POOL`, copies the frame with `pbuf_take()`, then calls `netif->input`.

## Link handling

The example polls link every 500 ms. `dm9051_lwip_link_is_up()` uses
`dm9051_core_link_is_up()` to read NSR through the staged core.

## Safety notes

- `tx_buf` and `rx_buf` are static and not reentrant. Call lwIP input/output
  from one context only.
- In `NO_SYS=1`, do not call lwIP raw API from ISR.
- Do not enable socket/netconn APIs unless migrating to `NO_SYS=0` and a real
  OS/tcpip thread.
- The lwIP adapter owns one staged core instance; do not share that chip
  instance with another stack adapter.
