
#include "adc.h"

void adcInit(void)
{
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADNREF = 0;
    ADCON1bits.ADPREF = 0b00;
    
    ADCON1bits.ADCS = 0b110;

    ADCON0bits.ADON = 0;
}

unsigned int adcRead(uint8_t channel)
{
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADCS0 = 1;
    ADCON1bits.ADCS1 = 1;
    ADCON1bits.ADCS2 = 0;
    ADCON0bits.CHS = channel;        //Setting channel selection bits
    ADCON0bits.ADON = 1;
    __delay_ms(1);               //Acquisition time to charge hold capacitor
    ADCON0bits.GO_nDONE = 1;         //Initializes A/D conversion
    while(ADCON0bits.GO_nDONE);      //Waiting for conversion to complete

    return ((ADRESH<<8)+ADRESL); //Return result    
}