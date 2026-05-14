#include "mh2030a_spi2.h"
#include "delay.h"
#if DM9058_SPI_DEBUG
#include <stdio.h>
#endif

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
    DM9058_DBG_PRINT("[DM9058 DBG] Pins MOSI(PA8)=%u CS(PA9)=%u SCK(PA11)=%u MISO(PA12)=%u RST(PF7)=%u\r\n",
                     (GPIOA->ODR & DM9058_PIN_MOSI) ? 1u : 0u,
                     (GPIOA->IDR & DM9058_PIN_CS)   ? 1u : 0u,
                     (GPIOA->IDR & DM9058_PIN_SCK)  ? 1u : 0u,
                     (GPIOA->IDR & DM9058_PIN_MISO) ? 1u : 0u,
                     (GPIOF->IDR & DM9058_RST_PIN)  ? 1u : 0u);
}

static void DM9058_DebugPrintSpiState(void)
{
    DM9058_DBG_PRINT("[DM9058 DBG] SPI: bit-bang mode (PA8=MOSI, PA9=CS, PA11=SCK, PA12=MISO)\r\n");
}
#endif

void MH2030A_SPI2_Init(void)
{
    GPIO_InitTypeDef gpio;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

    /* CS: output, default high */
    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_PIN_CS;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_10MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DM9058_GPIO_PORT, &gpio);
    DM9058_CS_High();

    /* RST */
    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_RST_PIN;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_10MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DM9058_RST_PORT, &gpio);
    DM9058_HardwareReset();

    /* MOSI + SCK: output push-pull, no AF needed for bit-bang */
    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_PIN_MOSI | DM9058_PIN_SCK;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_10MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(DM9058_GPIO_PORT, &gpio);
    GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);  /* SCK idle = LOW (Mode 0) */
    GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);

    /* MISO: input with pull-up */
    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = DM9058_PIN_MISO;
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_Speed = GPIO_Speed_10MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DM9058_GPIO_PORT, &gpio);

#if DM9058_SPI_DEBUG
    DM9058_DBG_PRINT("[DM9058 DBG] bit-bang SPI init done (PA8=MOSI, PA11=SCK, PA12=MISO)\r\n");
    DM9058_DebugPrintPinState();
#endif
}

uint8_t MH2030A_SPI2_Transfer(uint8_t tx)
{
    uint8_t rx = 0u;
    uint8_t i;

    /* Bit-bang SPI Mode 0: CPOL=0 (SCK idle LOW), CPHA=0 (sample on rising edge), MSB first */
    for (i = 0u; i < 8u; i++) {
        /* Set MOSI before rising edge */
        if (tx & 0x80u) {
            GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);
        } else {
            GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);
        }
        tx = (uint8_t)(tx << 1u);

        /* Rising edge: DM9058 samples MOSI, MCU samples MISO */
        GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
        rx = (uint8_t)(rx << 1u);
        if (GPIO_ReadInputDataBit(DM9058_GPIO_PORT, DM9058_PIN_MISO)) {
            rx |= 0x01u;
        }

        /* Falling edge */
        GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
    }
    return rx;
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

#if DM9058_SPI_DEBUG
/* Bit-by-bit verbose register read.
 * Confirms:
 *   1. CS ODR actually changes (bit 9 clears)
 *   2. Each MISO bit level during the 8 data clocks
 * If MISO is stuck at 1 for all 8 data bits -> DM9058 not responding (HW issue).
 */
