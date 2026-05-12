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
void COMP_Configuration(void);

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
	
	PRINTF_LOG("COMP Out Test.\n");
	
	PRINTF_LOG("Comp1 Inp ！！ PA3\n");
	PRINTF_LOG("Comp1 Inm ！！ PA5\n");
	PRINTF_LOG("Comp1 Out ！！ PA11\n");

	PRINTF_LOG("Comp2 Inp ！！ PB0\n");
	PRINTF_LOG("Comp2 Inm ！！ PA6\n");
	PRINTF_LOG("Comp2 Out ！！ PB9\n");	

	COMP_Configuration();
	
	
	while(1);
}

void COMP_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	COMP_InitTypeDef COMP_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_7);//comp1 out
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_7);//comp2 out
	
	//comp1 inp 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//comp2 inp 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//comp1 inm
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//comp2 inm
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//comp1 out
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//comp2 out
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//comp1 init
	COMP_InitStructure.COMP_InvertingInput = COMP1_InvertingInput_IO_PA5;
	COMP_InitStructure.COMP_InphaseInput = COMP1_InphaseInput_IO_PA3;
	COMP_InitStructure.COMP_Hysteresis = COMP_Hysteresis_Low;
	COMP_InitStructure.COMP_Mode = COMP_Mode_MediumSpeed;
	COMP_InitStructure.COMP_Output = COMP_Output_None;
	COMP_InitStructure.COMP_OutputPol = COMP_OutputPol_NonInverted;
	COMP_Init(COMP_Selection_COMP1,&COMP_InitStructure);
	
	//comp2 init
	COMP_InitStructure.COMP_InvertingInput = COMP2_InvertingInput_IO_PA6;
	COMP_InitStructure.COMP_InphaseInput = COMP2_InphaseInput_IO_PB0;
	COMP_Init(COMP_Selection_COMP2,&COMP_InitStructure);
	
	COMP_WindowCmd(DISABLE);
	
	COMP_Cmd(COMP_Selection_COMP1,ENABLE);
	COMP_Cmd(COMP_Selection_COMP2,ENABLE);
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

