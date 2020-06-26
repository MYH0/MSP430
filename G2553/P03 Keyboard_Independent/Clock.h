/******************************************************/
//�趨һЩȫ�ֱ���
/******************************************************/
typedef unsigned int uint;
typedef unsigned char uchar;

double CPU_freq = 0;


/******************************************************/
//У׼DCO
/******************************************************/
void DCO_Adjust(int dco_x)
{
	switch (dco_x)
	{
		case 16:DCOCTL = CALDCO_16MHZ; break;
		case 12:DCOCTL = CALDCO_12MHZ; break;
		case 8:DCOCTL = CALDCO_8MHZ; break;
		case 1:DCOCTL = CALDCO_1MHZ; break;
		default:break;
	}
}

/******************************************************/
//�趨ʱ��ԴMCLK,SMCLK,ACLK
/******************************************************/

//�����趨MCLK

void MCLK_Init(int mclk_a)			 //aΪ�����趨MCLK��bΪMCLK��Ƶ��DIVM
{	
	switch (mclk_a)
	{
		case 16:BCSCTL1 = CALBC1_16MHZ; CPU_freq = 16000000; break;
		case 12:BCSCTL1 = CALBC1_12MHZ; CPU_freq = 12000000; break;
		case 8:BCSCTL1 = CALBC1_8MHZ; CPU_freq = 8000000; break;
		case 1:BCSCTL1 = CALBC1_1MHZ; CPU_freq = 1000000; break;
		default:break;
	}
}

//�趨MCLK��Ƶ

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

//�趨SMCLK��Ƶ

void SMCLK_DIV(int divs_c)
{
	if (divs_c == 1)
		BCSCTL2 |= DIVS_1;
	if (divs_c == 2)
		BCSCTL2 |= DIVS_2;
	if (divs_c == 3)
		BCSCTL2 |= DIVS_3;
}

//����ACLK

void ACLK_Init(int aclk_d)	//dΪѡ��ʱ��Դ��eΪ����ACLK��Ƶ
{
	/*ѡ��ʱ��Դ*/
	if (aclk_d == 1)			//d=1ʱ��ѡVLOΪʱ��Դ;d=0ʱ�����ⲿ����
	{
		BCSCTL3 |= LFXT1S_2;
	}

}

//�趨ACLK��Ƶ

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
//��1������ʵ����������
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
//����
/******************************************************
1.MCLK=16MHz,SMCLK=16MHz,ACLK����VLO��ACLK=12kHz
  BCS_Init(16, 16, 0, 0, 1, 0);		
********************************************************/

/******************************************************/
//��ʱms
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
//��ʱus
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