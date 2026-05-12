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
void SPI_Configuration(void);
void DMA_Configuration(void);

#define SPI_BUFF_SIZE	256
uint8_t SPI_TX_BUFF[SPI_BUFF_SIZE];
uint8_t SPI_RX_BUFF[SPI_BUFF_SIZE];

RCC_ClocksTypeDef clocks;
int main(void)
{	
	uint16_t i;

	CLK_Configuration();
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);

	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK_Frequency/1000000);

	PRINTF_LOG("SPI Int Test.\n");
	PRINTF_LOG("please connect mo(PA7) and mi(PA6)\n");

	for(i = 0; i < SPI_BUFF_SIZE; i++)
	{
		SPI_TX_BUFF[i] = i+1;
	}
	memset(SPI_RX_BUFF,0, sizeof(SPI_RX_BUFF));

	SPI_Configuration();  

	Delay_Ms(100);
	if(memcmp(SPI_RX_BUFF,SPI_TX_BUFF,SPI_BUFF_SIZE) == 0)  
		PRINTF_LOG("SPI Int Success\n");
	else
		PRINTF_LOG("SPI Int Fail\n");

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

void SPI_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE );
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE );
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource4,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_0);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	
	SPI_RxFIFOThresholdConfig(SPI1,SPI_RxFIFOThreshold_QF);
	
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);		

	SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_RXNE,ENABLE);
	SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_TXE,ENABLE);
	
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
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

void USART1_IRQHandler(void)
{
	uint16_t cmd;
	if(USART_GetITStatus(USART_TEST, USART_IT_RXNE) != RESET)
	{
		cmd = USART_ReceiveData(USART_TEST);
		PRINTF_LOG("accept char :%c\n",cmd);
	}
}
uint16_t count_tx,count_rx=0;
void SPI1_IRQHandler(void)
{
	if(SET == SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))
	{
		if(count_tx < SPI_BUFF_SIZE)
		{
			SPI_SendData8(SPI1,SPI_TX_BUFF[count_tx++]);
		}
		else
		{
			count_tx=0;
		}
	}
	if(SET == SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE))
	{
		if(count_rx < SPI_BUFF_SIZE)
		{
		 SPI_RX_BUFF[count_rx++] = SPI_ReceiveData8(SPI1);
		}
		else
		{
			count_rx=0;
		}
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

