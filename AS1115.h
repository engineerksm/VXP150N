/* 
 * File:   AS1115.h
 * Author: pc
 *
 * Created on 2022년 6월 15일 (수), 오전 10:49
 */

#ifndef AS1115_H
#define	AS1115_H

#include "I2C.h"

#define AS1115_ADR      0x00
#define AS1115_DOT		0x80
#define AS1115_BLANK	0x00

/**
 * Digits registers.
 */
enum AS1115_DIGIT
{
	DIGIT0	= 0x01,
	DIGIT1	= 0x02,
	DIGIT2	= 0x03,
	DIGIT3	= 0x04,
	DIGIT4	= 0x05,
	DIGIT5	= 0x06,
	DIGIT6	= 0x07,
	DIGIT7	= 0x08
};

/**
 * Registers addresses.
 * See "Digits- and control-Registers".
 */
enum AS1115_REGISTER
{
	DECODE_MODE			= 0x09,	///< Sets the decode mode (BCD or HEX).
	GLOBAL_INTENSITY	= 0x0A, ///< Sets the entire display intensity.
	SCAN_LIMIT			= 0x0B,	///< Controls how many digits are to be displayed.
	SHUTDOWN			= 0x0C,	///<
	SELF_ADDRESSING		= 0x2D,	///< Uses 2 of the 16 keys to change the device's address.
	FEATURE				= 0x0E,	///< Enables various features such as clock mode and blinking.
	DISPLAY_TEST_MODE	= 0x0F,	///< Detects open or shorted LEDs.
	DIG01_INTENSITY		= 0x10,	///< Sets the display intensity for digit 0 and 1.
	DIG23_INTENSITY		= 0x11, ///< Sets the display intensity for digit 2 and 3.
	DIG45_INTENSITY		= 0x12, ///< Sets the display intensity for digit 4 and 5.
	DIG67_INTENSITY		= 0x13, ///< Sets the display intensity for digit 6 and 7.
	DIAG_DIGIT0			= 0x14, ///< Gets the results of the LEDS open/short test for digit 0.
	DIAG_DIGIT1			= 0x15,	///< Gets the results of the LEDS open/short test for digit 1.
	DIAG_DIGIT2			= 0x16,	///< Gets the results of the LEDS open/short test for digit 2.
	DIAG_DIGIT3			= 0x17,	///< Gets the results of the LEDS open/short test for digit 3.
	DIAG_DIGIT4			= 0x18,	///< Gets the results of the LEDS open/short test for digit 4.
	DIAG_DIGIT5			= 0x19,	///< Gets the results of the LEDS open/short test for digit 5.
	DIAG_DIGIT6			= 0x1A,	///< Gets the results of the LEDS open/short test for digit 6.
	DIAG_DIGIT7			= 0x1B,	///< Gets the results of the LEDS open/short test for digit 7.
	KEY_A				= 0x1C,	///< Gets the result of the debounced keyscan for KEYA.
	KEY_B				= 0x1D	///< Gets the result of the debounced keyscan for KEYB.
};

/**
 * SHUTDOWN register flags.
 */
enum AS1115_SHUTDOWN_MODE
{
	SHUTDOWN_MODE		= 0x00,	///< Shutdown and reset FEATURE register to default settings.
	NORMAL_OPERATION	= 0x01,	///< Resume operation and reset FEATURE register to default settings.
	RESET_FEATURE		= 0x00,	///< FEATURE register is resetted to default settings.
	PRESERVE_FEATURE	= 0x80	///< FEATURE register is unchanged.
};

enum AS1115_DECODE_SEL
{
	CODE_B_DECODING		= 0x00,
	HEX_DECODING		= 0x01
};

/**
 * FEATURE register bits.
 */
enum AS1115_FEATURE
{
	CLOCK_ACTIVE		= 0,	///< Enables the external clock.
	RESET_ALL			= 1, 	///< Resets all control register except the FEATURE register.
	DECODE_SEL			= 2, 	///< Enable Code-B or HEX decoding for the selected digits.
	BLINK_ENABLE		= 4,	///< Enables blinking.
	BLINK_FREQ_SEL		= 5,	///< Sets the blinking frequency.
	SYNC				= 6,	///< Synchronize blinking with LD/CS pin.
	BLINK_START			= 7		///< Sets wether to start the blinking with the display turned on or off.
};

/**
 * DISPLAY_TEST_MODE register bits.
 */
enum AS1115_DISPLAY_TEST_MODE
{
	DISP_TEST	= 0,	///< Optical display test.
	LED_SHORT	= 1,	///< Starts a test for shorted LEDs.
	LED_OPEN	= 2,	///< Starts a test for open LEDs.
	LED_TEST	= 3,	///< Indicates an ongoing open/short LED test.
	LED_GLOBAL	= 4,	///< Indicates that the last open/short LED test has detected an error.
	RSET_OPEN	= 5,	///< Checks if external resistor Rset is open.
	RSET_SHORT	= 6		///< Checks if external resistor Rset is shorted.
};

void I2C_AS1115_Write(unsigned char cmd,unsigned char data);

#endif	/* AS1115_H */

