#include <msp430g2553.h> 
#include"Clock.h"
#include"GPIO.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	BCS_Init(16, 16, 0, 0, 1, 0);
	GPIO_Init();
	P1OUT |= BIT6;
	P1OUT &= ~BIT0;
	GPIO_Interrupt_Init();
	_EINT();
	while (1);
}
