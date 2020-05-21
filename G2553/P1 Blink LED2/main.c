#include <msp430g2553.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT6;
	while (1)
	{
		int i=0;
		P1OUT |= BIT6;
		for(i=10000;i>0;i--);
		P1OUT &= ~BIT6;
		for(i=10000;i>0;i--);
	}
}
