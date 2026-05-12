#include "at24cxx.h"

uint32_t AT24Cxx_Timeout;
uint8_t AT24Cxx_Address=0;
uint8_t AT24Cxx_DataNum=0;


/*
主机模式
普通模式  100kHZ
I2C时钟频率32000KHz
使用模拟滤波器
不使用数字滤波器
上升时间100ns
下降时间10ns
*/
uint32_t AT24Cxx_TIMEOUT_UserCallback(void)
{
    /* Block communication and all processes */
  /*  while (1)
    {   
    }*/
	return AT24Cxx_FAIL;
}


void I2C2_Init(void)
{
	I2C_InitTypeDef I2C_InitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;
   	I2C_DeInit(I2C1);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_1);
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    I2C_InitStruct.I2C_Ack=I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_AnalogFilter=I2C_AnalogFilter_Enable;
    I2C_InitStruct.I2C_DigitalFilter=0x00;
    I2C_InitStruct.I2C_Mode=I2C_Mode_I2C;
    I2C_InitStruct.I2C_OwnAddress1=0x00;
    I2C_InitStruct.I2C_Timing=0x30E32E44;//0x20D22E37;
    I2C_Init(I2C1,&I2C_InitStruct);
	
	RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK);
	I2C_Cmd(I2C1, ENABLE);
}

void AT24CXX_Init(void)
{
    I2C2_Init();
    AT24Cxx_Address = AT24Cxx_HW_Address;
}

uint32_t AT24Cxx_WaitEepromStandbyState(void)      
{
    __IO uint32_t sEETrials = 0;

	/* Configure CR2 register : set Slave Address and end mode */
    I2C_TransferHandling(AT24Cxx_I2C, 
                         AT24Cxx_Address,
                         0, 
                         I2C_AutoEnd_Mode,
                         I2C_No_StartStop);  

    do
    { 
        /* Initialize sEETimeout */
        AT24Cxx_Timeout = AT24Cxx_FLAG_TIMEOUT;

        /* Clear NACKF */
        I2C_ClearFlag(AT24Cxx_I2C, 
                      I2C_ICR_NACKCF | I2C_ICR_STOPCF);

        /* Generate start */
        I2C_GenerateSTART(AT24Cxx_I2C, ENABLE);

        /* Wait until timeout elapsed */
        while (AT24Cxx_Timeout-- != 0); 

        /* Check if the maximum allowed numbe of trials has bee reached */
        if (sEETrials++ == AT24Cxx_MAX_TRIALS_NUMBER)
        {
            /* If the maximum number of trials has been reached, exit the function */
            return AT24Cxx_TIMEOUT_UserCallback();
        }
    }

    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_NACKF) != RESET);

    /* Clear STOPF */
    I2C_ClearFlag(AT24Cxx_I2C, I2C_ICR_STOPCF);

    /* Return sEE_OK if device is ready */
    return AT24Cxx_OK;
}

uint32_t AT24Cxx_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite)
{
    uint32_t DataNum = 0;
#if defined(AT24C04) || defined(AT24C08)|| defined(AT24C16) || defined(AT24C32)|| defined(AT24C64) 
    I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, 2, I2C_Reload_Mode, I2C_Generate_Start_Write);
#else
	I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
#endif
    AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;

    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TXIS) == RESET)
    {
        if((AT24Cxx_Timeout--) == 0) 
        {
            return AT24Cxx_TIMEOUT_UserCallback();
        }
    }

#if defined(AT24C04) || defined(AT24C08)|| defined(AT24C16) || defined(AT24C32)|| defined(AT24C64) 
  /* Send MSB of memory address */
    I2C_SendData(AT24Cxx_I2C, (uint8_t)((WriteAddr & 0xFF00) >> 8));  

  /* Wait until TXIS flag is set */
    AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;

    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TXIS) == RESET)
    {
        if((AT24Cxx_Timeout--) == 0) 
        {
            return AT24Cxx_TIMEOUT_UserCallback();
        }
    }
