/******************************************************/
//�趨һЩȫ�ֱ���
/******************************************************/
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long int ulint;
typedef long int lint;

lint CPU_freq = 0;


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
		default:DCOCTL = CALDCO_1MHZ; break;
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
		default:BCSCTL1 = CALBC1_1MHZ; CPU_freq = 1000000; break;
	}
}

//�趨MCLK��Ƶ

void MCLK_DIV(int divm_b)
{
	switch (divm_b)
	{
		case 1:BCSCTL2 |= DIVM_0; break;
		case 2:BCSCTL2 |= DIVM_1; CPU_freq /= 2; break;
		case 4:BCSCTL2 |= DIVM_2; CPU_freq /= 4; break;
		case 8:BCSCTL2 |= DIVM_3; CPU_freq /= 8; break;
		default:BCSCTL2 |= DIVM_0; break;
	}
}

//�趨SMCLK��Ƶ

void SMCLK_DIV(int divs_c)
{
	switch (divs_c)
	{
		case 1:BCSCTL2 |= DIVS_0; break;
		case 2:BCSCTL2 |= DIVS_1; break;
		case 4:BCSCTL2 |= DIVS_2; break;
		case 8:BCSCTL2 |= DIVS_3; break;
		default:BCSCTL2 |= DIVS_0; break;
	}
}

//����ACLK

void ACLK_Init(int aclk_d)	//aclk_dΪѡ��ʱ��Դ
{
	//ѡ��ʱ��Դ
	//aclk_d=1ʱ��ѡVLOΪʱ��Դ;d=0ʱ�����ⲿ����
	if (aclk_d == 1)			
	{
		BCSCTL3 |= LFXT1S_2;
	}
}

//�趨ACLK��Ƶ

void ACLK_DIV(int diva_e)
{
	switch (diva_e)
	{
		case 1:BCSCTL1 |= DIVA_0; break;
		case 2:BCSCTL1 |= DIVA_1; break;
		case 4:BCSCTL1 |= DIVA_2; break;
		case 8:BCSCTL1 |= DIVA_3; break;
		default:BCSCTL1 |= DIVA_0; break;
	}
}

/******************************************************/
//��1������ʵ����������
/******************************************************/

void BCS_Init(int dco_x0,int mclk_a0,int divm_b0,int divs_c0,int aclk_d0,int diva_e0)
{
	DCO_Adjust(dco_x0);

	MCLK_Init(mclk_a0);

	MCLK_DIV(divm_b0);

	SMCLK_DIV(divs_c0);

	ACLK_Init(aclk_d0);

	ACLK_DIV(diva_e0);
}

/******************************************************/
//����
/******************************************************
1.MCLK=16MHz,SMCLK=16MHz,ACLK����VLO��ACLK=12kHz,1��Ƶ
  BCS_Init(16, 16, 1, 1, 1, 1);		
2.MCLK=16MHz,SMCLK=16MHz,ACLK����VLO��ACLK=6kHz��2��Ƶ
  BCS_Init(16, 16, 1, 1, 1, 2);
3.
********************************************************/

//��ʱ******************************************************
//volatile���Ϳɷ�ֹ�������Ż����´���ʧЧ

//��ʱms******

void Delay_ms(int timelong_ms)
{
	volatile int x = 0;
	volatile double y = 0;
	x = timelong_ms;
	y = CPU_freq / 1000;
	for (; x > 0; x--)
		for (; y > 0; y--);
}

//��ʱus*******

void Delay_us(int timelong_us)
{
	volatile int x = 0;
	volatile double y = 0;
	x = timelong_us;
	y = CPU_freq / 1000000;
	for (; x > 0; x--)
		for (; y > 0; y--);
}
