/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MH20XX_COMP_H
#define __MH20XX_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mh20xx.h"

/** @addtogroup COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  COMP Init structure definition  
  */
  
typedef struct
{

  uint32_t COMP_InvertingInput;     /*!< Selects the inverting input of the comparator.
                                          This parameter can be a value of @ref COMP_InvertingInput */
	
  uint32_t COMP_InphaseInput;     	/*!< Selects the inphase input of the comparator.
                                          This parameter can be a value of @ref COMP_InphaseInput */	

  uint32_t COMP_Output;             /*!< Selects the output redirection of the comparator.
                                          This parameter can be a value of @ref COMP_Output */

  uint32_t COMP_OutputPol;           /*!< Selects the output polarity of the comparator.
                                          This parameter can be a value of @ref COMP_OutputPolarity */

  uint32_t COMP_Hysteresis;         /*!< Selects the hysteresis voltage of the comparator.
                                          This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t COMP_Mode;               /*!< Selects the operating mode of the comparator
                                         and allows to adjust the speed/consumption.
                                          This parameter can be a value of @ref COMP_Mode */

}COMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
   
/** @defgroup COMP_Exported_Constants
  * @{
  */ 

/** @defgroup COMP_Selection
  * @{
  */

#define COMP_Selection_COMP1                    ((uint32_t)0x00000000) /*!< COMP1 Selection */
#define COMP_Selection_COMP2                    ((uint32_t)0x00000010) /*!< COMP2 Selection */

#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP_Selection_COMP1) || \
                                    ((PERIPH) == COMP_Selection_COMP2))
 
/**
  * @}
  */ 

/** @defgroup COMP1_InvertingInput
  * @{
  */

#define COMP1_InvertingInput_1_16VREFINT          	((uint32_t)0x00000000)
#define COMP1_InvertingInput_2_16VREFINT          	((uint32_t)0x01000000)
#define COMP1_InvertingInput_3_16VREFINT          	((uint32_t)0x02000000)
#define COMP1_InvertingInput_4_16VREFINT          	((uint32_t)0x03000000)
#define COMP1_InvertingInput_5_16VREFINT          	((uint32_t)0x04000000)
#define COMP1_InvertingInput_6_16VREFINT          	((uint32_t)0x05000000)
#define COMP1_InvertingInput_7_16VREFINT          	((uint32_t)0x06000000)
#define COMP1_InvertingInput_8_16VREFINT          	((uint32_t)0x07000000)
#define COMP1_InvertingInput_9_16VREFINT          	((uint32_t)0x08000000)
#define COMP1_InvertingInput_10_16VREFINT          	((uint32_t)0x09000000)
#define COMP1_InvertingInput_11_16VREFINT          	((uint32_t)0x0A000000)
#define COMP1_InvertingInput_12_16VREFINT          	((uint32_t)0x0B000000)
#define COMP1_InvertingInput_IO_PB1		          	((uint32_t)0x0C000000)
#define COMP1_InvertingInput_VREFINT             	((uint32_t)0x0D000000)
#define COMP1_InvertingInput_IO_PA5            		((uint32_t)0x0E000000) 
#define COMP1_InvertingInput_IO_PB12                ((uint32_t)0x0F000000) 

#define IS_COMP1_INVERTING_INPUT(INPUT) (((INPUT) == COMP1_InvertingInput_1_16VREFINT)  || \
                                        ((INPUT) == COMP1_InvertingInput_2_16VREFINT) 	|| \
                                        ((INPUT) == COMP1_InvertingInput_3_16VREFINT)   || \
                                        ((INPUT) == COMP1_InvertingInput_4_16VREFINT)   || \
                                        ((INPUT) == COMP1_InvertingInput_5_16VREFINT)   || \
                                        ((INPUT) == COMP1_InvertingInput_6_16VREFINT) 	|| \
                                        ((INPUT) == COMP1_InvertingInput_7_16VREFINT)	|| \
										((INPUT) == COMP1_InvertingInput_8_16VREFINT)	|| \
										((INPUT) == COMP1_InvertingInput_9_16VREFINT)	|| \
										((INPUT) == COMP1_InvertingInput_10_16VREFINT)	|| \
										((INPUT) == COMP1_InvertingInput_11_16VREFINT)	|| \
										((INPUT) == COMP1_InvertingInput_12_16VREFINT)	|| \
										((INPUT) == COMP1_InvertingInput_IO_PB1)		|| \
										((INPUT) == COMP1_InvertingInput_VREFINT)		|| \
										((INPUT) == COMP1_InvertingInput_IO_PA5)		|| \
										((INPUT) == COMP1_InvertingInput_IO_PB12))

