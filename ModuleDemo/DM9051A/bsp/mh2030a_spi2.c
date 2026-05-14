#include "mh2030a_spi2.h"
#include "delay.h"
#if DM9058_SPI_DEBUG
#include <stdio.h>
#endif

#define DM9058_SPI               SPI2

/* Schematic:
 *   PA8  -> SPI2_MOSI
 *   PA9  -> SPI_CS, driven as GPIO
 *   PA11 -> SPI2_SCK
 *   PA12 -> SPI2_MISO
 */
#define DM9058_GPIO_PORT         GPIOA
#define DM9058_PIN_MOSI          GPIO_Pin_8
#define DM9058_PIN_CS            GPIO_Pin_9
#define DM9058_PIN_SCK           GPIO_Pin_11
#define DM9058_PIN_MISO          GPIO_Pin_12

#define DM9058_RST_PORT          GPIOF
#define DM9058_RST_PIN           GPIO_Pin_7

#if DM9058_SPI_DEBUG
#define DM9058_DBG_PRINT         printf

static void DM9058_DebugPrintPinState(void)
{
    DM9058_DBG_PRINT("[DM9058 DBG] GPIOA MODER=0x%08lX IDR=0x%04X ODR=0x%04X AFRH=0x%08lX\r\n",
                     GPIOA->MODER, GPIOA->IDR, GPIOA->ODR, GPIOA->AFR[1]);
    DM9058_DBG_PRINT("[DM9058 DBG] GPIOF MODER=0x%08lX IDR=0x%04X ODR=0x%04X\r\n",
                     GPIOF->MODER, GPIOF->IDR, GPIOF->ODR);
    DM9058_DBG_PRINT("[DM9058 DBG] Pins CS(PA9)=%u RST(PF7)=%u MISO(PA12)=%u\r\n",
                     (GPIOA->IDR & DM9058_PIN_CS) ? 1u : 0u,
                     (GPIOF->IDR & DM9058_RST_PIN) ? 1u : 0u,
                     (GPIOA->IDR & DM9058_PIN_MISO) ? 1u : 0u);
}

static void DM9058_DebugPrintSpiState(void)
{
    DM9058_DBG_PRINT("[DM9058 DBG] SPI2 CR1=0x%04X CR2=0x%04X SR=0x%04X I2SCFGR=0x%04X\r\n",
                     DM9058_SPI->CR1, DM9058_SPI->CR2, DM9058_SPI->SR, DM9058_SPI->I2SCFGR);
}
#endif

void MH2030A_SPI2_Init(void)
{
    GPIO_InitTypeDef gpio;
    SPI_InitTypeDef spi;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_PIN_CS;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_10MHz;             // GPIO_Speed_50MHz, GPIO_Speed_10MHz
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DM9058_GPIO_PORT, &gpio);
    DM9058_CS_High();

    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_RST_PIN;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_10MHz;             // GPIO_Speed_50MHz, GPIO_Speed_10MHz
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DM9058_RST_PORT, &gpio);
    DM9058_HardwareReset();

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_8);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_8);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_8);

    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_PIN_MOSI | DM9058_PIN_SCK | DM9058_PIN_MISO;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_10MHz;             // GPIO_Speed_50MHz, GPIO_Speed_10MHz
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(DM9058_GPIO_PORT, &gpio);

    SPI_I2S_DeInit(DM9058_SPI);
    SPI_StructInit(&spi);
    spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi.SPI_Mode = SPI_Mode_Master;
    spi.SPI_DataSize = SPI_DataSize_8b;
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_CPHA = SPI_CPHA_1Edge;
    spi.SPI_NSS = SPI_NSS_Soft;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    spi.SPI_FirstBit = SPI_FirstBit_MSB;
    spi.SPI_CRCPolynomial = 7;
    SPI_Init(DM9058_SPI, &spi);
    SPI_RxFIFOThresholdConfig(DM9058_SPI, SPI_RxFIFOThreshold_QF);
    SPI_Cmd(DM9058_SPI, ENABLE);

#if DM9058_SPI_DEBUG
    DM9058_DBG_PRINT("[DM9058 DBG] SPI2 init done\r\n");
    DM9058_DebugPrintPinState();
    DM9058_DebugPrintSpiState();
#endif
}

uint8_t MH2030A_SPI2_Transfer(uint8_t tx)
{
    uint32_t timeout;

    timeout = 1000000u;
    while (SPI_I2S_GetFlagStatus(DM9058_SPI, SPI_I2S_FLAG_TXE) == RESET) {
        if (--timeout == 0u) {
#if DM9058_SPI_DEBUG
            DM9058_DBG_PRINT("[DM9058 DBG] TXE timeout, SR=0x%04X\r\n", DM9058_SPI->SR);
#endif
            return 0x00u;
        }
    }
    SPI_SendData8(DM9058_SPI, tx);

    timeout = 1000000u;
    while (SPI_I2S_GetFlagStatus(DM9058_SPI, SPI_I2S_FLAG_RXNE) == RESET) {
        if (--timeout == 0u) {
#if DM9058_SPI_DEBUG
            DM9058_DBG_PRINT("[DM9058 DBG] RXNE timeout, tx=0x%02X SR=0x%04X CR1=0x%04X CR2=0x%04X\r\n",
                             tx, DM9058_SPI->SR, DM9058_SPI->CR1, DM9058_SPI->CR2);
#endif
            return 0x00u;
        }
    }
    return SPI_ReceiveData8(DM9058_SPI);
}

void DM9058_CS_Low(void)
{
    GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_CS);
}

void DM9058_CS_High(void)
{
    GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_CS);
}

