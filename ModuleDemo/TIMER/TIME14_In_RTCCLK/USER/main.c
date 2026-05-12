#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;

void UART_Configuration(uint32_t bound);
void CLK_Configuration(void);
void TIM_Configuration(void);
void RTCCLK_Configuration(void);

RCC_ClocksTypeDef clocks;
uint32_t testcnt;
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
	
	PRINTF_LOG("TIME14 IN RTCCLK Test.\n");
	
	RTCCLK_Configuration();
	
	TIM_Configuration();
	
	while(1)
	{
		Delay_Ms(1000);
		PRINTF_LOG("testcnt = %d\n",testcnt);
	}
}
void TIM_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	//定时器初始化
	TIM_TimeBaseStructure.TIM_Period = 99; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler = clocks.PCLK_Frequency/1000000 - 1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; 
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM14, &TIM_ICInitStructure);
	
	TIM_RemapConfig(TIM14,TIM14_RTC_CLK);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;  //TIM14中断
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;  //优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM14,TIM_IT_CC1,ENABLE);//允许CC1IE捕获中断	
	
	TIM_Cmd(TIM14, ENABLE);  //使能TIMx	
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

void RTCCLK_Configuration(void)
{
	RTC_InitTypeDef RTC_InitStruct;
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	RCC_BackupResetCmd(ENABLE);
	RCC_BackupResetCmd(DISABLE);
	
	RCC_LSEConfig(RCC_LSE_ON);
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();

	RTC_InitStruct.RTC_AsynchPrediv = 0x7F;
	RTC_InitStruct.RTC_SynchPrediv = 0xFF;
	RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
	RTC_Init(&RTC_InitStruct);
	
    RTC_DateStructure.RTC_Year = 24;
    RTC_DateStructure.RTC_Month = 1;
    RTC_DateStructure.RTC_Date = 1;
    RTC_DateStructure.RTC_WeekDay = 1;
    RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
	
    RTC_TimeStructure.RTC_H12 = RTC_H12_AM;
    RTC_TimeStructure.RTC_Hours = 12;
    RTC_TimeStructure.RTC_Minutes = 0;
    RTC_TimeStructure.RTC_Seconds = 0;
    RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);	

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

//定时器14中断服务程序	 
void TIM14_IRQHandler(void)
{ 
	if(TIM_GetITStatus(TIM14, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
	{	
		testcnt = TIM_GetCapture1(TIM14);
		TIM_SetCounter(TIM14,0);
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
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