/** @defgroup COMP2_InvertingInput
  * @{
  */
#define COMP2_InvertingInput_1_16VREFINT          	((uint32_t)0x00000000)
#define COMP2_InvertingInput_2_16VREFINT          	((uint32_t)0x10000000)
#define COMP2_InvertingInput_3_16VREFINT          	((uint32_t)0x20000000)
#define COMP2_InvertingInput_4_16VREFINT          	((uint32_t)0x30000000)
#define COMP2_InvertingInput_5_16VREFINT          	((uint32_t)0x40000000)
#define COMP2_InvertingInput_6_16VREFINT          	((uint32_t)0x50000000)
#define COMP2_InvertingInput_7_16VREFINT          	((uint32_t)0x60000000)
#define COMP2_InvertingInput_8_16VREFINT          	((uint32_t)0x70000000)
#define COMP2_InvertingInput_9_16VREFINT          	((uint32_t)0x80000000)
#define COMP2_InvertingInput_10_16VREFINT          	((uint32_t)0x90000000)
#define COMP2_InvertingInput_11_16VREFINT          	((uint32_t)0xA0000000)
#define COMP2_InvertingInput_12_16VREFINT          	((uint32_t)0xB0000000)
#define COMP2_InvertingInput_IO_PA2		          	((uint32_t)0xC0000000)
#define COMP2_InvertingInput_VREFINT             	((uint32_t)0xD0000000)
#define COMP2_InvertingInput_IO_PA6            		((uint32_t)0xE0000000) 
#define COMP2_InvertingInput_IO_PB12                ((uint32_t)0xF0000000) 

#define IS_COMP2_INVERTING_INPUT(INPUT) (((INPUT) == COMP2_InvertingInput_1_16VREFINT)  || \
                                        ((INPUT) == COMP2_InvertingInput_2_16VREFINT) 	|| \
                                        ((INPUT) == COMP2_InvertingInput_3_16VREFINT)   || \
                                        ((INPUT) == COMP2_InvertingInput_4_16VREFINT)   || \
                                        ((INPUT) == COMP2_InvertingInput_5_16VREFINT)   || \
                                        ((INPUT) == COMP2_InvertingInput_6_16VREFINT) 	|| \
                                        ((INPUT) == COMP2_InvertingInput_7_16VREFINT)	|| \
										((INPUT) == COMP2_InvertingInput_8_16VREFINT)	|| \
										((INPUT) == COMP2_InvertingInput_9_16VREFINT)	|| \
										((INPUT) == COMP2_InvertingInput_10_16VREFINT)	|| \
										((INPUT) == COMP2_InvertingInput_11_16VREFINT)	|| \
										((INPUT) == COMP2_InvertingInput_12_16VREFINT)	|| \
										((INPUT) == COMP2_InvertingInput_IO_PA2)		|| \
										((INPUT) == COMP2_InvertingInput_VREFINT)		|| \
										((INPUT) == COMP2_InvertingInput_IO_PA6)		|| \
										((INPUT) == COMP2_InvertingInput_IO_PB12))
										
/** @defgroup COMP1_InphaseInput
  * @{
  */
#define COMP1_InphaseInput_IO_PA3			    ((uint32_t)0x00000000)
#define COMP1_InphaseInput_IO_PA5			    ((uint32_t)0x00000010)
#define COMP1_InphaseInput_IO_PA6			    ((uint32_t)0x00000020)
#define COMP1_InphaseInput_IO_PB0			    ((uint32_t)0x00000030)
#define COMP1_InphaseInput_IO_PB1			    ((uint32_t)0x00000040)
#define COMP1_InphaseInput_IO_PA2			    ((uint32_t)0x00000050)
#define COMP1_InphaseInput_IO_PB11			  	((uint32_t)0x00000060)
#define COMP1_InphaseInput_IO_PA7			    ((uint32_t)0x00000070)
#define IS_COMP1_INPHASE_INPUT(INPUT) (((INPUT) == COMP1_InphaseInput_IO_PA3)  || \
                                        ((INPUT) == COMP1_InphaseInput_IO_PA5) || \
                                        ((INPUT) == COMP1_InphaseInput_IO_PA6) || \
                                        ((INPUT) == COMP1_InphaseInput_IO_PA7) || \
                                        ((INPUT) == COMP1_InphaseInput_IO_PB0) || \
                                        ((INPUT) == COMP1_InphaseInput_IO_PB1) || \
                                        ((INPUT) == COMP1_InphaseInput_IO_PA2) || \
										((INPUT) == COMP1_InphaseInput_IO_PB11))
										
