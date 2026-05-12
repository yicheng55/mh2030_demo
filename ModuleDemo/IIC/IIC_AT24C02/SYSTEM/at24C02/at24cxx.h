/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT24CXX_H
#define __AT24CXX_H

/* Includes ------------------------------------------------------------------*/
#include "mh20xx.h"

#define AT24Cxx_FLAG_TIMEOUT         ((uint32_t)0x2000)
#define AT24Cxx_LONG_TIMEOUT         ((uint32_t)(10 * AT24Cxx_FLAG_TIMEOUT))

#define AT24Cxx_MAX_TRIALS_NUMBER     300

#define AT24Cxx_OK                    0
#define AT24Cxx_FAIL                  1   
#define AT24Cxx_I2C                   I2C1


//AT24C01 AT24C02           一页  8Byte
//AT24C04 AT24C08 AT24C16   一页  16Byte
//AT24C32 AT24C64           一页  32Byte
#define AT24C02   //定义你使用的芯片型号

#if defined(AT24C01) || defined(AT24C02)
	#define AT24Cxx_PAGESIZE              8
#elif defined(AT24C04) || defined(AT24C08)|| defined(AT24C16) 
	#define AT24Cxx_PAGESIZE              16
#else
	#define AT24Cxx_PAGESIZE              32
#endif

#define AT24Cxx_HW_Address            0xA2//硬件地址

extern void AT24CXX_Init(void);
extern void AT24Cxx_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
extern uint32_t AT24Cxx_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead);

#endif
