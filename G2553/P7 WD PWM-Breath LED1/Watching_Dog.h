#ifndef WATCHING_DOG_H_
#define WATCHING_DOG_H_
#endif /* WATCHING_DOG_H_ */

//1.�ع�*****************************************************************

void WD_STOP()
{
    WDTCTL = WDTPW + WDTHOLD;
}

//2.WDTimer*****************************************************************

//2-1.��ʼ��WDTimer
//WDT�жϲ���_EINT();����

void WDTimer_Init()
{
    WDTCTL = WDT_ADLY_1_9;

    IE1 |= WDTIE;                        //����WDT�ж�

}

//2-2.WDTimer�ж�
//ֻ������Ϊ��ʱ���Ļ�����һ�㶨ʱ��һ��

//2-2-1.WDTimer�жϺ�ʵ�ֵĹ���

void WDT_Interrupt_Function()
{
    T0_PWM_Breath_Bright();

}

//2-2-2.����WDTimer�ж�

#pragma vector=WDT_VECTOR
__interrupt void WDT_Interrupt()
{
    WDT_Interrupt_Function();

}

//3.NMI�ж�*****************************************************************

//3-1.��ʼ��NMI

void NMI_Interrupt_Init()
{
    WDTCTL = WDTPW + WDTHOLD + WDTNMI;      //����NMIģʽ

    IE1 = NMIIE;                            //����NMI�ж�

}

//3-2.NMI�ж�
//NMIÿ���жϺ󣬶����Զ��ر��ж�ʹ��

//3-2-1.�����жϺ�Ĺ���

void NMI_Interrupt_Function()
{
    P1OUT &= ~BIT6;

}

//3-2-2.�����ж�

#pragma vector=NMI_VECTOR
__interrupt void NMI_Interrupt()
{
    NMI_Interrupt_Function();

}

