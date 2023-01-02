/*
 * File:   timer.c
 * Author: pc
 *
 * Created on 2022년 6월 14일 (화), 오후 2:44
 */

#include "timer.h"

void timerInit(timer_t *time,uint16_t timeSet,timer_f func)  // 사용할 타이머를 초기화 한다.
{
    time->start = FALSE;
    time->tick = FALSE;
    time->set = timeSet;
    time->interval = 0;
    time->timeProc = func;
}

void timerProc(timer_t *time)
{
    time->timeProc();
}

void timerEventStart(timer_t *time)
{
    time->start = TRUE;
}

bool timerGetTick(timer_t *time)
{
    return time->tick;
}

void timerTickClear(timer_t *time,bool start)
{
    time->start = start;
    time->tick = FALSE;
    time->interval = 0;
}

void timerInterruptProc(timer_t *time , uint8_t ch_count)
{
    for(uint8_t i=0; i < ch_count; i++)
    {
        if((time+i)->start)
        {
            if((time+i)->interval < (time+i)->set)
            {
                ++ (time+i)->interval;
            }
            else
            {
                (time+i)->interval = 0;
                (time+i)->tick = TRUE;
            }
        }        
    }
}
