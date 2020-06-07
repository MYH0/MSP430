//��ʼ��GPIO*********************************************************************
/*
PxSEL=0ʱ���ܽ�ΪI/O����
PxDIR=0ʱ���ܽ�Ϊ���빦��
PxREN=1ʱ����������/��������
PxOUT=1ʱ���ܽ����H��ƽ��������������
*/

//LED-IO��ʼ��
void GPIO_LED_Init()
{
	P1SEL &= ~(BIT0 + BIT6);
	P1DIR |= BIT0 + BIT6;
	P1OUT |= BIT0;
	P1OUT &= ~BIT6;
}

//Key_P13-IO��ʼ��
void GPIO_Key_Init()
{
	P1SEL &= ~(BIT3);
	P1DIR &= ~(BIT3);
	P1REN |= BIT3;
	P1OUT |= BIT3;
}

//�ܳ�ʼ��
void GPIO_Init()
{
	GPIO_LED_Init();
	GPIO_Key_Init();

}

//P13��������********************************************************************
void Key_P13_Function()
{
	P1OUT ^= BIT0;
	P1OUT ^= BIT6;
}

//IO�ж�*************************************************************************
/*
PxIE=1ʱ������IO�ж�
PxIES=1ʱ���½��ش���IO�ж�
PxIFG=0ʱ����0�ж�Px��־λ
*/

//��ʼ��IO�ж�

void GPIO_Interrupt_Init()
{
	P1IE |= BIT3;
	P1IES |= BIT3;
}

//��IO�жϺ�Ĺ���

//P13�жϰ�������

void GPIO_Interrupt_P13_Function()
{
	Key_P13_Function();
}

//IO�жϼ��(������ʱ��)
//����������������ģ�

void GPIO_Interrupt_Scan()
{
	uint Input = 0;
	Input = P1IFG & (~P1DIR);		//ֻ����������ɵ��жϣ��ų�����ڵ�Ӱ��
	Delay_us(500);
	if ((P1IN & Input) == 0)		//�ж�����ʱǰ�Ƿ�һ��
	{
		switch (Input)			//��Ҫ�ж����ĸ�����ڵ��ж�
		{
			case BIT3:GPIO_Interrupt_P13_Function(); break;

			default:break;
		}
	}
}

//����IO�ж�
//P1IFG�жϱ�־λҪ�ֶ���0

#pragma vector=PORT1_VECTOR
__interrupt void P1_Interrupt()
{
	GPIO_Interrupt_Scan();
	P1IFG = 0;
}

//�������-WDTimer�ж�(������),��Ҫ����Watching_Dog�ļ�*********************************

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
