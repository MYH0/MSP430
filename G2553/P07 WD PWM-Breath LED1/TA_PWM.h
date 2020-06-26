//1.设定死区时间***********************************************************************
#define DEADTIME 20                         //预设死区时间，以TA的clk为单位
//2.设定TA输出IO口*********************************************************************

//2-1-1.TA0.0输出口
#define TA00_P11_PWM_OUT P1SEL|=BIT1;P1DIR|=BIT1   //启用P1.1作PWM输出
#define TA00_P11_PWM_OFF P1SEL&=~BIT1			   //关闭P1.1的PWM输出

#define TA00_P15_PWM_OUT P1SEL|=BIT5;P1DIR|=BIT5   //启用P1.5作PWM输出
#define TA00_P15_PWM_OFF P1SEL&=~BIT5			   //关闭P1.5的PWM输出

//2-1-2.TA0.1输出口
#define TA01_P16_PWM_OUT P1SEL|=BIT6;P1DIR|=BIT6   //启用P1.6作PWM输出
#define TA01_P16_PWM_OFF P1SEL&=~BIT6			   //关闭P1.6的PWM输出

#define TA01_P12_PWM_OUT P1SEL|=BIT2;P1DIR|=BIT2   //启用P1.2作PWM输出
#define TA01_P12_PWM_OFF P1SEL&=~BIT2			   //关闭P1.2的PWM输出

#define TA01_P26_PWM_OUT P2SEL|=BIT6;P2DIR|=BIT6   //启用P2.6作PWM输出
#define TA01_P26_PWM_OFF P2SEL&=~BIT6			   //关闭P2.6的PWM输出

//2-1-3.TA1.0输出口
#define TA11_P20_PWM_OUT P2SEL|=BIT0;P2DIR|=BIT0   //P2.0
#define TA11_P20_PWM_OFF P2SEL&=~BIT0

#define TA11_P23_PWM_OUT P2SEL|=BIT3;P2DIR|=BIT3   //P2.3
#define TA11_P23_PWM_OFF P2SEL&=~BIT3

//2-1-4.TA1.1输出口
#define TA11_P21_PWM_OUT P2SEL|=BIT1;P2DIR|=BIT1   //P2.1
#define TA11_P21_PWM_OFF P2SEL&=~BIT1

#define TA11_P22_PWM_OUT P2SEL|=BIT2;P2DIR|=BIT2   //P2.2
#define TA11_P22_PWM_OFF P2SEL&=~BIT2

//2-1-5.TA1.2输出口
#define TA11_P24_PWM_OUT P2SEL|=BIT4;P2DIR|=BIT4   //P2.4
#define TA11_P24_PWM_OFF P2SEL&=~BIT4

#define TA11_P25_PWM_OUT P2SEL|=BIT5;P2DIR|=BIT5   //P2.5
#define TA11_P25_PWM_OFF P2SEL&=~BIT5

//3.若以TA0作为PWM的定时器*************************************************************

//3-1.设定计数模式

void TA0_PWM_MODE(int Mode1)
{
    switch (Mode1)                                                                 
    {
        case 3:
        case 7:TA0_Method(1); break;                 //普通PWM
        case 2:
        case 6:TA0_Method(3); break;                 //死区PWM
        default: break;                              
    }
}

//3-2.设定PWM通道的输出模式
/*
mode1:单稳态脉冲：(OUT控制位预先置1)--__--
mode5:单稳态脉冲：(OUT控制位预先置0)__--__
mode3:产生PWM:__--__
mode7:产生PWM:--__--
mode2:死区双路对称PWM-TACCR2：-___-
mode6:死区双路对称PWM-TACCR1：__-__
      注意！死区PWM要求TACCR1-TACCR2>DeadTime
mode4:3路方波，占空比50%，相位可调(TACCR0,TACCR1,TACCR2),OUT控制位预先置0
*/

//3-2-1.设置PWM通道1输出模式

