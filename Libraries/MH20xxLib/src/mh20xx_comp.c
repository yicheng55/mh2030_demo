/* Includes ------------------------------------------------------------------*/
#include "mh20xx_comp.h"

/** @defgroup COMP 
  * @brief COMP driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* CSR register Mask */
#define COMP_CSR_CLEAR_MASK              ((uint32_t)0x00003F7C)
#define COMP_CTRL_CLEAR_MASK             ((uint32_t)0x0F000000)
#define COMP1_CTRL_FILTER_CLEAR_MASK     ((uint32_t)0x000031C0)
#define COMP2_CTRL_FILTER_CLEAR_MASK     ((uint32_t)0x0000CE00)
#define COMP2_CTRL_VREF_MODE_MASK        ((uint32_t)0x00000002)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup COMP_Private_Functions
  * @{
  */

/** @defgroup COMP_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
               ##### Initialization and Configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */
   
/**
  * @brief  Deinitializes COMP peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  None
  * @retval None
  */
void COMP_DeInit(void)
{
  COMP->CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
}

/**
  * @brief  Initializes the COMP peripheral according to the specified parameters
  *         in COMP_InitStruct
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @note   By default, PA1 is selected as COMP1 non inverting input.
  *         To use PA4 as COMP1 non inverting input call COMP_Init()
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure that contains 
  *         the configuration information for the specified COMP peripheral.
  * @retval None
  */
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_COMP_OUTPUT(COMP_InitStruct->COMP_Output));
  assert_param(IS_COMP_OUTPUT_POL(COMP_InitStruct->COMP_OutputPol));
  assert_param(IS_COMP_HYMHERESIS(COMP_InitStruct->COMP_Hysteresis));
  assert_param(IS_COMP_MODE(COMP_InitStruct->COMP_Mode));

  if(COMP_Selection_COMP1 == COMP_Selection)
  {
	assert_param(IS_COMP1_INVERTING_INPUT(COMP_InitStruct->COMP_InvertingInput));
	assert_param(IS_COMP1_INPHASE_INPUT(COMP_InitStruct->COMP_InphaseInput));
	COMP->CTRL &= (uint32_t) ~(COMP_CTRL_CLEAR_MASK);
  }
  else if(COMP_Selection_COMP2 == COMP_Selection)
  {
	assert_param(IS_COMP2_INVERTING_INPUT(COMP_InitStruct->COMP_InvertingInput));
	assert_param(IS_COMP2_INPHASE_INPUT(COMP_InitStruct->COMP_InphaseInput));	  
	COMP->CTRL &= (uint32_t) ~(COMP_CTRL_CLEAR_MASK<<4);
  }
  
  tmpreg = COMP->CSR;

  tmpreg &= (uint32_t) ~(COMP_CSR_CLEAR_MASK<<COMP_Selection);

  tmpreg |= (uint32_t)((COMP_InitStruct->COMP_InphaseInput | COMP_InitStruct->COMP_Output |
                       COMP_InitStruct->COMP_OutputPol | COMP_InitStruct->COMP_Hysteresis |
                       COMP_InitStruct->COMP_Mode)<<COMP_Selection);

  COMP->CTRL |= COMP_InitStruct->COMP_InvertingInput;
  COMP->CSR = tmpreg;  
}

/**
  * @brief  Fills each COMP_InitStruct member with its default value.
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct)
{
  COMP_InitStruct->COMP_InvertingInput = COMP1_InvertingInput_1_16VREFINT;
  COMP_InitStruct->COMP_InphaseInput = COMP1_InphaseInput_IO_PA3;
  COMP_InitStruct->COMP_Output = COMP_Output_None;
  COMP_InitStruct->COMP_OutputPol = COMP_OutputPol_NonInverted;
  COMP_InitStruct->COMP_Hysteresis = COMP_Hysteresis_No;
  COMP_InitStruct->COMP_Mode = COMP_Mode_UltraLowPower;
}

/**
  * @brief  Enable or disable the COMP peripheral.
  * @note   If the selected comparator is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  * @param  NewState: new state of the COMP peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, the comparator compares the non inverting input with 
  *         the inverting input and the comparison result is available on comparator output.
  * @note   When disabled, the comparator doesn't perform comparison and the 
  *         output level is low.
  * @retval None
  */
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected COMP peripheral */
    COMP->CSR |= (uint32_t) (1<<COMP_Selection);
  }
  else
  {
    /* Disable the selected COMP peripheral  */
    COMP->CSR &= (uint32_t)(~((uint32_t)1<<COMP_Selection));
  }
}

