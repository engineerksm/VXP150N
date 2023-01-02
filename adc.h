/* 
 * File:   adc.h
 * Author: pc
 *
 * Created on 2022년 6월 14일 (화), 오후 2:39
 */

#ifndef ADC_H
#define	ADC_H

#include "common.h"

void adcInit(void);
unsigned int adcRead(unsigned char channel);

#endif	/* ADC_H */

