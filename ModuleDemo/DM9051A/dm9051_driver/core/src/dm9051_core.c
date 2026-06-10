/*
 * Future stack-neutral DM9051 core implementation.
 *
 * Current source of truth:
 *   drivers/dm9051_edriver_v1.6.1a_beta/core/dm9051_beta.c
 *
 * Planned internal sections:
 *   - public API compatibility wrappers
 *   - init/configuration
 *   - MAC address handling
 *   - register/PHY helpers
 *   - IRQ/event state
 *   - RX path
 *   - TX path
 *
 * Keep this file out of existing builds until the compatibility shim is ready.
 */

#include "dm9051_core.h"
#include "dm9051_hal.h"

#include <string.h>

/* -------------------------------------------------------------------------
 * Staging rules
 * -------------------------------------------------------------------------
 *
 * - Do not include uIP, lwIP, or MH2030A platform headers here.
 * - Keep RX/TX/PHY/IRQ in this file as internal sections for now.
 * - Move only diagnostics/logging helpers to dm9051_debug.c.
 * - Add production symbols only after running impact analysis for each public
 *   function being copied or changed.
 */

/* -------------------------------------------------------------------------
 * Driver state
 * ---------------------------------------------------------------------- */

/* Future owner for dm9051_internal.h state:
 *   - instance configuration
 *   - interrupt event flag
 *   - EXTI line
 *   - HAL binding pointer/context
 */

/* Staging state model:
 *   dm9051_device_t
 *     runtime.config
 *     runtime.current_mac
 *     runtime.irq_line
 *     runtime.interrupt_event
 *     runtime.device_found
 *     hal
 *
 * The `hal` member is intentionally opaque here because dm9051_types.h should
 * stay independent from hal/inc. dm9051_core.c will cast it to dm9051_hal_t
 * once the staged implementation is wired.
 */

static int dm9051_core_hal_is_valid(const dm9051_hal_t *hal)
{
    if ((hal == 0) || (hal->ops == 0)) {
        return 0;
    }

    if ((hal->ops->read_reg == 0) ||
        (hal->ops->write_reg == 0) ||
        (hal->ops->read_mem == 0) ||
        (hal->ops->write_mem == 0) ||
        (hal->ops->delay_ms == 0) ||
        (hal->ops->delay_us == 0)) {
        return 0;
    }

    return 1;
}

/* -------------------------------------------------------------------------
 * Public API compatibility wrappers
 * ---------------------------------------------------------------------- */

/* Future public API location:
 *   dm9051_conf
 *   dm9051_init
 *   dm9051_rx
 *   dm9051_tx
 *   cspi_phy_read
 *   dm9051_interrupt_set
 *   dm9051_interrupt_get
 *   dm9051_interrupt_reset
 */

void dm9051_core_default_config(dm9051_config_t *config)
{
    if (config == 0) {
        return;
    }

    (void)memset(config, 0, sizeof(*config));
    config->interrupt_mode = DM9051_INPUT_MODE_POLL;
}

int dm9051_core_config_is_valid(const dm9051_config_t *config)
{
    if (config == 0) {
        return 0;
    }

    if ((config->interrupt_mode != DM9051_INPUT_MODE_POLL) &&
        (config->interrupt_mode != DM9051_INPUT_MODE_INTERRUPT) &&
        (config->interrupt_mode != DM9051_INPUT_MODE_INTERRUPT_CLKOUT)) {
        return 0;
    }

    return 1;
}

int dm9051_netif_device_is_valid(const dm9051_netif_device_t *dev)
{
    if (dev == 0) {
        return 0;
    }

    return 1;
}

int dm9051_core_open(dm9051_device_t *dev,
                     const dm9051_config_t *config,
                     struct dm9051_hal *hal)
{
    if ((dev == 0) ||
        !dm9051_core_config_is_valid(config) ||
        !dm9051_core_hal_is_valid((const dm9051_hal_t *)hal)) {
        return DM9051_ERR_PARAM;
    }

    dev->runtime.config = *config;
    dev->runtime.irq_line = 0u;
    dev->runtime.interrupt_event = 0u;
    dev->runtime.device_found = 0u;
    dev->hal = hal;

