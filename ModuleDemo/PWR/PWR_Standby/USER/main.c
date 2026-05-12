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
int main(void)
{	
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
	PRINTF_LOG("PWR Standby Test.\n");
	
	PRINTF_LOG("1:Enable WakeUp1 Pin - PA0\n");
	PRINTF_LOG("2:Enable WakeUp2 Pin - PC13\n");
	PRINTF_LOG("4:Enable WakeUp4 Pin - PA2\n");
	PRINTF_LOG("6:Enable WakeUp6 Pin - PB5\n");
	PRINTF_LOG("7:Enable WakeUp7 Pin - PB15\n");

	WAKEUP_Configuration();
	
	PRINTF_LOG("PWR->CSR = 0x%x\n",PWR->CSR);
	PRINTF_LOG("Please Input 's', Come Standby Mode\n");
	while(GetCmd() != 's');
	PWR_EnterSTANDBYMode();
	
	while(1);
}

void WAKEUP_Configuration(void)
{
	uint8_t cmd;

	PWR_WakeUpPinCmd(PWR_WakeUpPin_1,DISABLE);
	PWR_WakeUpPinCmd(PWR_WakeUpPin_2,DISABLE);
	PWR_WakeUpPinCmd(PWR_WakeUpPin_4,DISABLE);
	PWR_WakeUpPinCmd(PWR_WakeUpPin_6,DISABLE);
	PWR_WakeUpPinCmd(PWR_WakeUpPin_7,DISABLE);
	while(1)
	{
		cmd = GetCmd();
		
		switch (cmd)
		{
			case '1':
			{
				PWR_WakeUpPinCmd(PWR_WakeUpPin_1,ENABLE);
				PRINTF_LOG("Enable WakeUp1 Success\n");
				return;
			}
			
			case '2':
			{
				PWR_WakeUpPinCmd(PWR_WakeUpPin_2,ENABLE);
				PRINTF_LOG("Enable WakeUp2 Success\n");
				return;
			}

			case '4':
			{
				PWR_WakeUpPinCmd(PWR_WakeUpPin_4,ENABLE);
				PRINTF_LOG("Enable WakeUp4 Success\n");
				return;
			}

			case '6':
			{
				PWR_WakeUpPinCmd(PWR_WakeUpPin_6,ENABLE);
				PRINTF_LOG("Enable WakeUp6 Success\n");
				return;
			}

			case '7':
			{
				PWR_WakeUpPinCmd(PWR_WakeUpPin_7,ENABLE);
				PRINTF_LOG("Enable WakeUp7 Success\n");
				return;
			}
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
