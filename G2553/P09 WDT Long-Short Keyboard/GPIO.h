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

//一般

void Key_P13()
{
	P1OUT ^= BIT0;
	P1OUT ^= BIT6;
}

//短按

void Key_P13_Short()
{
	P1OUT ^= BIT0;

}

//长按

void Key_P13_Long()
{
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
	Key_P13();
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
//WDTimer设定在16~20ms左右比较好

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
		Key_P13();
}

//按键检测-WDTimer中断(无阻塞)-Melay状态机**********************************************
//WDTimer设定在16~20ms左右比较好

//状态机宏定义
#define FREE 0
#define SHORT 1
#define LONG 2
#define MUST_BE_LONG 40    //按下20*40=800ms后,认定为长按

uchar WDT_Count = 0;       //对按下时间计数

//长按检测
uchar Key_Long_Scan()
{
	WDT_Count++;
	if (WDT_Count == MUST_BE_LONG)
	{
		WDT_Count = 0;
		return 1;
	}
	else
		return 0;
}

//状态机

void WDT_Interrupt_Key_Scan_SM()
{
	static uchar State = 0;
	static uchar Key_Now = 0;
	uchar Key_Past = 0;
	uchar Key_Action = 0;          //按键的动态变化，2为弹起，1为按下
								   //存疑：为什么Key_Action初值必须为0，不能用0来表示按键动态弹起
	Key_Past = Key_Now;
	if (P1IN & BIT3)				//存疑：为什么不能写成if((P1IN&BIT3)==1)
		Key_Now = 1;
	else
		Key_Now = 0;
//	Key_Now = P1IN & BIT3;		   //读取按键当前状态

	if ((Key_Past == 1) && (Key_Now == 0))		//电平先高后低，为按下
		Key_Action = 1;
	if ((Key_Past == 0) && (Key_Now == 1))		//电平先低后高，为弹起
		Key_Action = 2;
	
	switch (State)
	{
		case FREE: 
		{
			WDT_Count = 0;
			if (Key_Action == 1)
				State = SHORT;
			break;
		}
		case SHORT:
		{
			if(Key_Action==2)
			{
				State = FREE;
				Key_P13_Short();
			}
			if (Key_Long_Scan() == 1)
			{
				State = LONG;
				Key_P13_Long();
			}
			break;
		}
		case LONG:
		{
			WDT_Count = 0;
			if (Key_Action == 2)
			{
				State = FREE;
			}
			break;
		}
		default:State = FREE; break;
	}
}
