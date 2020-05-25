/***********************************************/
//��ʼ��Timer_A
/***********************************************/

//�趨TimerA��ʱ��Դ

void TA_CLK(int ta_clk)
{
	switch (ta_clk)
	{
		case 0:TA0CTL |= TASSEL_0; break;		//ʹ��TACLK
		case 1:TA0CTL |= TASSEL_1; break;		//ʹ��ACLK
		case 2:TA0CTL |= TASSEL_2; break;		//ʹ��SMCLK
		case 3:TA0CTL |= TASSEL_3; break;		//ʹ��INCLK
		default:break;
	}
}

//�趨����ģʽ

void TA_Method(int ta_method)
{
	switch (ta_method)
	{
		case 0:TA0CTL |= MC_0; break;		//ֹͣ����
		case 1:TA0CTL |= MC_1; break;		//��0�ӵ�TA0CCR0
		case 2:TA0CTL |= MC_2; break;		//��0�ӵ�65535
		case 3:TA0CTL |= MC_3; break;		//��0�ӵ�TA0CCR0���ټ���0
		default:break;
	}
}

//�趨ʱ�ӷ�Ƶ

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

//���ϣ���ʼ��TimerA

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

/*****************************************************************
���ӣ�
1.����12000,ʹ��VLO-12kHz,��0�ӵ�TA0CCR0=12000,��Ƶ��=0
TimerA_Init(12000, 1, 1, 0);
******************************************************************/

/****************************************************************/
//Timer_A��ʱ�ж�
/****************************************************************/

//�жϺ�Ĳ���
void TimerA_Interrupt_Function()
{
	P1OUT ^= BIT0;
}

//�жϺ���
//TimerA���жϱ�־λ���Զ���0�����ù�
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerA_Interrupt()
{
	TimerA_Interrupt_Function();
}
