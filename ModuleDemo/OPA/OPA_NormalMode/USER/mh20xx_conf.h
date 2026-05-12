/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MH210x_CONF_H
#define __MH210x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
#include "mh20xx_adc.h"
#include "mh20xx_crc.h"
#include "mh20xx_comp.h"
#include "mh20xx_dbgmcu.h"
#include "mh20xx_dma.h"
#include "mh20xx_exti.h"
#include "mh20xx_flash.h"
#include "mh20xx_gpio.h"
#include "mh20xx_syscfg.h"
#include "mh20xx_i2c.h"
#include "mh20xx_iwdg.h"
#include "mh20xx_pwr.h"
#include "mh20xx_rcc.h"
#include "mh20xx_rtc.h"
#include "mh20xx_spi.h"
#include "mh20xx_tim.h"
#include "mh20xx_usart.h"
#include "mh20xx_wwdg.h"
#include "mh20xx_divqsrt.h"
#include "mh20xx_opa.h"
#include "mh20xx_misc.h"  

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __mh210x_CONF_H */

/******************* (C) COPYRIGHT  MHSEMICONDUCTOR *****END OF FILE****/
