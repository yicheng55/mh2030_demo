#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"
#include "oled.h"
#include "bmp.h"

#define PRINTF_LOG 	printf

void CLK_Configuration(void);
void UART_Configuration(uint32_t bound);

USART_TypeDef* USART_TEST = USART1;

RCC_ClocksTypeDef clocks;
int main(void)
{	
	u8 t=' ';
	
	CLK_Configuration();

	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);
	
	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);
	
	PRINTF_LOG("IIC Hardware OLED Test.\n");
	
	OLED_Init();
	while(1)
	{
		OLED_ShowPicture(0,0,128,8,BMP1);
		Delay_Ms(500);	
		
		OLED_ShowChinese(10,0,0,16);//兆
		OLED_ShowChinese(28,0,1,16);//讯
		OLED_ShowChinese(46,0,2,16);//恒
		OLED_ShowChinese(64,0,3,16);//达
		OLED_ShowChinese(82,0,4,16);//科
		OLED_ShowChinese(100,0,5,16);//技

		OLED_ShowString(25,16,"MEGAHUNT",16);
		OLED_ShowString(20,32,"2023/10/01",16);
		OLED_ShowString(0,48,"ASCII:",16);  
		OLED_ShowString(63,48,"CODE:",16);
		OLED_ShowChar(48,48,t,16);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16);
		OLED_Refresh();
		Delay_Ms(2000);
		OLED_Clear();

		OLED_ShowChinese(16,0,0,24); //24*24 中
		OLED_ShowChinese(24,20,0,32);//32*32 中
		OLED_ShowChinese(64,0,0,64); //64*64 中
		OLED_Refresh();
		Delay_Ms(2000);
		OLED_Clear();
		OLED_ShowString(0,0,"ABC",12);//6*12 “ABC”
		OLED_ShowString(0,12,"ABC",16);//8*16 “ABC”
		OLED_ShowString(0,28,"ABC",24);//8*16 “ABC”
		OLED_Refresh();
		Delay_Ms(2000);
		
		OLED_ScrollDisplay(12,4);		
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

