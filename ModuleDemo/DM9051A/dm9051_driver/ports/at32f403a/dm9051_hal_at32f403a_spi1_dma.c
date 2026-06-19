#include "dm9051_hal_at32f403a_spi1_dma.h"
#include "dm9051_hal_at32f403a_spi1_priv.h"

#if DM9051_AT32F403A_ENABLE_DMA

#define DM9051_AT32F403A_RX_DMA       DMA1_CHANNEL2
#define DM9051_AT32F403A_TX_DMA       DMA1_CHANNEL3
#define DM9051_AT32F403A_RX_DMA_FLAG  DMA1_FDT2_FLAG
#define DM9051_AT32F403A_TX_DMA_FLAG  DMA1_FDT3_FLAG

#if defined(__GNUC__)
#define DM9051_AT32F403A_DMA_ALIGN4_PREFIX
#define DM9051_AT32F403A_DMA_ALIGN4_SUFFIX __attribute__((aligned(4)))
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define DM9051_AT32F403A_DMA_ALIGN4_PREFIX __align(4)
#define DM9051_AT32F403A_DMA_ALIGN4_SUFFIX
#else
#define DM9051_AT32F403A_DMA_ALIGN4_PREFIX
#define DM9051_AT32F403A_DMA_ALIGN4_SUFFIX
#endif

DM9051_AT32F403A_DMA_ALIGN4_PREFIX
static volatile uint8_t dm9051_at32f403a_dma_dummy_tx_byte
    DM9051_AT32F403A_DMA_ALIGN4_SUFFIX = 0x00u;
DM9051_AT32F403A_DMA_ALIGN4_PREFIX
static volatile uint8_t dm9051_at32f403a_dma_dummy_rx_byte
    DM9051_AT32F403A_DMA_ALIGN4_SUFFIX;

static void dm9051_at32f403a_dma_bus_init(void)
{
    dm9051_at32f403a_spi1_bus_init_common();
    crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
    spi_i2s_dma_enable(DM9051_AT32F403A_SPI,
                       SPI_I2S_DMA_REQUEST_RX | SPI_I2S_DMA_REQUEST_TX,
                       TRUE);

    printf("[AT32F403A] DM9051 SPI bus initialized (DMA transfer)\r\n");
}

static void dm9051_at32f403a_dma_configure(uint8_t *rx,
                                           const uint8_t *tx,
                                           uint16_t len)
{
    dma_init_type dma;

    dma_channel_enable(DM9051_AT32F403A_RX_DMA, FALSE);
    dma_channel_enable(DM9051_AT32F403A_TX_DMA, FALSE);
    dma_flag_clear(DM9051_AT32F403A_RX_DMA, DM9051_AT32F403A_RX_DMA_FLAG);
    dma_flag_clear(DM9051_AT32F403A_TX_DMA, DM9051_AT32F403A_TX_DMA_FLAG);

    dma_reset(DM9051_AT32F403A_RX_DMA);
    dma_default_para_init(&dma);
    dma.peripheral_base_addr = (uint32_t)&DM9051_AT32F403A_SPI->dt;
    dma.memory_base_addr = (uint32_t)rx;
    dma.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
    dma.buffer_size = len;
    dma.peripheral_inc_enable = FALSE;
    dma.memory_inc_enable = (rx == (uint8_t *)&dm9051_at32f403a_dma_dummy_rx_byte) ?
                             FALSE : TRUE;
    dma.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma.loop_mode_enable = FALSE;
    dma.priority = DMA_PRIORITY_VERY_HIGH;
    dma_init(DM9051_AT32F403A_RX_DMA, &dma);

    dma_reset(DM9051_AT32F403A_TX_DMA);
    dma_default_para_init(&dma);
    dma.peripheral_base_addr = (uint32_t)&DM9051_AT32F403A_SPI->dt;
    dma.memory_base_addr = (uint32_t)tx;
    dma.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
    dma.buffer_size = len;
    dma.peripheral_inc_enable = FALSE;
    dma.memory_inc_enable = (tx == (const uint8_t *)&dm9051_at32f403a_dma_dummy_tx_byte) ?
                             FALSE : TRUE;
    dma.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma.loop_mode_enable = FALSE;
    dma.priority = DMA_PRIORITY_VERY_HIGH;
    dma_init(DM9051_AT32F403A_TX_DMA, &dma);
}

