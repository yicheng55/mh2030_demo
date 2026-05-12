/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup mh20xx_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_MH20XX_H
#define __SYSTEM_MH20XX_H

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup MH20xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup MH20xx_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @addtogroup MH20xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup MH20xx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup MH20xx_System_Exported_Functions
  * @{
  */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_MH20XX_H */

/**
  * @}
  */
  
/**
  * @}
  */  