#endif

    /* Send LSB of memory address  */
    I2C_SendData(AT24Cxx_I2C, (uint8_t)(WriteAddr & 0x00FF));

    /* Wait until TCR flag is set */
    AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TCR) == RESET)
    {
        if((AT24Cxx_Timeout--) == 0) 
        {
            return AT24Cxx_TIMEOUT_UserCallback();
        }
    }

    /* Update CR2 : set Slave Address , set write request, generate Start and set end mode */
    I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, (uint8_t)(*NumByteToWrite), I2C_AutoEnd_Mode, I2C_No_StartStop);

    while (DataNum != (*NumByteToWrite))
    {      
        /* Wait until TXIS flag is set */
        AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TXIS) == RESET)
        {
        if((AT24Cxx_Timeout--) == 0) 
        {
          return AT24Cxx_TIMEOUT_UserCallback();
        }
        }  

        /* Write data to TXDR */
        I2C_SendData(AT24Cxx_I2C, (uint8_t)(pBuffer[DataNum]));

        /* Update number of transmitted data */
        DataNum++;   
    }  

    /* Wait until STOPF flag is set */
    AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_STOPF) == RESET)
    {
        if((AT24Cxx_Timeout--) == 0) 
        {
            return AT24Cxx_TIMEOUT_UserCallback();
        }
    }   

    /* Clear STOPF flag */
    I2C_ClearFlag(AT24Cxx_I2C, I2C_ICR_STOPCF);
    return AT24Cxx_OK;
}




void AT24Cxx_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t NumOfPage = 0, NumOfSingle = 0, count = 0;
    uint16_t Addr = 0;

    Addr = WriteAddr % AT24Cxx_PAGESIZE;
    count = AT24Cxx_PAGESIZE - Addr;
    NumOfPage =  NumByteToWrite / AT24Cxx_PAGESIZE;
    NumOfSingle = NumByteToWrite % AT24Cxx_PAGESIZE;

    /*!< If WriteAddr is sEE_PAGESIZE aligned  */
    if(Addr == 0) 
    {
        /*!< If NumByteToWrite < sEE_PAGESIZE */
        if(NumOfPage == 0) 
        {
            /* Store the number of data to be written */
            AT24Cxx_DataNum = NumOfSingle;
            /* Start writing data */
            AT24Cxx_WritePage(pBuffer, WriteAddr, (uint8_t*)(&AT24Cxx_DataNum));
            AT24Cxx_WaitEepromStandbyState();
        }
        /*!< If NumByteToWrite > sEE_PAGESIZE */
        else  
        {
            while(NumOfPage--)
            {
                /* Store the number of data to be written */
                AT24Cxx_DataNum = AT24Cxx_PAGESIZE;        
                AT24Cxx_WritePage(pBuffer, WriteAddr, (uint8_t*)(&AT24Cxx_DataNum)); 
                AT24Cxx_WaitEepromStandbyState();
                WriteAddr +=  AT24Cxx_PAGESIZE;
                pBuffer += AT24Cxx_PAGESIZE;
            }

            if(NumOfSingle!=0)
            {
                /* Store the number of data to be written */
                AT24Cxx_DataNum = NumOfSingle;          
                AT24Cxx_WritePage(pBuffer, WriteAddr, (uint8_t*)(&AT24Cxx_DataNum));
                AT24Cxx_WaitEepromStandbyState();
            }
        }
    }
    /*!< If WriteAddr is not sEE_PAGESIZE aligned  */
    else 
    {
        /*!< If NumByteToWrite < sEE_PAGESIZE */
        if(NumOfPage== 0) 
        {
            /*!< If the number of data to be written is more than the remaining space 
            in the current page: */
            if (NumByteToWrite > count)
            {
                /* Store the number of data to be written */
                AT24Cxx_DataNum = count;        
                /*!< Write the data conained in same page */
                AT24Cxx_WritePage(pBuffer, WriteAddr, (uint8_t*)(&AT24Cxx_DataNum));
                AT24Cxx_WaitEepromStandbyState();      

                /* Store the number of data to be written */
                AT24Cxx_DataNum = (NumByteToWrite - count);          
                /*!< Write the remaining data in the following page */
                AT24Cxx_WritePage((uint8_t*)(pBuffer + count), (WriteAddr + count), (uint8_t*)(&AT24Cxx_DataNum));
                AT24Cxx_WaitEepromStandbyState();        
            }      
            else      
            {
                /* Store the number of data to be written */
                AT24Cxx_DataNum = NumOfSingle;         
                AT24Cxx_WritePage(pBuffer, WriteAddr, (uint8_t*)(&AT24Cxx_DataNum));
                AT24Cxx_WaitEepromStandbyState();        
            }     
        }
        /*!< If NumByteToWrite > sEE_PAGESIZE */
        else
        {
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / AT24Cxx_PAGESIZE;
            NumOfSingle = NumByteToWrite % AT24Cxx_PAGESIZE;

            if(count != 0)
            {  
                /* Store the number of data to be written */
                AT24Cxx_DataNum = count;         
                AT24Cxx_WritePage(pBuffer, WriteAddr, (uint8_t*)(&AT24Cxx_DataNum));
                AT24Cxx_WaitEepromStandbyState();
                WriteAddr += count;
                pBuffer += count;
            } 

            while(NumOfPage--)
            {
                /* Store the number of data to be written */
                AT24Cxx_DataNum = AT24Cxx_PAGESIZE;          
                AT24Cxx_WritePage(pBuffer, WriteAddr, (uint8_t*)(&AT24Cxx_DataNum));
                AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
                AT24Cxx_WaitEepromStandbyState();
                WriteAddr +=  AT24Cxx_PAGESIZE;
                pBuffer += AT24Cxx_PAGESIZE;  
            }
            if(NumOfSingle != 0)
            {
                /* Store the number of data to be written */
                AT24Cxx_DataNum = NumOfSingle;           
                AT24Cxx_WritePage(pBuffer, WriteAddr, (uint8_t*)(&AT24Cxx_DataNum)); 
                AT24Cxx_WaitEepromStandbyState();
            }
        }
    }  
}



