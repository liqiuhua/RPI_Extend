#include "stm32f10x.h"
#include "Debug.h"
void RGB_LED_PWM_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
//    /* Peripheral clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //AFIO复用功能模块时钟

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);

      
    GPIO_InitStruct.GPIO_Pin =   GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    
    TIM_TimeBaseStructure.TIM_Prescaler=5;//13;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_Period =4000;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化定时器

	//初始化TIM4 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OCInitStructure.TIM_Pulse = 2000;

    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4OC2
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM4在CCR2上的预装载寄存器
 	
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4OC3
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM4在CCR3上的预装载寄存器
 	
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4OC4
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM4在CCR4上的预装载寄存器
    TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能
    TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
   
}
void RGB_LED_Set_PWM(uint8_t R_data,uint8_t G_data,uint8_t B_data)
{
        
        TIM1->CCR2=(uint16_t)((R_data/255.0*4000)); 
        TIM1->CCR3=(uint16_t)((G_data/255.0*4000)); 
        TIM1->CCR4=(uint16_t)((B_data/255.0*4000)); 
        


    TIM_SetAutoreload(TIM1,40000);
}

void RGB_LED_init(void)
{
        GPIO_InitTypeDef GPIO_InitStruct = {0};
//    /* Peripheral clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);


      
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
}
void RGB_LED_Set(uint8_t R_data,uint8_t G_data,uint8_t B_data)
{
    R_data>0?GPIO_ResetBits(GPIOE,GPIO_Pin_13):GPIO_SetBits(GPIOE,GPIO_Pin_13);
    G_data>0?GPIO_ResetBits(GPIOE,GPIO_Pin_14):GPIO_SetBits(GPIOE,GPIO_Pin_14);
    B_data>0?GPIO_ResetBits(GPIOE,GPIO_Pin_11):GPIO_SetBits(GPIOE,GPIO_Pin_11);
}