/** @defgroup COMP2_InphaseInput
  * @{
  */
#define COMP2_InphaseInput_IO_PA3			    ((uint32_t)0x00000000)
#define COMP2_InphaseInput_IO_PA5			    ((uint32_t)0x00000010)
#define COMP2_InphaseInput_IO_PA6			    ((uint32_t)0x00000020)
#define COMP2_InphaseInput_IO_PB0			    ((uint32_t)0x00000030)
#define COMP2_InphaseInput_IO_PB1			    ((uint32_t)0x00000040)
#define COMP2_InphaseInput_IO_PA2			    ((uint32_t)0x00000050)
#define COMP2_InphaseInput_IO_PB11			    ((uint32_t)0x00000060)
#define COMP2_InphaseInput_IO_PA4			    ((uint32_t)0x00000070)
#define IS_COMP2_INPHASE_INPUT(INPUT) (((INPUT) == COMP2_InphaseInput_IO_PA3)  || \
                                        ((INPUT) == COMP2_InphaseInput_IO_PA5) || \
                                        ((INPUT) == COMP2_InphaseInput_IO_PA6) || \
                                        ((INPUT) == COMP2_InphaseInput_IO_PB0) || \
                                        ((INPUT) == COMP2_InphaseInput_IO_PB1) || \
                                        ((INPUT) == COMP2_InphaseInput_IO_PA2) || \
                                        ((INPUT) == COMP2_InphaseInput_IO_PB11) || \
										((INPUT) == COMP2_InphaseInput_IO_PA4))										
/**
  * @}
  */

/** @defgroup COMP_Output
  * @{
  */

#define COMP_Output_None                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
#define COMP_Output_TIM1BKIN              COMP_CSR_COMP1OUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_Output_TIM1IC1               COMP_CSR_COMP1OUTSEL_1   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_Output_TIM1OCREFCLR          ((uint32_t)0x00000300)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_Output_TIM2IC4               COMP_CSR_COMP1OUTSEL_2   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_Output_TIM2OCREFCLR          ((uint32_t)0x00000500)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM3IC1               ((uint32_t)0x00000600)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_Output_TIM3OCREFCLR          COMP_CSR_COMP1OUTSEL     /*!< COMP output connected to TIM3 OCREF Clear */


#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_Output_None)         || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN)     || \
                                ((OUTPUT) == COMP_Output_TIM1IC1)      || \
                                ((OUTPUT) == COMP_Output_TIM1OCREFCLR) || \
                                ((OUTPUT) == COMP_Output_TIM2IC4)      || \
                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR) || \
                                ((OUTPUT) == COMP_Output_TIM3IC1)      || \
                                ((OUTPUT) == COMP_Output_TIM3OCREFCLR))
/**
  * @}
  */ 

/** @defgroup COMP_OutputPolarity
  * @{
  */
#define COMP_OutputPol_NonInverted          ((uint32_t)0x00000000)  /*!< COMP output on GPIO isn't inverted */
#define COMP_OutputPol_Inverted             COMP_CSR_COMP1POL       /*!< COMP output on GPIO is inverted */

#define IS_COMP_OUTPUT_POL(POL) (((POL) == COMP_OutputPol_NonInverted)  || \
                                 ((POL) == COMP_OutputPol_Inverted))

/**
  * @}
  */ 

/** @defgroup COMP_Hysteresis
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the hysteresis level */
#define COMP_Hysteresis_No                         0x00000000           /*!< No hysteresis */
#define COMP_Hysteresis_Low                        COMP_CSR_COMP1HYST_0 /*!< Hysteresis level low */
#define COMP_Hysteresis_Medium                     COMP_CSR_COMP1HYST_1 /*!< Hysteresis level medium */
#define COMP_Hysteresis_High                       COMP_CSR_COMP1HYST   /*!< Hysteresis level high */

#define IS_COMP_HYMHERESIS(HYMHERESIS)    (((HYMHERESIS) == COMP_Hysteresis_No) || \
                                           ((HYMHERESIS) == COMP_Hysteresis_Low) || \
                                           ((HYMHERESIS) == COMP_Hysteresis_Medium) || \
                                           ((HYMHERESIS) == COMP_Hysteresis_High))
/**
  * @}
  */

