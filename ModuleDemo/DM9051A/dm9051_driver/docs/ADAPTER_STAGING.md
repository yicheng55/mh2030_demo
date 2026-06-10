# Adapter Staging Notes

This document records the current staging behavior for network-stack adapters.
The production uIP adapter remains unchanged.

## Current Staging Behavior

| Adapter | Function | Behavior |
| --- | --- | --- |
| uIP | `dm9051_uip_init(dev)` | Uses `dm9051_netif_device_is_valid(dev)` and returns `DM9051_ERR_PARAM` for invalid input, otherwise `DM9051_ERR_NOT_READY`. |
| uIP | `dm9051_uip_poll()` | No-op. |
| uIP | `dm9051_uip_target_mode()` | Returns `"staging"`. |
| lwIP | `dm9051_lwip_init(netif, dev)` | Requires non-NULL `netif` and a valid staged netif device; otherwise returns `DM9051_ERR_PARAM`, then `DM9051_ERR_NOT_READY`. |
| lwIP | `dm9051_lwip_poll(netif)` | No-op. |

`dm9051_netif_device_is_valid()` is intentionally permissive at this stage. It
checks only that the device pointer exists; MAC and IP policy should be copied
from the production adapter only after the core/HAL init path is ready.

## Why Not Call uIP/lwIP Yet?

The staged core does not yet perform real chip initialization, RX, or TX.
Calling uIP/lwIP from these adapters would make the API look more complete than
it is. Keep the adapters explicit and quiet until the core/HAL path is wired.

## Future Migration

1. Bind `dm9051_device_t` and `dm9051_hal_t` from the example or board layer.
2. Make adapter init call `dm9051_core_open()`.
3. Move RX/TX stack handling from the production adapter into the staged adapter.
4. Keep MH2030A headers out of adapter source files.
