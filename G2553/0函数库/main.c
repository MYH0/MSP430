#include"MSP430G2553.h"
#include"Clock.h"

#include"GPIO.h"

void main() 
{
	WDTCTL = WDTPW + WDTHOLD;	            //�ع�

    BCS_Init(16, 16, 1, 1, 1, 1);

    GPIO_Init();	

    _bis_SR_register(LPM3_bits);	        //����Ҫwhile(1)�ĵط�����������ģʽ

}

