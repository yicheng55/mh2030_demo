#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;

#define FLASH_TEST_ADDR		(0x0800F800)
#define FLASH_TEST_SIZE		(512)

void UART_Configuration(uint32_t bound);
void CLK_Configuration(void);
void FLASH_EraseProgram(void);

int main(void)
{	
	RCC_ClocksTypeDef clocks;
	
	CLK_Configuration();
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	
	PRINTF_LOG("FLASH Erase Program Tset.\n");
	
	FLASH_EraseProgram();
	while(1)
	{
		
	}
}

void FLASH_EraseProgram(void)
{
	uint8_t buff[FLASH_TEST_SIZE] = {0};
	uint32_t i;
	
	FLASH_Unlock();
	
	memset(buff,0xFF,sizeof(buff));
	
	FLASH_ErasePage(FLASH_TEST_ADDR);
	
	if(strncmp((char *)FLASH_TEST_ADDR,(char *)buff,FLASH_TEST_SIZE) == 0)
	{
		PRINTF_LOG("Erase Page Success\n");
	}
	else
	{
		PRINTF_LOG("Erase Page Fail\n");
		while(1);
	}
	
	for(i = 0; i < FLASH_TEST_SIZE/2; i++)
	{
		FLASH_ProgramHalfWord(FLASH_TEST_ADDR+(2*i),0x5A5A);	
	}
	
	memset(buff,0x5A,sizeof(buff));
	if(strncmp((char *)FLASH_TEST_ADDR,(char *)buff,FLASH_TEST_SIZE) == 0)
	{
		PRINTF_LOG("Program Half Word Success\n");
	}
	else
	{
		PRINTF_LOG("Program Half Word Fail\n");
		while(1);
	}
	
	FLASH_Lock();
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
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
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
