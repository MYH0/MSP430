#include <msp430g2553.h> 
#include"Clock.h"
#include"GPIO.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	BCS_Init(16, 16, 0, 0, 1, 0);
	GPIO_Init();
	GPIO_Interrupt_Init();
	_EINT();
	while (1);
}
