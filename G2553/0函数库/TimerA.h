//***需前置Clock.h
/************************************TA0作定时器**************************************/

//1.初始化TA0**********************************

//1-1.设定TimerA0的时钟源

void TA0_CLK(char ta0_clk)
{
	switch (ta0_clk)
	{
		case 't':
		case 'T':TA0CTL |= TASSEL_0; break;		//使用外部输入TACLK
		case 'a':
		case 'A':TA0CTL |= TASSEL_1; break;		//使用ACLK
		case 's':
		case 'S':TA0CTL |= TASSEL_2; break;		//使用SMCLK
		case 'i':
		case 'I':TA0CTL |= TASSEL_3; break;		//使用外部输入TACLK取反,得INCLK
		default:break;
	}
}

//1-2.设定计数模式

void TA0_Method(int ta0_method)
{
	switch (ta0_method)
	{
		case 0:TA0CTL |= MC_0; break;		//停止计数
		case 1:TA0CTL |= MC_1; break;		//从0加到TA0CCR0
		case 2:TA0CTL |= MC_2; break;		//从0加到65535
		case 3:TA0CTL |= MC_3; break;		//从0加到TA0CCR0，再减到0
		default:break;
	}
}

//1-3.设定时钟分频

void TA0_DIV(int ta0_div)
{
	switch (ta0_div)
	{
		case 1:TA0CTL |= ID_0; break;
		case 2:TA0CTL |= ID_1; break;
		case 4:TA0CTL |= ID_2; break;
		case 8:TA0CTL |= ID_3; break;
		default:break;
	}
}

//1-4.整合，初始化TA0

void TA0_Init(char ta0_clk0, int ta0_div0,int ta0_method0, int time_long)
{
	TA0CTL = 0;				//清除以前的设置
	TA0CCTL0 |= CCIE;		//使能“捕获/比较”寄存器，以允许存储阈值
	TA0CTL |= TACLR;		//计数器清0
	TA0_CLK(ta0_clk0);		//设定时钟源
	TA0_DIV(ta0_div0);        //设定时钟分频(默认是不用的)	
	TA0_Method(ta0_method0);  //设定计数模式
	TA0CCR0 = time_long;    //设定阈值初始值
}

/*****************************************************************
例子：
1.计数12000,使用VLO-ACLK-12kHz,从0加到TA0CCR0=12000,1分频
TA0_Init('A', 1, 1, 12000);
******************************************************************/

//2.TA0定时中断********************************

//2-1.中断后的操作

void TA0_Interrupt_Function()
{
	P1OUT ^= BIT0;
}

//2-2.中断函数
//TA0的中断标志位会自动清0，不用管

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_Interrupt()
{
	TA0_Interrupt_Function();
}



/************************************TA1作定时器**************************************/

//1.初始化TA1*******************************

//1-1.设定TA1的时钟源

void TA1_CLK(char ta1_clk)
{
	switch (ta1_clk)
	{
	case 't':
	case 'T':TA1CTL |= TASSEL_0; break;		//使用外部输入TACLK
	case 'a':
	case 'A':TA1CTL |= TASSEL_1; break;		//使用ACLK
	case 's':
	case 'S':TA1CTL |= TASSEL_2; break;		//使用SMCLK
	case 'i':
	case 'I':TA1CTL |= TASSEL_3; break;		//使用外部输入TACLK取反,得INCLK
	default:break;
	}
}

//1-2.设定计数模式

void TA1_Method(int ta1_method)
{
	switch (ta1_method)
	{
	case 0:TA1CTL |= MC_0; break;		//停止计数
	case 1:TA1CTL |= MC_1; break;		//从0加到TA0CCR0
	case 2:TA1CTL |= MC_2; break;		//从0加到65535
	case 3:TA1CTL |= MC_3; break;		//从0加到TA0CCR0，再减到0
	default:break;
	}
}

//1-3.设定时钟分频

void TA1_DIV(int ta1_div)
{
	switch (ta1_div)
	{
	case 1:TA1CTL |= ID_0; break;
	case 2:TA1CTL |= ID_1; break;
	case 4:TA1CTL |= ID_2; break;
	case 8:TA1CTL |= ID_3; break;
	default:break;
	}
}

//1-4.整合，初始化TA0

void TA1_Init(char ta1_clk0, int ta1_div0, int ta1_method0, int time_long)
{
	TA1CTL = 0;				//清除以前的设置
	TA1CCTL0 |= CCIE;		//使能“捕获/比较”寄存器，以允许存储阈值
	TA1CTL |= TACLR;		//计数器清0
	TA1_CLK(ta1_clk0);		//设定时钟源
	TA1_DIV(ta1_div0);        //设定时钟分频(默认是不用的)	
	TA1_Method(ta1_method0);  //设定计数模式
	TA1CCR0 = time_long;    //设定阈值初始值
}


/*****************************************************************
例子：
1.计数12000,使用VLO-ACLK-12kHz,从0加到TA0CCR0=12000,1分频
TA1_Init('A', 1, 1, 12000);
******************************************************************/

//2.TA1定时中断********************************

//2-1.中断后的操作

void TA1_Interrupt_Function()
{
	P1OUT ^= BIT0;
}

//2-2.中断函数
//TA1的中断标志位会自动清0，不用管

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA1_Interrupt()
{
	TA1_Interrupt_Function();
}
