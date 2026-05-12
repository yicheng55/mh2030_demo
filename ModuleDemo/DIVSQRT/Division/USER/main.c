#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;

void UART_Configuration(uint32_t bound);
void CLK_Configuration(void);

uint32_t UNDIVIDEND[10] = {10, 11, 22, 33, 44, 55, 66, 77, 88, 99};
uint32_t UNDIVISOR[10] = {65535, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128};

int32_t DIVIDEND[10] = {-1, 11, -22, 33, -44, 55, -66, 77, -88, 99};
int32_t DIVISOR[10] = {-32767, 32767, -16384, 16384, -4096, 4096, 2048, -2048, 1024, -1024};

int main(void)
{	
	uint32_t i,j;
	uint32_t udivres[2], uremainder[2];
	int32_t divres[2], remainder[2];
	
	RCC_ClocksTypeDef clocks;
	
	CLK_Configuration();
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	
	PRINTF_LOG("DIVQSRT Test.\n");
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DIVQSRT,ENABLE);
	RCC_AHBPeriphResetCmd(RCC_AHBPeriph_DIVQSRT,ENABLE);
	RCC_AHBPeriphResetCmd(RCC_AHBPeriph_DIVQSRT,DISABLE);
	
	DIVQSRT_SetDivMode(DIV_MODE_UNSIGNED);
	for(i = 0; i < sizeof(UNDIVIDEND)/sizeof(uint32_t); i++)
	{
		for(j = 0; j < sizeof(UNDIVISOR)/sizeof(uint32_t); j++)
		{
			udivres[0] = UNDIVIDEND[i]/UNDIVISOR[j];
			uremainder[0] = UNDIVIDEND[i]%UNDIVISOR[j];
			
			DIVQSRT_SetDivisor(UNDIVISOR[j]);
			DIVQSRT_SetDividend(UNDIVIDEND[i]);
			while(DIVQSRT_GetFlagStatus(DIVQSRT_FLAG_DIVOVERFLOW) == SET);
			udivres[1] = DIVQSRT_GetDivres();
			uremainder[1] = DIVQSRT_GetRemainder();
			
			if((udivres[0] != udivres[1]) | (uremainder[0] != uremainder[1]))
			{
				PRINTF_LOG("Error\n");
				PRINTF_LOG("软件计算结果》》被除数为：%d, 除数为：%d, 商为：%d, 余数为：%d\n",UNDIVIDEND[i],UNDIVISOR[j],udivres[0],uremainder[0]);
				PRINTF_LOG("硬件计算结果》》被除数为：%d, 除数为：%d, 商为：%d, 余数为：%d\n",UNDIVIDEND[i],UNDIVISOR[j],udivres[1],uremainder[1]);
				while(1);
			}
		}
	}
	PRINTF_LOG("hardware unsigned division test success\n");
	
	
	DIVQSRT_SetDivMode(DIV_MODE_SIGNED);
	for(i = 0; i < sizeof(DIVIDEND)/sizeof(uint32_t); i++)
	{
		for(j = 0; j < sizeof(DIVISOR)/sizeof(uint32_t); j++)
		{
			divres[0] = DIVIDEND[i]/DIVISOR[j];
			remainder[0] = DIVIDEND[i]%DIVISOR[j];
			
			DIVQSRT_SetDivisor(DIVISOR[j]);
			DIVQSRT_SetDividend(DIVIDEND[i]);
			while(DIVQSRT_GetFlagStatus(DIVQSRT_FLAG_DIVOVERFLOW) == SET);
			divres[1] = DIVQSRT_GetDivres();
			remainder[1] = DIVQSRT_GetRemainder();
			
			if((udivres[0] != udivres[1]) | (uremainder[0] != uremainder[1]))
			{
				PRINTF_LOG("Error\n");
				PRINTF_LOG("软件计算结果》》被除数为：%d, 除数为：%d, 商为：%d, 余数为：%d\n",DIVIDEND[i],DIVISOR[j],divres[0],remainder[0]);
				PRINTF_LOG("硬件计算结果》》被除数为：%d, 除数为：%d, 商为：%d, 余数为：%d\n",DIVIDEND[i],DIVISOR[j],divres[1],remainder[1]);
				while(1);
			}
		}
	}
	PRINTF_LOG("hardware signed division test success\n");
	
	while(1);
}


void CLK_Configuration(void)
{
	RCC_DeInit();
	
	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
	
	RCC_PLLCmd(DISABLE);
	
	FLASH_Unlock();
	FLASH_SetLatency(FLASH_Latency_2);
	FLASH_Lock();
	
	RCC_PLLConfig(RCC_PLLSource_HSE,RCC_PLLMul_9);
	
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_HCLK_Div1);
}

void UART_Configuration(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_ITConfig(USART_TEST, USART_IT_RXNE, ENABLE);

	USART_Init(USART_TEST, &USART_InitStructure);
	USART_Cmd(USART_TEST, ENABLE);
	
	
}

int SER_PutChar (int ch)
{
	while(!USART_GetFlagStatus(USART_TEST,USART_FLAG_TC));
	USART_SendData(USART_TEST, (uint8_t) ch);

	return ch;
}

int fputc(int c, FILE *f)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	if (c == '\n')
	{
		SER_PutChar('\r');
	}
	return (SER_PutChar(c));
}

