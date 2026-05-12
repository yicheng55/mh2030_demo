/* Includes ------------------------------------------------------------------*/
#include "mh20xx_opa.h"

void OPA_DeInit(OPA_TypeDef* OPAx)
{
  /* Check the parameters */
  assert_param(IS_OPA_ALL_PERIPH(OPAx));

  OPAx->CTRL = 0x00;
}

void OPA_SetMode(OPA_TypeDef* OPAx, uint32_t OPA_Mode)
{
	/* Check the parameters */
	assert_param(IS_OPA_ALL_PERIPH(OPAx));
	assert_param(IS_OPA_MDOE(OPA_Mode));
	
	OPAx->CTRL &= ~OPA_MODE_HIGH;
	OPAx->CTRL |= OPA_Mode;
}

void OPA_Enable(OPA_TypeDef* OPAx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_OPA_ALL_PERIPH(OPAx));
	
	if (NewState != DISABLE)
	{
		OPAx->CTRL |= OPA_CTRL_EN;
	}
	else
	{
		OPAx->CTRL &= ~OPA_CTRL_EN;
	}
}

