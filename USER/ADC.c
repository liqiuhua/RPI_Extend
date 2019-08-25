#include "ADC.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"



void ADC1_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure = {0};
     ADC_InitTypeDef ADC_InitStructure; 
  /*Configure GPIO pin */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72M/6=12M max 14M
    

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
     
     ADC_DeInit(ADC1); 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);	
     
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5 );
     ADC_Cmd(ADC1, ENABLE);
     ADC_ResetCalibration(ADC1);	
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);	
	while(ADC_GetCalibrationStatus(ADC1));
}
uint16_t getVoltage(void)//À©´ó10±¶
{
    float ADC_ConvertedValue; 
     float ADC_ConvertedValueLocal; 
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
    for(uint8_t i=0;i<3;++i)
    {
	  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )){} 
       ADC_ConvertedValue=ADC_GetConversionValue(ADC1); 
    }
    
	ADC_ConvertedValueLocal=(float)ADC_ConvertedValue*(3.3/4095.0)*53;   
    return (uint16_t)ADC_ConvertedValueLocal;
}
