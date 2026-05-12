/* Includes ------------------------------------------------------------------*/
#include "mh20xx_divqsrt.h"

void DIVQSRT_SetDivMode(uint32_t DIVQSRT_DivMode)
{
    assert_param(IS_DIV_MODE(DIVQSRT_DivMode));

    if (DIVQSRT_DivMode != DIV_MODE_UNSIGNED)
    {
        DIVQSRT->DIVCR &= ~DIV_MODE_UNSIGNED;
    }
    else
    {
        DIVQSRT->DIVCR |= DIV_MODE_UNSIGNED;
    }
}

void DIVQSRT_SetDividend(int32_t DIVQSRT_Dividend)
{
	DIVQSRT->DIVIDEND = DIVQSRT_Dividend;
}

void DIVQSRT_SetDivisor(int32_t DIVQSRT_Divisor)
{
	DIVQSRT->DIVISOR = DIVQSRT_Divisor;
}

int32_t DIVQSRT_GetDivres(void)
{
	return DIVQSRT->DIVRES;
}

int32_t DIVQSRT_GetRemainder(void)
{
	return DIVQSRT->REMAINDER;
}

void DIVQSRT_SetRadicand(int32_t DIVQSRT_Radicand)
{
	DIVQSRT->RADICAND = DIVQSRT_Radicand;
}

int32_t DIVQSRT_GetSqrtres(void)
{
	return DIVQSRT->SQRTRES;
}

void DIVQSRT_ITConfig(uint32_t DIVQSRT_IT,FunctionalState NewState)
{
	assert_param(IS_DIVQSRT_CONFIG_IT(DIVQSRT_IT));

	if (NewState != DISABLE)
	{
		DIVQSRT->DIVCR |= DIVQSRT_IT;
	}
	else
	{
		DIVQSRT->DIVCR &= ~DIVQSRT_IT;
	}
}

FlagStatus DIVQSRT_GetFlagStatus(uint32_t DIVQSRT_FLAG)
{
	FlagStatus bitstatus = RESET;
	
	assert_param(IS_DIVQSRT_FLAG(DIVQSRT_FLAG));
	
	if ((DIVQSRT->DIVSR & DIVQSRT_FLAG) != (uint16_t)RESET)
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	return bitstatus;
}

void DIVQSRT_ClearFlag(uint32_t DIVQSRT_FLAG)
{
	assert_param(IS_DIVQSRT_FLAG(DIVQSRT_FLAG));

	DIVQSRT->DIVSR |= DIVQSRT_FLAG;
}
