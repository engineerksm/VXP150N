/*
 * File:   AS1115.c
 * Author: pc
 *
 * Created on 2022년 6월 15일 (수), 오전 10:49
 */

#include "AS1115.h"


void I2C_AS1115_Write(unsigned char cmd,unsigned char data)
{
    I2CStart();
    I2CSend(AS1115_ADR);
    I2CAck();
    I2CSend(cmd);
    I2CAck();
    I2CSend(data);
    I2CAck();
    I2CStop();    
}