/** @defgroup COMP_Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_Mode_HighSpeed                     0x00000000            /*!< High Speed */
#define COMP_Mode_MediumSpeed                   COMP_CSR_COMP1MODE_0  /*!< Medium Speed */
#define COMP_Mode_LowPower                      COMP_CSR_COMP1MODE_1 /*!< Low power mode */
#define COMP_Mode_UltraLowPower                 COMP_CSR_COMP1MODE   /*!< Ultra-low power mode */

#define IS_COMP_MODE(MODE)    (((MODE) == COMP_Mode_UltraLowPower) || \
                               ((MODE) == COMP_Mode_LowPower)      || \
                               ((MODE) == COMP_Mode_MediumSpeed)   || \
                               ((MODE) == COMP_Mode_HighSpeed))
/**
  * @}
  */

/** @defgroup COMP_Fliter_Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_Fliter_Mode_OFF                     ((uint32_t)0x00000000) /*!< Filter OFF */
#define COMP_Fliter_Mode_Low                     ((uint32_t)0x00000001) /*!< Filter Low */
#define COMP_Fliter_Mode_High                    ((uint32_t)0x00000002) /*!< Filter High */
#define COMP_Fliter_Mode_Both                    ((uint32_t)0x00000003) /*!< Filter Both */

#define IS_COMP_FLITER_MODE(FLITER_MODE)    (((FLITER_MODE) == COMP_Fliter_Mode_OFF) || \
                                             ((FLITER_MODE) == COMP_Fliter_Mode_Low) || \
                                             ((FLITER_MODE) == COMP_Fliter_Mode_High) || \
                                             ((FLITER_MODE) == COMP_Fliter_Mode_Both))
/**
  * @}
  */

/** @defgroup COMP_Fliter_Clock
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_Fliter_Clock_0                      ((uint32_t)0x00000000) /*!< Filter 0 Clock */
#define COMP_Fliter_Clock_2                      ((uint32_t)0x00000001) /*!< Filter 0 Clock */
#define COMP_Fliter_Clock_4                      ((uint32_t)0x00000002) /*!< Filter 0 Clock */
#define COMP_Fliter_Clock_8                      ((uint32_t)0x00000003) /*!< Filter 0 Clock */
#define COMP_Fliter_Clock_16                     ((uint32_t)0x00000004) /*!< Filter 0 Clock */
#define COMP_Fliter_Clock_32                     ((uint32_t)0x00000005) /*!< Filter 0 Clock */
#define COMP_Fliter_Clock_64                     ((uint32_t)0x00000006) /*!< Filter 0 Clock */
#define COMP_Fliter_Clock_128                    ((uint32_t)0x00000007) /*!< Filter 0 Clock */

#define IS_COMP_FLITER_CLOCK(FLITER_CLOCK)    (((FLITER_CLOCK) == COMP_Fliter_Clock_0) || \
                                               ((FLITER_CLOCK) == COMP_Fliter_Clock_2) || \
                                               ((FLITER_CLOCK) == COMP_Fliter_Clock_4) || \
                                               ((FLITER_CLOCK) == COMP_Fliter_Clock_8) || \
                                               ((FLITER_CLOCK) == COMP_Fliter_Clock_16) || \
                                               ((FLITER_CLOCK) == COMP_Fliter_Clock_32) || \
                                               ((FLITER_CLOCK) == COMP_Fliter_Clock_64) || \
                                               ((FLITER_CLOCK) == COMP_Fliter_Clock_128))
/**
  * @}
  */

/** @defgroup COMP_Verf_Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_Vref_Mode0                      ((uint32_t)0x00000000) /*!< Vref Mode 0 */
#define COMP_Vref_Mode1                      COMP_CSR_COMP1SW1      /*!< Vref Mode 1 */

#define IS_COMP_VREF_MODE(VREF_MODE)    (((VREF_MODE) == COMP_Vref_Mode0) || \
                                         ((VREF_MODE) == COMP_Vref_Mode1))
/**
  * @}
  */

/** @defgroup COMP_OutputLevel
  * @{
  */ 
/* When output polarity is not inverted, comparator output is high when
   the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OutputLevel_High                   COMP_CSR_COMP1OUT
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputLevel_Low                    ((uint32_t)0x00000000)

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_DeInit(void);

/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct);
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct);
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection);
void COMP_FilterConfig(uint32_t COMP_Selection, uint32_t Filter_Mode, uint32_t Filter_Clock);
void COMP_VerfSelect(uint32_t Vref_Mode);

/* Window mode control function ***********************************************/
void COMP_WindowCmd(FunctionalState NewState);

/* COMP configuration locking function ****************************************/
void COMP_LockConfig(uint32_t COMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__MH20XX_COMP_H */

/**
  * @}
  */ 

/**
  * @}
  */
