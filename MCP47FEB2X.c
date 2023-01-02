
#include "MCP47FEB2X.h"

void I2C_DAC_Write(unsigned char address,int* data)
{

    I2CStart_2();
    I2CSend_2(Model_ID);
    I2CAck_2();
    I2CSend_2((address << 3) & 0xF8);
    I2CAck_2();
    I2CSend_2(((*data) >> 8) & 0xFF);
    I2CAck_2();
    I2CSend_2((*data) & 0xFF);
    I2CAck_2();
    I2CStop_2();
}

unsigned int I2C_DAC_Read(unsigned char address)
{
    unsigned int data;
    
	I2CStart_2();
	I2CSend_2(Model_ID);
    I2CAck_2();
    I2CSend_2(((address << 3) | 0x06));
    I2CAck_2();
   
	I2CRestart_2();
	I2CSend_2(Model_ID | 0x01);
    I2CAck_2();
    data = (I2CRead_2() << 8);
    I2CAck_2();
    data |= I2CRead_2();
   
    I2CNak_2();
    I2CStop_2();
    return data;

}

void I2C_Config_Write(unsigned char address){
    I2CStart_2();
    I2CSend_2(Model_ID);
    I2CAck_2();
    I2CSend_2((address << 3) & 0xF4);
    I2CAck_2();
    I2CSend_2((address << 3) & 0xF4);
    I2CAck_2();
    I2CStop_2();
}
