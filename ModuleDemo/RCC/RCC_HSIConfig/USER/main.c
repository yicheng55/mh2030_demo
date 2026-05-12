#include "delay.h"
#include "mh20xx.h"
#include "mh2030a_board.h"

extern int SER_PutChar(int ch);

static void UART_SendString(const char *text)
{
	while (*text != '\0')
	{
		SER_PutChar((uint8_t)*text++);
	}
}

void CLK_Configuration(void);

RCC_ClocksTypeDef clocks;
int main(void)
{
	Delay_Init();
	UART_Configuration(115200);

	UART_SendString("USART2 Test Start 115200\r\n");

	while(1)
	{
		UART_SendString("Hello USART2\r\n");
		Delay_Ms(500);
	}
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
