#ifndef WATCHING_DOG_H_
#define WATCHING_DOG_H_
#endif /* WATCHING_DOG_H_ */

//��ʼ��WDTimer
//WDT�жϲ���_EINT();����

void WDTimer_Init()
{
    WDTCTL = WDT_ADLY_250;

    IE1 = WDTIE;                        //����WDT�ж�
}

//WDTimer�ж�

#pragma vector=WDT_VECTOR
__interrupt void WDT_Interrupt()
{
    P1OUT ^= BIT0;
}
