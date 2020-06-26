#ifndef WATCHING_DOG_H_
#define WATCHING_DOG_H_
#endif /* WATCHING_DOG_H_ */

//1.关狗*****************************************************************

void WD_STOP()
{
    WDTCTL = WDTPW + WDTHOLD;
}


//2.WDTimer*****************************************************************

//2-1.初始化WDTimer
//WDT中断不受_EINT();控制

void WDTimer_Init()
{
    WDTCTL = WDT_ADLY_250;
    IE1 = WDTIE;                        //允许WDT中断

}

//2-2.WDTimer中断
//只单纯作为定时器的话，与一般定时器一样

//2-2-1.WDTimer中断后实现的功能

void WDT_Interrupt_Function()
{
    
}

//2-2-2.进入WDTimer中断

#pragma vector=WDT_VECTOR
__interrupt void WDT_Interrupt()
{
    WDT_Interrupt_Function();
}

//3.NMI中断*****************************************************************

//3-1.初始化NMI

void NMI_Interrupt_Init()
{
    WDTCTL = WDTPW + WDTHOLD + WDTNMI;      //启用NMI模式
    IE1 = NMIIE;                            //允许NMI中断

}


//3-2.NMI中断
//NMI每次中断后，都会自动关闭中断使能

//3-2-1.RST按键功能

void Key_RST_Function()
{
    P1OUT &= ~BIT6;
}

//3-2-2.进入中断后的功能

void NMI_Interrupt_Function()
{
    Key_RST_Function();
}

//3-2-3.进入中断

#pragma vector=NMI_VECTOR
__interrupt void NMI_Interrupt()
{
    NMI_Interrupt_Function();
}

