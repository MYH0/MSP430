#include"MSP430G2553.h"
#include"Clock.h"
#include"TimerA.h"
#include"TA_PWM.h"
#include"GPIO.h"

void main() 
{
	WDTCTL = WDTPW + WDTHOLD;	            //关狗
    BCS_Init(16, 16, 0, 0, 1, 0);

    GPIO_Init();	

    _bis_SR_register(LPM3_bits);	        //不需要while(1)的地方，进入休眠模式		
}
