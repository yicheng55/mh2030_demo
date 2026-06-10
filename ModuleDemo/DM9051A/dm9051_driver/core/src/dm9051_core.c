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
