/**
 * @file    main.c
 * @brief   DM9051A bring-up on MH2030A – read and verify VID/PID via SPI2.
 *
 * Hardware connections
 * ────────────────────
 *  SPI2  PB12=CS  PB13=SCK  PB14=MISO  PB15=MOSI
 *  RST   PF7  (active-low output)
 *  INT   PF6  (active-low EXTI input)
 *  UART2 PA2=TX  PA3=RX  (115200 8N1, console log)
 *
 * Expected output (115200 baud serial console):
 *   VID = 0x0A46, PID = 0x9051
 *   DM9051A ID check: PASS
 */

#include <stdio.h>
#include "mh20xx.h"
#include "delay.h"
#include "mh2030a_spi2.h"
#include "dm9051a.h"

/* -----------------------------------------------------------------------
 * Macro – redirect printf to USART2
 * ----------------------------------------------------------------------- */
#define PRINTF_LOG  printf

USART_TypeDef * const USART_TEST = USART2;

/* -----------------------------------------------------------------------
 * Forward declarations
 * ----------------------------------------------------------------------- */
static void CLK_Configuration(void);
static void UART_Configuration(uint32_t baud);

/* -----------------------------------------------------------------------
 * printf retarget (fputc)
 * ----------------------------------------------------------------------- */
int fputc(int ch, FILE *f)
{
    (void)f;
    USART_SendData(USART_TEST, (uint16_t)ch);
    while (USART_GetFlagStatus(USART_TEST, USART_FLAG_TXE) == RESET) {}
    return ch;
}

/* -----------------------------------------------------------------------
 * main
 * ----------------------------------------------------------------------- */
int main(void)
{
    uint16_t vid, pid;
    DM9051A_Status status;
    RCC_ClocksTypeDef clocks;

    /* System initialisation */
    CLK_Configuration();
    Delay_Init();
    UART_Configuration(115200);

    RCC_GetClocksFreq(&clocks);
    PRINTF_LOG("\r\n=== MH2030A + DM9051A Bring-up ===\r\n");
    PRINTF_LOG("SYSCLK: %.1f MHz  HCLK: %.1f MHz  PCLK: %.1f MHz\r\n",
               (float)clocks.SYSCLK_Frequency / 1000000.0f,
               (float)clocks.HCLK_Frequency   / 1000000.0f,
               (float)clocks.PCLK_Frequency   / 1000000.0f);

    /* SPI2 / GPIO / DMA / EXTI initialisation */
    MH2030A_SPI2_Init();
    PRINTF_LOG("SPI2 initialised (CPOL=Low, CPHA=1Edge, prescaler=256)\r\n");

    /* DM9051A hardware + software reset */
    DM9051A_Reset(Delay_Ms);
    PRINTF_LOG("DM9051A reset done.\r\n");

    /* Read and print VID / PID */
    DM9051A_ReadVidPid(&vid, &pid);
    PRINTF_LOG("VID = 0x%04X, PID = 0x%04X\r\n", vid, pid);

    /* Verify chip ID */
    status = DM9051A_CheckID();
    if (status == DM9051A_OK) {
        PRINTF_LOG("DM9051A ID check: PASS\r\n");

        /* Speed up SPI2 to PCLK/4 = 18 MHz for normal operation */
        MH2030A_SPI2_SetSpeed(SPI_BaudRatePrescaler_4);

        /* Minimal peripheral init */
        DM9051A_BasicInit();
        PRINTF_LOG("DM9051A basic init done.\r\n");
    } else {
        PRINTF_LOG("DM9051A ID check: FAIL  (expected VID=0x0A46 PID=0x9051)\r\n");
    }

    PRINTF_LOG("=== Entering idle loop ===\r\n");
    while (1) {
        Delay_Ms(1000);
    }
}

/* -----------------------------------------------------------------------
 * CLK_Configuration – HSI/2 + PLL × 18 = 72 MHz
 * ----------------------------------------------------------------------- */
static void CLK_Configuration(void)
{
    RCC_DeInit();

    RCC_HSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET) {}

    RCC_PLLCmd(DISABLE);

    FLASH_Unlock();
    FLASH_SetLatency(FLASH_Latency_2);
    FLASH_Lock();

    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_18);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLKConfig(RCC_HCLK_Div1);
}

/* -----------------------------------------------------------------------
 * UART_Configuration – USART2 on PA2(TX)/PA3(RX), AF1
 * ----------------------------------------------------------------------- */
static void UART_Configuration(uint32_t baud)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA,   ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1); /* TX */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1); /* RX */

    /* TX – PA2 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* RX – PA3 */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = baud;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART_TEST, &USART_InitStructure);
    USART_Cmd (USART_TEST, ENABLE);
}

/* -----------------------------------------------------------------------
 * EXTI4_15_IRQHandler – DM9051A INT pin (PF6, EXTI Line 6)
 * ----------------------------------------------------------------------- */
void EXTI4_15_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
        /* TODO: signal upper layer to service DM9051A RX FIFO */
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
}
