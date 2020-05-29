#include"MSP430G2553.h"
#include"Clock.h"
#include"TimerA.h"
#include"TA_PWM.h"
#include"GPIO.h"

void main() 
{
	WDTCTL = WDTPW + WDTHOLD;	            //�ع�
    BCS_Init(16, 16, 0, 0, 1, 0);
    TA0_PWM_Init('A', 1, 7, 0, 500);
    GPIO_Init();											
    GPIO_Interrupt_Init();
    _EINT();							
    _bis_SR_register(LPM3_bits);	        //����Ҫwhile(1)�ĵط�����������ģʽ		
}
