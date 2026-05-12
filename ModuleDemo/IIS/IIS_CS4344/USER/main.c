#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"
#include "audio.h"

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;

void CLK_Configuration(void);
void UART_Configuration(uint32_t bound);
void IIS_Configuration(void);
void DMA_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);

uint8_t Flag;


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
	
	PRINTF_LOG("IIS CS4344 Test.\n");
	
	IIS_Configuration();
	GPIO_Configuration();
	DMA_Configuration();
	NVIC_Configuration();
	
	DMA_Cmd(DMA1_Channel5,ENABLE);

	while(1)
	{
		if(Flag == 1)
		{
			PRINTF_LOG("IIS DMA Data Send Success\n");
			Flag = 0;
			
			DMA_Configuration();
			DMA_Cmd(DMA1_Channel5,ENABLE); 
		}	
	}
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
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

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void IIS_Configuration(void)
{
	I2S_InitTypeDef I2S_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE );
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_0);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12| GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	SPI_I2S_DeInit(SPI2);
	I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;                                 
	I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;          
	I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
	I2S_InitStructure.I2S_AudioFreq = 4000;//I2S_AudioFreq_8k;         
	I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;                
	I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Enable;	
	I2S_Init(SPI2, &I2S_InitStructure);
	
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Tx,ENABLE);
	I2S_Cmd(SPI2, ENABLE);  
}

void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_DeInit(DMA1_Channel5);  
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;                           
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DATA;                    
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                               
	DMA_InitStructure.DMA_BufferSize = DATA_LEN;                         
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                           
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;          
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;                  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                                     
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                           
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                      
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    
	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);
	
	DMA_RemapConfig(DMA1,DMA1_CH5_SPI2_TX);
	
	/* Enable SPI1 DMA TX request */   	
	DMA_Cmd(DMA1_Channel5, DISABLE);
}

void DMA1_Channel4_5_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC5) == SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_TC5);
		DMA_ClearFlag(DMA1_FLAG_TC5);   
		DMA_Cmd(DMA1_Channel5,DISABLE); 
		Flag = 1;
	}
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

