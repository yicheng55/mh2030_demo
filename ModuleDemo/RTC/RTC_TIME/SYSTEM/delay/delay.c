#include "delay.h"

static uint8_t  UsNumber=0;							   
static uint16_t MsNumber=0;							

void Delay_Init()
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	UsNumber=SystemCoreClock/8000000;				
	MsNumber=(uint16_t)UsNumber*1000;					
}								    

    								   
void Delay_Us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*UsNumber; 						 
	SysTick->VAL=0x00;        					
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
	SysTick->VAL =0X00;      					
}

void Delay_Ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*MsNumber;				
	SysTick->VAL =0x00;							
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
	SysTick->VAL =0X00;       					
} 

