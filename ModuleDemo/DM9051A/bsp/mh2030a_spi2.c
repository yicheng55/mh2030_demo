/**
 * @file    mh2030a_spi2.c
 * @brief   SPI2 bus driver for MH2030A — hardware layer for DM9051A.
 *
 * Peripheral mapping
 * ──────────────────
 *  SPI2  APB1  (max 36 MHz @ PCLK=72 MHz, prescaler≥2)
 *  GPIOA AHB   PA9=CS  PA11=SCK  PA12=MISO  PA8=MOSI  (AF0)
 *  GPIOF AHB   PF7=RST  PF6=INT
 *  DMA1  AHB   CH4=SPI2_RX (remap)   CH5=SPI2_TX (remap)
 *  SYSCFG APB2  for EXTI mapping and DMA remap
 *
 * SPI mode: CPOL=Low, CPHA=2Edge.
 */

#include <stddef.h>
#include "mh2030a_spi2.h"
#include "mh20xx_dma.h"

#define MH2030A_SPI2_XFER_TIMEOUT   (1000000u)

/* -----------------------------------------------------------------------
 * Internal DMA dummy buffers (used when caller passes NULL)
 * ----------------------------------------------------------------------- */
static uint8_t  s_dma_dummy_tx = 0xFFu;
static uint8_t  s_dma_dummy_rx;
static MH2030A_SPI2_Status s_spi2_last_status = MH2030A_SPI2_OK;

/* -----------------------------------------------------------------------
 * MH2030A_SPI2_Init
 * ----------------------------------------------------------------------- */
void MH2030A_SPI2_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef   SPI_InitStructure;
    DMA_InitTypeDef   DMA_InitStructure;
    EXTI_InitTypeDef  EXTI_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    /* ------------------------------------------------------------------
     * 1. Enable clocks
     * ------------------------------------------------------------------ */
    RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOF |
                           RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* ------------------------------------------------------------------
    * 2. GPIO – SPI2 pins (PA8/11/12 → AF0)
     * ------------------------------------------------------------------ */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,  GPIO_AF_0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_0);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ------------------------------------------------------------------
    * 3. GPIO – CS (PA9) output, initially de-asserted (high)
     * ------------------------------------------------------------------ */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    DM9051A_CS_H();

    /* ------------------------------------------------------------------
     * 4. GPIO – RST (PF7) output, initially asserted low
     *          INT (PF6) input with pull-up
     * ------------------------------------------------------------------ */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    DM9051A_RST_L(); /* hold in reset until dm9051a_init calls RST_H */

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* ------------------------------------------------------------------
    * 5. SPI2 – CPOL=Low, CPHA=2Edge, 8-bit, MSB-first
     *    Start slow (prescaler 256 ≈ 281 kHz), speed up after ID check.
     * ------------------------------------------------------------------ */
    SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial     = 7;
    SPI_Init(SPI2, &SPI_InitStructure);
    SPI_Cmd(SPI2, ENABLE);

    /* ------------------------------------------------------------------
     * 6. DMA – remap CH4→SPI2_RX, CH5→SPI2_TX then configure both
     * ------------------------------------------------------------------ */
    DMA_RemapConfig(DMA1, DMA1_CH4_SPI2_RX);
    DMA_RemapConfig(DMA1, DMA1_CH5_SPI2_TX);

    /* CH4 – SPI2 RX (peripheral → memory) */
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)&s_dma_dummy_rx;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = 1;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);

    /* CH5 – SPI2 TX (memory → peripheral) */
    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)&s_dma_dummy_tx;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);

    /* Wire SPI2 DMA requests */
    SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
    SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);

    /* ------------------------------------------------------------------
     * 7. EXTI – PF6 falling-edge (DM9051A active-low INT)
     * ------------------------------------------------------------------ */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource6);

    EXTI_InitStructure.EXTI_Line    = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearITPendingBit(EXTI_Line6);

    /* EXTI4_15_IRQn covers lines 4-15 on MH20xx (Cortex-M0 style) */
    NVIC_InitStructure.NVIC_IRQChannel         = EXTI4_15_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/* -----------------------------------------------------------------------
 * MH2030A_SPI2_ReadWriteByte  (polling)
 * ----------------------------------------------------------------------- */
