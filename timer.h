/* 
 * File:   timer.h
 * Author: pc
 *
 * Created on 2022년 6월 14일 (화), 오후 2:43
 */

#ifndef TIMER_H
#define	TIMER_H

#include "common.h"

typedef void (*timer_f)(void);

typedef struct {
    bool start;
    bool tick;
    uint16_t set;
    uint16_t interval;
    timer_f timeProc;
}timer_t;

void timerInit(timer_t *time,uint16_t timeSet,timer_f func);
void timerEventStart(timer_t *time);
void timerProc(timer_t *time);

bool timerGetTick(timer_t *time);
void timerTickClear(timer_t *time,bool start);
void timerInterruptProc(timer_t *time , uint8_t ch_count);


#endif	/* TIMER_H */

