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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //AFIO���ù���ģ��ʱ��

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);

      
    GPIO_InitStruct.GPIO_Pin =   GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    
    TIM_TimeBaseStructure.TIM_Prescaler=5;//13;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period =4000;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��

	//��ʼ��TIM4 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_Pulse = 2000;

    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4OC2
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR2�ϵ�Ԥװ�ؼĴ���
 	
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4OC3
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
 	
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4OC4
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR4�ϵ�Ԥװ�ؼĴ���
    TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��
    TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
   
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