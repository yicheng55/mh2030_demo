/* Includes ------------------------------------------------------------------*/
#include "mh20xx_dbgmcu.h"

/** @defgroup DBGMCU 
  * @brief DBGMCU driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup DBGMCU_Private_Functions 
  * @{
  */
  

/** @defgroup DBGMCU_Group1 Device and Revision ID management functions
 *  @brief   Device and Revision ID management functions
 *
@verbatim
  ==============================================================================
            ##### Device and Revision ID management functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Returns the device revision identifier.
  * @param  None
  * @retval Device revision identifier
  */
uint32_t DBGMCU_GetREVID(void)
{
   return(DBGMCU->IDCODE >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @param  None
  * @retval Device identifier
  */
uint32_t DBGMCU_GetDEVID(void)
{
   return(DBGMCU->IDCODE & IDCODE_DEVID_MASK);
}

/**
  * @}
  */
  
/** @defgroup DBGMCU_Group2 Peripherals Configuration functions
 *  @brief   Peripherals Configuration
 *
@verbatim
  ==============================================================================
               ##### Peripherals Configuration functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Configures low power mode behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the low power mode.
  *          This parameter can be any combination of the following values:
  *             @arg DBGMCU_MHOP: Keep debugger connection during MHOP mode
  *             @arg DBGMCU_MHANDBY: Keep debugger connection during MHANDBY mode
  * @param  NewState: new state of the specified low power mode in Debug mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->CR |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->CR &= ~DBGMCU_Periph;
  }
}


/**
  * @brief  Configures APB1 peripheral behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the APB1 peripheral.
  *          This parameter can be any combination of the following values:
  *             @arg DBGMCU_TIM2_MHOP: TIM2 counter stopped when Core is halted
  *             @arg DBGMCU_TIM3_MHOP: TIM3 counter stopped when Core is halted
  *             @arg DBGMCU_TIM6_MHOP: TIM6 counter stopped when Core is halted
  *             @arg DBGMCU_TIM14_MHOP: TIM14 counter stopped when Core is halted
  *             @arg DBGMCU_RTC_MHOP: RTC Calendar and Wakeup counter stopped 
  *                                   when Core is halted.
  *             @arg DBGMCU_WWDG_MHOP: Debug WWDG stopped when Core is halted
  *             @arg DBGMCU_IWDG_MHOP: Debug IWDG stopped when Core is halted
  *             @arg DBGMCU_I2C1_SMBUS_TIMEOUT: I2C1 SMBUS timeout mode stopped 
  *                                             when Core is halted
  * @param  NewState: new state of the specified APB1 peripheral in Debug mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_APB1PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->APB1FZ |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->APB1FZ &= ~DBGMCU_Periph;
  }
}

/**
  * @brief  Configures APB2 peripheral behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the APB2 peripheral.
  *          This parameter can be any combination of the following values:
  *             @arg DBGMCU_TIM1_MHOP: TIM1 counter stopped when Core is halted
  *             @arg DBGMCU_TIM15_MHOP: TIM15 counter stopped when Core is halted
  *             @arg DBGMCU_TIM16_MHOP: TIM16 counter stopped when Core is halted
  *             @arg DBGMCU_TIM17_MHOP: TIM17 counter stopped when Core is halted
  * @param  NewState: new state of the specified APB2 peripheral in Debug mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_APB2PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->APB2FZ |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->APB2FZ &= ~DBGMCU_Periph;
  }
}

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
