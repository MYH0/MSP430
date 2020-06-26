/*************************************************/
//��ʼ��GPIO
/**************************************************
PxSEL=0ʱ���ܽ�ΪI/O����
PxDIR=0ʱ���ܽ�Ϊ���빦��
PxREN=1ʱ����������/��������
PxOUT=1ʱ���ܽ����H��ƽ��������������
***************************************************/

void GPIO_Init()
{
	P1SEL &= ~BIT6;
//	P1REN |= BIT3;
//	P1OUT |= BIT3;
	P1DIR |= BIT6;
	P1OUT |= BIT6;

}

/*************************************************/
//IO�ж�
/**************************************************
PxIE=1ʱ������IO�ж�
PxIES=1ʱ���½��ش���IO�ж�
PxIFG=0ʱ����0�ж�Px��־λ
***************************************************/

//��ʼ��IO�ж�

void GPIO_Interrupt_Init()
{
	P1IE |= BIT3;
	P1IES |= BIT3;
}

//��IO�жϺ�Ĺ���

//P13�ж�

void P13_Interrupt_Function()
{


}

//IO�жϼ��

void GPIO_Interrupt_Scan()
{
	uint Pin_Interrupt = 0;
	Pin_Interrupt = P1IFG & (~P1DIR);		//ֻ����������ɵ��жϣ��ų�����ڵ�Ӱ��
	Delay_us(500);
	if ((P1IN & Pin_Interrupt) == 0)		//�ж�����ʱǰ�Ƿ�һ��
	{
		switch (Pin_Interrupt)
		{
			case BIT3:P13_Interrupt_Function(); break;

			default:break;
		}
	}
}

//�趨IO�жϺ���

#pragma vector=PORT1_VECTOR
__interrupt void P1_Interrupt()
{
	GPIO_Interrupt_Scan();
	P1IFG = 0;
}
