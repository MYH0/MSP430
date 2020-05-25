/*************************************************/
//初始化GPIO
/**************************************************
PxSEL=0时：管脚为I/O功能
PxDIR=0时：管脚为输入功能
PxREN=1时：启用上拉/下拉电阻
PxOUT=1时：管脚输出H电平、启动上拉电阻
***************************************************/

void GPIO_Init()
{
	P1SEL &= ~(BIT0 + BIT3 + BIT6);			
	P1DIR |= BIT0 + BIT6;
	P1OUT |= BIT6;
	P1OUT &= ~BIT0;
	P1DIR &= ~BIT3;
	P1REN |= BIT3;
}

/*************************************************/
//IO中断
/**************************************************
PxIE=1时：允许IO中断
PxIES=1时：下降沿触发IO中断
PxIFG=0时：清0中断Px标志位
***************************************************/

//初始化IO中断

void GPIO_Interrupt_Init()
{
	P1IE |= BIT3;
	P1IES |= BIT3;
	P1IFG = 0;
}

//各IO中断后的功能

void P13_Interrupt()
{
	P1OUT ^= (BIT0 + BIT6);
}

//IO中断检测

void GPIO_Interrupt_Scan()
{
	int Pin_Interrupt = 0;
	Pin_Interrupt = P1IFG & (~P1DIR);		//只检测输入口造成的中断，排除输出口的影响
	Delay_us(500);
	if ((P1IN & Pin_Interrupt) == 0)		//排除按键抬起造成的抖动
	{
		switch (Pin_Interrupt)
		{
		case BIT3:P13_Interrupt(); break;
		default:break;
		}
	}
}

//设定IO中断函数
#pragma vector=PORT1_VECTOR
__interrupt void P1_Interrupt()
{
	GPIO_Interrupt_Scan();
	P1IFG = 0;
}
