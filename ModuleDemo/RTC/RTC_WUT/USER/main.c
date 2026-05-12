#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;
void CLK_Configuration(void);
void UART_Configuration(uint32_t bound);
uint8_t GetCmd(void);

RCC_ClocksTypeDef clocks;

void RTC_Config(void);

int main(void)
{	
	GPIO_InitTypeDef 	gpioInitStruct;
	RTC_TimeTypeDef 	RTC_TimeStruct;
	
	CLK_Configuration();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG ,ENABLE);
	
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	PRINTF_LOG("RTC Wuk Test.\n");
	PRINTF_LOG("Please Input 's', Come Stop Mode\n");
	
	
	RTC_Config();
	
	while(GetCmd() != 's');
	while(1)
	{
		PWR_EnterSTOPMode(PWR_Regulator_LowPower,PWR_STOPEntry_WFI);
		SystemInit();
		CLK_Configuration();
		UART_Configuration(115200);
		PRINTF_LOG("WakeUp Success\n");
	}
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
	
	RCC_PLLConfig(RCC_PLLSource_HSE,RCC_PLLMul_6);
	
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

	USART_Init(USART_TEST, &USART_InitStructure);
	USART_Cmd(USART_TEST, ENABLE);
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


void RTC_Config(void)
{
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_InitTypeDef RTC_InitStruct;
	RTC_DateTypeDef	RTC_DataStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	
	RCC_BackupResetCmd(ENABLE);
	RCC_BackupResetCmd(DISABLE);
	
	RCC_LSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	
	RTC_InitStruct.RTC_AsynchPrediv = 39;
	RTC_InitStruct.RTC_SynchPrediv = 999;
	RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
	
	RTC_Init(&RTC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
	
	RTC_SetWakeUpCounter(2);//3S
	
	RTC_ClearFlag(RTC_FLAG_WUTF);
	
	RTC_ITConfig(RTC_IT_WUT, ENABLE);
	
	RTC_WakeUpCmd(ENABLE);
	
	RTC_ExitInitMode();//ÍË³ö»½ÐÑÄ£Ê½
	
	EXTI_ClearITPendingBit(EXTI_Line20);
	EXTI_InitStruct.EXTI_Line = EXTI_Line20;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}

void RTC_IRQHandler(void)
{
	RTC_ClearFlag(RTC_FLAG_WUTF);
	EXTI_ClearITPendingBit(EXTI_Line20);
}