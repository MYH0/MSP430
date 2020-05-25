/***********************************************/
//初始化Timer_A
/***********************************************/

//设定TimerA的时钟源

void TA_CLK(int ta_clk)
{
	switch (ta_clk)
	{
		case 0:TA0CTL |= TASSEL_0; break;		//使用TACLK
		case 1:TA0CTL |= TASSEL_1; break;		//使用ACLK
		case 2:TA0CTL |= TASSEL_2; break;		//使用SMCLK
		case 3:TA0CTL |= TASSEL_3; break;		//使用INCLK
		default:break;
	}
}

//设定计数模式

void TA_Method(int ta_method)
{
	switch (ta_method)
	{
		case 0:TA0CTL |= MC_0; break;		//停止计数
		case 1:TA0CTL |= MC_1; break;		//从0加到TA0CCR0
		case 2:TA0CTL |= MC_2; break;		//从0加到65535
		case 3:TA0CTL |= MC_3; break;		//从0加到TA0CCR0，再减到0
		default:break;
	}
}

//设定时钟分频

void TA_DIV(int ta_div)
{
	switch (ta_div)
	{
		case 1:TA0CTL |= ID_1; break;
		case 2:TA0CTL |= ID_2; break;
		case 3:TA0CTL |= ID_3; break;
		default:break;
	}
}

//整合，初始化TimerA

void TimerA_Init(int time_long,int ta_clk0, int ta_method0,int ta_div0)
{
	TA0CCTL0 |= CCIE;		//使能“捕获/比较”寄存器，以允许存储阈值
	TA0CCR0 = time_long;    //设定阈值初始值
	TA0CTL |= TACLR;		//计数器清0
	TA_CLK(ta_clk0);		//设定时钟源
	TA_Method(ta_method0);  //设定计数模式
	if (ta_div0 != 0)       //设定时钟分频(默认是不用的)
	{
		TA_DIV(ta_div0);
	}	
}

/*****************************************************************
例子：
1.计数12000,使用VLO-12kHz,从0加到TA0CCR0=12000,分频数=0
TimerA_Init(12000, 1, 1, 0);
******************************************************************/

/****************************************************************/
//Timer_A定时中断
/****************************************************************/

//中断后的操作
void TimerA_Interrupt_Function()
{
	P1OUT ^= BIT0;
}

//中断函数
//TimerA的中断标志位会自动清0，不用管
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerA_Interrupt()
{
	TimerA_Interrupt_Function();
}
