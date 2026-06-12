#include "dm9051_hal_mh2030a_spi1_dma.h"
#include "dm9051_hal_mh2030a_spi1_priv.h"

#if DM9051_MH2030A_ENABLE_DMA

#define DM9051_MH2030A_RX_DMA       DMA1_Channel2
#define DM9051_MH2030A_TX_DMA       DMA1_Channel3
#define DM9051_MH2030A_RX_DMA_FLAG  DMA1_FLAG_TC2
#define DM9051_MH2030A_TX_DMA_FLAG  DMA1_FLAG_TC3

static uint8_t dm9051_mh2030a_dma_dummy_tx_byte = 0x00u;
static uint8_t dm9051_mh2030a_dma_dummy_rx_byte;

static void dm9051_mh2030a_dma_bus_init(void)
{
    dm9051_mh2030a_spi1_polling_bus_init();
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_RemapConfig(DMA1, DMA1_CH2_SPI1_RX);
    DMA_RemapConfig(DMA1, DMA1_CH3_SPI1_TX);
    SPI_I2S_DMACmd(DM9051_MH2030A_SPI,
                   SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx,
                   ENABLE);

    printf("[MH2030A uIP] DM9051 SPI bus initialized (DMA transfer)\r\n");
}

static void dm9051_mh2030a_dma_configure(uint8_t *rx,
                                         const uint8_t *tx,
                                         uint16_t len)
{
    DMA_InitTypeDef dma;

    DMA_Cmd(DM9051_MH2030A_RX_DMA, DISABLE);
    DMA_Cmd(DM9051_MH2030A_TX_DMA, DISABLE);
    DMA_ClearFlag(DM9051_MH2030A_RX_DMA_FLAG | DM9051_MH2030A_TX_DMA_FLAG);

    DMA_DeInit(DM9051_MH2030A_RX_DMA);
    DMA_StructInit(&dma);
    dma.DMA_PeripheralBaseAddr = (uint32_t)&DM9051_MH2030A_SPI->DR;
    dma.DMA_MemoryBaseAddr = (uint32_t)rx;
    dma.DMA_DIR = DMA_DIR_PeripheralSRC;
    dma.DMA_BufferSize = len;
    dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma.DMA_MemoryInc = (rx == &dm9051_mh2030a_dma_dummy_rx_byte) ?
                         DMA_MemoryInc_Disable : DMA_MemoryInc_Enable;
    dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma.DMA_Mode = DMA_Mode_Normal;
    dma.DMA_Priority = DMA_Priority_VeryHigh;
    dma.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DM9051_MH2030A_RX_DMA, &dma);

    DMA_DeInit(DM9051_MH2030A_TX_DMA);
    DMA_StructInit(&dma);
    dma.DMA_PeripheralBaseAddr = (uint32_t)&DM9051_MH2030A_SPI->DR;
    dma.DMA_MemoryBaseAddr = (uint32_t)tx;
    dma.DMA_DIR = DMA_DIR_PeripheralDST;
    dma.DMA_BufferSize = len;
    dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma.DMA_MemoryInc = (tx == &dm9051_mh2030a_dma_dummy_tx_byte) ?
                         DMA_MemoryInc_Disable : DMA_MemoryInc_Enable;
    dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma.DMA_Mode = DMA_Mode_Normal;
    dma.DMA_Priority = DMA_Priority_VeryHigh;
    dma.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DM9051_MH2030A_TX_DMA, &dma);
}

