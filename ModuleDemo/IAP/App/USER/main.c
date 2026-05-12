#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"

#define PRINTF_LOG 	printf

#define GPIO_GROUP_TEST		GPIOB
#define GPIO_PIN_TEST		GPIO_Pin_0

USART_TypeDef* USART_TEST = USART1;

void CLK_Configuration(void);
void UART_Configuration(uint32_t bound);
void GPIO_Configuration(void);

RCC_ClocksTypeDef clocks;
void IAP_Load_App(uint32_t appxaddr);
#define AppAdrress	0x8005000
unsigned int NvicTable[0xc0] __attribute__((section(".ARM.__at_0x20000000")));
int main(void)
{	
	unsigned int i;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);
	for(i = 0 ; i < 0xc0; i++)
		NvicTable[i] = *(unsigned int*)(0x8005000 + i *4);
	
	CLK_Configuration();
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("APP SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	
	PRINTF_LOG("APP GPIO IOInput Test,Falling edge(PB0).\n");
	GPIO_Configuration();
	
 	while(1);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_TEST;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIO_GROUP_TEST, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource0);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;//EXTI0中断通道
	NVIC_InitStructure.NVIC_IRQChannelPriority=0;//优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line0);
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

	USART_Init(USART_TEST, &USART_InitStructure);
	USART_Cmd(USART_TEST, ENABLE);
}
void EXTI0_1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		Delay_Ms(10);
		PRINTF_LOG("App Falling edge detected\n");
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
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
