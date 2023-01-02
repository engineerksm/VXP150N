#include "pwm.h"

void pwmInit_ccp2(unsigned int freq, float duty)
{
    unsigned int ccpr1l_ccp1con;

    //T2CONbits.T2CKPS = 0b10;
    //T2CONbits.T2OUTPS = 0b0000;
    //T2CONbits.TMR2ON = 1;

    //T1CONbits.T1CKPS = 0b00;
    //T1CONbits.TMR1ON = 1;
    //PR2 = 255;
    CCP2CONbits.P2M = 0b00;     // Single output; P1A modulated; P1B, P1C, P1D assigned as port pins
    CCP2CONbits.CCP2M = 0b1100; // PWM mode; P1A, P1C active-high; P1B, P1D active-high
    CCPTMRS0bits.C2TSEL = 0b00;

    PIR1bits.TMR2IF = 1;
   // PIE1bits.TMR2IE = 1;
    
    APFCONbits.CCP2SEL = 1;

    
    
#ifdef _USE_DEBUG
    sprintf(uart1queue.txBuff,"freq: %d  duty: %f \n",freq,duty);
    Put_Str_UART(_DEF_UART1,uart1queue.txBuff, 50); 
#endif    
    
    PR2 = (_XTAL_FREQ / (4*freq*TMR2Pre)) - 1;
#ifdef _USE_DEBUG    
    sprintf(uart1queue.txBuff,"PR2: %d \n",PR2);
    Put_Str_UART(_DEF_UART1,uart1queue.txBuff, 50); 
#endif    
    ccpr1l_ccp1con =(4*(PR2+1))*((float)duty/100); // On reducing //duty = (((float)duty/1023)*(1/PWM_freq)) / ((1/_XTAL_FREQ) * TMR2PRESCALE);    
    
#ifdef _USE_DEBUG    
    sprintf(uart1queue.txBuff,"CCP : %d \n",ccpr1l_ccp1con);
    Put_Str_UART(_DEF_UART1,uart1queue.txBuff, 50); 
#endif
    
    CCPR2L = (ccpr1l_ccp1con ) >> 2;
    CCP2CONbits.DC2B0 = ccpr1l_ccp1con & 0x0001;
    CCP2CONbits.DC2B1 = ccpr1l_ccp1con & 0x0010;
}

void pwmStart_ccp2()
{
    CCP2CONbits.CCP2M = 0b1100;         // PWM mode; P1A, P1C active-high; P1B, P1D active-high

    T2CONbits.T2CKPS = 0b10;        // 분주
    T2CONbits.T2OUTPS = 0b0000;
    T2CONbits.TMR2ON = 1;
}

void pwmStop_ccp2()
{
    CCP2CONbits.CCP2M = 0;         // PWM mode; P1A, P1C active-high; P1B, P1D active-high
    T2CONbits.TMR2ON = 0;
}

void pwmInit_ccp3(unsigned int freq, float duty)
{
    unsigned int ccpr3l_ccp3con;
        
    // CCP3  
    CCP3CONbits.CCP3M3 = 1;
    CCP3CONbits.CCP3M2 = 1;
    CCP3CONbits.CCP3M1 = 0;
    CCP3CONbits.CCP3M0 = 0;
    
    CCP3CONbits.P3M1 = 0;
    CCP3CONbits.P3M0 = 0;
    
    CCPTMRS0bits.C3TSEL = 0b01;

    
    PR4 = (_XTAL_FREQ / (4*freq*TMR2Pre)) - 1;
    ccpr3l_ccp3con =(4*(PR4+1))*((float)duty/100); // On reducing //duty = (((float)duty/1023)*(1/PWM_freq)) / ((1/_XTAL_FREQ) * TMR2PRESCALE);
    
    CCPR3L = (ccpr3l_ccp3con ) >> 2;
    CCP3CONbits.DC3B0 = ccpr3l_ccp3con & 0x0001;
    CCP3CONbits.DC3B1 = ccpr3l_ccp3con & 0x0010;
    
}

void pwmStart_ccp3()
{

    CCP3CONbits.CCP3M3 = 1;
    CCP3CONbits.CCP3M2 = 1;
    CCP3CONbits.CCP3M1 = 0;
    CCP3CONbits.CCP3M0 = 0;    
    
    T4CONbits.T4CKPS = 0b10;        // 분주
    T4CONbits.T4OUTPS = 0b0000;
    T4CONbits.TMR4ON = 1;
}

void pwmStop_ccp3()
{
    CCP3CONbits.CCP3M3 = 0;
    CCP3CONbits.CCP3M2 = 0;
    CCP3CONbits.CCP3M1 = 0;
    CCP3CONbits.CCP3M0 = 0;

    T4CONbits.TMR4ON = 0;
}