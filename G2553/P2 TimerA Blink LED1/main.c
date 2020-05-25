#include <msp430g2553.h> 
#include"Clock.h"
#include"GPIO.h"
#include"TimerA.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	BCS_Init(16, 16, 0, 0, 1, 0);	//int dco_x0,int mclk_a0,int divm_b0,int divs_c0,int aclk_d0,int diva_e0
	TimerA_Init(12000, 1, 1, 0);	//int time_long,int ta_clk0, int ta_method0,int ta_div0
	GPIO_Init();
	_EINT();					//¿ª×ÜÖÐ¶Ï
	while (1);
}
