
#include "common.h"

timer_t Timer[TIMER_COUNT];
COMMAND cmd;

extern volatile unsigned long timer0_millis;

bool event_btn_Expose()
{
    bool ret = TRUE;
    
    uint16_t temp;
    
    //temp = 2000;
    
    if(!cmd.f_XRAY_ON)
    {
        temp = adcTodac(cmd.v_adc_kV_Adj);
        I2C_DAC_Write(Volatile_DAC0_Register, &temp);  // voltage set
        pwmInit_ccp3(1000, 50);  // 380kV pwm
        pwmStart_ccp3();

        cmd.c_anodeCurrent_cnt = 5;
        pwmInit_ccp2(1000, 0);  // mA pwm
        pwmStart_ccp2();
        timerEventStart(&Timer[e_anodeCurrent]);

        //temp = adcTodac(cmd.v_adc_mA_Adj);
        //I2C_DAC_Write(Volatile_DAC1_Register, &temp);  // mA set

        LED_XRAY_ON  = ON;
        LED_XRAY_OFF = OFF;

        KV_EN = LOW;
        GATE_EN = LOW;

        cmd.f_XRAY_ON = ON;
        
    }
    
    return  ret;
}


bool event_btn_Stop()
{
    bool ret = TRUE;

    uint16_t temp;
    
    KV_EN = HIGH;
    GATE_EN = HIGH;
    
    temp = 0;
    I2C_DAC_Write(Volatile_DAC0_Register,&temp);  // voltage set
    pwmStop_ccp3();

    pwmStop_ccp2();
    timerTickClear(&Timer[e_anodeCurrent],STOP);
    
    LED_XRAY_ON  = OFF;
    LED_XRAY_OFF = ON;
    
    cmd.f_XRAY_ON = OFF;
    
    return  ret;
}

//////// 버튼 처리 타이머 /////////////
void event_timer_Button()           // 각종 버튼 채터링 타이머
{
    if(timerGetTick(&Timer[e_button]))
    {
        timerTickClear(&Timer[e_button],TRUE);
        
        processButtons();   // 버튼처리
    }
}

void event_expose()   //  /KV_EN, /GATE_EN
{
    if(timerGetTick(&Timer[e_expose]))
    {
        timerTickClear(&Timer[e_expose],TRUE);
    }
}

void event_display()   // AS1115 display
{
    if(timerGetTick(&Timer[e_display]))
    {
        timerTickClear(&Timer[e_display],TRUE);

        I2C_AS1115_Write(SHUTDOWN,NORMAL_OPERATION);
        I2C_AS1115_Write(GLOBAL_INTENSITY,7);
        I2C_AS1115_Write(DECODE_MODE,0x3F);
        I2C_AS1115_Write(SCAN_LIMIT,0x05);   
        
        if(cmd.f_XRAY_ON)
        {
            cmd.v_adc_kV = adcRead(3);
            cmd.v_adc_mA = adcRead(4);
            disp_kv(cmd.v_adc_kV);
            disp_ma_result(cmd.v_adc_mA);
            
            if(cmd.v_adc_mA > cmd.f_anodeCurrent_serch)
            { 
                timerTickClear(&Timer[e_anodeCurrent],STOP);
            }
            
            if(cmd.v_adc_mA > (cmd.v_adc_mA_Adj) + 20 || cmd.v_adc_mA < (cmd.v_adc_mA_Adj) - 20)
            {
                timerEventStart(&Timer[e_anodeCurrent]);
                cmd.f_anodeCurrent_serch = true;
            }
            
        }else
        {
            cmd.v_adc_kV_Adj = adcRead(2);
            cmd.v_adc_mA_Adj = adcRead(1);
            
            // if(cmd.v_adc_mA_Adj > 205) cmd.v_adc_mA_Adj -= 205;
            // else cmd.v_adc_mA_Adj = 0;

            disp_kv(cmd.v_adc_kV_Adj);
            disp_ma_result(cmd.v_adc_mA_Adj);
            cmd.f_anodeCurrent_serch = false;
        }
        
        //disp_ADC(adcRead(4));

    }
}

void event_rst()        // Reset
{
    if(timerGetTick(&Timer[e_rst]))
    {
        timerTickClear(&Timer[e_rst],STOP);
        
        RESET = HIGH;

    }
    
}

