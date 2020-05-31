#ifndef WATCHING_DOG_H_
#define WATCHING_DOG_H_
#endif /* WATCHING_DOG_H_ */

//初始化WDTimer
//WDT中断不受_EINT();控制

void WDTimer_Init()
{
    WDTCTL = WDT_ADLY_250;

    IE1 = WDTIE;                        //允许WDT中断
}

//WDTimer中断

#pragma vector=WDT_VECTOR
__interrupt void WDT_Interrupt()
{
    P1OUT ^= BIT0;
}
