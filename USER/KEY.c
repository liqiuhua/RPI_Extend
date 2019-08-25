#include "KEY.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

#define KEY_FOUR_PIN             GPIO_Pin_7
#define KEY_THREE_PIN            GPIO_Pin_6
#define KEY_PORT       GPIOA

static uint8_t KEY_Value = 0x00;
void KEY_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure = {0};

  /*Configure GPIO pin */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    
    GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
    GPIO_InitStructure.GPIO_Pin =  KEY_FOUR_PIN |KEY_THREE_PIN ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);

}
uint8_t getKeyStatus(void)
{

    if(GPIO_ReadInputDataBit(KEY_PORT, KEY_THREE_PIN)==RESET)
    {
        vTaskDelay(50);
        if(GPIO_ReadInputDataBit(KEY_PORT, KEY_THREE_PIN)==RESET)
        {
            KEY_Value |=KEY_THREE_CLICK;
        }
    }
    else
    {
        KEY_Value &= (~KEY_THREE_CLICK);
    }
        if(GPIO_ReadInputDataBit(KEY_PORT, KEY_FOUR_PIN)==RESET)
    {
        vTaskDelay(50);
        if(GPIO_ReadInputDataBit(KEY_PORT, KEY_FOUR_PIN)==RESET)
        {
            KEY_Value |=KEY_FOUR_CLICK;
        }
    }
    else
    {
        KEY_Value &= (~KEY_FOUR_CLICK);
    }
}
