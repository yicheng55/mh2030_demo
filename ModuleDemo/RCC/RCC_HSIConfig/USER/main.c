#include <stdarg.h>
#include <stdio.h>
#include "delay.h"
#include "mh20xx.h"
#include "mh2030a_board.h"

/* 定義此巨集啟用直接發送測試，關閉後改用 printf */
// #define USART2_RAW_TEST

#ifdef USART2_RAW_TEST
extern int UART_PutChar(int ch);
static void UART_SendString(const char *text)
{
	while (*text != '\0')
		UART_PutChar((uint8_t)*text++);
}
#define PRINTF_LOG(fmt, ...)  /* 停用 */
#else
#define PRINTF_LOG  printf
#endif

#define SYSCLK_MODE_HSI_8M      0
#define SYSCLK_MODE_HSI_PLL     1

/* 切換此巨集以選擇時鐘模式 */
#define SYSCLK_MODE             SYSCLK_MODE_HSI_PLL

/* 實測 PLL 輸入為 HSI/2，因此需 x18 才能到 72 MHz */
#define HSI_PLL_SOURCE          RCC_PLLSource_HSI
#define HSI_PLL_MUL             RCC_PLLMul_18

static void CLK_Configuration(void);
static void Clock_UpdateCoreClock(void);
static void Clock_PrintConfig(void);
static void Clock_Log(const char *fmt, ...);
static const char *Clock_GetPllSourceName(void);
static uint32_t Clock_GetPllMulFactor(void);

RCC_ClocksTypeDef clocks;
int main(void)
{
#ifdef USART2_RAW_TEST
	CLK_Configuration();
	Clock_UpdateCoreClock();
	Delay_Init();
	UART_Configuration(115200);
	Clock_PrintConfig();

	UART_SendString("USART2 Test Start 115200\r\n");
	while(1)
	{
		UART_SendString("Hello USART2\r\n");
		Delay_Ms(500);
	}
#else
	CLK_Configuration();
	Clock_UpdateCoreClock();
	Delay_Init();
	UART_Configuration(115200);
	Clock_PrintConfig();

	while(1)
	{
		PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\n",
			(float)clocks.SYSCLK_Frequency / 1000000,
			(float)clocks.HCLK_Frequency   / 1000000,
			(float)clocks.PCLK_Frequency   / 1000000);
		Delay_Ms(500);
	}
#endif
}

static void Clock_UpdateCoreClock(void)
{
	RCC_GetClocksFreq(&clocks);
	SystemCoreClock = clocks.HCLK_Frequency;
}

static void Clock_Log(const char *fmt, ...)
{
	char buffer[96];
	va_list args;

	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

#ifdef USART2_RAW_TEST
	UART_SendString(buffer);
#else
	printf("%s", buffer);
#endif
}

static void Clock_PrintConfig(void)
{
	Clock_UpdateCoreClock();
	Clock_Log("Clock mode: %s\r\n",
#if SYSCLK_MODE == SYSCLK_MODE_HSI_PLL
		"HSI/2 + PLL (72MHz target)"
#else
		"HSI 8MHz"
#endif
	);
	Clock_Log("PLL source: %s, PLL mul: x%lu\r\n",
		Clock_GetPllSourceName(),
		(unsigned long)Clock_GetPllMulFactor());
	Clock_Log("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK: %3.1fMhz\r\n",
		(float)clocks.SYSCLK_Frequency / 1000000,
		(float)clocks.HCLK_Frequency   / 1000000,
		(float)clocks.PCLK_Frequency   / 1000000);
}

static const char *Clock_GetPllSourceName(void)
{
	uint32_t pll_source;

	pll_source = RCC->CFGR & RCC_CFGR_PLLSRC;
	if (pll_source == RCC_CFGR_PLLSRC_HSI_DIV2)
		return "HSI/2";
	if (pll_source == RCC_CFGR_PLLSRC_HSI_PREDIV)
		return "HSI";
	return "HSE/PREDIV1";
}

static uint32_t Clock_GetPllMulFactor(void)
{
	uint32_t pll_mul;

	pll_mul = (RCC->CFGR & RCC_CFGR_PLLMULL) >> 18;
	if ((RCC->CFGR & RCC_CFGR_PLLMULL_4) == RCC_CFGR_PLLMULL_4)
		return pll_mul + 1;
	return pll_mul + 2;
}

static void CLK_Configuration(void)
{
	RCC_DeInit();

	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	while(RCC_GetSYSCLKSource() != 0x00);

	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_HCLK_Div1);

#if SYSCLK_MODE == SYSCLK_MODE_HSI_PLL
	/* 實測 PLL 輸入為 HSI/2，故以 4 MHz x 18 = 72 MHz */
	RCC_PLLCmd(DISABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET);

	FLASH_Unlock();
	FLASH_SetLatency(FLASH_Latency_2);
	FLASH_Lock();

	RCC_PLLConfig(HSI_PLL_SOURCE, HSI_PLL_MUL);

	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08);
#else
	FLASH_Unlock();
	FLASH_SetLatency(FLASH_Latency_0);
	FLASH_Lock();
#endif
}
