#include "millis.h"


volatile unsigned long timer0_millis = 0;  // 사용시 extern하여 사용함.

void init_millis()
{
    timer0_millis = 0;
}

millis_t millis()
{
    millis_t ms;
    ms = timer0_millis;
    return ms;
}

millis_t get_millis(millis_t now, millis_t prev_now)
{
    return (now - prev_now);
}

