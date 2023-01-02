/* 
 * File:   MCP47FEB2X.h
 * Author: pc
 *
 * Created on 2022년 6월 16일 (목), 오후 1:35
 */

#ifndef MCP47FEB2X_H
#define	MCP47FEB2X_H

#include "I2C.h"
//#ifdef  __USE_DAC

// MCP47FEB02A0-E/ST AAAK  8bit
#define Model_ID 0xC0
#define I2C_BUS_ACCESS_TIMEOUT				10

#define Volatile_DAC0_Register              0x00
#define Volatile_DAC1_Register              0x01
#define VREF_Register                       0x08
#define Power_Down_Register                 0x09
#define Gain_and_Status_Register            0x0A
#define WiperLock_Technology_Register       0x0B
#define Nonvolatile_DAC0_Register           0x10
#define Nonvolatile_DAC1_Register           0x11
#define Nonvolatile_VREF_Register           0x18
#define Nonvolatile_Power_Down_Register     0x19
#define NV_Gain_and_Slave_Address           0x1A

void I2C_DAC_Write(unsigned char address,int* data);
void I2C_Config_Write(unsigned char address);
unsigned int I2C_DAC_Read(unsigned char address);

#endif	/* MCP47FEB2X_H */

