//1.�趨����ʱ��***********************************************************************
#define DEADTIME 20                         //Ԥ������ʱ�䣬��TA��clkΪ��λ
//2.�趨TA���IO��*********************************************************************

//2-1-1.TA0.0�����
#define TA00_P11_PWM_OUT P1SEL|=BIT1;P1DIR|=BIT1   //����P1.1��PWM���
#define TA00_P11_PWM_OFF P1SEL&=~BIT1			   //�ر�P1.1��PWM���

#define TA00_P15_PWM_OUT P1SEL|=BIT5;P1DIR|=BIT5   //����P1.5��PWM���
#define TA00_P15_PWM_OFF P1SEL&=~BIT5			   //�ر�P1.5��PWM���

//2-1-2.TA0.1�����
#define TA01_P16_PWM_OUT P1SEL|=BIT6;P1DIR|=BIT6   //����P1.6��PWM���
#define TA01_P16_PWM_OFF P1SEL&=~BIT6			   //�ر�P1.6��PWM���

#define TA01_P12_PWM_OUT P1SEL|=BIT2;P1DIR|=BIT2   //����P1.2��PWM���
#define TA01_P12_PWM_OFF P1SEL&=~BIT2			   //�ر�P1.2��PWM���

#define TA01_P26_PWM_OUT P2SEL|=BIT6;P2DIR|=BIT6   //����P2.6��PWM���
#define TA01_P26_PWM_OFF P2SEL&=~BIT6			   //�ر�P2.6��PWM���

//2-1-3.TA1.0�����
#define TA11_P20_PWM_OUT P2SEL|=BIT0;P2DIR|=BIT0   //P2.0
#define TA11_P20_PWM_OFF P2SEL&=~BIT0

#define TA11_P23_PWM_OUT P2SEL|=BIT3;P2DIR|=BIT3   //P2.3
#define TA11_P23_PWM_OFF P2SEL&=~BIT3

//2-1-4.TA1.1�����
#define TA11_P21_PWM_OUT P2SEL|=BIT1;P2DIR|=BIT1   //P2.1
#define TA11_P21_PWM_OFF P2SEL&=~BIT1

#define TA11_P22_PWM_OUT P2SEL|=BIT2;P2DIR|=BIT2   //P2.2
#define TA11_P22_PWM_OFF P2SEL&=~BIT2

//2-1-5.TA1.2�����
#define TA11_P24_PWM_OUT P2SEL|=BIT4;P2DIR|=BIT4   //P2.4
#define TA11_P24_PWM_OFF P2SEL&=~BIT4

#define TA11_P25_PWM_OUT P2SEL|=BIT5;P2DIR|=BIT5   //P2.5
#define TA11_P25_PWM_OFF P2SEL&=~BIT5

//3.����TA0��ΪPWM�Ķ�ʱ��*************************************************************

//3-1.�趨����ģʽ

void TA0_PWM_MODE(int Mode1)
{
    switch (Mode1)                                                                 
    {
        case 3:
        case 7:TA0_Method(1); break;                 //��ͨPWM
        case 2:
        case 6:TA0_Method(3); break;                 //����PWM
        default: break;                              
    }
}

//3-2.�趨PWMͨ�������ģʽ
/*
mode1:����̬���壺(OUT����λԤ����1)--__--
mode5:����̬���壺(OUT����λԤ����0)__--__
mode3:����PWM:__--__
mode7:����PWM:--__--
mode2:����˫·�Գ�PWM-TACCR2��-___-
mode6:����˫·�Գ�PWM-TACCR1��__-__
      ע�⣡����PWMҪ��TACCR1-TACCR2>DeadTime
mode4:3·������ռ�ձ�50%����λ�ɵ�(TACCR0,TACCR1,TACCR2),OUT����λԤ����0
*/

//3-2-1.����PWMͨ��1���ģʽ

