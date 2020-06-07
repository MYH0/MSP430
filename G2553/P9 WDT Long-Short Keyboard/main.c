#include<msp430g2553.h>
#include"Clock.h"
#include"GPIO.h"
#include"Watching_Dog.h"


void main() 
{
    WDT_STOP();	            //�ع�

    BCS_Init(16, 16, 1, 1, 1, 2);

    GPIO_Init();

    WDTimer_Init();

    _EINT();

    _bis_SR_register(LPM3_bits);	        //����Ҫwhile(1)�ĵط�����������ģʽ

}

