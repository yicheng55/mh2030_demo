#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"
#include "mh2030a_board.h"

/* 定義此巨集啟用直接發送測試，關閉後改用 printf */
// #define USART2_RAW_TEST

#ifdef USART2_RAW_TEST
extern int SER_PutChar(int ch);
static void UART_SendString(const char *text)
{
	while (*text != '\0')
		SER_PutChar((uint8_t)*text++);
}
#define PRINTF_LOG(fmt, ...)  /* 停用 */
#else
#define PRINTF_LOG  printf
#endif

void CLK_Configuration(void);

RCC_ClocksTypeDef clocks;
int main(void)
{
#ifdef USART2_RAW_TEST
	Delay_Init();
	UART_Configuration(115200);

	UART_SendString("USART2 Test Start 115200\r\n");
	while(1)
	{
		UART_SendString("Hello USART2\r\n");
		Delay_Ms(500);
	}
#else
	/* 不切 PLL，直接使用開機預設 HSI 8 MHz */
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);

	while(1)
	{
		PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n",
			(float)clocks.SYSCLK_Frequency / 1000000,
			(float)clocks.HCLK_Frequency   / 1000000,
			(float)clocks.PCLK_Frequency   / 1000000);
		Delay_Ms(500);
	}
#endif
}

void CLK_Configuration(void)
{
	RCC_DeInit();

	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	RCC_PLLCmd(DISABLE);

	FLASH_Unlock();
	FLASH_SetLatency(FLASH_Latency_2);
	FLASH_Lock();

	RCC_PLLConfig(RCC_PLLSource_HSI,RCC_PLLMul_9);

	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_HCLK_Div1);
}
