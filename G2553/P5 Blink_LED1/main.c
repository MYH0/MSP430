#include <msp430g2553.h>
#include"Clock.h"
#include"Watching_Dog.h"
#include"GPIO.h"


void main()
{
    BCS_Init(16, 16, 1, 1, 1, 1);

    WDTimer_Init();
    
    GPIO_Init();

    _EINT();

    _bis_SR_register(LPM3_bits);	        //����Ҫwhile(1)�ĵط�����������ģʽ	

}

