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
void WAKEUP_Configuration(void);

RCC_ClocksTypeDef clocks;

typedef struct UserTimeStruct
{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t waittime;
	void (*add)(struct UserTimeStruct *time); 
}UserTimeTypeDef;

void RTC_Config(void);
void RTC_AlarmConfig(void);

void UserTimeAdd(struct UserTimeStruct *time)
{
	time->seconds += time->waittime;
	
	while(time->seconds > 59)
	{
		time->seconds -= 60;
		time->minutes ++;
	}
	while(time->minutes > 59)
	{
		time->minutes -= 60;
		time->hours ++;
	}
	while(time->hours > 23)
	{
		time->hours -= 24;
	}
}

UserTimeTypeDef UserTime;

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
	PRINTF_LOG("PWR Stop Test.\n");
	PRINTF_LOG("Enable WakeUp Pin - PA0\n");
	PRINTF_LOG("Please Input 's', Come Stop Mode\n");
	
	UserTime.waittime = 2;
	UserTime.add = UserTimeAdd;
	
	RTC_Config();
	
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
	UserTime.hours = RTC_TimeStruct.RTC_Hours;
	UserTime.minutes = RTC_TimeStruct.RTC_Minutes;
	UserTime.seconds = RTC_TimeStruct.RTC_Seconds;
	
	RTC_AlarmConfig();
	
	WAKEUP_Configuration();
	
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

void WAKEUP_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
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

void EXTI0_1_IRQHandler(void)
{
	EXTI_ClearFlag(EXTI_Line0);
}

void RTC_Config(void)
{
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_InitTypeDef RTC_InitStruct;
	RTC_DateTypeDef	RTC_DataStruct;
	
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
	
	RTC_TimeStruct.RTC_H12 = RTC_H12_AM;
	RTC_TimeStruct.RTC_Hours = 0;
	RTC_TimeStruct.RTC_Minutes = 0;
	RTC_TimeStruct.RTC_Seconds = 0;
	
	RTC_DataStruct.RTC_Date = 0;
	RTC_DataStruct.RTC_Month = RTC_Month_January;
	RTC_DataStruct.RTC_WeekDay = RTC_Weekday_Monday;
	RTC_DataStruct.RTC_Year = 0;
	
	RTC_SetDate(RTC_Format_BIN, &RTC_DataStruct);
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
	RTC_Init(&RTC_InitStruct);
	
}

void RTC_AlarmConfig(void)
{
	RTC_AlarmTypeDef RTC_AlarmStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStruct.EXTI_Line = EXTI_Line17;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	UserTime.add(&UserTime);
	
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE);
	RTC_AlarmStruct.RTC_AlarmDateWeekDay =RTC_Weekday_Monday;
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay|RTC_AlarmMask_Hours|RTC_AlarmMask_Minutes;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = UserTime.hours;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = UserTime.minutes;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Seconds = UserTime.seconds;

	RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmStruct);
	
	RTC_ClearFlag(RTC_FLAG_ALRAF);
	EXTI_ClearITPendingBit(EXTI_Line17);
	RTC_ITConfig(RTC_IT_ALRA,ENABLE);
	RTC_AlarmCmd(RTC_Alarm_A,ENABLE);
}

void RTC_IRQHandler(void)
{
	RTC_AlarmTypeDef RTC_AlarmStruct;
	
	if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
	{
		RTC_ClearFlag(RTC_FLAG_ALRAF);
		
		UserTime.add(&UserTime);
	
		RTC_AlarmCmd(RTC_Alarm_A,DISABLE);

		RTC_WaitForSynchro();	
		
		RTC_AlarmStruct.RTC_AlarmDateWeekDay =RTC_Weekday_Monday;
		RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
		RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay|RTC_AlarmMask_Hours|RTC_AlarmMask_Minutes;
		RTC_AlarmStruct.RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
		RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = UserTime.hours;
		RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = UserTime.minutes;
		RTC_AlarmStruct.RTC_AlarmTime.RTC_Seconds = UserTime.seconds;
		
		RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmStruct);
		
		RTC_AlarmCmd(RTC_Alarm_A,ENABLE);
		RTC_ClearITPendingBit(RTC_IT_ALRA);
		EXTI_ClearITPendingBit(EXTI_Line17);
	}
}
