/* 
 * File:   common.h
 * Author: pc
 *
 * Created on 2022년 6월 14일 (화), 오후 1:28
 */

#ifndef COMMON_H
#define	COMMON_H

#include <xc.h>  
#include <pic16f1947.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <eeprom_routines.h>
#include <limits.h>

#include "config.h"

#include "ap.h"
#include "adc.h"
#include "timer.h"
#include "millis.h"
#include "I2C.h"
#include "pwm.h"
#include "app.h"
#include "button.h"
#include "AS1115.h"
#include "MCP47FEB2X.h"

#define TIMER_COUNT         6   // *필수사항* 타이머 등록 개수

typedef enum
{
    e_button = 1,
    e_expose,
    e_rst,
    e_anodeCurrent,
    e_display 
} timer_ch_t;



// 접두사  v_: value
//         s_: status
//         f_: flag
//         c_: count

typedef struct
{
    uint16_t v_cnt;
    
    uint16_t v_adc_mA_Adj;
    uint16_t v_adc_kV_Adj;
    
    uint16_t v_adc_kV;
    uint16_t v_adc_mA;
    
    uint8_t v_adcTomA_set;
    uint8_t v_adcTokV_set;
    
    uint8_t f_XRAY_ON;
    
    float c_anodeCurrent_cnt;
    uint8_t f_anodeCurrent_serch;
    
    
}COMMAND;

// input
#define SW_XRAY_ON       PORTFbits.RF1
#define SW_XRAY_OFF       PORTFbits.RF0


// output
#define KV_EN           LATCbits.LATC0
#define GATE_EN         LATCbits.LATC1

#define RESET           LATBbits.LATB4
#define BUZZER          LATDbits.LATD0
#define LED_XRAY_ON     LATDbits.LATD3
#define LED_XRAY_OFF    LATEbits.LATE3


#endif	/* COMMON_H */