static int dm9051_at32f403a_dma_transfer(const dm9051_at32f403a_config_t *config,
                                         uint8_t *rx,
                                         const uint8_t *tx,
                                         uint16_t len)
{
    uint32_t timeout;

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    if ((config == 0) || (rx == 0) || (tx == 0)) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (dm9051_at32f403a_wait_spi_idle(config) != DM9051_HAL_OK) {
        return DM9051_HAL_ERR_TIMEOUT;
    }

    dm9051_at32f403a_dma_configure(rx, tx, len);
    dma_channel_enable(DM9051_AT32F403A_RX_DMA, TRUE);
    dma_channel_enable(DM9051_AT32F403A_TX_DMA, TRUE);

    timeout = config->spi_timeout * (uint32_t)len;
    while (dma_flag_get(DM9051_AT32F403A_RX_DMA, DM9051_AT32F403A_RX_DMA_FLAG) == RESET) {
        if (timeout == 0u) {
            dma_channel_enable(DM9051_AT32F403A_TX_DMA, FALSE);
            dma_channel_enable(DM9051_AT32F403A_RX_DMA, FALSE);
            dma_flag_clear(DM9051_AT32F403A_RX_DMA, DM9051_AT32F403A_RX_DMA_FLAG);
            dma_flag_clear(DM9051_AT32F403A_TX_DMA, DM9051_AT32F403A_TX_DMA_FLAG);
            DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] DMA timeout: RX len=%u\r\n", len);
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }

    timeout = config->spi_timeout * (uint32_t)len;
    while (dma_flag_get(DM9051_AT32F403A_TX_DMA, DM9051_AT32F403A_TX_DMA_FLAG) == RESET) {
        if (timeout == 0u) {
            dma_channel_enable(DM9051_AT32F403A_TX_DMA, FALSE);
            dma_channel_enable(DM9051_AT32F403A_RX_DMA, FALSE);
            dma_flag_clear(DM9051_AT32F403A_RX_DMA, DM9051_AT32F403A_RX_DMA_FLAG);
            dma_flag_clear(DM9051_AT32F403A_TX_DMA, DM9051_AT32F403A_TX_DMA_FLAG);
            DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] DMA timeout: TX len=%u\r\n", len);
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }

    dma_channel_enable(DM9051_AT32F403A_TX_DMA, FALSE);
    dma_channel_enable(DM9051_AT32F403A_RX_DMA, FALSE);
    dma_flag_clear(DM9051_AT32F403A_RX_DMA, DM9051_AT32F403A_RX_DMA_FLAG);
    dma_flag_clear(DM9051_AT32F403A_TX_DMA, DM9051_AT32F403A_TX_DMA_FLAG);

    return dm9051_at32f403a_wait_spi_idle(config);
}

static void dm9051_at32f403a_dma_reset(void *ctx)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;

    dm9051_at32f403a_dma_bus_init();
    dm9051_at32f403a_irq_init_if_enabled(config);
    dm9051_at32f403a_reset_gpio_sequence();
}

static int dm9051_at32f403a_dma_read_mem(void *ctx,
                                         uint8_t *buf,
                                         uint16_t len)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;
    uint8_t dummy;
    int status;

    if ((config == 0) || ((buf == 0) && (len != 0u))) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    dm9051_at32f403a_select();
    status = dm9051_at32f403a_transfer_byte(config,
                                            (uint8_t)(DM9051_MRCMD | DM9051_OPC_REG_R),
                                            &dummy);
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_dma_transfer(config,
                                               buf,
                                               (const uint8_t *)&dm9051_at32f403a_dma_dummy_tx_byte,
                                               len);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_finish_transfer(config);
    } else {
        (void)dm9051_at32f403a_finish_transfer(config);
    }
    dm9051_at32f403a_deselect();

    DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] dma read mem len=%u status=%d\r\n",
                                 len,
                                 status);

    return status;
}

static int dm9051_at32f403a_dma_write_mem(void *ctx,
                                          const uint8_t *buf,
                                          uint16_t len)
{
    const dm9051_at32f403a_config_t *config = (const dm9051_at32f403a_config_t *)ctx;
    uint8_t dummy;
    int status;

    if ((config == 0) || ((buf == 0) && (len != 0u))) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    dm9051_at32f403a_select();
    status = dm9051_at32f403a_transfer_byte(config,
                                            (uint8_t)(DM9051_MWCMD | DM9051_OPC_REG_W),
                                            &dummy);
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_dma_transfer(config,
                                               (uint8_t *)&dm9051_at32f403a_dma_dummy_rx_byte,
                                               buf,
                                               len);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_at32f403a_finish_transfer(config);
    } else {
        (void)dm9051_at32f403a_finish_transfer(config);
    }
    dm9051_at32f403a_deselect();

    DM9051_AT32F403A_DIAG_PRINTF("[DM9051 HAL] dma write mem len=%u status=%d\r\n",
                                 len,
                                 status);

    return status;
}

const dm9051_hal_ops_t dm9051_at32f403a_dma_ops = {
    dm9051_at32f403a_polling_read_reg,
    dm9051_at32f403a_polling_write_reg,
    dm9051_at32f403a_dma_read_mem,
    dm9051_at32f403a_dma_write_mem,
    dm9051_at32f403a_dma_reset,
    dm9051_at32f403a_delay_ms,
    dm9051_at32f403a_delay_us,
    dm9051_at32f403a_irq_enable_if_enabled,
    dm9051_at32f403a_irq_disable_if_enabled,
    dm9051_at32f403a_enter_critical,
    dm9051_at32f403a_exit_critical
};

#endif /* DM9051_AT32F403A_ENABLE_DMA */
