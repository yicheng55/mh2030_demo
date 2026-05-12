#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#include "FreeRTOS.h"  
#include "task.h" 

#define PRINTF_LOG 	printf

USART_TypeDef* USART_TEST = USART1;

void UART_Configuration(uint32_t bound);
void NVIC_Configuration(void);
void CLK_Configuration(void);

//函数声明
TaskHandle_t THREAD1Handle;
TaskHandle_t THREAD2Handle;

void Delay_ms( uint16_t time_ms );

void TEST_Thread1(void const * argument)
{
	for (;;)
	{
		PRINTF_LOG("%s\n",__FUNCTION__);
		vTaskDelay(1000);
	}
}

void TEST_Thread2(void const * argument)
{
	for (;;)
	{
		PRINTF_LOG("%s\n",__FUNCTION__);
		vTaskDelay(2000);
	}
}

int main(void)
{
	RCC_ClocksTypeDef clocks;
	
	CLK_Configuration();
	Delay_Init();
	UART_Configuration(115200);
	NVIC_Configuration();
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	
	xTaskCreate((TaskFunction_t )TEST_Thread1,            //任务函数
	(const char*    )"Task Start1",          //任务名称
	(uint16_t       )64,                    //任务堆栈大小
	(void*          )NULL,                  //传递给任务函数的参数
	(UBaseType_t    )1,                      //任务优先级 越大优先级越高
	(TaskHandle_t*  )&THREAD1Handle);  //任务句柄
		
	xTaskCreate((TaskFunction_t )TEST_Thread2,            //任务函数
	(const char*    )"Task Start2",          //任务名称
	(uint16_t       )64,                    //任务堆栈大小
	(void*          )NULL,                  //传递给任务函数的参数
	(UBaseType_t    )2,                      //任务优先级 越大优先级越高
	(TaskHandle_t*  )&THREAD2Handle);  //任务句柄				
	vTaskStartScheduler();          //开启任务调度							

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
	
	USART_ITConfig(USART5, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART5, ENABLE);
}

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
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

