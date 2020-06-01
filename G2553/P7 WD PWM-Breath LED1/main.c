#include<msp430g2553.h>
#include"Clock.h"

#include"TimerA.h"
#include"TA_PWM.h"
#include"Watching_Dog.h"
#include"GPIO.h"

void main() 
{
    WD_STOP();	            //关狗

    BCS_Init(16, 16, 1, 1, 1, 2);

    TA0_PWM_Init('A', 1, 7, 0, 50);

    WDTimer_Init();	

    _EINT();

    _bis_SR_register(LPM3_bits);	        //不需要while(1)的地方，进入休眠模式

}