void TA0_PWM_OUT1(int Mode1)
{
    switch (Mode1)                                     
    {
        case 3:TA0CCTL1 = OUTMOD_3; TA01_P16_PWM_OUT; break;
        case 7:TA0CCTL1 = OUTMOD_7; TA01_P16_PWM_OUT; break;
        case 6:TA0CCTL1 = OUTMOD_6; TA01_P16_PWM_OUT; break;
        case 0:TA01_P16_PWM_OFF; break;                                                              //�������Ϊ����
        default:TA01_P16_PWM_OFF; break;                                                                   //TA0.1�ָ�Ϊ��ͨIO�� 
    }
}

//3-2-2.����PWMͨ��2���ģʽ

void TA0_PWM_OUT2(int Mode2)
{
    switch (Mode2)                     
    {
        case 3:TA0CCTL2 = OUTMOD_3; TA00_P15_PWM_OUT; break;
        case 7:TA0CCTL2 = OUTMOD_7; TA00_P15_PWM_OUT;  break;
        case 2:TA0CCTL2 = OUTMOD_2; TA00_P15_PWM_OUT; break;
        case 0:TA00_P15_PWM_OFF; break;
        default:break;
    }
}

//3-3.������TA0Ϊ��ʱ������ʼ��
//ע�⣺TA0CCR0Ӧ<65535
//     ��������ΪTA0CCR0������

void TA0_PWM_Init(char ta0_clk,int ta0_div,int Mode1,int Mode2, int Period)
{
    TA0CTL =0;                                                                        // �����ǰ����
    TA0_CLK(ta0_clk);
    TA0_DIV(ta0_div);
    TA0_PWM_MODE(Mode1);
    TA0_PWM_OUT1(Mode1);
    TA0_PWM_OUT2(Mode2);
    TA0CCR0 = Period;
}

/************************************************************************************
ʾ����
1.ʹ��ACLK,1��Ƶ����·��ͨPWM��OUT_MOD7ģʽ������Ϊ500
    TA0_PWM_Init('A', 1, 7, 0, 500);
*************************************************************************************/

//3-4.�趨ռ�ձ�
/******************************************************************************************************
* ��    �ƣ�TA0_PWM_SetPermill()
* ��    �ܣ�����PWM�����ռ�ձ�(ǧ�ֱ�),��ΪPWM����������0.1%
* ��ڲ�����Channel: ��ǰ���õ�ͨ���� 
            Duty: PWM�ߵ�ƽ��Чʱ���ǧ�ֱ� (0~1000)��
* ˵    ��: 1000=100.0%  500=50.0% ���������ơ�����ģʽʱ����channelͬʱ�趨��
* ��    ��: TA0_PWM_SetPermill(1,300)����PWMͨ��1������ռ�ձ�Ϊ30.0%
            TA0_PWM_SetPermill(2,,825)����PWMͨ��2������ռ�ձ�Ϊ82.5%
 ******************************************************************************************************/

void TA0_PWM_SetPermill(int Channel,lint Duty)
{
    int mode = 0;
    int DeadPermill = 0;
    DeadPermill = ((DEADTIME * 1000) / TA0CCR0);       //����������ʱ�任���ǧ�ֱ�����ʱ��
    switch (Channel)                                   //���жϳ�ͨ���Ĺ���ģʽ
    {
        case 1:mode = (TA0CCTL1 & 0x00e0) >> 5; break;  //��ȡ���ģʽ��OUT_MOD0λ��5-7λ
        case 2:mode = (TA0CCTL2 & 0x00e0) >> 5; break;  //��ȡ���ģʽ��OUT_MOD1λ��5-7λ           
        default:break;
    }

    switch(mode)        //����ģʽ�趨TACCRx
    {
        case 2: 
        case 6:         //����ģʽ2,6ʱ����Ҫ�ж���������ʱ�䣬��ͬʱ�趨TA0CCR1/2 ��ֵ
        {
            if ((1000 - 2 * Duty) <= DeadPermill)           //Ԥ������ʱ��
                Duty = (1000 - DeadPermill) / 2;
            TA0CCR1 = Duty * TA0CCR0 / 1000;
            TA0CCR2 = TA0CCR0 - TA0CCR1;
            break;
        }
        case 7:
        {
            if (Duty > 1000)
                Duty = 1000;
            if (Channel == 1)
                TA0CCR1 = TA0CCR0 * Duty / 1000;
            if (Channel == 2) 
                TA0CCR2 = TA0CCR0 * Duty / 1000;
            break;
        }
        case 3:     //ռ�ձ�һ��Ϊ������������Ҫ TA0CCR0��ȥռ�ձ�
        {
            if (Duty > 1000)
                Duty = 1000;
            if (Channel == 1)
                TA0CCR1 = TA0CCR0 * (1 - Duty / 1000);
            if (Channel == 2) 
                TA0CCR2 = TA0CCR0 * (1 - Duty / 1000);
            break;
        }
        default: break;
    }
}

