/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MH210x_IT_H
#define __MH210x_IT_H

#include "mh20xx.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif /* __MH210x_IT_H */
