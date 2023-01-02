/* 
 * File:   config.h
 * Author: pc
 *
 * Created on 2022년 6월 14일 (화), 오후 1:36
 */

#ifndef CONFIG_H
#define	CONFIG_H
 
#pragma config CPD = OFF        // Memory Code Protection
#pragma config BOREN = ON       // Brown-out Reset Enable
#pragma config IESO = OFF       // Internal/External Switchover
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable
#pragma config MCLRE = OFF      // MCLR Pin Function Select
#pragma config WDTE = OFF       // Watchdog Timer Enable
#pragma config  CP = OFF        // Flash Program Memory Code Protection
#pragma config  PWRTE = OFF     // Power-up Timer Enable
#pragma config CLKOUTEN = OFF   // Clock Out Enable
#pragma config PLLEN = ON     // PLL Enable

#define _USE_4MHZ
#define _USE_DAC8


#ifdef _USE_4MHZ

    #pragma config FOSC = INTOSC       // Oscillator Selection
    #define _XTAL_FREQ                  4000000         // 4MHz

    #define CLK_DIV                     0b010           // 1:8
    #define TMR0_DEFINE                 131

#endif

#ifdef _USE_8MHZ

    #pragma config FOSC = INTOSC       // Oscillator Selection
    #define _XTAL_FREQ                  8000000         // 8MHz

    #define CLK_DIV                     0b011           // 1:16
    #define TMR0_DEFINE                 131             // 1ms

#endif

#ifdef _USE_32MHZ
    #pragma config FOSC = INTOSC       // Oscillator Selection
    #define _XTAL_FREQ                  32000000         // 32MHz


    #define TMR1_DEFINE         65435 //65535-500 = 500usec

//////////////// 1ms  //////////////////////////
    #define CLK_DIV                     0b101           // 1:64
    #define TMR0_DEFINE                 131

//////////////// 10uS //////////////////////////
//    #define CLK_DIV                     0b001           // 1:4
//    #define TMR0_DEFINE                 235             // 

//////////////// 100uS //////////////////////////
//    #define CLK_DIV                     0b010           // 1:8
//    #define TMR0_DEFINE                 158             // 
//////////////// 100uS //////////////////////////
//    #define CLK_DIV                     0b011           // 1:16
//    #define TMR0_DEFINE                 207             // 

//    #define TMR0_DEFINE                 32 
// 1ms


    
#endif

#ifdef _USE_DAC12  // 12bit

    #define VOLTAGE_SET_65kV            3169 // 3.25V at 65kv
    #define VOLTAGE_SET_30kV            1462 // 1.5V at 30kV
    #define VOLTAGE_SET_10kV            487 // 0.5V at 10kV

    #define VOLTAGE_SET_70_35kV         3413 // 3.5V at 70kv
    #define VOLTAGE_SET_30k_15kV        1462 // 1.5V at 30kV
    #define VOLTAGE_SET_10kV            487 // 0.5V at 10kV
    #define CURRENT_SET                 3901 // 4V at4mA
    #define CURRENT_SET_0               0 // 
    #define DACOUT_4V                   3901 // 4V
    #define VOLTAGE_SET_25kV            2438 // 2.5 V 25kV

    #define DAC_BIT                     4096

#endif

#ifdef _USE_DAC8   //8BIT

    #define DAC_ref_targetDAC    250    // 4V at 100kV  250
    #define DAC_ref_targetVolt  100     // 4V at 100kV  250

    #define VOLTAGE_SET_0kV                0 // 4V at 100kV
    #define VOLTAGE_SET_30kV               75
    #define nonvolatile_VolTAGE_SET_30kV               37

    #define VOLTAGE_SET_100kV               250 // 4V at 100kV  250
    #define VOLTAGE_SET_95kV                237 // ?V at 95kV 237.5
    #define VOLTAGE_SET_90kV                225 // V at 90kV  225
    #define VOLTAGE_SET_85kV                212 // V at 85kV  212.5
    #define VOLTAGE_SET_80kV                200 // V at 80kV  200
    #define VOLTAGE_SET_75kV                187 // V at 75kV  187.5
    #define VOLTAGE_SET_70kV                175 // V at 70kV  175

    #define SHOT_LED_OFF                0
    #define SHOT_LED_ON                 254
    #define SHOT_LED_HALF_ON            76      // 1.5V

    #define DAC_BIT                     256

#endif

#define UNUSED(var) ((void)(var))
#define EMPTY_FUNC	((void)(0))

#define noinline __attribute__ ((__noinline__))

#define delay(ms) __delay_ms(ms)
#define delay_us(us) __delay_us(us)

// Quick and easy macro for a for loop
#define LOOP(count, var) for(byte var=0;var<count;var++)

// Reverse loop sometimes produces smaller/faster code
#define LOOPR(count, var) for(byte var=count;var--;)

#define CONCAT(a, b) a ## b

#define bit_set_concat(reg, reg2, bit)		(CONCAT(reg, reg2) |= _BV(bit))
#define bit_clr_concat(reg, reg2, bit)		(CONCAT(reg, reg2) &= ~_BV(bit))
#define bit_tog_concat(reg, reg2, bit)		(CONCAT(reg, reg2) ^= _BV(bit))
#define bit_is_set_concat(reg, reg2, bit)	(bit_is_set(CONCAT(reg, reg2), bit))

/* 한 비트 클리어 */
#define clear_bit(data, loc)    ((data) &= ~(0x1 << (loc)))
#define clear_data(data, loc)    ((data) &= ~(0x1 << (loc)))

/* 연속된 여러 비트 클리어 */
#define clear_bits(data, area, loc)     ((data) &= ~((area) << (loc)))
  
/* 한 비트 설정 */
#define set_bit(data, loc)      ((data) |= (0x1 << (loc)))
#define set_data(data, loc)      ((data) |= (0x1 << (loc)))

/* 연속된 여러 비트 설정 */
#define set_bits(data, area, loc)  ((data) |= ((area) << (loc)))
  
/* 한 비트 반전 */
#define invert_bit(data, loc)   ((data) ^= (0x1 << (loc)))
/* 연속된 여러 비트 반전 */
#define invert_bits(data, area, loc)    ((data) ^= ((area) << (loc)))
  
/* 비트 검사 */
#define check_bit(data, loc)    ((data) & (0x1 << (loc)))
  
/* 비트 추출 */
#define extract_bits(data, area, loc)   (((data) >> (loc)) & (area))

#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

typedef unsigned long millis_t;

typedef uint8_t byte;
typedef uint16_t uint;
typedef uint32_t ulong;

#define START                       1
#define STOP                        0

#define TRUE                        1           // bool
#define FALSE                       0

#define HIGH                        1
#define LOW                         0

#define ON                          1
#define OFF                         0


#endif	/* CONFIG_H */