    if (config->mac_addr != 0) {
        (void)memcpy(dev->runtime.current_mac,
                     config->mac_addr,
                     DM9051_MAC_ADDR_LENGTH);
    } else {
        (void)memset(dev->runtime.current_mac, 0, DM9051_MAC_ADDR_LENGTH);
    }

    return DM9051_ERR_NOT_READY;
}

int dm9051_core_close(dm9051_device_t *dev)
{
    if (dev == 0) {
        return DM9051_ERR_PARAM;
    }

    (void)memset(dev, 0, sizeof(*dev));
    return DM9051_OK;
}

uint16_t dm9051_core_receive(dm9051_device_t *dev,
                             uint8_t *buf,
                             uint16_t buf_len)
{
    (void)dev;
    (void)buf;
    (void)buf_len;
    return 0u;
}

int dm9051_core_send(dm9051_device_t *dev, const uint8_t *buf, uint16_t len)
{
    (void)dev;
    (void)buf;
    (void)len;
    return DM9051_ERR_NOT_READY;
}

uint16_t dm9051_core_phy_read(dm9051_device_t *dev, uint16_t reg)
{
    (void)dev;
    (void)reg;
    return 0xffffu;
}

int dm9051_core_phy_write(dm9051_device_t *dev, uint16_t reg, uint16_t value)
{
    (void)dev;
    (void)reg;
    (void)value;
    return DM9051_ERR_NOT_READY;
}

void dm9051_core_interrupt_set(dm9051_device_t *dev, uint32_t irq_line)
{
    if (dev == 0) {
        return;
    }

    dev->runtime.irq_line = irq_line;
    dev->runtime.interrupt_event = 1u;
}

int dm9051_core_interrupt_take(dm9051_device_t *dev)
{
    if (dev == 0) {
        return 0;
    }

    if (dev->runtime.interrupt_event == 0u) {
        return 0;
    }

    dev->runtime.interrupt_event = 0u;
    return 1;
}

void dm9051_core_interrupt_reset(dm9051_device_t *dev)
{
    if (dev == 0) {
        return;
    }

    dev->runtime.interrupt_event = 0u;
}

const uint8_t *dm9051_core_mac(const dm9051_device_t *dev)
{
    if (dev == 0) {
        return 0;
    }

    return dev->runtime.current_mac;
}

/* -------------------------------------------------------------------------
 * Init / configuration
 * ---------------------------------------------------------------------- */

/* Future internal owner for:
 *   cspi_core_reset
 *   cspi_soft_default
 *   cspi_core_start1
 *   env_chip_id_and_ticks
 *   check_force_stop
 *   cspi_get_chipid
 *   cspi_get_control_status
 */

/* -------------------------------------------------------------------------
 * MAC address handling
 * ---------------------------------------------------------------------- */

/* Future internal owner for:
 *   is_zero_ether_addr
 *   validate_macaddr
 *   cspi_macaddr_process
 *   cspi_get_par
 *   cspi_set_par
 */

/* -------------------------------------------------------------------------
 * Register / PHY helpers
 * ---------------------------------------------------------------------- */

/* Future internal owner for:
 *   cspi_write_regs
 *   cspi_read_regs
 *   cspi_phy_read
 *   cspi_phy_write
 *   cspi_phycore_on
 */

/* -------------------------------------------------------------------------
 * IRQ / event state
 * ---------------------------------------------------------------------- */

/* Future internal owner for:
 *   conf_ext_line
 *   dm9051_isr_enab
 *   dm9051_imr_disab
 *   dm9051_imr_enab
 *   cspi_set_imr
 *   cspi_disble_irq
 *   cspi_enable_irq
 */

/* -------------------------------------------------------------------------
 * RX path
 * ---------------------------------------------------------------------- */

/* Future internal owner for:
 *   cspi_set_recv
 *   cspi_set_mar
 *   cspi_set_fcr
 *   cspi_set_rcr
 *   cspi_rx_ready
 *   cspi_rx_head
 *   rx_head_takelen
 *   cspi_rx_read
 *   cspi_rx_discard
 *   cspi_get_rwpa
 *   cspi_get_mrrl
 *   rx_pointers_equ
 */

/* -------------------------------------------------------------------------
 * TX path
 * ---------------------------------------------------------------------- */

/* Future internal owner for:
 *   cspi_tx_len
 *   cspi_tx_packet_len
 *   cspi_tx_write
 *   cspi_tx_req
 */