static void DM9058_DebugVerboseRegRead(uint8_t reg)
{
    uint8_t cmd = (uint8_t)(reg | DM9058_OP_REG_R);
    uint8_t data = 0u;
    uint8_t miso;
    uint8_t i;

    DM9058_DBG_PRINT("[DM9058 DBG] --- verbose read reg=0x%02X cmd=0x%02X ---\r\n", reg, cmd);
    DM9058_DBG_PRINT("[DM9058 DBG]   pre-CS  ODR=0x%04X IDR=0x%04X\r\n",
                     GPIOA->ODR, GPIOA->IDR);

    DM9058_CS_Low();
    DM9058_DBG_PRINT("[DM9058 DBG]   CS low  ODR=0x%04X IDR=0x%04X  (PA9 bit9 must be 0)\r\n",
                     GPIOA->ODR, GPIOA->IDR);

    /* Command byte: clock out 8 bits, show MISO at each rising edge */
    DM9058_DBG_PRINT("[DM9058 DBG]   cmd phase  MOSI MISO per bit (b7..b0):\r\n");
    for (i = 0u; i < 8u; i++) {
        uint8_t mosi_bit = (cmd & 0x80u) ? 1u : 0u;
        if (mosi_bit) {
            GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);
        } else {
            GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);
        }
        cmd = (uint8_t)(cmd << 1u);
        GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
        miso = GPIO_ReadInputDataBit(DM9058_GPIO_PORT, DM9058_PIN_MISO) ? 1u : 0u;
        DM9058_DBG_PRINT("[DM9058 DBG]     bit%u  MOSI=%u MISO=%u\r\n", 7u - i, mosi_bit, miso);
        GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
    }

    /* Data byte: clock in 8 bits from MISO (MOSI=0) */
    DM9058_DBG_PRINT("[DM9058 DBG]   data phase MISO per bit (b7..b0):\r\n");
    for (i = 0u; i < 8u; i++) {
        GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);
        GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
        miso = GPIO_ReadInputDataBit(DM9058_GPIO_PORT, DM9058_PIN_MISO) ? 1u : 0u;
        data = (uint8_t)((data << 1u) | miso);
        DM9058_DBG_PRINT("[DM9058 DBG]     bit%u  MISO=%u  IDR=0x%04X\r\n",
                         7u - i, miso, GPIOA->IDR);
        GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
    }

    DM9058_CS_High();
    DM9058_DBG_PRINT("[DM9058 DBG]   result=0x%02X  CS high ODR=0x%04X IDR=0x%04X\r\n",
                     data, GPIOA->ODR, GPIOA->IDR);
    DM9058_DBG_PRINT("[DM9058 DBG] --- end verbose read ---\r\n");
}
#endif

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
    raw1 = MH2030A_SPI2_Transfer(DM9058_CHIPR | DM9058_OP_REG_R); // read cmd (bit7=0)
    raw2 = MH2030A_SPI2_Transfer(0x00u);                           // data phase: expect CHIPR value
    DM9058_CS_High();
    DM9058_DBG_PRINT("[DM9058 DBG] raw CHIPR read: cmd=0x%02X data=0x%02X (expect non-zero if DM9058 responds)\r\n", raw1, raw2);

    /* Bit-by-bit trace to confirm CS toggles and check every MISO level */
    DM9058_DebugVerboseRegRead(DM9058_CHIPR);

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

    /* CS polarity inversion test: clock a full transfer while CS stays HIGH.
     * If result != 0xFF -> CS is wired inverted (board inverter / active-high chip select). */
    {
        uint8_t cs_cmd = (uint8_t)(DM9058_CHIPR | DM9058_OP_REG_R);
        uint8_t cs_inv_result = 0u;
        uint8_t j;

        DM9058_CS_High();   /* keep PA9=1 (our de-asserted state) during transfer */
        for (j = 0u; j < 8u; j++) {
            if (cs_cmd & 0x80u) GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);
            else                GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);
            cs_cmd = (uint8_t)(cs_cmd << 1u);
            GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
            GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
        }
        for (j = 0u; j < 8u; j++) {
            GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_MOSI);
            GPIO_SetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
            cs_inv_result = (uint8_t)((cs_inv_result << 1u) |
                            (GPIO_ReadInputDataBit(DM9058_GPIO_PORT, DM9058_PIN_MISO) ? 1u : 0u));
            GPIO_ResetBits(DM9058_GPIO_PORT, DM9058_PIN_SCK);
        }
        DM9058_CS_High();
        DM9058_DBG_PRINT("[DM9058 DBG] CS polarity test (CS=HIGH): CHIPR=0x%02X  %s\r\n",
                         cs_inv_result,
                         (cs_inv_result != 0xFFu) ? "<<< CS wired INVERTED! use active-high CS >>>"
                                                  : "(0xFF = CS polarity OK, problem is elsewhere)");
    }

    /* Diagnosis summary */
    if (chipr == 0xFFu) {
        DM9058_DBG_PRINT("[DM9058 DBG] DIAGNOSIS: MISO stuck HIGH for all 16 clocks.\r\n");
        DM9058_DBG_PRINT("[DM9058 DBG]   -> Check 1: DM9058 VCC/GND power supply\r\n");
        DM9058_DBG_PRINT("[DM9058 DBG]   -> Check 2: MISO wire PA12 <-> DM9058 pin continuity\r\n");
        DM9058_DBG_PRINT("[DM9058 DBG]   -> Check 3: RST (PF7) wiring and active level\r\n");
        DM9058_DBG_PRINT("[DM9058 DBG]   -> Check 4: see CS polarity test result above\r\n");
    } else {
        DM9058_DBG_PRINT("[DM9058 DBG] DIAGNOSIS: CHIPR=0x%02X (DM9058 responding)\r\n", chipr);
    }

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
