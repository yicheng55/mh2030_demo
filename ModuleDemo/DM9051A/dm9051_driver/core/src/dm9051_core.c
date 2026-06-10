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

static int dm9051_core_hal_status(int status)
{
    if (status == DM9051_HAL_OK) {
        return DM9051_OK;
    }

    if (status == DM9051_HAL_ERR_TIMEOUT) {
        return DM9051_ERR_TIMEOUT;
    }

    if (status == DM9051_HAL_ERR_PARAM) {
        return DM9051_ERR_PARAM;
    }

    return DM9051_ERR_NOT_READY;
}

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

static int dm9051_core_read_reg(const dm9051_hal_t *hal,
                                uint8_t reg,
                                uint8_t *val)
{
    if ((hal == 0) || (hal->ops == 0) || (hal->ops->read_reg == 0)) {
        return DM9051_ERR_PARAM;
    }

    return dm9051_core_hal_status(hal->ops->read_reg(hal->ctx, reg, val));
}

static int dm9051_core_write_reg(const dm9051_hal_t *hal,
                                 uint8_t reg,
                                 uint8_t val)
{
    if ((hal == 0) || (hal->ops == 0) || (hal->ops->write_reg == 0)) {
        return DM9051_ERR_PARAM;
    }

    return dm9051_core_hal_status(hal->ops->write_reg(hal->ctx, reg, val));
}

static int dm9051_core_read_mem(const dm9051_hal_t *hal,
                                uint8_t *buf,
                                uint16_t len)
{
    if ((hal == 0) || (hal->ops == 0) || (hal->ops->read_mem == 0)) {
        return DM9051_ERR_PARAM;
    }

    return dm9051_core_hal_status(hal->ops->read_mem(hal->ctx, buf, len));
}

static int dm9051_core_probe(dm9051_device_t *dev, const dm9051_hal_t *hal)
{
    uint8_t vidl;
    uint8_t vidh;
    uint8_t pidl;
    uint8_t pidh;
    uint8_t chipr;
    int status;

    if ((dev == 0) || (hal == 0)) {
        return DM9051_ERR_PARAM;
    }

    status = dm9051_core_read_reg(hal, DM9051_VIDL, &vidl);
    if (status != DM9051_OK) {
        return status;
    }

    status = dm9051_core_read_reg(hal, DM9051_VIDH, &vidh);
    if (status != DM9051_OK) {
        return status;
    }

    status = dm9051_core_read_reg(hal, DM9051_PIDL, &pidl);
    if (status != DM9051_OK) {
        return status;
    }

    status = dm9051_core_read_reg(hal, DM9051_PIDH, &pidh);
    if (status != DM9051_OK) {
        return status;
    }

    status = dm9051_core_read_reg(hal, DM9051_CHIPR, &chipr);
    if (status != DM9051_OK) {
        return status;
    }

    dev->runtime.vendor_id = (uint16_t)((uint16_t)vidl | ((uint16_t)vidh << 8));
    dev->runtime.product_id = (uint16_t)((uint16_t)pidl | ((uint16_t)pidh << 8));
    dev->runtime.chip_revision = chipr;

    if ((dev->runtime.vendor_id != DM9051_VENDOR_ID) ||
        (dev->runtime.product_id != DM9051_PRODUCT_ID)) {
        return DM9051_ERR_NOT_READY;
    }

    if (chipr == 0xffu) {
        return DM9051_ERR_NOT_READY;
    }

    dev->runtime.device_found = 1u;
    return DM9051_OK;
}

static int dm9051_core_set_par(dm9051_device_t *dev, const dm9051_hal_t *hal)
{
    uint8_t i;
    int status;

    for (i = 0u; i < DM9051_MAC_ADDR_LENGTH; ++i) {
        status = dm9051_core_write_reg(hal,
                                       (uint8_t)(DM9051_PAR + i),
                                       dev->runtime.current_mac[i]);
        if (status != DM9051_OK) {
            return status;
        }
    }

    return DM9051_OK;
}