void event_anodeCurrent()        // Reset
{
    if(timerGetTick(&Timer[e_anodeCurrent]))
    {
        timerTickClear(&Timer[e_anodeCurrent],START);
        
        if(cmd.f_anodeCurrent_serch)
        {
            if(cmd.v_adc_mA > cmd.v_adc_mA_Adj + 10)
            {
                cmd.c_anodeCurrent_cnt -= 0.1;
            }if(cmd.v_adc_mA < cmd.v_adc_mA_Adj - 10)
            {
                cmd.c_anodeCurrent_cnt += 0.1;
            }
        }else{
            cmd.c_anodeCurrent_cnt +=0.1;
        }
       
        if(cmd.c_anodeCurrent_cnt > 95)
        {
            cmd.c_anodeCurrent_cnt = 95;
        }if(cmd.c_anodeCurrent_cnt < 5)
        {
            cmd.c_anodeCurrent_cnt = 5;
        }
        
        pwmInit_ccp2(1000,cmd.c_anodeCurrent_cnt);
        
    }
    
}

void apInit(void)
{
    initPort();
    adcInit();
    initTimer();
    I2CInit(500);
    I2CInit_2(400);
    
    ei();
    
    WDTCONbits.SWDTEN = 0b01;  // watchDog 타이머 enable
    
    timerInit(&Timer[e_button],10,event_timer_Button);                 // time 초기화(Time_t 사용변수, 시간(ms), 이벤트함수)
    timerInit(&Timer[e_expose],1000,event_expose);                     // time 초기화(Time_t 사용변수, 시간(ms), 이벤트함수)
    timerInit(&Timer[e_display],200,event_display);                    // time 초기화(Time_t 사용변수, 시간(ms), 이벤트함수)
    timerInit(&Timer[e_rst],500,event_rst);                            // time 초기화(Time_t 사용변수, 시간(ms), 이벤트함수)
    timerInit(&Timer[e_anodeCurrent],10,event_anodeCurrent);           // time 초기화(Time_t 사용변수, 시간(ms), 이벤트함수)
    
    timerEventStart(&Timer[e_button]);      // 버튼 처리 타이머 시작
    timerEventStart(&Timer[e_expose]);
    timerEventStart(&Timer[e_display]);
    timerEventStart(&Timer[e_rst]);

    buttons_init(); // button 누름 시간 초기화 내부에 설정할수 있음.
    buttons_setFuncs(event_btn_Expose,event_btn_Stop); // 버튼 콜백함수 등록

    I2C_AS1115_Write(SHUTDOWN,NORMAL_OPERATION);
    I2C_AS1115_Write(GLOBAL_INTENSITY,7);
    I2C_AS1115_Write(DECODE_MODE,0x3F);
    I2C_AS1115_Write(SCAN_LIMIT,0x05);
    
    uint16_t D_temp;

    D_temp = 0x000F;
    //I2C_DAC_Write(unsigned char address, int* data)
    I2C_DAC_Write(VREF_Register,&D_temp);  // Vref pin buffed enable

    D_temp = 2048;
    I2C_DAC_Write(Nonvolatile_DAC0_Register,&D_temp);  // voltage set   
    I2C_DAC_Write(Volatile_DAC0_Register,&D_temp);  // voltage set   

    I2C_DAC_Write(Nonvolatile_DAC1_Register,&D_temp);  // 
    I2C_DAC_Write(Volatile_DAC1_Register,&D_temp);  // 
    
    event_btn_Stop();
    
//    pwmInit_ccp2(1000,50);
//    pwmStart_ccp2();

    //pwmInit_ccp3(1000,50);
    //pwmStart_ccp3();
    
    
}

void apMain(void)
{
//    millis_t now,prev;
    
    while(1)
    {
        timerProc(&Timer[e_button]);            // 버튼 time processor 함수 콜
        timerProc(&Timer[e_expose]);            //expose 함수 콜
        timerProc(&Timer[e_display]);           //display 함수 콜
        timerProc(&Timer[e_rst]);               //reset 함수 콜
        timerProc(&Timer[e_anodeCurrent]);      //anode current 함수 콜

//        if(SW_XRAY_ON)
//        {
//            cmd.f_XRAY_ON = ON;
//            event_btn_Expose();
//        } 
//            
//        if(SW_XRAY_OFF)
//        {
//            cmd.f_XRAY_ON = OFF;
//            event_btn_Stop();
//        }

        
//        now = millis();
//        
//        if(get_millis(now,prev) > 1000)
//        {
//            disp_3digit(cmd.v_cnt++);
//            init_millis();
//            prev = 0;
//        }
        
        CLRWDT();
//        
//        if(SW_XRAY_OFF) LATD |= 0x08;
//        else clear_bit(LATD, 3);
        
    }
}

