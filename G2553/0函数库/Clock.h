/******************************************************/
//设定一些全局变量
/******************************************************/
double CPU_freq = 0;


/******************************************************/
//校准DCO
/******************************************************/
void DCO_Adjust(int dco_x)
{
	if (dco_x == 16)
		DCOCTL = CALDCO_16MHZ;
	if (dco_x == 12)
		DCOCTL = CALDCO_12MHZ;
	if (dco_x == 8)
		DCOCTL = CALDCO_8MHZ;
	if (dco_x == 1)
		DCOCTL = CALDCO_1MHZ;

}

/******************************************************/
//设定时钟源MCLK,SMCLK,ACLK
/******************************************************/

/*初步设定MCLK*/
void MCLK_Init(int mclk_a)			 //a为初步设定MCLK，b为MCLK分频的DIVM
{									
	if (mclk_a == 16)
	{
		BCSCTL1 = CALBC1_16MHZ;
		CPU_freq = 16000000;
	}
	if (mclk_a == 12)
	{
		BCSCTL1 = CALBC1_12MHZ;
		CPU_freq = 12000000;
	}
	if (mclk_a == 8)
	{
		BCSCTL1 = CALBC1_8MHZ;
		CPU_freq = 8000000;
	}
	if (mclk_a == 1)
	{
		BCSCTL1 = CALBC1_1MHZ;
		CPU_freq = 1000000;
	}
}

/*设定MCLK分频*/
void MCLK_DIV(int divm_b)
{
	if (divm_b == 1)
	{
		BCSCTL2 |= DIVM_1;
		CPU_freq /= 2;
	}
	if (divm_b == 2)
	{
		BCSCTL2 |= DIVM_2;
		CPU_freq /= 4;
	}
	if (divm_b == 3)
	{
		BCSCTL2 |= DIVM_3;
		CPU_freq /= 8;
	}
}

/*设定SMCLK分频*/
void SMCLK_DIV(int divs_c)
{
	if (divs_c == 1)
		BCSCTL2 |= DIVS_1;
	if (divs_c == 2)
		BCSCTL2 |= DIVS_2;
	if (divs_c == 3)
		BCSCTL2 |= DIVS_3;
}

/*设置ACLK*/
void ACLK_Init(int aclk_d)	//d为选择时钟源，e为设置ACLK分频
{
	/*选择时钟源*/
	if (aclk_d == 1)			//d=1时，选VLO为时钟源;d=0时，用外部晶振
	{
		BCSCTL3 |= LFXT1S_2;
	}

}

/*设定ACLK分频*/
void ACLK_DIV(int diva_e)
{
	if (diva_e == 1)
		BCSCTL1 |= DIVA_1;
	if (diva_e == 2)
		BCSCTL1 |= DIVA_2;
	if (diva_e == 3)
		BCSCTL1 |= DIVA_3;
}


/******************************************************/
//用1个函数实现上述功能
/******************************************************/
void BCS_Init(int dco_x0,int mclk_a0,int divm_b0,int divs_c0,int aclk_d0,int diva_e0)
{
	DCO_Adjust(dco_x0);
	MCLK_Init(mclk_a0);
	if (divm_b0 != 0)
	{
		MCLK_DIV(divm_b0);
	}
	if (divs_c0 != 0)
	{
		SMCLK_DIV(divs_c0);
	}
	ACLK_Init(aclk_d0);
	if (diva_e0 != 0)
	{
		ACLK_DIV(diva_e0);
	}
}

/******************************************************/
//例子
/******************************************************
1.MCLK=16MHz,SMCLK=16MHz,ACLK采用VLO，ACLK=12kHz
  BCS_Init(16, 16, 0, 0, 1, 0);		
********************************************************/

/******************************************************/
//延时ms
/******************************************************/
void Delay_ms(int timelong_ms)
{
	int x = 0;
	double y = 0;
	x = timelong_ms;
	y = CPU_freq / 1000;
	for (; x > 0; x--)
		for (; y > 0; y--);
}

/******************************************************/
//延时us
/******************************************************/
void Delay_us(int timelong_us)
{
	int x = 0;
	double y = 0;
	x = timelong_us;
	y = CPU_freq / 1000000;
	for (; x > 0; x--)
		for (; y > 0; y--);
}
