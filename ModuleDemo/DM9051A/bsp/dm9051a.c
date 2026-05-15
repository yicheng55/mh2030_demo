#include "dm9051a.h"

void DM9051A_Init(void)
{
    MH2030A_SPI1_Init();
}

uint8_t DM9051A_ReadReg(uint8_t reg)
{
    return DM9058_ReadReg(reg);
}

void DM9051A_WriteReg(uint8_t reg, uint8_t val)
{
    DM9058_WriteReg(reg, val);
}

uint16_t DM9051A_ReadVID(void)
{
    return DM9058_ReadVID();
}

uint16_t DM9051A_ReadPID(void)
{
    return DM9058_ReadPID();
}
