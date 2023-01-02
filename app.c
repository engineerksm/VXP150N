/*
 * File:   app.c
 * Author: pc
 *
 * Created on 2022년 6월 15일 (수), 오후 3:40
 */

#include "app.h"

extern COMMAND cmd;

void disp_3digit(uint16_t data)
{
    I2C_AS1115_Write(DIGIT3,(data/100)%10);
    I2C_AS1115_Write(DIGIT4,(data/10)%10);
    I2C_AS1115_Write(DIGIT5,data%10);
}

void disp_ADC(uint16_t data)
{
    float temp;
    uint16_t temp2;

    temp = (float)(data*5)/1024;
    temp2 = (uint16_t)(temp*100);
    
    I2C_AS1115_Write(DIGIT0,(temp2/100)%10 | AS1115_DOT);
    I2C_AS1115_Write(DIGIT1,(temp2/10)%10 );
    I2C_AS1115_Write(DIGIT2,temp2%10);
}

void disp_ma(uint16_t data)
{
    float temp;
    uint16_t temp2;
    temp = (float)(data*10)/1024;
    temp2 = (uint16_t)(temp*10);
    I2C_AS1115_Write(DIGIT3,(temp2/100)%10);
    I2C_AS1115_Write(DIGIT4,(temp2/10)%10 | AS1115_DOT);
    I2C_AS1115_Write(DIGIT5,temp2%10);
}

void disp_ma_result(uint16_t data)
{
    float temp;
    uint16_t temp2=0;

    temp = (float)(data*10)/811;        // 4V ref.
    temp2 = (uint16_t)(temp*10);
    // if(temp2>100) temp2=100;    // 100mA Limit
    
    I2C_AS1115_Write(DIGIT3,(temp2/100)%10);
    I2C_AS1115_Write(DIGIT4,(temp2/10)%10 | AS1115_DOT);
    I2C_AS1115_Write(DIGIT5,temp2%10);
    
}

void disp_kv(uint16_t data)
{
    float temp;
    uint16_t temp2=0;
    
    temp = (float)(data*15)/811;       // 5V ref --> 4V ref by ksm, 0102
    
    if(temp < 10)
    {
        temp2 = (uint16_t)(temp*100); 
        I2C_AS1115_Write(DIGIT0,(temp2/100)%10 );
        I2C_AS1115_Write(DIGIT1,(temp2/10)%10 | AS1115_DOT);
        I2C_AS1115_Write(DIGIT2,temp2%10);
    }else
    {
        temp2 = (uint16_t)(temp*10);    
        // if(temp2>150)   temp2 = 150;    // 150kV Limit
        I2C_AS1115_Write(DIGIT0,(temp2/100)%10);
        I2C_AS1115_Write(DIGIT1,(temp2/10)%10 | !AS1115_DOT);
        I2C_AS1115_Write(DIGIT2,temp2%10);
    }
    
}

int adcTodac(uint16_t data)
{
    long double temp;
    
//    temp = ((((data*5)/1023) - 0.8) * 4096)/4.2;
    temp = data * 3.8;
    //temp = ((((float)(data*5)/1023) - 1 ) * 3900) / 4.0;
    
    return (int)temp;
}
