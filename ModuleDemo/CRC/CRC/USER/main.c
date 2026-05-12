#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;

void UART_Configuration(uint32_t bound);
void CLK_Configuration(void);
void CRC_Test(void);

const uint32_t CRCBuffer32[] = 
{
	0x00001021, 0x20423063, 0x408450a5, 0x60c670e7, 0x9129a14a, 0xb16bc18c,\
	0xd1ade1ce, 0xf1ef1231, 0x32732252, 0x52b54294, 0x72f762d6, 0x93398318,
};

uint32_t ExpectedCRC = 0x6124095d;

RCC_ClocksTypeDef clocks;
int main(void)
{	
	CLK_Configuration();
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	
	PRINTF_LOG("CRC Test.\n");
	CRC_Test();
	
	while(1);
}

void CRC_Test(void)
{
	uint32_t crcresult = 0;
	
	PRINTF_LOG("多项式：0x4C11DB7\n");
	PRINTF_LOG("多项式位宽：32\n");
	PRINTF_LOG("初始值：0x00\n");
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	CRC_DeInit();
	CRC_SetInitRegister(0);
	CRC_PolynomialSizeSelect(CRC_PolSize_32);
	CRC_SetPolynomial(0x4C11DB7);
	
	CRC_ReverseOutputDataCmd(DISABLE);
	CRC_ReverseInputDataSelect(CRC_ReverseInputData_32bits);
	
	crcresult = CRC_CalcBlockCRC((uint32_t *)CRCBuffer32, sizeof(CRCBuffer32)/sizeof(uint32_t));
	if(ExpectedCRC == crcresult)
	{
		PRINTF_LOG("RC Test Success\n");
	}
	else
	{
		PRINTF_LOG("CRC Test Fail, Reality Value is 0x%x\n",crcresult);
	}
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

void USART1_IRQHandler(void)
{
	uint16_t cmd;
	if(USART_GetITStatus(USART_TEST, USART_IT_RXNE) != RESET)
	{
		cmd = USART_ReceiveData(USART_TEST);
		PRINTF_LOG("accept char :%c\n",cmd);
	}
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