static int dm9051_core_set_mar(const dm9051_hal_t *hal)
{
    uint8_t i;
    int status;

    for (i = 0u; i < 8u; ++i) {
        status = dm9051_core_write_reg(hal,
                                       (uint8_t)(DM9051_MAR + i),
                                       (i == 7u) ? 0x80u : 0x00u);
        if (status != DM9051_OK) {
            return status;
        }
    }

    return DM9051_OK;
}

static uint8_t dm9051_core_imr_value(const dm9051_config_t *config)
{
    if (config->interrupt_mode == DM9051_INPUT_MODE_POLL) {
        return DM9051_IMR_POL_DEFAULT;
    }

    return DM9051_IMR_INT_DEFAULT;
}

static uint8_t dm9051_core_rcr_value(const dm9051_config_t *config)
{
    uint8_t value = (uint8_t)(DM9051_RCR_DEFAULT | DM9051_RCR_RXEN);

    if (config->accept_all != 0u) {
        value = (uint8_t)(value | DM9051_RCR_ALL | DM9051_RCR_PRMSC);
    }

    return value;
}

static int dm9051_core_init_device(dm9051_device_t *dev,
                                   const dm9051_hal_t *hal)
{
    int status;

    status = dm9051_core_write_reg(hal, DM9051_GPR, 0x00u);
    if (status != DM9051_OK) {
        return status;
    }
    hal->ops->delay_ms(25u);

    status = dm9051_core_write_reg(hal, DM9051_NCR, DM9051_NCR_RESET);
    if (status != DM9051_OK) {
        return status;
    }
    hal->ops->delay_ms(5u);

    status = dm9051_core_set_par(dev, hal);
    if (status != DM9051_OK) {
        return status;
    }

    status = dm9051_core_set_mar(hal);
    if (status != DM9051_OK) {
        return status;
    }

    status = dm9051_core_write_reg(hal,
                                   DM9051_IMR,
                                   dm9051_core_imr_value(&dev->runtime.config));
    if (status != DM9051_OK) {
        return status;
    }

    return dm9051_core_write_reg(hal,
                                 DM9051_RCR,
                                 dm9051_core_rcr_value(&dev->runtime.config));
}

static uint16_t dm9051_core_rx_pad_len(uint16_t len)
{
    return len;
}

static int dm9051_core_rx_ready(const dm9051_hal_t *hal, uint8_t *ready_byte)
{
    uint8_t value;
    int status;

    status = dm9051_core_read_reg(hal, DM9051_MRCMDX, &value);
    if (status != DM9051_OK) {
        return status;
    }

    status = dm9051_core_read_reg(hal, DM9051_MRCMDX, &value);
    if (status != DM9051_OK) {
        return status;
    }

    if (ready_byte != 0) {
        *ready_byte = value;
    }

    if (value == 0u) {
        return DM9051_ERR_NOT_READY;
    }

    if (value != DM9051_PKT_RDY) {
        return DM9051_ERR;
    }

    return DM9051_OK;
}

static int dm9051_core_rx_header(const dm9051_hal_t *hal,
                                 uint8_t header[DM9051_RX_HEAD_SIZE],
                                 uint16_t *rx_len)
{
    uint8_t rx_status;
    int status;

    if ((header == 0) || (rx_len == 0)) {
        return DM9051_ERR_PARAM;
    }

    status = dm9051_core_read_mem(hal, header, DM9051_RX_HEAD_SIZE);
    if (status != DM9051_OK) {
        return status;
    }

    status = dm9051_core_write_reg(hal, DM9051_ISR, DM9051_ISR_CLEAR_RX);
    if (status != DM9051_OK) {
        return status;
    }

    rx_status = header[1];
    *rx_len = (uint16_t)((uint16_t)header[2] | ((uint16_t)header[3] << 8));

    if ((rx_status & DM9051_RSR_ERR_BITS) != 0u) {
        return DM9051_ERR;
    }

    if ((*rx_len == 0u) || (*rx_len > DM9051_ETH_FRAME_MAX)) {
        return DM9051_ERR;
    }

    return DM9051_OK;
}

