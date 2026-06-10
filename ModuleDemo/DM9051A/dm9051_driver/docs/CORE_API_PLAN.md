# Core API Plan

This document defines the staged core API direction. It is documentation only;
the existing production driver remains unchanged.

## Goals

- Keep current legacy entry points available while the Keil/uIP targets are
  migrated.
- Add a context-based API that can eventually support explicit HAL binding and
  more than one device instance.
- Avoid exposing uIP, lwIP, or MH2030A details from `core/inc`.

## Context-Based API

Declared in `core/inc/dm9051_core.h`:

```c
struct dm9051_hal;

int dm9051_core_open(dm9051_device_t *dev,
                     const dm9051_config_t *config,
                     struct dm9051_hal *hal);
int dm9051_core_close(dm9051_device_t *dev);

uint16_t dm9051_core_receive(dm9051_device_t *dev,
                             uint8_t *buf,
                             uint16_t buf_len);
int dm9051_core_send(dm9051_device_t *dev,
                     const uint8_t *buf,
                     uint16_t len);

uint16_t dm9051_core_phy_read(dm9051_device_t *dev, uint16_t reg);
int dm9051_core_phy_write(dm9051_device_t *dev, uint16_t reg, uint16_t value);

void dm9051_core_interrupt_set(dm9051_device_t *dev, uint32_t irq_line);
int dm9051_core_interrupt_take(dm9051_device_t *dev);
void dm9051_core_interrupt_reset(dm9051_device_t *dev);

const uint8_t *dm9051_core_mac(const dm9051_device_t *dev);
```

`struct dm9051_hal` is forward-declared to keep `dm9051_core.h` independent
from `hal/inc/dm9051_hal.h`.

## Legacy Compatibility Mapping

| Current API | Future wrapper behavior |
| --- | --- |
| `dm9051_conf()` | Configure/bind the default static `dm9051_device_t`. |
| `dm9051_init(adr)` | Call `dm9051_core_open(&default_dev, config, hal)` and return active MAC. |
| `dm9051_rx(buf, len)` | Call `dm9051_core_receive(&default_dev, buf, len)`. |
| `dm9051_tx(buf, len)` | Call `dm9051_core_send(&default_dev, buf, len)`. |
| `cspi_phy_read(reg)` | Call `dm9051_core_phy_read(&default_dev, reg)`. |
| `dm9051_interrupt_set(line)` | Call `dm9051_core_interrupt_set(&default_dev, line)`. |
| `dm9051_interrupt_get()` | Call `dm9051_core_interrupt_take(&default_dev)`. |
| `dm9051_interrupt_reset()` | Call `dm9051_core_interrupt_reset(&default_dev)`. |

## Migration Rule

Start with one default static device in `dm9051_core.c` to preserve current
single-instance behavior. After existing uIP targets pass, adapters can be
moved to the context API directly.

## Impact Requirements

Before changing any production implementation for the legacy APIs, run GitNexus
impact analysis for that symbol. Treat `dm9051_rx`, `dm9051_tx`, and
`dm9051_interrupt_*` as HIGH practical risk even if graph impact appears low,
because they are Ethernet hot-path and IRQ-path behavior.

