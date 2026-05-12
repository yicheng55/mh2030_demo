#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;

void UART_Configuration(uint32_t bound);
void NVIC_Configuration(void);
void CLK_Configuration(void);
void DMA_Rx_Cfg(uint32_t Recive_Size);
void DMA_Tx_Cfg(uint32_t Send_Size);
uint8_t Rx_Buffer[100];
uint8_t Tx_Buffer[100];
void Send_Buffer_Init(void);

int main(void)
{	
	RCC_ClocksTypeDef clocks;
	uint32_t i;
	CLK_Configuration();
	Delay_Init();
	Send_Buffer_Init();
	UART_Configuration(115200);
	DMA_Rx_Cfg(10);
	DMA_Tx_Cfg(100);
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	
	PRINTF_LOG("USART Asyn Test.\n");
	DMA_Cmd(DMA1_Channel3, ENABLE);
	DMA_Cmd(DMA1_Channel2, ENABLE);
	
	while(1)
	{
		if(DMA_GetFlagStatus(DMA1_FLAG_TC3)==1)
		{
			DMA_ClearFlag(DMA1_FLAG_TC3);
			
			PRINTF_LOG("USART Recive Sucess.\n");
			for(i=0;i<10;i++)
		{
			PRINTF_LOG("Rx_Data=%x\n",Rx_Buffer[i]);
		}
		}
		if(DMA_GetFlagStatus(DMA1_FLAG_TC2)==1)
		{
			DMA_ClearFlag(DMA1_FLAG_TC2);
			PRINTF_LOG("USART Send Sucess.\n");
		}
	}
}
void Send_Buffer_Init(void)
{
	uint32_t i;
	for(i=0;i<100;i++)
	{
		Tx_Buffer[i]=i;
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

	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);

	USART_Init(USART_TEST, &USART_InitStructure);
	USART_Cmd(USART_TEST, ENABLE);
}
void DMA_Tx_Cfg(uint32_t Send_Size)
{
	DMA_InitTypeDef  DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//TX
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->TDR;
	DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)&Tx_Buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = Send_Size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2,&DMA_InitStructure);

}
void DMA_Rx_Cfg(uint32_t Recive_Size)
{
	DMA_InitTypeDef  DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//RX
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->RDR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Rx_Buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = Recive_Size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel3,&DMA_InitStructure);
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