void TA0_PWM_OUT1(int Mode1)
{
    switch (Mode1)                                     
    {
        case 3:TA0CCTL1 = OUTMOD_3; TA01_P16_PWM_OUT; break;
        case 7:TA0CCTL1 = OUTMOD_7; TA01_P16_PWM_OUT; break;
        case 6:TA0CCTL1 = OUTMOD_6; TA01_P16_PWM_OUT; break;
        case 0:TA01_P16_PWM_OFF; break;                                                              //如果设置为禁用
        default:TA01_P16_PWM_OFF; break;                                                                   //TA0.1恢复为普通IO口 
    }
}

//3-2-2.设置PWM通道2输出模式

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

//3-3.最终以TA0为定时器，初始化
//注意：TA0CCR0应<65535
//     死区周期为TA0CCR0的两倍

void TA0_PWM_Init(char ta0_clk,int ta0_div,int Mode1,int Mode2, int Period)
{
    TA0CTL =0;                                                                        // 清除以前设置
    TA0_CLK(ta0_clk);
    TA0_DIV(ta0_div);
    TA0_PWM_MODE(Mode1);
    TA0_PWM_OUT1(Mode1);
    TA0_PWM_OUT2(Mode2);
    TA0CCR0 = Period;
}

/************************************************************************************
示例：
1.使用ACLK,1分频，单路普通PWM，OUT_MOD7模式，周期为500
    TA0_PWM_Init('A', 1, 7, 0, 500);
*************************************************************************************/

//3-4.设定占空比
/******************************************************************************************************
* 名    称：TA0_PWM_SetPermill()
* 功    能：设置PWM输出的占空比(千分比),因为PWM精度至少在0.1%
* 入口参数：Channel: 当前设置的通道号 
            Duty: PWM高电平有效时间的千分比 (0~1000)，
* 说    明: 1000=100.0%  500=50.0% ，依次类推。死区模式时，两channel同时设定。
* 范    例: TA0_PWM_SetPermill(1,300)设置PWM通道1方波的占空比为30.0%
            TA0_PWM_SetPermill(2,,825)设置PWM通道2方波的占空比为82.5%
 ******************************************************************************************************/