//3-5.PWM���������ȵ���
//ռ�ձ�>40%ʱ�����ȱ仯������

void T0_PWM_Breath_Bright()
{
    static int bright = 0;                             
    static int bright_flag = 0;             //�ж�����/��������;0��1��
    TA0_PWM_SetPermill(1, bright);
    if (bright <= 0)
        bright_flag = 0;
    if (bright >= 400)
        bright_flag = 1;
    if (bright_flag == 0)
        bright = bright + 2;
    if (bright_flag == 1)
        bright = bright - 2;

}


//4.��TA1��ΪPWM�Ķ�ʱ��****************************************************************

//4-1.�趨����ģʽ

void TA1_PWM_MODE(int Mode1)
{
    switch (Mode1)
    {
    case 3:
    case 7:TA1_Method(1); break;                 //��ͨPWM
    case 2:
    case 6:TA1_Method(3); break;                 //����PWM
    default: break;
    }
}

//4-2.�趨PWMͨ�������ģʽ
/*
mode1:����̬���壺(OUT����λԤ����1)--__--
mode5:����̬���壺(OUT����λԤ����0)__--__
mode3:����PWM:__--__
mode7:����PWM:--__--
mode2:����˫·�Գ�PWM-TACCR2��-___-
mode6:����˫·�Գ�PWM-TACCR1��__-__
      ע�⣡����PWMҪ��TACCR1-TACCR2>DeadTime
mode4:3·������ռ�ձ�50%����λ�ɵ�(TACCR0,TACCR1,TACCR2),OUT����λԤ����0
*/

//4-2-1.����PWMͨ��1���ģʽ

void TA1_PWM_OUT1(int Mode1)
{
    switch (Mode1)
    {
    case 3:TA1CCTL1 = OUTMOD_3; TA01_P16_PWM_OUT; break;
    case 7:TA1CCTL1 = OUTMOD_7; TA01_P16_PWM_OUT; break;
    case 6:TA1CCTL1 = OUTMOD_6; TA01_P16_PWM_OUT; break;
    case 0:TA01_P16_PWM_OFF; break;                                                              //�������Ϊ����
    default:TA01_P16_PWM_OFF; break;                                                                   //TA0.1�ָ�Ϊ��ͨIO�� 
    }
}

//4-2-2.����PWMͨ��2���ģʽ

void TA1_PWM_OUT2(int Mode2)
{
    switch (Mode2)
    {
    case 3:TA1CCTL2 = OUTMOD_3; TA00_P15_PWM_OUT; break;
    case 7:TA1CCTL2 = OUTMOD_7; TA00_P15_PWM_OUT;  break;
    case 2:TA1CCTL2 = OUTMOD_2; TA00_P15_PWM_OUT; break;
    case 0:TA00_P15_PWM_OFF; break;
    default:break;
    }
}

//4-3.������TA1Ϊ��ʱ������ʼ��
//ע�⣺TA1CCR0Ӧ<65535
//     ��������ΪTA0CCR0������

