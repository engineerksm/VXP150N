/* 
 * File:   I2C.h
 * Author: pc
 *
 * Created on 2022년 6월 15일 (수), 오전 10:43
 */

#ifndef I2C_H
#define	I2C_H


#include "common.h"


void I2CInit(uint16_t freq1);
void I2CStart();
void I2CStop();
void I2CRestart();
void I2CAck();
void I2CNak();
void I2CWait();
void I2CSend(unsigned char dat);
void Read_I2CSend(unsigned char dat);

void I2CInit_2(uint16_t freq2);
void I2CStart_2();
void I2CStop_2();
void I2CRestart_2();
void I2CAck_2();
void I2CNak_2();
void I2CWait_2();
void I2CSend_2(unsigned char dat);
void Read_I2CSend_2(unsigned char dat);


#endif	/* I2C_H */

