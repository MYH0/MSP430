#include <msp430g2553.h> 
#include "Clock.h"
#include "GPIO.h"
#include "TimerA.h"

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	BCS_Init(16, 16, 0, 0, 1, 0);
	TA0_Init('A', 1, 1, 12000);
	GPIO_Init();
	_EINT(); 					//¿ª×ÜÖÐ¶Ï
	while (1);
}