void initPort(void)
{

#ifdef _USE_4MHZ
    OSCCONbits.SCS = 0b00;
    OSCCONbits.IRCF = 0b1101;   // 4Mhz
#endif

#ifdef _USE_8MHZ
    OSCCONbits.SPLLEN = 0;
    OSCCONbits.SCS = 0b10;
    OSCCONbits.IRCF = 0b1110;  // 8 or 32 Mhz   datasheet page 74
#endif
    
#ifdef _USE_32MHZ
    OSCCONbits.SCS = 0b00;
    OSCCONbits.IRCF = 0b1110;  // 8 or 32 Mhz   datasheet page 74
#endif

//    WPUEN: Weak Pull-Up Enable bit
//    1 = All weak pull-ups are disabled (except MCLR, if it is enabled)
//    0 = Weak pull-ups are enab led by individual WPUx latch values    
    OPTION_REGbits.nWPUEN = 0;    
    
    // input : 1
    // output : 0    
    
    
    PORTA = 0x00;
    LATA = 0x00;
    ANSELA = 0b00111110;
    TRISA =  0b11111111;
    
    PORTB = 0x00;
    LATB = 0x00;
    WPUB = 0b10000100;
//    TRISB = 0x27;
    TRISB = 0b10101110;           // PGD포트 Remote 사용

    PORTC = 0x00;
    LATC = 0x03;                  // KV_EN(RC0),GATE_EN(RC1) HIGH 초기화.
    TRISC = 0b11111000;           // i2C RC3, RC4 in used
    
    PORTD = 0x00;
    LATD = 0x00;
    TRISD = 0b011100100;
    
    PORTE = 0x00;
    LATE = 0x00;
    ANSELE = 0x00;
    TRISE = 0b01110000;
    
    PORTF = 0x00;
    LATF = 0x00;             
    ANSELF = 0x00;
    TRISF = 0b10000011;
    
    PORTG = 0x00;
    LATG = 0x00;
    TRISG = 0b00011100;
    ANSELG = 0;
    WPUG = 0;
   
    //ADCON0bits.ADON = 0;   
 
}

void initTimer(void)
{
    
    OPTION_REGbits.TMR0CS = 0;
    OPTION_REGbits.TMR0SE = 0;
    OPTION_REGbits.PSA = 0;
    
    OPTION_REGbits.PS = CLK_DIV;     
    TMR0 = TMR0_DEFINE;

#ifdef Timer1
    T1CONbits.TMR1CS = 0b00; // 00 = Timer1 clock source is instruction clock (FOSC/4)
    T1CONbits.T1CKPS = 0b11; // 11 = 1:8 Prescale value
    T1CONbits.nT1SYNC = 1;
    
    TMR1H = (uint8_t)((TMR1_DEFINE >> 8) & 0x00FF);
    TMR1L = (uint8_t)(TMR1_DEFINE & 0x00FF);
    
    T1CONbits.TMR1ON = 1; // 1 = Enable
    PIE1bits.TMR1IE  = 1;
#endif
    
#ifdef Timer2  
    //TMR2 = 0;
    //PR2 = 255;
    //T2CONbits.T2OUTPS = 0x00;
    //T2CONbits.T2CKPS = 0x00;
    //T2CONbits.TMR2ON = TRUE;
    
    //PIE1bits.TMR2IE = 1;
    //PIR1bits.TMR2IF = 0;
#endif
    
    //INTCONbits.GIE = 1;
    //INTCONbits.PEIE = 1;
    
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;

}

void interrupt isr()
{
    
    if(PIR4bits.RC2IF)
    {
//        uart1queue.head % = BUFFER_SIZE;
//        uart1queue.data[uart1queue.head ++] = RC2REG;
    }
    
    if (INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        TMR0 = TMR0_DEFINE;     // 1ms
        timer0_millis ++;        
   
        timerInterruptProc(Timer, TIMER_COUNT);
    }

#ifdef Timer1    
    if (PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        
        TMR1H = (uint8_t)((TMR1_DEFINE >> 8) & 0x00FF);
        TMR1L = (uint8_t)(TMR1_DEFINE & 0x00FF);
              
    }  
#endif

#ifdef Timer2    
    if(PIR1bits.TMR2IF)
    {
       PIR1bits.TMR2IF = 0;
       
        //LATE ^= 0x80;
    }
#endif
    
}