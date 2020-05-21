/***********************************************/
//��ʼ��Timer_A
/***********************************************/

/*�趨TimerA��ʱ��Դ*/
void TA_CLK(int ta_clk)
{
	if (ta_clk == 0)		   //ʹ��TACLK
		TA0CTL |= TASSEL_0;
	if (ta_clk == 1)		   //ʹ��ACLK
		TA0CTL |= TASSEL_1;
	if (ta_clk == 2)		   //ʹ��SMCLK
		TA0CTL |= TASSEL_2;
	if (ta_clk == 3)		   //ʹ��INCLK
		TA0CTL |= TASSEL_3;
}

/*�趨����ģʽ*/
void TA_Method(int ta_method)
{
	if (ta_method == 0)		  //ֹͣ����
		TA0CTL |= MC_0;
	if (ta_method == 1)		  //��0�ӵ�TA0CCR0
		TA0CTL |= MC_1;
	if (ta_method == 2)		  //��0�ӵ�65535
		TA0CTL |= MC_2;
	if (ta_method == 3)		  //��0�ӵ�TA0CCR0���ټ���0
		TA0CTL |= MC_3;
}

/*�趨ʱ�ӷ�Ƶ*/
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
	TA0CCTL0 |= CCIE;		//ʹ�ܡ�����/�Ƚϡ��Ĵ�����������洢��ֵ
	TA0CCR0 = time_long;    //�趨��ֵ��ʼֵ
	TA0CTL |= TACLR;		//��������0
	TA_CLK(ta_clk0);		//�趨ʱ��Դ
	TA_Method(ta_method0);  //�趨����ģʽ
	if (ta_div0 != 0)       //�趨ʱ�ӷ�Ƶ(Ĭ���ǲ��õ�)
	{
		TA_DIV(ta_div0);
	}
	
}

/***********************************************/
//Timer_A��ʱ�ж�
/***********************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A()
{
 /***�����жϺ�Ĳ���***/
	P1OUT ^= BIT0;
}
