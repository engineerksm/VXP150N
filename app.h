/* 
 * File:   app.h
 * Author: pc
 *
 * Created on 2022년 6월 15일 (수), 오후 3:40
 */

#ifndef APP_H
#define	APP_H

#include "common.h"

void disp_3digit(uint16_t data);
void disp_ADC(uint16_t data);
void disp_kv(uint16_t data);
void disp_ma(uint16_t data);
void disp_ma_result(uint16_t data);

int adcTodac(uint16_t data);

#endif	/* APP_H */

