//初始化GPIO*********************************************************************
/*
PxSEL=0时：管脚为I/O功能
PxDIR=0时：管脚为输入功能
PxREN=1时：启用上拉/下拉电阻
PxOUT=1时：管脚输出H电平、启动上拉电阻
*/

//LED-IO初始化
void GPIO_LED_Init()
{
	P1SEL &= ~(BIT0 + BIT6);
	P1DIR |= BIT0 + BIT6;
	P1OUT |= BIT0;
	P1OUT &= ~BIT6;
}

//Key_P13-IO初始化
void GPIO_Key_Init()
{
	P1SEL &= ~(BIT3);
	P1DIR &= ~(BIT3);
	P1REN |= BIT3;
	P1OUT |= BIT3;
}

//总初始化
void GPIO_Init()
{
	GPIO_LED_Init();
	GPIO_Key_Init();

}

//P13按键功能********************************************************************
void Key_P13_Function()
{
	P1OUT ^= BIT0;
	P1OUT ^= BIT6;
}

//IO中断*************************************************************************
/*
PxIE=1时：允许IO中断
PxIES=1时：下降沿触发IO中断
PxIFG=0时：清0中断Px标志位
*/

//初始化IO中断

void GPIO_Interrupt_Init()
{
	P1IE |= BIT3;
	P1IES |= BIT3;
}

//各IO中断后的功能

//P13中断按键功能

void GPIO_Interrupt_P13_Function()
{
	Key_P13_Function();
}

//IO中断检测(阻塞延时型)
//按键检测是有阻塞的！

void GPIO_Interrupt_Scan()
{
	uint Input = 0;
	Input = P1IFG & (~P1DIR);		//只检测输入口造成的中断，排除输出口的影响
	Delay_us(500);
	if ((P1IN & Input) == 0)		//判断与延时前是否一致
	{
		switch (Input)			//需要判断是哪个输入口的中断
		{
			case BIT3:GPIO_Interrupt_P13_Function(); break;

			default:break;
		}
	}
}

//进入IO中断
//P1IFG中断标志位要手动清0

#pragma vector=PORT1_VECTOR
__interrupt void P1_Interrupt()
{
	GPIO_Interrupt_Scan();
	P1IFG = 0;
}

//按键检测-WDTimer中断(无阻塞),需要后置Watching_Dog文件*********************************

void WDT_Interrupt_Key_Scan()
{
	static uchar Key_Now = 0;
	uchar Key_Past = 0;
	Key_Past = Key_Now;

	if ((P1IN & BIT3) == 0)
		Key_Now = 0;
	else
		Key_Now = 1;

	if ((Key_Past == 1) && (Key_Now == 0))
		Key_P13_Function();
}