static int dm9051_mh2030a_dma_transfer(const dm9051_mh2030a_config_t *config,
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

    if (dm9051_mh2030a_wait_spi_idle(config) != DM9051_HAL_OK) {
        return DM9051_HAL_ERR_TIMEOUT;
    }

    dm9051_mh2030a_dma_configure(rx, tx, len);
    DMA_Cmd(DM9051_MH2030A_RX_DMA, ENABLE);
    DMA_Cmd(DM9051_MH2030A_TX_DMA, ENABLE);

    timeout = config->spi_timeout * (uint32_t)len;
    while (DMA_GetFlagStatus(DM9051_MH2030A_RX_DMA_FLAG) == RESET) {
        if (timeout == 0u) {
            DMA_Cmd(DM9051_MH2030A_TX_DMA, DISABLE);
            DMA_Cmd(DM9051_MH2030A_RX_DMA, DISABLE);
            DMA_ClearFlag(DM9051_MH2030A_RX_DMA_FLAG | DM9051_MH2030A_TX_DMA_FLAG);
            DM9051_MH2030A_DIAG_PRINTF("[DM9051 HAL] DMA timeout: RX len=%u\r\n", len);
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }

    timeout = config->spi_timeout * (uint32_t)len;
    while (DMA_GetFlagStatus(DM9051_MH2030A_TX_DMA_FLAG) == RESET) {
        if (timeout == 0u) {
            DMA_Cmd(DM9051_MH2030A_TX_DMA, DISABLE);
            DMA_Cmd(DM9051_MH2030A_RX_DMA, DISABLE);
            DMA_ClearFlag(DM9051_MH2030A_RX_DMA_FLAG | DM9051_MH2030A_TX_DMA_FLAG);
            DM9051_MH2030A_DIAG_PRINTF("[DM9051 HAL] DMA timeout: TX len=%u\r\n", len);
            return DM9051_HAL_ERR_TIMEOUT;
        }
        --timeout;
    }

    DMA_Cmd(DM9051_MH2030A_TX_DMA, DISABLE);
    DMA_Cmd(DM9051_MH2030A_RX_DMA, DISABLE);
    DMA_ClearFlag(DM9051_MH2030A_RX_DMA_FLAG | DM9051_MH2030A_TX_DMA_FLAG);

    return dm9051_mh2030a_wait_spi_idle(config);
}

static void dm9051_mh2030a_dma_reset(void *ctx)
{
    const dm9051_mh2030a_config_t *config = (const dm9051_mh2030a_config_t *)ctx;

    dm9051_mh2030a_dma_bus_init();
    dm9051_mh2030a_irq_init_if_enabled(config);
    dm9051_mh2030a_reset_gpio_sequence();
}

static int dm9051_mh2030a_dma_read_mem(void *ctx,
                                       uint8_t *buf,
                                       uint16_t len)
{
    const dm9051_mh2030a_config_t *config = (const dm9051_mh2030a_config_t *)ctx;
    uint8_t dummy;
    int status;

    if ((config == 0) || ((buf == 0) && (len != 0u))) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    dm9051_mh2030a_select();
    status = dm9051_mh2030a_transfer_byte(config,
                                          (uint8_t)(DM9051_MRCMD | DM9051_OPC_REG_R),
                                          &dummy);
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_dma_transfer(config,
                                             buf,
                                             &dm9051_mh2030a_dma_dummy_tx_byte,
                                             len);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_finish_transfer(config);
    } else {
        (void)dm9051_mh2030a_finish_transfer(config);
    }
    dm9051_mh2030a_deselect();

    return status;
}

static int dm9051_mh2030a_dma_write_mem(void *ctx,
                                        const uint8_t *buf,
                                        uint16_t len)
{
    const dm9051_mh2030a_config_t *config = (const dm9051_mh2030a_config_t *)ctx;
    uint8_t dummy;
    int status;

    if ((config == 0) || ((buf == 0) && (len != 0u))) {
        return DM9051_HAL_ERR_PARAM;
    }

    if (len == 0u) {
        return DM9051_HAL_OK;
    }

    dm9051_mh2030a_select();
    status = dm9051_mh2030a_transfer_byte(config,
                                          (uint8_t)(DM9051_MWCMD | DM9051_OPC_REG_W),
                                          &dummy);
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_dma_transfer(config,
                                             &dm9051_mh2030a_dma_dummy_rx_byte,
                                             buf,
                                             len);
    }
    if (status == DM9051_HAL_OK) {
        status = dm9051_mh2030a_finish_transfer(config);
    } else {
        (void)dm9051_mh2030a_finish_transfer(config);
    }
    dm9051_mh2030a_deselect();

    DM9051_MH2030A_DIAG_PRINTF("[DM9051 HAL] dma write mem len=%u status=%d\r\n",
                               len,
                               status);

    return status;
}

const dm9051_hal_ops_t dm9051_mh2030a_dma_ops = {
    dm9051_mh2030a_polling_read_reg,
    dm9051_mh2030a_polling_write_reg,
    dm9051_mh2030a_dma_read_mem,
    dm9051_mh2030a_dma_write_mem,
    dm9051_mh2030a_dma_reset,
    dm9051_mh2030a_delay_ms,
    dm9051_mh2030a_delay_us,
    dm9051_mh2030a_irq_enable_if_enabled,
    dm9051_mh2030a_irq_disable_if_enabled,
    0,
    0
};

#endif /* DM9051_MH2030A_ENABLE_DMA */