void TA1_PWM_Init(char ta1_clk, int ta1_div, int Mode1, int Mode2, int Period)
{
    //TA1CTL = 0;                                                                   // �����ǰ����
    TA1_CLK(ta1_clk);
    TA1_DIV(ta1_div);
    TA1_PWM_MODE(Mode1);
    TA1_PWM_OUT1(Mode1);
    TA1_PWM_OUT2(Mode2);
    TA1CCR0 = Period;
}

//4-4.����PWM�����ռ�ձ�(ǧ�ֱ�)
/******************************************************************************************************
* ��    �ƣ�TA1_PWM_SetPermill()
* ��    �ܣ�����PWM�����ռ�ձ�(ǧ�ֱ�)
* ��ڲ�����Channel: ��ǰ���õ�ͨ����  1/2
            Duty: PWM�ߵ�ƽ��Чʱ���ǧ�ֱ� (0~1000)��
* ���ڲ�����1���óɹ���0����ʧ��
* ˵    ��: 1000=100.0%  500=50.0% ���������ơ�����ģʽʱ����channelͬʱ�趨��
* ��    ��: TA_PWM_SetPermill(1,300)����PWMͨ��1������ռ�ձ�Ϊ30.0%
               TA_PWM_SetPermill(2,,825)����PWMͨ��2������ռ�ձ�Ϊ82.5%
 ******************************************************************************************************/
void TA1_PWM_SetPermill(int Channel, lint Duty)
{
    int mode = 0;
    int DeadPermill = 0;
    DeadPermill = ((DEADTIME * 1000) / TA1CCR0);       //����������ʱ�任���ǧ�ֱ�����ʱ��
    switch (Channel)                                   //���жϳ�ͨ���Ĺ���ģʽ
    {
    case 1:mode = (TA1CCTL1 & 0x00e0) >> 5; break;  //��ȡ���ģʽ��OUT_MOD0λ��5-7λ
    case 2:mode = (TA1CCTL2 & 0x00e0) >> 5; break;  //��ȡ���ģʽ��OUT_MOD1λ��5-7λ           
    default:break;
    }

    switch (mode)        //����ģʽ�趨TACCRx
    {
    case 2:
    case 6:         //����ģʽ2,6ʱ����Ҫ�ж���������ʱ�䣬��ͬʱ�趨TA0CCR1/2 ��ֵ
    {
        if ((1000 - 2 * Duty) <= DeadPermill)           //Ԥ������ʱ��
            Duty = (1000 - DeadPermill) / 2;
        TA1CCR1 = Duty * TA1CCR0 / 1000;
        TA1CCR2 = TA1CCR0 - TA1CCR1;
        break;
    }
    case 7:
    {
        if (Duty > 1000)
            Duty = 1000;
        if (Channel == 1)
            TA1CCR1 = TA1CCR0 * Duty / 1000;
        if (Channel == 2)
            TA1CCR2 = TA1CCR0 * Duty / 1000;
        break;
    }
    case 3:     //ռ�ձ�һ��Ϊ������������Ҫ TA0CCR0��ȥռ�ձ�
    {
        if (Duty > 1000)
            Duty = 1000;
        if (Channel == 1)
            TA1CCR1 = TA1CCR0 * (1 - Duty / 1000);
        if (Channel == 2)
            TA1CCR2 = TA1CCR0 * (1 - Duty / 1000);
        break;
    }
    default: break;
    }
}

//4-5.PWM���������ȵ���
//ռ�ձ�>40%ʱ�����ȱ仯������
//�Ƽ�PWM����Ϊ50��ACLK=6kHz

void T1_PWM_Breath_Bright()
{
    static int bright = 0;
    static int bright_flag = 0;             //�ж�����/��������;0��1��
    TA1_PWM_SetPermill(1, bright);
    if (bright <= 0)
        bright_flag = 0;
    if (bright >= 400)
        bright_flag = 1;
    if (bright_flag == 0)
        bright = bright + 2;
    if (bright_flag == 1)
        bright = bright - 2;

}

