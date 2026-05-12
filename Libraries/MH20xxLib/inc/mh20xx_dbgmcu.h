/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MH20XX_DBGMCU_H
#define __MH20XX_DBGMCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mh20xx.h"

/** @addtogroup DBGMCU
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/


/** @defgroup DBGMCU_Exported_Constants
  * @{
  */

#define DBGMCU_MHOP                  DBGMCU_CR_DBG_MHOP
#define DBGMCU_MHANDBY               DBGMCU_CR_DBG_MHANDBY
#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFF9) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM2_MHOP             DBGMCU_APB1_FZ_DBG_TIM2_MHOP
#define DBGMCU_TIM3_MHOP             DBGMCU_APB1_FZ_DBG_TIM3_MHOP
#define DBGMCU_TIM6_MHOP             DBGMCU_APB1_FZ_DBG_TIM6_MHOP
#define DBGMCU_TIM14_MHOP            DBGMCU_APB1_FZ_DBG_TIM14_MHOP
#define DBGMCU_RTC_MHOP              DBGMCU_APB1_FZ_DBG_RTC_MHOP
#define DBGMCU_WWDG_MHOP             DBGMCU_APB1_FZ_DBG_WWDG_MHOP
#define DBGMCU_IWDG_MHOP             DBGMCU_APB1_FZ_DBG_IWDG_MHOP
#define DBGMCU_I2C1_SMBUS_TIMEOUT    DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT
#define IS_DBGMCU_APB1PERIPH(PERIPH) ((((PERIPH) & 0xFFDFE2EC) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM1_MHOP             DBGMCU_APB2_FZ_DBG_TIM1_MHOP
#define DBGMCU_TIM15_MHOP            DBGMCU_APB2_FZ_DBG_TIM15_MHOP
#define DBGMCU_TIM16_MHOP            DBGMCU_APB2_FZ_DBG_TIM16_MHOP
#define DBGMCU_TIM17_MHOP            DBGMCU_APB2_FZ_DBG_TIM17_MHOP
#define IS_DBGMCU_APB2PERIPH(PERIPH) ((((PERIPH) & 0xFFF8F7FF) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/* Device and Revision ID management functions ********************************/ 
uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);

/* Peripherals Configuration functions ****************************************/ 
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __MH20XX_DBGMCU_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