uint32_t AT24Cxx_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead)
{  
    uint32_t NumbOfSingle = 0, Count = 0, DataNum = 0, StartCom = 0;

    /* Get number of reload cycles */
    Count = (*NumByteToRead) / 255;  
    NumbOfSingle = (*NumByteToRead) % 255;
#if defined(AT24C04) || defined(AT24C08)|| defined(AT24C16) || defined(AT24C32)|| defined(AT24C64)  
    /* Configure slave address, nbytes, reload and generate start */
    I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, 2, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
#else
	I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
#endif
    /* Wait until TXIS flag is set */
    AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TXIS) == RESET)
    {
        if((AT24Cxx_Timeout--) == 0) 
        {
            return AT24Cxx_TIMEOUT_UserCallback();
        }
    }
	
#if defined(AT24C04) || defined(AT24C08)|| defined(AT24C16) || defined(AT24C32)|| defined(AT24C64)  
    /* Send MSB of memory address */
    I2C_SendData(AT24Cxx_I2C, (uint8_t)((ReadAddr & 0xFF00) >> 8));

    /* Wait until TXIS flag is set */
    AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;  
    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TXIS) == RESET)
    {
        if((AT24Cxx_Timeout--) == 0)
			return AT24Cxx_TIMEOUT_UserCallback();
    }
