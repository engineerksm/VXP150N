/* 
 * File:   pwm.h
 * Author: pc
 *
 * Created on 2022년 6월 17일 (금), 오전 9:17
 */

#ifndef PWM_H
#define	PWM_H

#include "common.h"

#define TMR2Pre 16

void pwmInit_ccp2(unsigned int freq, float duty);
void pwmStart_ccp2();
void pwmStop_ccp2();

void pwmInit_ccp3(unsigned int freq, float duty);
void pwmStart_ccp3();
void pwmStop_ccp3();


#endif	/* PWM_H */

