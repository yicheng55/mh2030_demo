#ifndef __MH2030A_BOARD_H
#define __MH2030A_BOARD_H

#include <stdio.h>
#include "mh20xx.h"

extern USART_TypeDef* USART_TEST;

void UART_Configuration(uint32_t bound);
uint8_t GetCmd(void);
int UART_PutChar(int ch);

#endif /* __MH2030A_BOARD_H */
