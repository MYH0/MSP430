//***��ǰ��Clock.h
/************************************TA0����ʱ��**************************************/

//1.��ʼ��TA0**********************************

//1-1.�趨TimerA0��ʱ��Դ

void TA0_CLK(char ta0_clk)
{
	switch (ta0_clk)
	{
		case 't':
		case 'T':TA0CTL |= TASSEL_0; break;		//ʹ���ⲿ����TACLK
		case 'a':
		case 'A':TA0CTL |= TASSEL_1; break;		//ʹ��ACLK
		case 's':
		case 'S':TA0CTL |= TASSEL_2; break;		//ʹ��SMCLK
		case 'i':
		case 'I':TA0CTL |= TASSEL_3; break;		//ʹ���ⲿ����TACLKȡ��,��INCLK
		default:break;
	}
}

//1-2.�趨����ģʽ

void TA0_Method(int ta0_method)
{
	switch (ta0_method)
	{
		case 0:TA0CTL |= MC_0; break;		//ֹͣ����
		case 1:TA0CTL |= MC_1; break;		//��0�ӵ�TA0CCR0
		case 2:TA0CTL |= MC_2; break;		//��0�ӵ�65535
		case 3:TA0CTL |= MC_3; break;		//��0�ӵ�TA0CCR0���ټ���0
		default:break;
	}
}

//1-3.�趨ʱ�ӷ�Ƶ

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

//1-4.���ϣ���ʼ��TA0

void TA0_Init(char ta0_clk0, int ta0_div0,int ta0_method0, int time_long)
{
	TA0CTL = 0;				//�����ǰ������
	TA0CCTL0 |= CCIE;		//ʹ�ܡ�����/�Ƚϡ��Ĵ�����������洢��ֵ
	TA0CTL |= TACLR;		//��������0
	TA0_CLK(ta0_clk0);		//�趨ʱ��Դ
	TA0_DIV(ta0_div0);        //�趨ʱ�ӷ�Ƶ(Ĭ���ǲ��õ�)	
	TA0_Method(ta0_method0);  //�趨����ģʽ
	TA0CCR0 = time_long;    //�趨��ֵ��ʼֵ
}

/*****************************************************************
���ӣ�
1.����12000,ʹ��VLO-ACLK-12kHz,��0�ӵ�TA0CCR0=12000,1��Ƶ
TA0_Init('A', 1, 1, 12000);
******************************************************************/

//2.TA0��ʱ�ж�********************************

//2-1.�жϺ�Ĳ���

void TA0_Interrupt_Function()
{
	P1OUT ^= BIT0;
}

//2-2.�жϺ���
//TA0���жϱ�־λ���Զ���0�����ù�

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_Interrupt()
{
	TA0_Interrupt_Function();
}



/************************************TA1����ʱ��**************************************/

//1.��ʼ��TA1*******************************

//1-1.�趨TA1��ʱ��Դ

void TA1_CLK(char ta1_clk)
{
	switch (ta1_clk)
	{
	case 't':
	case 'T':TA1CTL |= TASSEL_0; break;		//ʹ���ⲿ����TACLK
	case 'a':
	case 'A':TA1CTL |= TASSEL_1; break;		//ʹ��ACLK
	case 's':
	case 'S':TA1CTL |= TASSEL_2; break;		//ʹ��SMCLK
	case 'i':
	case 'I':TA1CTL |= TASSEL_3; break;		//ʹ���ⲿ����TACLKȡ��,��INCLK
	default:break;
	}
}

//1-2.�趨����ģʽ

void TA1_Method(int ta1_method)
{
	switch (ta1_method)
	{
	case 0:TA1CTL |= MC_0; break;		//ֹͣ����
	case 1:TA1CTL |= MC_1; break;		//��0�ӵ�TA0CCR0
	case 2:TA1CTL |= MC_2; break;		//��0�ӵ�65535
	case 3:TA1CTL |= MC_3; break;		//��0�ӵ�TA0CCR0���ټ���0
	default:break;
	}
}

//1-3.�趨ʱ�ӷ�Ƶ

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

//1-4.���ϣ���ʼ��TA0

void TA1_Init(char ta1_clk0, int ta1_div0, int ta1_method0, int time_long)
{
	TA1CTL = 0;				//�����ǰ������
	TA1CCTL0 |= CCIE;		//ʹ�ܡ�����/�Ƚϡ��Ĵ�����������洢��ֵ
	TA1CTL |= TACLR;		//��������0
	TA1_CLK(ta1_clk0);		//�趨ʱ��Դ
	TA1_DIV(ta1_div0);        //�趨ʱ�ӷ�Ƶ(Ĭ���ǲ��õ�)	
	TA1_Method(ta1_method0);  //�趨����ģʽ
	TA1CCR0 = time_long;    //�趨��ֵ��ʼֵ
}


/*****************************************************************
���ӣ�
1.����12000,ʹ��VLO-ACLK-12kHz,��0�ӵ�TA0CCR0=12000,1��Ƶ
TA1_Init('A', 1, 1, 12000);
******************************************************************/

//2.TA1��ʱ�ж�********************************

//2-1.�жϺ�Ĳ���

void TA1_Interrupt_Function()
{
	P1OUT ^= BIT0;
}

//2-2.�жϺ���
//TA1���жϱ�־λ���Զ���0�����ù�

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA1_Interrupt()
{
	TA1_Interrupt_Function();
}
