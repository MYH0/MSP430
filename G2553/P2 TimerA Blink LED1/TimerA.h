/***********************************************/
//初始化Timer_A
/***********************************************/

/*设定TimerA的时钟源*/
void TA_CLK(int ta_clk)
{
	if (ta_clk == 0)		   //使用TACLK
		TA0CTL |= TASSEL_0;
	if (ta_clk == 1)		   //使用ACLK
		TA0CTL |= TASSEL_1;
	if (ta_clk == 2)		   //使用SMCLK
		TA0CTL |= TASSEL_2;
	if (ta_clk == 3)		   //使用INCLK
		TA0CTL |= TASSEL_3;
}

/*设定计数模式*/
void TA_Method(int ta_method)
{
	if (ta_method == 0)		  //停止计数
		TA0CTL |= MC_0;
	if (ta_method == 1)		  //从0加到TA0CCR0
		TA0CTL |= MC_1;
	if (ta_method == 2)		  //从0加到65535
		TA0CTL |= MC_2;
	if (ta_method == 3)		  //从0加到TA0CCR0，再减到0
		TA0CTL |= MC_3;
}

/*设定时钟分频*/
void TA_DIV(int ta_div)
{
	if (ta_div == 1)
		TA0CTL |= ID_1;
	if (ta_div == 2)
		TA0CTL |= ID_2;
	if (ta_div == 3)
		TA0CTL |= ID_3;
}


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

/***********************************************/
//Timer_A定时中断
/***********************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A()
{
 /***进入中断后的操作***/
	P1OUT ^= BIT0;
}
