# DM9051 API Manual

## Core API

- `dm9051_core_default_config(config)`: clears config, enables TX checksuming,
  flow control, polling input mode by default.
- `dm9051_core_config_is_valid(config)`: accepts only poll, interrupt, or
  interrupt-with-CLKOUT modes.
- `dm9051_netif_device_is_valid(dev)`: validates MAC, static IP, gateway, and
  netmask for staged adapters.
- `dm9051_core_open(dev, config, hal)`: binds a HAL, probes the chip, resets and
  starts RX. Returns `DM9051_OK` only after chip ID and init succeed.
- `dm9051_core_close(dev)`: clears the device context.
- `dm9051_core_receive(dev, buf, buf_len)`: receives one frame, returns length
  or zero.
- `dm9051_core_receive_ex(dev, buf, buf_len, out_len)`: receives one frame and
  returns explicit status.
- `dm9051_core_send(dev, buf, len)`: sends one Ethernet frame.
- `dm9051_core_tx_poll_done(dev)`: available only when
  `DM9051_TX_WAIT_DONE=0`.
- `dm9051_core_phy_read/write`: reads or writes PHY registers through EPCR.
- `dm9051_core_link_is_up(dev)`: reads NSR link status.
- `dm9051_core_interrupt_set/take/reset`: ISR-to-main-loop event flag API.
- `dm9051_core_mac/device_found/vendor_id/product_id/chip_revision`: query
  staged runtime state.

## HAL API

Required operations for production use:

- `read_reg`, `write_reg`: one-byte DM9051 register access.
- `read_mem`, `write_mem`: contiguous FIFO access using MRCMD/MWCMD.
- `delay_ms`, `delay_us`: used during reset, PHY busy waits, and TX wait.

Optional but important operations:

- `reset`: initializes bus/reset GPIO and performs hardware reset.
- `irq_enable`, `irq_disable`: gate MCU interrupt line.
- `enter_critical`, `exit_critical`: protect shared state. Required by
  `dm9051_core_open()` when interrupt mode is configured.

## MH2030A port API

- `dm9051_mh2030a_default_config(config)`: fills SPI1 pin map, polling
  transport, IRQ off, and default timeout.
- `dm9051_mh2030a_hal_bind(hal, config)`: validates config and selects polling
  or DMA FIFO ops.
- `dm9051_mh2030a_irq_attach_device(dev)`: binds the device used by EXTI ISR.
- `dm9051_mh2030a_irq_handler()`: ISR handoff helper when the application owns
  `EXTI4_15_IRQHandler`.

## uIP adapter API

- `dm9051_uip_attach(dev)`: attaches an already opened core device.
- `dm9051_uip_init(netif_dev)`: validates IP/MAC config and requires an attached
  device.
- `dm9051_uip_input(buf, len)`: calls core receive.
- `dm9051_uip_output(buf, len)`: calls core send.
- `dm9051_uip_stack_init(dev)`: initializes uIP, ARP, MAC, IP, gateway, netmask,
  and timers.
- `dm9051_uip_stack_poll()`: drains RX bursts, runs uIP periodic timers, sends
  generated output frames.

## lwIP adapter API

- `dm9051_if_init(netif)`: sets `netif` name, output callbacks, MTU, flags, and
  initializes hardware.
- `dm9051_lwip_input(netif)`: receives one hardware frame, allocates a pbuf, and
  calls `netif->input`.
- `dm9051_lwip_poll(netif)`: wrapper for `dm9051_lwip_input`.
- `dm9051_lwip_link_is_up()`: returns staged core link status when available,
  otherwise defaults to up.

## Minimal staged initialization example

```c
dm9051_device_t dev;
dm9051_hal_t hal;
dm9051_config_t core_cfg;
dm9051_mh2030a_config_t port_cfg;

dm9051_core_default_config(&core_cfg);
core_cfg.mac_addr = mac;
core_cfg.interrupt_mode = DM9051_INPUT_MODE_POLL;

dm9051_mh2030a_default_config(&port_cfg);
port_cfg.transport = DM9051_MH2030A_TRANSPORT_POLLING;
port_cfg.irq_mode = DM9051_MH2030A_IRQ_OFF;

if (dm9051_mh2030a_hal_bind(&hal, &port_cfg) == DM9051_HAL_OK) {
    (void)dm9051_core_open(&dev, &core_cfg, &hal);
}
```