static int dm9051_core_rx_discard(const dm9051_hal_t *hal, uint16_t len)
{
    uint8_t drop[32];
    uint16_t left = dm9051_core_rx_pad_len(len);
    uint16_t chunk;
    int status;

    while (left != 0u) {
        chunk = (left > sizeof(drop)) ? (uint16_t)sizeof(drop) : left;
        status = dm9051_core_read_mem(hal, drop, chunk);
        if (status != DM9051_OK) {
            return status;
        }
        left = (uint16_t)(left - chunk);
    }

    return dm9051_core_write_reg(hal, DM9051_ISR, DM9051_ISR_CLEAR_RX);
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
    int status;

    if ((dev == 0) ||
        !dm9051_core_config_is_valid(config) ||
        !dm9051_core_hal_is_valid((const dm9051_hal_t *)hal)) {
        return DM9051_ERR_PARAM;
    }

    dev->runtime.config = *config;
    dev->runtime.irq_line = 0u;
    dev->runtime.interrupt_event = 0u;
    dev->runtime.device_found = 0u;
    dev->runtime.vendor_id = 0u;
    dev->runtime.product_id = 0u;
    dev->runtime.chip_revision = 0u;
    dev->hal = hal;

    if (config->mac_addr != 0) {
        (void)memcpy(dev->runtime.current_mac,
                     config->mac_addr,
                     DM9051_MAC_ADDR_LENGTH);
    } else {
        (void)memset(dev->runtime.current_mac, 0, DM9051_MAC_ADDR_LENGTH);
    }

    if (((dm9051_hal_t *)hal)->ops->reset != 0) {
        ((dm9051_hal_t *)hal)->ops->reset(((dm9051_hal_t *)hal)->ctx);
    }

    status = dm9051_core_probe(dev, (const dm9051_hal_t *)hal);
    if (status != DM9051_OK) {
        return status;
    }

    return dm9051_core_init_device(dev, (const dm9051_hal_t *)hal);
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
    const dm9051_hal_t *hal;
    uint8_t ready_byte;
    uint8_t header[DM9051_RX_HEAD_SIZE];
    uint16_t rx_len;
    int status;

    if ((dev == 0) || (dev->hal == 0)) {
        return 0u;
    }

    hal = (const dm9051_hal_t *)dev->hal;
    status = dm9051_core_rx_ready(hal, &ready_byte);
    if (status != DM9051_OK) {
        return 0u;
    }

    status = dm9051_core_rx_header(hal, header, &rx_len);
    if (status != DM9051_OK) {
        return 0u;
    }

    if ((buf == 0) || (buf_len < rx_len)) {
        (void)dm9051_core_rx_discard(hal, rx_len);
        return 0u;
    }

    status = dm9051_core_read_mem(hal, buf, dm9051_core_rx_pad_len(rx_len));
    if (status != DM9051_OK) {
        return 0u;
    }

    status = dm9051_core_write_reg(hal, DM9051_ISR, DM9051_ISR_CLEAR_RX);
    if (status != DM9051_OK) {
        return 0u;
    }

    return rx_len;
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

int dm9051_core_device_found(const dm9051_device_t *dev)
{
    if (dev == 0) {
        return 0;
    }

    return dev->runtime.device_found != 0u;
}

uint16_t dm9051_core_vendor_id(const dm9051_device_t *dev)
{
    if (dev == 0) {
        return 0u;
    }

    return dev->runtime.vendor_id;
}

uint16_t dm9051_core_product_id(const dm9051_device_t *dev)
{
    if (dev == 0) {
        return 0u;
    }

    return dev->runtime.product_id;
}

uint8_t dm9051_core_chip_revision(const dm9051_device_t *dev)
{
    if (dev == 0) {
        return 0u;
    }

    return dev->runtime.chip_revision;
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