void TA0_PWM_SetPermill(int Channel,lint Duty)
{
    int mode = 0;
    int DeadPermill = 0;
    DeadPermill = ((DEADTIME * 1000) / TA0CCR0);       //将绝对死区时间换算成千分比死区时间
    switch (Channel)                                   //先判断出通道的工作模式
    {
        case 1:mode = (TA0CCTL1 & 0x00e0) >> 5; break;  //读取输出模式，OUT_MOD0位于5-7位
        case 2:mode = (TA0CCTL2 & 0x00e0) >> 5; break;  //读取输出模式，OUT_MOD1位于5-7位           
        default:break;
    }

    switch(mode)        //根据模式设定TACCRx
    {
        case 2: 
        case 6:         //死区模式2,6时，需要判断修正死区时间，且同时设定TA0CCR1/2 的值
        {
            if ((1000 - 2 * Duty) <= DeadPermill)           //预留死区时间
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
        case 3:     //占空比一律为正脉宽，所以需要 TA0CCR0减去占空比
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

//3-5.PWM呼吸灯亮度调节
//占空比>40%时，亮度变化不明显

void T0_PWM_Breath_Bright()
{
    static int bright = 0;                             
    static int bright_flag = 0;             //判断增加/减少亮度;0增1减
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


//4.以TA1作为PWM的定时器****************************************************************

//4-1.设定计数模式

void TA1_PWM_MODE(int Mode1)
{
    switch (Mode1)
    {
    case 3:
    case 7:TA1_Method(1); break;                 //普通PWM
    case 2:
    case 6:TA1_Method(3); break;                 //死区PWM
    default: break;
    }
}

//4-2.设定PWM通道的输出模式
/*
mode1:单稳态脉冲：(OUT控制位预先置1)--__--
mode5:单稳态脉冲：(OUT控制位预先置0)__--__
mode3:产生PWM:__--__
mode7:产生PWM:--__--
mode2:死区双路对称PWM-TACCR2：-___-
mode6:死区双路对称PWM-TACCR1：__-__
      注意！死区PWM要求TACCR1-TACCR2>DeadTime
mode4:3路方波，占空比50%，相位可调(TACCR0,TACCR1,TACCR2),OUT控制位预先置0
*/

//4-2-1.设置PWM通道1输出模式

void TA1_PWM_OUT1(int Mode1)
{
    switch (Mode1)
    {
    case 3:TA1CCTL1 = OUTMOD_3; TA01_P16_PWM_OUT; break;
    case 7:TA1CCTL1 = OUTMOD_7; TA01_P16_PWM_OUT; break;
    case 6:TA1CCTL1 = OUTMOD_6; TA01_P16_PWM_OUT; break;
    case 0:TA01_P16_PWM_OFF; break;                                                              //如果设置为禁用
    default:TA01_P16_PWM_OFF; break;                                                                   //TA0.1恢复为普通IO口 
    }
}

//4-2-2.设置PWM通道2输出模式

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

//4-3.最终以TA1为定时器，初始化
//注意：TA1CCR0应<65535
//     死区周期为TA0CCR0的两倍

void TA1_PWM_Init(char ta1_clk, int ta1_div, int Mode1, int Mode2, int Period)
{
    //TA1CTL = 0;                                                                   // 清除以前设置
    TA1_CLK(ta1_clk);
    TA1_DIV(ta1_div);
    TA1_PWM_MODE(Mode1);
    TA1_PWM_OUT1(Mode1);
    TA1_PWM_OUT2(Mode2);
    TA1CCR0 = Period;
}

//4-4.设置PWM输出的占空比(千分比)
/******************************************************************************************************
* 名    称：TA1_PWM_SetPermill()
* 功    能：设置PWM输出的占空比(千分比)
* 入口参数：Channel: 当前设置的通道号  1/2
            Duty: PWM高电平有效时间的千分比 (0~1000)，
* 出口参数：1设置成功，0设置失败
* 说    明: 1000=100.0%  500=50.0% ，依次类推。死区模式时，两channel同时设定。
* 范    例: TA_PWM_SetPermill(1,300)设置PWM通道1方波的占空比为30.0%
               TA_PWM_SetPermill(2,,825)设置PWM通道2方波的占空比为82.5%
 ******************************************************************************************************/
void TA1_PWM_SetPermill(int Channel, lint Duty)
{
    int mode = 0;
    int DeadPermill = 0;
    DeadPermill = ((DEADTIME * 1000) / TA1CCR0);       //将绝对死区时间换算成千分比死区时间
    switch (Channel)                                   //先判断出通道的工作模式
    {
    case 1:mode = (TA1CCTL1 & 0x00e0) >> 5; break;  //读取输出模式，OUT_MOD0位于5-7位
    case 2:mode = (TA1CCTL2 & 0x00e0) >> 5; break;  //读取输出模式，OUT_MOD1位于5-7位           
    default:break;
    }

    switch (mode)        //根据模式设定TACCRx
    {
    case 2:
    case 6:         //死区模式2,6时，需要判断修正死区时间，且同时设定TA0CCR1/2 的值
    {
        if ((1000 - 2 * Duty) <= DeadPermill)           //预留死区时间
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
    case 3:     //占空比一律为正脉宽，所以需要 TA0CCR0减去占空比
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

//4-5.PWM呼吸灯亮度调节
//占空比>40%时，亮度变化不明显
//推荐PWM周期为50，ACLK=6kHz

void T1_PWM_Breath_Bright()
{
    static int bright = 0;
    static int bright_flag = 0;             //判断增加/减少亮度;0增1减
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