void DM9058_HardwareReset(void)
{
#if DM9058_SPI_DEBUG
    DM9058_DBG_PRINT("[DM9058 DBG] Hardware reset start\r\n");
#endif
    GPIO_ResetBits(DM9058_RST_PORT, DM9058_RST_PIN);
    Delay_Ms(2);
    GPIO_SetBits(DM9058_RST_PORT, DM9058_RST_PIN);
    Delay_Ms(10);
#if DM9058_SPI_DEBUG
    DM9058_DBG_PRINT("[DM9058 DBG] Hardware reset done, RST(PF7)=%u\r\n",
                     (GPIOF->IDR & DM9058_RST_PIN) ? 1u : 0u);
#endif
}

void DM9058_DebugDump(const char *tag)
{
#if DM9058_SPI_DEBUG
    uint8_t raw1;
    uint8_t raw2;
    uint8_t ncr;
    uint8_t nsr;
    uint8_t vidl;
    uint8_t vidh;
    uint8_t pidl;
    uint8_t pidh;
    uint8_t chipr;
    uint8_t isr;
    uint8_t imr;

    DM9058_DBG_PRINT("\r\n[DM9058 DBG] dump: %s\r\n", tag ? tag : "");
    DM9058_DebugPrintPinState();
    DM9058_DebugPrintSpiState();

    DM9058_CS_Low();
    raw1 = MH2030A_SPI2_Transfer(0xFFu);
    raw2 = MH2030A_SPI2_Transfer(0x00u);
    DM9058_CS_High();
    DM9058_DBG_PRINT("[DM9058 DBG] raw CS-low xfer FF->0x%02X 00->0x%02X\r\n", raw1, raw2);

    ncr = DM9058_ReadReg(DM9058_NCR);
    nsr = DM9058_ReadReg(0x01u);
    vidl = DM9058_ReadReg(DM9058_VIDL);
    vidh = DM9058_ReadReg(DM9058_VIDH);
    pidl = DM9058_ReadReg(DM9058_PIDL);
    pidh = DM9058_ReadReg(DM9058_PIDH);
    chipr = DM9058_ReadReg(DM9058_CHIPR);
    isr = DM9058_ReadReg(0x7Eu);
    imr = DM9058_ReadReg(0x7Fu);

    DM9058_DBG_PRINT("[DM9058 DBG] regs NCR=0x%02X NSR=0x%02X VIDL=0x%02X VIDH=0x%02X PIDL=0x%02X PIDH=0x%02X CHIPR=0x%02X ISR=0x%02X IMR=0x%02X\r\n",
                     ncr, nsr, vidl, vidh, pidl, pidh, chipr, isr, imr);
    DM9058_DebugPrintSpiState();
#else
    (void)tag;
#endif
}

uint8_t DM9058_ReadReg(uint8_t reg)
{
    uint8_t val;

    DM9058_CS_Low();
    MH2030A_SPI2_Transfer((uint8_t)(reg | DM9058_OP_REG_R));
    val = MH2030A_SPI2_Transfer(0x00u);
    DM9058_CS_High();

    return val;
}

void DM9058_WriteReg(uint8_t reg, uint8_t val)
{
    DM9058_CS_Low();
    MH2030A_SPI2_Transfer((uint8_t)(reg | DM9058_OP_REG_W));
    MH2030A_SPI2_Transfer(val);
    DM9058_CS_High();
}

void DM9058_ReadRegBuf(uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t i;

    DM9058_CS_Low();
    MH2030A_SPI2_Transfer((uint8_t)(reg | DM9058_OP_REG_R));
    for (i = 0; i < len; i++) {
        buf[i] = MH2030A_SPI2_Transfer(0x00u);
    }
    DM9058_CS_High();
}

void DM9058_WriteRegBuf(uint8_t reg, const uint8_t *buf, uint16_t len)
{
    uint16_t i;

    DM9058_CS_Low();
    MH2030A_SPI2_Transfer((uint8_t)(reg | DM9058_OP_REG_W));
    for (i = 0; i < len; i++) {
        MH2030A_SPI2_Transfer(buf[i]);
    }
    DM9058_CS_High();
}

void DM9058_ReadMem(uint8_t *buf, uint16_t len)
{
    uint16_t i;

    DM9058_CS_Low();
    MH2030A_SPI2_Transfer((uint8_t)(DM9058_MRCMD | DM9058_OP_REG_R));
    for (i = 0; i < len; i++) {
        buf[i] = MH2030A_SPI2_Transfer(0x00u);
    }
    DM9058_CS_High();
}

void DM9058_WriteMem(const uint8_t *buf, uint16_t len)
{
    uint16_t i;

    DM9058_CS_Low();
    MH2030A_SPI2_Transfer((uint8_t)(DM9058_MWCMD | DM9058_OP_REG_W));
    for (i = 0; i < len; i++) {
        MH2030A_SPI2_Transfer(buf[i]);
    }
    DM9058_CS_High();
}

uint16_t DM9058_ReadVID(void)
{
    return (uint16_t)DM9058_ReadReg(DM9058_VIDL) |
           ((uint16_t)DM9058_ReadReg(DM9058_VIDH) << 8);
}

uint16_t DM9058_ReadPID(void)
{
    return (uint16_t)DM9058_ReadReg(DM9058_PIDL) |
           ((uint16_t)DM9058_ReadReg(DM9058_PIDH) << 8);
}

void DM9058_ReadMac(uint8_t mac[6])
{
    DM9058_ReadRegBuf(DM9058_PAR, mac, 6);
}

void DM9058_WriteMac(const uint8_t mac[6])
{
    DM9058_WriteRegBuf(DM9058_PAR, mac, 6);
}
