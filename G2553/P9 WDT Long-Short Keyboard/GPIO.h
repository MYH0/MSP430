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

//һ��

void Key_P13()
{
	P1OUT ^= BIT0;
	P1OUT ^= BIT6;
}

//�̰�

void Key_P13_Short()
{
	P1OUT ^= BIT0;

}

//����

void Key_P13_Long()
{
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
	Key_P13();
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
//WDTimer�趨��16~20ms���ұȽϺ�

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

//�������-WDTimer�ж�(������)-Melay״̬��**********************************************
//WDTimer�趨��16~20ms���ұȽϺ�

//״̬���궨��
#define FREE 0
#define SHORT 1
#define LONG 2
#define MUST_BE_LONG 40    //����20*40=800ms��,�϶�Ϊ����

uchar WDT_Count = 0;       //�԰���ʱ�����

//�������
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

//״̬��

void WDT_Interrupt_Key_Scan_SM()
{
	static uchar State = 0;
	static uchar Key_Now = 0;
	uchar Key_Past = 0;
	uchar Key_Action = 0;          //�����Ķ�̬�仯��2Ϊ����1Ϊ����
								   //���ɣ�ΪʲôKey_Action��ֵ����Ϊ0��������0����ʾ������̬����
	Key_Past = Key_Now;
	if (P1IN & BIT3)				//���ɣ�Ϊʲô����д��if((P1IN&BIT3)==1)
		Key_Now = 1;
	else
		Key_Now = 0;
//	Key_Now = P1IN & BIT3;		   //��ȡ������ǰ״̬

	if ((Key_Past == 1) && (Key_Now == 0))		//��ƽ�ȸߺ�ͣ�Ϊ����
		Key_Action = 1;
	if ((Key_Past == 0) && (Key_Now == 1))		//��ƽ�ȵͺ�ߣ�Ϊ����
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
