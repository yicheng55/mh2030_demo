#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;

void CLK_Configuration(void);
void UART_Configuration(uint32_t bound);
void GPIO_Configuration(void);
void ADC_Configuration(void);

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
	
	PRINTF_LOG("ADC Int Test\n");
	
	ADC_Configuration();
	
	while(1)
	{
		ADC_StartOfConversion(ADC1);
		Delay_Ms(1000);
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

void ADC_Configuration(void)
{
	ADC_InitTypeDef     ADC_InitStruct;
	GPIO_InitTypeDef    GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* ADC1 DeInit */  
	ADC_DeInit(ADC1);

	/* Enable  GPIOA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	/* ADC1 Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* Configure PA.01  as analog input */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStruct);			

	NVIC_InitStructure.NVIC_IRQChannel = ADC1_COMP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* ADC DMA request in circular mode */
	ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_OneShot);

	/* Initialize ADC structure */
	ADC_StructInit(&ADC_InitStruct);

	/* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ScanDirection = ADC_ScanDirection_Backward;
	ADC_Init(ADC1, &ADC_InitStruct); 

	/* Convert the ADC1 Vref  with 55.5 Cycles as sampling time */ 
	ADC_ChannelConfig(ADC1, ADC_Channel_6, ADC_SampleTime_55_5Cycles); 

	/* ADC Calibration */
	ADC_GetCalibrationFactor(ADC1);

	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);     

	/* Wait the ADCEN falg */
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  
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

void ADC1_COMP_IRQHandler(void)
{
	if(ADC_GetITStatus(ADC1,ADC_IT_EOC) == SET)
	{
		PRINTF_LOG("value = 0x%x\n",ADC_GetConversionValue(ADC1));
		
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
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

