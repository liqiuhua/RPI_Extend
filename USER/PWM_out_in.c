
#include "stm32f10x.h"
#include "oled.h"
void PWM_OUT_1_4_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    TIM_TimeBaseStructure.TIM_Prescaler=1;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period=20000;
    
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 5000;
    
    TIM_OC1Init(TIM4,&TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
    TIM_OC2Init(TIM4,&TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
    TIM_OC3Init(TIM4,&TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
    TIM_OC4Init(TIM4,&TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
    
    TIM_ARRPreloadConfig(TIM4,ENABLE);
    TIM_Cmd(TIM4,ENABLE);
    
    
}
void PWM_OUT_1_4_out(uint8_t ch,uint16_t data)
{
    if(data>20000)
        data=20000;
    switch(ch)
    {
        case 4:
            TIM4->CCR1=data; 
        break;
        case 3:
            TIM4->CCR2=data; 
        break;
        case 2:
            TIM4->CCR3=data; 
        break;
        case 1:
            TIM4->CCR4=data; 
        break;
        case 0xff:
         TIM4->CCR1=data; 
        TIM4->CCR2=data; 
        TIM4->CCR3=data; 
        TIM4->CCR4=data; 
            break;
        default:
        break;
    }
    TIM_SetAutoreload(TIM4,20000);
}
void PWM_OUT_5_8_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    TIM_TimeBaseStructure.TIM_Prescaler=71;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period=20000;
    
    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 5000;
    
    TIM_OC1Init(TIM5,&TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
    TIM_OC2Init(TIM5,&TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
    TIM_OC3Init(TIM5,&TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);
    TIM_OC4Init(TIM5,&TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
    
    TIM_ARRPreloadConfig(TIM5,ENABLE);
    TIM_Cmd(TIM5,ENABLE);
}
void PWM_OUT_5_8_out(uint8_t ch,uint16_t data)
{
    if(data>20000)
        data=20000;
    switch(ch)
    {
        case 1:
            TIM5->CCR1=data; 
        break;
        case 2:
            TIM5->CCR2=data; 
        break;
        case 3:
            TIM5->CCR3=data; 
        break;
        case 4:
            TIM5->CCR4=data; 
        break;
        case 0xff:
         TIM5->CCR1=data; 
        TIM5->CCR2=data; 
        TIM5->CCR3=data; 
        TIM5->CCR4=data; 
            break;
        default:
        break;
    }
    TIM_SetAutoreload(TIM5,20000);
}
static uint16_t  TIM3_IC_Value[4];
void PWM_IN_1_4_Init(void)
{
      NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;			//定义TME3信息结构体;
  TIM_ICInitTypeDef  TIM3_ICInitStructure;
    /* Peripheral clock enable */
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /**TIM3 GPIO Configuration    
    PC6     ------> TIM3_CH1
    PC7     ------> TIM3_CH2
    PC8     ------> TIM3_CH3
    PC9     ------> TIM3_CH4 
    */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
  
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF; 	     //自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=8;      //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	//TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	
    
    
        /* TIM3 interrupt Init */
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x06; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
	//初始化TIM3输入捕获参数
    
    TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
    TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
    TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
    
    TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
    TIM_ICInit(TIM3, &TIM3_ICInitStructure);
    
    TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM3, &TIM3_ICInitStructure);
    TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM3, &TIM3_ICInitStructure);
    TIM3_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM3, &TIM3_ICInitStructure);
    
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
    
    TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3
}
void TIM3_IRQHandler(void)
{
   
    static uint16_t ICValuePre[4],ICValueLast[4];
    static uint8_t ChannelTrig=0x0f;//bit0-bit3 表示 通道1-通道4 , set 表示上升沿，reset表示下降沿
    if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
    {   
        if((ChannelTrig&0x01))
        {
            ChannelTrig&=(~0x01);
            ICValuePre[0] = TIM3->CCR1;
            TIM3->CCER |=(1<<1);
        }
       else
       {
            ChannelTrig|=0x01;
            ICValueLast[0] = TIM3->CCR1;//TIM_GetCapture4(TIM3); 
            TIM3->CCER &=~(1<<1);
            if(ICValuePre[0]>ICValueLast[0])       
            {
                TIM3_IC_Value[0] =65535-ICValuePre[0]+ICValueLast[0];
            }
            else
            {                   
                TIM3_IC_Value[0] = ICValueLast[0]-ICValuePre[0];
            }
        }  
        TIM3->SR &=(~TIM_FLAG_CC1) ;

    }
    if(TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
    {   
        if((ChannelTrig&0x02))
        {
            ChannelTrig&=(~0x02);
            ICValuePre[1] = TIM3->CCR2;
            TIM3->CCER |=(1<<5);
        }
       else
       {
            ChannelTrig|=0x02;
            ICValueLast[1] = TIM3->CCR2;//TIM_GetCapture4(TIM3); 
            TIM3->CCER &=~(1<<5);
            if(ICValuePre[1]>ICValueLast[1])       
            {
                TIM3_IC_Value[1] =65535-ICValuePre[1]+ICValueLast[1];
            }
            else
            {                   
                TIM3_IC_Value[1] = ICValueLast[1]-ICValuePre[1];
            }
        }            
        TIM3->SR &=(~TIM_FLAG_CC2) ;

    }
    if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
    {   
        if((ChannelTrig&0x04))
        {
            ChannelTrig&=(~0x04);
            ICValuePre[2] = TIM3->CCR3;
            TIM3->CCER |=(1<<9);
        }
       else
       {
            ChannelTrig|=0x04;
            ICValueLast[2] = TIM3->CCR3;//TIM_GetCapture4(TIM3); 
            TIM3->CCER &=~(1<<9);
            if(ICValuePre[2]>ICValueLast[2])       
            {
                TIM3_IC_Value[2] =65535-ICValuePre[2]+ICValueLast[2];
            }
            else
            {                   
                TIM3_IC_Value[2] = ICValueLast[2]-ICValuePre[2];
            }
        }
        TIM3->SR &=(~TIM_FLAG_CC3) ;

    }
        if(TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
    {   
        
        
        if((ChannelTrig&0x08))
        {
            ChannelTrig&=(~0x08);
            ICValuePre[3] = TIM3->CCR4;//TIM_GetCapture4(TIM3);  
            TIM3->CCER |=(1<<13);
        }
       else
       {
            ChannelTrig|=0x08;
            ICValueLast[3] = TIM3->CCR4;//TIM_GetCapture4(TIM3); 
             TIM3->CCER &=~(1<<13);
            if(ICValuePre[3]>ICValueLast[3])       
            {
                TIM3_IC_Value[3] =65535-ICValuePre[3]+ICValueLast[3];
            }
            else
            {                   
                TIM3_IC_Value[3] = ICValueLast[3]-ICValuePre[3];
            }
       }

        TIM3->SR &=(~TIM_FLAG_CC4) ;

    }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

uint16_t getPWM_IN_1_4_ICValue(uint8_t channel)
{
    if(channel>3)
        return 0;
        
    return TIM3_IC_Value[channel];
}
static uint16_t  TIM2_IC_Value[4];
void PWM_IN_5_8_Init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;			//定义TME3信息结构体;
  TIM_ICInitTypeDef  TIM2_ICInitStructure;
    /* Peripheral clock enable */
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); 
  
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_3| GPIO_Pin_10| GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF; 	     //自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=8;      //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM2
	
	//TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	
    
    
        /* TIM3 interrupt Init */
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x07; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
	//初始化TIM3输入捕获参数
    
    TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
    TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
    TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
    
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
    
    TIM_Cmd(TIM2,ENABLE ); 	//使能定时器3
}
uint16_t getPWM_IN_5_8_ICValue(uint8_t channel)
{
    if(channel>3)
        return 0;
        
    return TIM2_IC_Value[channel];
}
void TIM2_IRQHandler(void)
{
   
    static uint16_t ICValuePre[4],ICValueLast[4];
    static uint8_t ChannelTrig=0x0f;//bit0-bit3 表示 通道1-通道4 , set 表示上升沿，reset表示下降沿
    if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
    {   
        if((ChannelTrig&0x01))
        {
            ChannelTrig&=(~0x01);
            ICValuePre[0] = TIM2->CCR1;
            TIM2->CCER |=(1<<1);
        }
       else
       {
            ChannelTrig|=0x01;
            ICValueLast[0] = TIM2->CCR1;
            TIM2->CCER &=~(1<<1);
            if(ICValuePre[0]>ICValueLast[0])       
            {
                TIM2_IC_Value[0] =65535-ICValuePre[0]+ICValueLast[0];
            }
            else
            {                   
                TIM2_IC_Value[0] = ICValueLast[0]-ICValuePre[0];
            }
        }  
        TIM2->SR &=(~TIM_FLAG_CC1) ;

    }
    if(TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
    {   
        if((ChannelTrig&0x02))
        {
            ChannelTrig&=(~0x02);
            ICValuePre[1] = TIM2->CCR2;
            TIM2->CCER |=(1<<5);
        }
       else
       {
            ChannelTrig|=0x02;
            ICValueLast[1] = TIM2->CCR2;
            TIM2->CCER &=~(1<<5);
            if(ICValuePre[1]>ICValueLast[1])       
            {
                TIM2_IC_Value[1] =65535-ICValuePre[1]+ICValueLast[1];
            }
            else
            {                   
                TIM2_IC_Value[1] = ICValueLast[1]-ICValuePre[1];
            }
        }            
        TIM2->SR &=(~TIM_FLAG_CC2) ;

    }
    if(TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
    {   
        if((ChannelTrig&0x04))
        {
            ChannelTrig&=(~0x04);
            ICValuePre[2] = TIM2->CCR3;
            TIM2->CCER |=(1<<9);
        }
       else
       {
            ChannelTrig|=0x04;
            ICValueLast[2] = TIM2->CCR3;
            TIM2->CCER &=~(1<<9);
            if(ICValuePre[2]>ICValueLast[2])       
            {
                TIM2_IC_Value[2] =65535-ICValuePre[2]+ICValueLast[2];
            }
            else
            {                   
                TIM2_IC_Value[2] = ICValueLast[2]-ICValuePre[2];
            }
        }
        TIM2->SR &=(~TIM_FLAG_CC3) ;

    }
        if(TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)
    {   
        
        
        if((ChannelTrig&0x08))
        {
            ChannelTrig&=(~0x08);
            ICValuePre[3] = TIM2->CCR4;
            TIM2->CCER |=(1<<13);
        }
       else
       {
            ChannelTrig|=0x08;
            ICValueLast[3] = TIM2->CCR4;
            TIM2->CCER &=~(1<<13);
            if(ICValuePre[3]>ICValueLast[3])       
            {
                TIM2_IC_Value[3] =65535-ICValuePre[3]+ICValueLast[3];
            }
            else
            {                   
                TIM2_IC_Value[3] = ICValueLast[3]-ICValuePre[3];
            }
       }

        TIM2->SR &=(~TIM_FLAG_CC4) ;

    }
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}