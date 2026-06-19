#ifndef DM9051_HAL_AT32F403A_INT_H
#define DM9051_HAL_AT32F403A_INT_H

#include "../../core/inc/dm9051_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* IRQ helpers for AT32F403A + DM9051.
 *
 * Conditionally compiled when DM9051_AT32F403A_ENABLE_IRQ=1.
 * Pin: PC7 / EXTI Line 7 / EXTI9_5_IRQn / falling edge.
 */

void dm9051_at32f403a_irq_attach_device(dm9051_device_t *dev);
void dm9051_at32f403a_irq_detach_device(void);
uint32_t dm9051_at32f403a_irq_line(void);
uint32_t dm9051_at32f403a_irq_count(void);
void dm9051_at32f403a_irq_handler(void);

#ifdef __cplusplus
}
#endif

#endif
