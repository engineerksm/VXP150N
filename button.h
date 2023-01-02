/* 
 * File:   button.h
 * Author: pc
 *
 * Created on 2022년 6월 16일 (목), 오전 11:34
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "common.h"

typedef enum
{
	BTN_1 = 0,
	BTN_2 = 1,
	BTN_COUNT = 2 // must be last
} btn_t;

enum {NETURAL, CW, CCW};

#define BTN_IS_PRESSED	1
#define BTN_NOT_PRESSED	1

typedef bool(*button_f)(void);

typedef struct {
	unsigned int pressedTime;	// 누름시간
    unsigned int pressCnt;
	bool processed;			// 누른시간 저장(다음 누르기 전까지 실행안함) 
	byte counter;			// 디바우스 카운터
	bool funcDone;			// 함수가 실행 (다음 누르기 전까지 실행안함)
	button_f onPress;		// 누를때 함수 실행
}s_button;


void processButtons(void);
void processButton(s_button* button, bool isPressed);

void buttons_init(void);
void buttons_update(void);
void buttons_startup(void);


void buttons_shutdown(void);
button_f buttons_setFunc(btn_t, button_f);
void buttons_setFuncs(button_f btn1, button_f btn2);
millis_t buttons_pressTime(btn_t);
bool buttons_isActive(void);
void buttons_wake(void);

#endif	/* BUTTON_H */

