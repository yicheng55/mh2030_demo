# AT32F403A Port for DM9051 Driver

## Pin Mapping

| Signal | Pin | Peripheral |
|--------|-----|------------|
| CS | PA15 | GPIO, active low |
| SCK | PA5 | SPI1, MUX |
| MISO | PA6 | SPI1, MUX, pull-up |
| MOSI | PA7 | SPI1, MUX |
| INT | PC7 | EXTI Line 7, falling edge |
| RST | PF7 | GPIO, active low pulse |
| UART TX | PA9 | USART1 TX |
| UART RX | PA10 | USART1 RX |

## Feature Flags

| Macro | Default | Description |
|-------|---------|-------------|
| `DM9051_AT32F403A_USE_DMA` | 0 | Enable DMA transport |
| `DM9051_AT32F403A_USE_IRQ` | 0 | Enable EXTI interrupt |
| `DM9051_AT32F403A_DIAG` | 1 | Diagnostic printf output |
| `DM9051_AT32F403A_TRACE` | 0 | Verbose SPI trace |

## Usage

```c
dm9051_device_t dev;
dm9051_hal_t hal;
dm9051_config_t cfg;
dm9051_at32f403a_config_t port_cfg;

at32f403a_uip_board_init(115200);

dm9051_core_default_config(&cfg);
cfg.mac_addr = my_mac;

dm9051_at32f403a_default_config(&port_cfg);
dm9051_at32f403a_hal_bind(&hal, &port_cfg);

dm9051_core_open(&dev, &cfg, &hal);
```

## Files

| File | Role |
|------|------|
| `at32f403a_platform.h` | Platform header aggregator |
| `dm9051_hal_at32f403a_spi1.h` | Port public API + config structs |
| `dm9051_hal_at32f403a_spi1_priv.h` | Private pin mapping + shared helpers |
| `dm9051_hal_at32f403a_spi1.c` | SPI1 polling HAL implementation |
| `dm9051_hal_at32f403a_spi1_dma.c` | DMA transport (STUB) |
| `dm9051_hal_at32f403a_int.c` | EXTI7 IRQ implementation |
| `dm9051_hal_at32f403a_int.h` | IRQ public API |
| `at32f403a_board.c` | Board bring-up (clock, UART) |
| `at32f403a_board.h` | Board init declarations |
| `delay.c` / `delay.h` | SysTick-based delay (ms/us) |