/**
  * @brief  Return the output level (high or low) of the selected comparator. 
  * @note   The output level depends on the selected polarity.
  * @note   If the polarity is not inverted:
  *          - Comparator output is low when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is high when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @note   If the polarity is inverted:
  *          - Comparator output is high when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is low when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected  
  * @retval Returns the selected comparator output level: low or high.
  *       
  */
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection)
{
  uint32_t compout = 0x0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Check if selected comparator output is high */
  if ((COMP->CSR & (COMP_CSR_COMP1OUT<<COMP_Selection)) != 0)
  {
    compout = COMP_OutputLevel_High;
  }
  else
  {
    compout = COMP_OutputLevel_Low;
  }

  /* Return the comparator output level */
  return (uint32_t)(compout);
}

/**
  * @brief  Configure filter of the selected comparator. 
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected  
  * @param  Filter_Mode: the selected filter mode. 
  *          This parameter can be one of the following values:
  *            @arg COMP_Fliter_Mode_OFF: Filter Off
  *            @arg COMP_Fliter_Mode_Low: Filter low
  *            @arg COMP_Fliter_Mode_High: Filter high
  *            @arg COMP_Fliter_Mode_Both: Filter both
  * @param  Filter_Clock: Filter clock. 
  *          This parameter can be one of the following values:
  *            @arg COMP_Fliter_Clock_0: Filter 0 clock
  *            @arg COMP_Fliter_Clock_2: Filter 2 clock
  *            @arg COMP_Fliter_Clock_4: Filter 4 clock
  *            @arg COMP_Fliter_Clock_8: Filter 8 clock
  *            @arg COMP_Fliter_Clock_16: Filter 16 clock
  *            @arg COMP_Fliter_Clock_32: Filter 32 clock
  *            @arg COMP_Fliter_Clock_64: Filter 64 clock
  *            @arg COMP_Fliter_Clock_128: Filter 128 clock
  * @retval Returns none.
  *
  */
void COMP_FilterConfig(uint32_t COMP_Selection, uint32_t Filter_Mode, uint32_t Filter_Clock)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_COMP_FLITER_MODE(Filter_Mode));
  assert_param(IS_COMP_FLITER_CLOCK(Filter_Clock));

  if(COMP_Selection == COMP_Selection_COMP1)
  {
    COMP->CTRL &= ~COMP1_CTRL_FILTER_CLEAR_MASK;
    COMP->CTRL |= (Filter_Mode << 12) | (Filter_Clock << 6);
  }
  else
  {
    COMP->CTRL &= ~(COMP2_CTRL_FILTER_CLEAR_MASK << 3);
    COMP->CTRL |= (Filter_Mode << 14) | (Filter_Clock << 9);
  }
}

/**
  * @brief  Configure vref mode of the selected comparator. 
  * @param  Vref_Mode: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP_Vref_Mode0: Vref mode 0
  *            @arg COMP_Vref_Mode1: Vref mode 1
  * @retval Returns none.
  *
  */
void COMP_VerfSelect(uint32_t Vref_Mode)
{
  assert_param(IS_COMP_VREF_MODE(Vref_Mode));

  COMP->CSR &= ~COMP2_CTRL_VREF_MODE_MASK;
  COMP->CSR |= Vref_Mode;
}

/**
  * @}
  */

/** @defgroup COMP_Group2 Window mode control function
 *  @brief   Window mode control function 
 *
@verbatim   
 ===============================================================================
                     ##### Window mode control function #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the window mode.
  * @note   In window mode, COMP1 and COMP2 non inverting inputs are connected
  *         together and only COMP1 non inverting input (PA1) can be used.
  * @param  NewState: new state of the window mode.
  *          This parameter can be :
  *           @arg ENABLE: COMP1 and COMP2 non inverting inputs are connected together.
  *           @arg DISABLE: OMP1 and COMP2 non inverting inputs are disconnected.
  * @retval None
  */
void COMP_WindowCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the window mode */
    COMP->CSR |= (uint32_t) COMP_CSR_WNDWEN;
  }
  else
  {
    /* Disable the window mode */
    COMP->CSR &= (uint32_t)(~COMP_CSR_WNDWEN);
  }
}

/**
  * @}
  */

/** @defgroup COMP_Group3 COMP configuration locking function
 *  @brief   COMP1 and COMP2 configuration locking function
 *           COMP1 and COMP2 configuration can be locked each separately.
 *           Unlocking is performed by system reset.
 *
@verbatim   
 ===============================================================================
                     ##### Configuration Lock function #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected comparator (COMP1/COMP2) configuration.
  * @note   Locking the configuration means that all control bits are read-only.
  *         To unlock the comparator configuration, perform a system reset.
  * @param  COMP_Selection: selects the comparator to be locked 
  *          This parameter can be a value of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 configuration is locked.
  *            @arg COMP_Selection_COMP2: COMP2 configuration is locked.  
  * @retval None
  */
void COMP_LockConfig(uint32_t COMP_Selection)
{
  /* Check the parameter */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Set the lock bit corresponding to selected comparator */
  COMP->CSR |= (uint32_t) (COMP_CSR_COMP1LOCK<<COMP_Selection);
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

