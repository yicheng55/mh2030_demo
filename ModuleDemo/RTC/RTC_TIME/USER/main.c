#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf
RTC_TimeTypeDef Get_Tim;
RTC_DateTypeDef Get_Data;

// RTC日历结构体
typedef struct {
    uint8_t year;     // 年 (00-99)
    uint8_t month;    // 月 (1-12)
    uint8_t day;      // 日 (1-31)
    uint8_t hour;     // 时 (0-23)
    uint8_t minute;   // 分 (0-59)
    uint8_t second;   // 秒 (0-59)
    uint8_t weekday;  // 星期 (1-7, 1=星期一)
} RTC_DateTime;

// 星期名称数组
const char* weekdays[] = {"", "星期一", "星期二", "星期三", 
                          "星期四", "星期五", "星期六", "星期日"};

// 月份名称数组
const char* months[] = {"", "一月", "二月", "三月", "四月", "五月", "六月",
                       "七月", "八月", "九月", "十月", "十一月", "十二月"};
void RTC_GetDateTime(RTC_DateTime *datetime);
			 
USART_TypeDef* USART_TEST = USART1;
void CLK_Configuration(void);
void UART_Configuration(uint32_t bound);
void RTC_Config(void);
void Rest_BKP(void);
void RTC_SET_TIM(uint16_t Hours,uint16_t Minutes,uint16_t Seconds);

RTC_TimeTypeDef RTC_TimInitStruct1;
RTC_DateTypeDef RTC_DateStruct1;
RCC_ClocksTypeDef clocks;
uint8_t Usart_Cmd;
int main(void)
{
    RTC_DateTime currentDateTime;
	
    CLK_Configuration();
    Delay_Init();
    UART_Configuration(115200);
    RCC_GetClocksFreq(&clocks);

    PRINTF_LOG("\n");
    PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
               (float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
               (float)clocks.PCLK_Frequency/1000000);

    PRINTF_LOG("RTC_SET_GET_TIM\n");
    PRINTF_LOG("发送 0 运行中修改时间\n");
    PRINTF_LOG("发送 1 运行备份域复位\n");
    if(RTC->BKP0R!=0xA5A5A5A5)//上电判断备份域是否发生改变，只有备份域掉电或者发生备份域复位才会清除备份域数据
    {
			RTC_Config();//配置RTC时间为3:04:05
    }
    while(1)
    {
			Delay_Ms(500);
			Delay_Ms(500);			
			
			/* 获取当前日期时间 */
			RTC_GetDateTime(&currentDateTime);

			PRINTF_LOG("20%02d年%02d月%02d日 %02d:%02d:%02d %s",
             currentDateTime.year, currentDateTime.month, currentDateTime.day,
             currentDateTime.hour, currentDateTime.minute, currentDateTime.second,
             weekdays[currentDateTime.weekday]);

			if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==1)
			{
				Usart_Cmd=USART1->RDR;
				if(Usart_Cmd=='0')//当串口收到字符0任意数据时修改时间
				{
					PRINTF_LOG("修改RTC时间为12:15:07\n");
					RTC_SET_TIM(0x12,0x15,0x7);//参数为BCD格式时，分，秒
				}
				else if(Usart_Cmd=='1')//当串口收到字符1发生备份域复位
				{
					PRINTF_LOG("备份域复位系统复位将重新配置RTC时间为3:04:05\n");
					Rest_BKP();
					RTC_Config();
				}
			}
    }
}

void Rest_BKP(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	PWR_BackupAccessCmd(ENABLE);

	RCC_BackupResetCmd(ENABLE);
	RCC_BackupResetCmd(DISABLE);

	PWR_BackupAccessCmd(ENABLE);
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
void RTC_SET_TIM(uint16_t Hours,uint16_t Minutes,uint16_t Seconds)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_TimInitStruct1.RTC_H12=RTC_H12_AM;
    RTC_TimInitStruct1.RTC_Hours=Hours;
    RTC_TimInitStruct1.RTC_Minutes=Minutes;
    RTC_TimInitStruct1.RTC_Seconds=Seconds;
    RTC_SetTime(RTC_Format_BIN,&RTC_TimInitStruct1);
	
		RTC_DateStruct1.RTC_WeekDay = 2;	// 星期 (1-7, 1=星期一)
		RTC_DateStruct1.RTC_Date =  1;	// 日 (1-31)
		RTC_DateStruct1.RTC_Month = 10; 	// 月 (1-12)
		RTC_DateStruct1.RTC_Year = 24;		// 年 (00-99)
		RTC_SetDate(RTC_Format_BIN,&RTC_DateStruct1);	
}
void RTC_Config(void)
{
    RTC_InitTypeDef RTC_InitStruct;
    RTC_TimeTypeDef RTC_TimInitStruct;
		RTC_DateTypeDef RTC_DateStruct;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

    PWR_BackupAccessCmd(ENABLE);

    RCC_LSEConfig(RCC_LSE_ON);

    while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForSynchro();

    RTC_TimInitStruct.RTC_H12=RTC_H12_AM;// AM/PM模式，24小时制下忽略
    RTC_TimInitStruct.RTC_Hours=0x3;
    RTC_TimInitStruct.RTC_Minutes=0x4;
    RTC_TimInitStruct.RTC_Seconds=0x5;
    RTC_SetTime(RTC_Format_BIN,&RTC_TimInitStruct);
		
		RTC_DateStruct.RTC_WeekDay = 6;	// 星期 (1-7, 1=星期一)
		RTC_DateStruct.RTC_Date =  15;	// 日 (1-31)
		RTC_DateStruct.RTC_Month = 1; 	// 月 (1-12)
		RTC_DateStruct.RTC_Year = 22;		// 年 (00-99)
		RTC_SetDate(RTC_Format_BIN,&RTC_DateStruct);
		
    RTC_InitStruct.RTC_AsynchPrediv = 127;
    RTC_InitStruct.RTC_SynchPrediv = 255;
    RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStruct);

    RTC_WriteBackupRegister(RTC_BKP_DR0,0xA5A5A5A5);
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
// 获取当前日期和时间
void RTC_GetDateTime(RTC_DateTime *datetime)
{
    RTC_DateTypeDef RTC_DateStructure;
    RTC_TimeTypeDef RTC_TimeStructure;
    
    /* 读取时间和日期 */
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
    
    /* 填充自定义结构体 */
    datetime->year = RTC_DateStructure.RTC_Year;
    datetime->month = RTC_DateStructure.RTC_Month;
    datetime->day = RTC_DateStructure.RTC_Date;
    datetime->weekday = RTC_DateStructure.RTC_WeekDay;
    
    datetime->hour = RTC_TimeStructure.RTC_Hours;
    datetime->minute = RTC_TimeStructure.RTC_Minutes;
    datetime->second = RTC_TimeStructure.RTC_Seconds;
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

