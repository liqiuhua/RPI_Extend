
#include "stm32f10x.h"
#include "RGB_LED.h"
#include "Debug.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "NumDisplay.h"
#include "oled.h"
#include "PWM_out_in.h"
#include "RCCar.h"
#include "KEY.h"
#include "ADC.h"
static void AppTaskCreate (void);
void vInteractionStart(void *pvParameters);
int main(void)
{
    SystemInit();
    __set_PRIMASK(1);

            
  AppTaskCreate ();  
    
    /* 启动调度， 开始执行任务 */
    vTaskStartScheduler();    
    
    while(1)
    {
    }
}
static void AppTaskCreate (void)
{
		DebugUart(115200);

    
        xTaskCreate( vRCStart,     		/* 任务函数  */
                 "vRCStart",   		/* 任务名    */
                 512,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 20,              		/* 任务优先级*/
                 &xHandleTaskRC );   /* 任务句柄  */
                 
        xTaskCreate( vInteractionStart,     		/* 任务函数  */
                 "vInteractionStart",   		/* 任务名    */
                 512,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 12,              		/* 任务优先级*/
                 NULL );   /* 任务句柄  */

}
void vInteractionStart(void *pvParameters)
{

        RGB_LED_init();
    RGB_LED_Set(0,0,0);
    DebugPrintf("Hello RPI\n");
    NumDisplayInit();
    display(0);
    OLED_Init();
    KEY_Init();
    ADC1_Init();
    uint8_t key_value=0;
    uint16_t count=0;
    uint8_t GUI_Page=0;
    while(1)
    {
        vTaskDelay(5);
        count++;
        key_value=getKeyStatus();
        if(key_value!=0)
        {
             if(key_value&KEY_THREE_CLICK)
            {
                if(GUI_Page>=2){GUI_Page=2;}
                else{GUI_Page++;}                                 
  
            }
            if(key_value&KEY_FOUR_CLICK)
            {
                if(GUI_Page<=1){GUI_Page=0;}  
                else{ GUI_Page--;}
                                  
  
            }
        }		
        if(count>200)
        {
            count=0;
            if(GUI_Page==1){
               OLED_ShowString(0,0,(uint8_t *)"RC Control data",32);
               OLED_ShowNum( 2,18, getPWM_IN_1_4_ICValue(3),8,12);
               OLED_ShowNum( 2,28, getPWM_IN_1_4_ICValue(2),8,12);
               OLED_ShowNum( 2,38, getPWM_IN_1_4_ICValue(1),8,12);
               OLED_ShowNum( 2,48, getPWM_IN_1_4_ICValue(0),8,12);
               OLED_ShowNum( 70,18, getPWM_IN_5_8_ICValue(0),8,12); 
               OLED_ShowNum( 70,28, getPWM_IN_5_8_ICValue(2),8,12);
               OLED_ShowNum( 70,38, getPWM_IN_5_8_ICValue(3),8,12);
               OLED_ShowNum( 70,48, getPWM_IN_5_8_ICValue(1),8,12);
            }else if(GUI_Page==2)
            {
               OLED_ShowString(0,0,(uint8_t *)"RC Car output data",32);
               OLED_ShowNum( 2,18, getRCControlData(THROTTLE_CH),8,12);
               OLED_ShowNum( 2,28, getRCControlData(LEFT_CH),8,12);
               OLED_ShowNum( 2,38, getRCControlData(RIGHT_CH),8,12);
               OLED_ShowNum( 2,48, getRCControlData(TRAVEL_DIRECTION_CH),8,12);
//               OLED_ShowNum( 70,18, getPWM_IN_5_8_ICValue(0),8,12); 
//               OLED_ShowNum( 70,28, getPWM_IN_5_8_ICValue(2),8,12);
//               OLED_ShowNum( 70,38, getPWM_IN_5_8_ICValue(3),8,12);
//               OLED_ShowNum( 70,48, getPWM_IN_5_8_ICValue(1),8,12);
            }else 
            {
                
            }
           OLED_Refresh_Gram();  
            display(getVoltage());

            
            
        }
				

    }

}