#endif
    /* Send LSB of memory address  */
    I2C_SendData(AT24Cxx_I2C, (uint8_t)(ReadAddr & 0x00FF));

    /* Wait until TC flag is set */
    AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TC) == RESET)
    {
        if((AT24Cxx_Timeout--) == 0) return AT24Cxx_TIMEOUT_UserCallback();
    }  

    /* If number of Reload cycles is not equal to 0 */
    if (Count != 0)
    {
        /* Starting communication */
        StartCom = 1;

        /* Wait until all reload cycles are performed */
        while( Count != 0)
        { 
            /* If a read transfer is performed */
            if (StartCom == 0)      
            {
                /* Wait until TCR flag is set */
                AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT; 
                while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TCR) == RESET)
                {
                    if((AT24Cxx_Timeout--) == 0) return AT24Cxx_TIMEOUT_UserCallback();
                }
            }      

            /* if remains one read cycle */
            if ((Count == 1) && (NumbOfSingle == 0))
            {
                /* if starting communication */
                if (StartCom != 0)
                {
                    /* Configure slave address, end mode and start condition */
                    I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, 255, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
                }
                else
                {
                    /* Configure slave address, end mode */
                    I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, 255, I2C_AutoEnd_Mode, I2C_No_StartStop);          
                }
            }
            else 
            {
                /* if starting communication */
                if (StartCom != 0)
                {
                    /* Configure slave address, end mode and start condition */
                    I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, 255, I2C_Reload_Mode, I2C_Generate_Start_Read);
                }
                else
                {
                    /* Configure slave address, end mode */
                    I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, 255, I2C_Reload_Mode, I2C_No_StartStop);          
                } 
            }

            /* Update local variable */
            StartCom = 0;      
            DataNum = 0;

            /* Wait until all data are received */
            while (DataNum != 255)
            {        
                /* Wait until RXNE flag is set */
                AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
                while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_RXNE) == RESET)
                {
                    if((AT24Cxx_Timeout--) == 0) return AT24Cxx_TIMEOUT_UserCallback();
                }

                /* Read data from RXDR */
                pBuffer[DataNum]= I2C_ReceiveData(AT24Cxx_I2C);

                /* Update number of received data */
                DataNum++;
                (*NumByteToRead)--;
            }      
            /* Update Pointer of received buffer */ 
            pBuffer += DataNum;  

            /* update number of reload cycle */
            Count--;
        }

        /* If number of single data is not equal to 0 */
        if (NumbOfSingle != 0)
        {            
            /* Wait until TCR flag is set */
            AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;   
            while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_TCR) == RESET)
            {
                if((AT24Cxx_Timeout--) == 0) return AT24Cxx_TIMEOUT_UserCallback();
            }

            /* Update CR2 : set Nbytes and end mode */
            I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, (uint8_t)(NumbOfSingle), I2C_AutoEnd_Mode, I2C_No_StartStop);

            /* Reset local variable */
            DataNum = 0;

            /* Wait until all data are received */
            while (DataNum != NumbOfSingle)
            {        
                /* Wait until RXNE flag is set */
                AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
                while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_RXNE) == RESET)
                {
                    if((AT24Cxx_Timeout--) == 0) return AT24Cxx_TIMEOUT_UserCallback();
                }

                /* Read data from RXDR */
                pBuffer[DataNum]= I2C_ReceiveData(AT24Cxx_I2C);

                /* Update number of received data */
                DataNum++;
                (*NumByteToRead)--;
            } 
        }
    }   
    else
    {
        /* Update CR2 : set Slave Address , set read request, generate Start and set end mode */
        I2C_TransferHandling(AT24Cxx_I2C, AT24Cxx_Address, (uint32_t)(NumbOfSingle), I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

        /* Reset local variable */
        DataNum = 0;

        /* Wait until all data are received */
        while (DataNum != NumbOfSingle)
        {
            /* Wait until RXNE flag is set */
            AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT; 
            while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_RXNE) == RESET)
            {
                if((AT24Cxx_Timeout--) == 0) return AT24Cxx_TIMEOUT_UserCallback();
            }

            /* Read data from RXDR */
            pBuffer[DataNum]= I2C_ReceiveData(AT24Cxx_I2C);

            /* Update number of received data */
            DataNum++;
            (*NumByteToRead)--;
        }    
    }  

    /* Wait until STOPF flag is set */
    AT24Cxx_Timeout = AT24Cxx_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(AT24Cxx_I2C, I2C_ISR_STOPF) == RESET)
    {
        if((AT24Cxx_Timeout--) == 0) return AT24Cxx_TIMEOUT_UserCallback();
    }

    /* Clear STOPF flag */
    I2C_ClearFlag(AT24Cxx_I2C, I2C_ICR_STOPCF);

    /* If all operations OK, return sEE_OK (0) */
    return AT24Cxx_OK;
}
