
#include "button.h"

static s_button buttons[BTN_COUNT];

static byte bitCount(byte);

void buttons_init()
{
    // 100 = 1초(10msX100번의 의미)   TimeEvent의 10ms 변경 가능함.
    buttons[BTN_1].pressedTime = 1;   // 1.5초 = 150 
    buttons[BTN_2].pressedTime = 1;
}

#ifdef  debug_button
void buttons_update()
{
	millis_t lastUpdate;

	// Update every 10ms

	millis_t now = millis(&MILLIS);

	if((millis_t)(now - lastUpdate) >= 10)  // 10ms 값 차이가 나면
	{
		lastUpdate = now;					// now는 지난값 저장함.
		processButtons();					// 버튼 처리 시작
	}
}
#endif

void processButtons(void)
{
	  // 버튼의 누름상태를 가져온다.
	bool isPressed[BTN_COUNT];       
	isPressed[BTN_1] = SW_XRAY_ON;
	isPressed[BTN_2] = SW_XRAY_OFF;

	// Process each button
	LOOPR(BTN_COUNT, i)
		processButton(&buttons[i], isPressed[i]);
}

void processButton(s_button* button, bool isPressed)
{
	button->counter <<= 1;
	if(isPressed)
	{
		button->counter |= 1;
		
		//if(bitCount(button->counter) >= BTN_IS_PRESSED)
		{
			
			if(!button->processed)
			{
                if(button->pressedTime <= button->pressCnt)
                {
                    button->processed = true;

                    
                    if(!button->funcDone && button->onPress != NULL && button->onPress() )
                    {
                        button->funcDone = true;
                    }
                    
                }
			}
		
            button->pressCnt ++;
        }
	}
	else // Not pressed
	{
		
		//if(bitCount(button->counter) <= BTN_NOT_PRESSED)
		{
			button->processed = false;
			button->funcDone = false;
            button->pressCnt = 0;
		}
	}	
}


static byte bitCount(byte val)
{
	byte count = 0;
	for(;val;val >>= 1)
		count += val & 1;
	return count;
}

#ifdef  debug_button

{
	button_f old = buttons[btn].onPress;
	buttons[btn].onPress = func;
	return old;
}
#endif

void buttons_setFuncs(button_f btn1, button_f btn2)
{
	buttons[BTN_1].onPress = btn1;
	buttons[BTN_2].onPress = btn2;
}

