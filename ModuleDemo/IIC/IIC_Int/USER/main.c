#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

void I2C_Configuration(void);
void CLK_Configuration(void);
void UART_Configuration(uint32_t bound);
void GPIO_Configuration(void);
uint8_t GetCmd(void);

USART_TypeDef* USART_TEST = USART1;

#define BUFF_SIZE	255
uint8_t SendBuff[BUFF_SIZE];
uint8_t RecvBuff[BUFF_SIZE];

RCC_ClocksTypeDef clocks;
int main(void)
{	
	uint16_t i;
	
	CLK_Configuration();
	I2C_Configuration();
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	
	PRINTF_LOG("IIC Int Test.\n");
	
	for(i=0;i<BUFF_SIZE;i++)
	{
		SendBuff[i]=i;
	}
	memset(RecvBuff,0, sizeof(RecvBuff));
	
	PRINTF_LOG("'1':Master Send\n");
	PRINTF_LOG("'2':Slave Receive\n");
	while(1)
	{
		if(GetCmd() == '1')
		{
			PRINTF_LOG("'1':Master Send\n");
			
			I2C_SlaveAddressConfig(I2C1,0XC0);
			I2C_AutoEndCmd(I2C1,ENABLE);
			I2C_NumberOfBytesConfig(I2C1,BUFF_SIZE);
			I2C_MasterRequestConfig(I2C1,I2C_Direction_Transmitter);
			I2C_ITConfig(I2C1,I2C_IT_TXIS,ENABLE);
			I2C_GenerateSTART(I2C1,ENABLE);
		}
		else if(GetCmd() == '2')
		{
			PRINTF_LOG("'2':Slave Receive\n");
			
			I2C_ITConfig(I2C1,I2C_IT_ADDR,ENABLE);
			I2C_ITConfig(I2C1,I2C_IT_RXNE,ENABLE);
			
			Delay_Ms(1000);
			
			if(memcmp(SendBuff,RecvBuff,BUFF_SIZE) == 0) //对比结果
				PRINTF_LOG("IIC Receive Success\n");
			else
				PRINTF_LOG("IIC Receive Fail\n");
		}
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

void I2C_Configuration(void)
{
	I2C_InitTypeDef  	I2C_InitStruct;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_1);
	
	I2C_InitStruct.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1=0XC0;
	I2C_InitStruct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_Timing=0x10420F13;
	I2C_InitStruct.I2C_AnalogFilter=I2C_AnalogFilter_Enable;
	I2C_InitStruct.I2C_DigitalFilter=0;
	I2C_InitStruct.I2C_Ack=I2C_Ack_Enable;
	I2C_Init(I2C1,&I2C_InitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel=I2C1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
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

uint8_t i=0;
void I2C1_IRQHandler(void)
{
	if(I2C_GetFlagStatus(I2C1,I2C_FLAG_ADDR)==SET)
	{
		I2C_ClearFlag(I2C1,I2C_FLAG_ADDR);
	}
	
	if(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS)==SET)
	{
		I2C_SendData(I2C1,SendBuff[i++]);
	}
	if(I2C_GetFlagStatus(I2C1,I2C_FLAG_RXNE)==SET)
	{
		RecvBuff[i++]=I2C_ReceiveData(I2C1);
	}
}

uint8_t GetCmd(void)
{
	uint8_t tmp = 0;

	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
	{
		tmp = USART_ReceiveData(USART1);
	}
	return tmp;
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

