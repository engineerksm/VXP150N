/* 
 * File:   ap.h
 * Author: pc
 *
 * Created on 2022년 6월 14일 (화), 오후 1:31
 */

#ifndef AP_H
#define	AP_H

void apInit(void);
void apMain(void);

void initPort(void);
void initTimer(void);

millis_t millis();
millis_t get_millis(millis_t now, millis_t prev_now);


#endif	/* AP_H */

