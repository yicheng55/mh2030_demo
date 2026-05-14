#include "mh2030a_spi2.h"

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

void MH2030A_SPI2_Init(void)
{
    GPIO_InitTypeDef gpio;
    SPI_InitTypeDef spi;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_8);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_8);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_8);

    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_PIN_MOSI | DM9058_PIN_SCK | DM9058_PIN_MISO;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(DM9058_GPIO_PORT, &gpio);

    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_PIN_CS;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DM9058_GPIO_PORT, &gpio);
    DM9058_CS_High();

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
    SPI_Cmd(DM9058_SPI, ENABLE);
}

uint8_t MH2030A_SPI2_Transfer(uint8_t tx)
{
    while (SPI_I2S_GetFlagStatus(DM9058_SPI, SPI_I2S_FLAG_TXE) == RESET) {
    }
    SPI_SendData8(DM9058_SPI, tx);

    while (SPI_I2S_GetFlagStatus(DM9058_SPI, SPI_I2S_FLAG_RXNE) == RESET) {
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
