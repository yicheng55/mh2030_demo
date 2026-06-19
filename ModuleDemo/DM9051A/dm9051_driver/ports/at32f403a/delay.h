#ifndef __DELAY_H
#define __DELAY_H

#include "at32f403a_407.h"

void Delay_Init(void);
void Delay_Ms(uint16_t nms);
void Delay_Us(uint32_t nus);

#endif
