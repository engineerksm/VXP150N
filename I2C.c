/*
 * File:   I2c.c
 * Author: pc
 *
 * Created on 2022년 6월 15일 (수), 오전 10:42
 */


#include "I2C.h"

extern COMMAND cmd;
extern volatile unsigned long timer0_millis = 0;

void I2CInit(uint16_t freq)
{

    SSP1STATbits.SMP = 1;
    SSP1STATbits.CKE = 1;

    SSP1CON1bits.SSPEN = 1;
    SSP1CON1bits.SSPM3 = 1; 
    SSP1CON1bits.SSPM2 = 0;
    SSP1CON1bits.SSPM1 = 0;
    SSP1CON1bits.SSPM0 = 0;

    SSP1CON2 = 0;
    SSP1ADD = (_XTAL_FREQ/(4*freq*1000))-1;
    SSP1STAT = 0;

}

void I2CStart()
{
    I2CWait();
    SSP1CON2bits.SEN = 1;
    //while(SSP2CON2bits.SEN); 
}

void I2CStop()
{
    I2CWait();
    SSP1CON2bits.PEN = 1; 
    //while(SSP2CON2bits.SEN); 
}

void I2CRestart()
{
    I2CWait();
    SSP1CON2bits.RSEN = 1; 
    //while(SSP2CON2bits.RSEN); 
}

void I2CAck()
{
    millis_t now,prev=0;
    init_millis();

    while(SSP1CON2bits.ACKEN)
    {
        now = millis();
        if(get_millis(now,prev) > 10)
        {
            break;
        }
    }
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1; 
}

void I2CNak()
{
    millis_t now,prev=0;
    init_millis();
    
    while(SSP1CON2bits.ACKEN)
    {
        now = millis();
        if(get_millis(now,prev) > 10)
        {
            break;
        }

    }
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
}

void I2CWait(void)
{
    millis_t now,prev=0;
    init_millis();
    
    //PIR1bits.SSP1IF = 0;
    while ( (SSP1CON2 & 0x1F) || ( SSP1STAT & 0x04 ))
    {
        now = millis();
        if(get_millis(now,prev) > 10)
        {
            break;
        }
    }
}

void I2CSend(unsigned char dat)
{
    I2CWait();
    SSP1BUF = dat;
}

unsigned char I2CRead()
{
    unsigned char temp;
    I2CWait(); 
    SSP1CON2bits.RCEN = 1;
    I2CWait(); 
    temp = SSP1BUF; 
    I2CWait(); 
    
    return temp;
}

void I2CInit_2(uint16_t freq)
{

    SSP2STATbits.SMP = 1;
    SSP2STATbits.CKE = 1;

    SSP2CON1bits.SSPEN = 1;
    SSP2CON1bits.SSPM3 = 1; 
    SSP2CON1bits.SSPM2 = 0;
    SSP2CON1bits.SSPM1 = 0;
    SSP2CON1bits.SSPM0 = 0;

    SSP2CON2 = 0;
    SSP2ADD = (_XTAL_FREQ/(4*freq*1000))-1;
    SSP2STAT = 0;
    
}

void I2CStart_2()
{
    I2CWait_2();
    SSP2CON2bits.SEN = 1;
    //while(SSP2CON2bits.SEN); 
}

void I2CStop_2()
{
    I2CWait_2();
    SSP2CON2bits.PEN = 1; 
    //while(SSP2CON2bits.SEN); 
}

void I2CRestart_2()
{
    I2CWait_2();
    SSP2CON2bits.RSEN = 1; 
    //while(SSP2CON2bits.RSEN); 
}

void I2CAck_2()
{
    millis_t now,prev=0;
    init_millis();
    
    while(SSP2CON2bits.ACKEN)
    {
        now = millis();
        if(get_millis(now,prev) > 10)
        {
            break;
        }
    }

    SSP2CON2bits.ACKDT = 0;
    SSP2CON2bits.ACKEN = 1; 
}

void I2CNak_2()
{
    millis_t now,prev=0;
    init_millis();
    
    while(SSP2CON2bits.ACKEN)
    {
        now = millis();
        if(get_millis(now,prev) > 10)
        {
            break;
        }
    }

    SSP2CON2bits.ACKDT = 1;
    SSP2CON2bits.ACKEN = 1;
}

void I2CWait_2(void)
{
    millis_t now,prev=0;
    init_millis();
    
    //PIR1bits.SSP1IF = 0;
    while ( (SSP2CON2 & 0x1F) || ( SSP2STAT & 0x04 ))
    {
        now = millis();
        if(get_millis(now,prev) > 10)
        {
            break;
        }
    }

}

void I2CSend_2(unsigned char dat)
{
    I2CWait_2();
    SSP2BUF = dat;
}

unsigned char I2CRead_2()
{
    unsigned char temp;
    I2CWait_2(); 
    SSP2CON2bits.RCEN = 1;
    I2CWait_2(); 
    temp = SSP2BUF; 
    I2CWait_2(); 
    
    return temp;
}
