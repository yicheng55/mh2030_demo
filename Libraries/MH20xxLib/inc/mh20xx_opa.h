#ifndef __MH20XX_OPA_H
#define __MH20XX_OPA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mh20xx.h"

#define IS_OPA_ALL_PERIPH(PERIPH) (((PERIPH) == OPA1) 	|| \
                                     ((PERIPH) == OPA2) || \
									 ((PERIPH) == OPA3))

#define OPA_MODE_NORMAL			((uint32_t)0x00000000)
#define OPA_MODE_HIGH			((uint32_t)0x00000002)

#define IS_OPA_MDOE(MODE) (((MODE) == OPA_MODE_NORMAL) 	|| \
									 ((MODE) == OPA_MODE_HIGH))

#define	OPA_CTRL_EN             ((uint32_t)0x00000001)

void OPA_DeInit(OPA_TypeDef* OPAx);
void OPA_SetMode(OPA_TypeDef* OPAx, uint32_t OPA_Mode);
void OPA_Enable(OPA_TypeDef* OPAx, FunctionalState NewState);

#endif