uint8_t MH2030A_SPI2_ReadWriteByte(uint8_t data)
{
    uint8_t rx_data = 0xFFu;

    (void)MH2030A_SPI2_ReadWriteByteChecked(data, &rx_data);
    return rx_data;
}

MH2030A_SPI2_Status MH2030A_SPI2_ReadWriteByteChecked(uint8_t data, uint8_t *pRx)
{
    uint32_t timeout;

    timeout = MH2030A_SPI2_XFER_TIMEOUT;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) {
        if (--timeout == 0u) {
            s_spi2_last_status = MH2030A_SPI2_ERR_TXE_TIMEOUT;
            return s_spi2_last_status;
        }
    }

    SPI_SendData8(SPI2, data);

    timeout = MH2030A_SPI2_XFER_TIMEOUT;
    while (SPI_GetReceptionFIFOStatus(SPI2) == SPI_ReceptionFIFOStatus_Empty) {
        if (--timeout == 0u) {
            s_spi2_last_status = MH2030A_SPI2_ERR_RX_TIMEOUT;
            return s_spi2_last_status;
        }
    }

    if (pRx != NULL) {
        *pRx = SPI_ReceiveData8(SPI2);
    } else {
        (void)SPI_ReceiveData8(SPI2);
    }

    s_spi2_last_status = MH2030A_SPI2_OK;
    return s_spi2_last_status;
}

/* -----------------------------------------------------------------------
 * MH2030A_SPI2_DMATransfer
 * ----------------------------------------------------------------------- */
void MH2030A_SPI2_DMATransfer(const uint8_t *pTx, uint8_t *pRx, uint16_t len)
{
    /* -- Disable channels before reconfiguring -- */
    DMA_Cmd(DMA1_Channel4, DISABLE);
    DMA_Cmd(DMA1_Channel5, DISABLE);

    DMA_ClearFlag(DMA1_FLAG_TC4 | DMA1_FLAG_TC5 |
                  DMA1_FLAG_TE4 | DMA1_FLAG_TE5);

    /* -- RX channel (CH4) -- */
    DMA1_Channel4->CCR  &= ~DMA_CCR_EN;
    DMA1_Channel4->CNDTR = len;
    if (pRx != NULL) {
        DMA1_Channel4->CMAR  = (uint32_t)pRx;
        DMA1_Channel4->CCR  |= DMA_CCR_MINC;   /* memory increment */
    } else {
        DMA1_Channel4->CMAR  = (uint32_t)&s_dma_dummy_rx;
        DMA1_Channel4->CCR  &= ~DMA_CCR_MINC;  /* discard into dummy */
    }

    /* -- TX channel (CH5) -- */
    DMA1_Channel5->CCR  &= ~DMA_CCR_EN;
    DMA1_Channel5->CNDTR = len;
    if (pTx != NULL) {
        DMA1_Channel5->CMAR  = (uint32_t)pTx;
        DMA1_Channel5->CCR  |= DMA_CCR_MINC;
    } else {
        s_dma_dummy_tx       = 0xFFu;
        DMA1_Channel5->CMAR  = (uint32_t)&s_dma_dummy_tx;
        DMA1_Channel5->CCR  &= ~DMA_CCR_MINC;
    }

    /* -- Start both channels simultaneously -- */
    DMA_Cmd(DMA1_Channel4, ENABLE);
    DMA_Cmd(DMA1_Channel5, ENABLE);

    /* -- Wait for TX complete (RX finishes at the same time) -- */
    while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) {}

    DMA_Cmd(DMA1_Channel4, DISABLE);
    DMA_Cmd(DMA1_Channel5, DISABLE);

    DMA_ClearFlag(DMA1_FLAG_TC4 | DMA1_FLAG_TC5);
}

/* -----------------------------------------------------------------------
 * MH2030A_SPI2_SetSpeed
 * ----------------------------------------------------------------------- */
void MH2030A_SPI2_SetSpeed(uint8_t prescaler)
{
    SPI_Cmd(SPI2, DISABLE);
    SPI2->CR1 = (SPI2->CR1 & ~SPI_CR1_BR) | (prescaler & SPI_CR1_BR);
    SPI_Cmd(SPI2, ENABLE);
}

MH2030A_SPI2_Status MH2030A_SPI2_GetLastStatus(void)
{
    return s_spi2_last_status;
}

void MH2030A_SPI2_ClearLastStatus(void)
{
    s_spi2_last_status = MH2030A_SPI2_OK;
}
