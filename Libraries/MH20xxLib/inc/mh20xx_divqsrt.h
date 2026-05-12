#ifndef __MH20XX_DIVQSRT_H
#define __MH20XX_DIVQSRT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mh20xx.h"

#define DIV_MODE_UNSIGNED  							((uint32_t)0x00000002)
#define DIV_MODE_SIGNED    							((uint32_t)0x00000000)
#define IS_DIV_MODE(MODE)                                                            \
     (((MODE) == DIV_MODE_UNSIGNED) || ((MODE) == DIV_MODE_SIGNED))


#define DIVQSRT_IT_DIVOVERFLOW                      ((uint32_t)0x00000001)
#define IS_DIVQSRT_CONFIG_IT(MODE)                  (((MODE) == DIVQSRT_IT_DIVOVERFLOW))

#define DIVQSRT_FLAG_DIVOVERFLOW                    ((uint32_t)0x00000001)
#define IS_DIVQSRT_FLAG(MODE)                  		(((MODE) == DIVQSRT_FLAG_DIVOVERFLOW))


void DIVQSRT_SetDivMode(uint32_t DIVQSRT_DivMode);
void DIVQSRT_SetDividend(int32_t DIVQSRT_Dividend);
void DIVQSRT_SetDivisor(int32_t DIVQSRT_Divisor);
int32_t DIVQSRT_GetDivres(void);
int32_t DIVQSRT_GetRemainder(void);
void DIVQSRT_SetRadicand(int32_t DIVQSRT_Radicand);
int32_t DIVQSRT_GetSqrtres(void);
void DIVQSRT_ITConfig(uint32_t DIVQSRT_IT,FunctionalState NewState);
FlagStatus DIVQSRT_GetFlagStatus(uint32_t DIVQSRT_FLAG);
void DIVQSRT_ClearFlag(uint32_t DIVQSRT_FLAG);
#endif
