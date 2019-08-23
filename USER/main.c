
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
static void AppTaskCreate (void);
void vTaskDisplayStart(void *pvParameters);
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
        xTaskCreate( vTaskDisplayStart,     		/* 任务函数  */
                 "vSystemDebugStart",   		/* 任务名    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 10,              		/* 任务优先级*/
                 NULL );   /* 任务句柄  */
    
//            xTaskCreate( vTask485,     		/* 任务函数  */
//                 "vTask485",   		/* 任务名    */
//                 64,            		/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,           		/* 任务参数  */
//                 15,              		/* 任务优先级*/
//                 NULL );   /* 任务句柄  */
//        xTaskCreate( vTaskBattery,     		/* 任务函数  */
//                 "vSystemNumDisplay",   		/* 任务名    */
//                 256,            		/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,           		/* 任务参数  */
//                 25,              		/* 任务优先级*/
//                 &xHandleTaskBattery );   /* 任务句柄  */
//        xTaskCreate( vTaskKey,     		/* 任务函数  */
//                 "vTaskKey",   		/* 任务名    */
//                 64,            		/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,           		/* 任务参数  */
//                 27,              		/* 任务优先级*/
//                 &xHandleTaskKey );   /* 任务句柄  */

}

void vTaskDisplayStart(void *pvParameters)
{
    DebugUart(115200);
    RGB_LED_init();
    RGB_LED_Set(0,0,0);
    uint32_t RGB_data=0;
    DebugPrintf("Hello RPI\n");
    NumDisplayInit();
    display();
    OLED_Init();
    PWM_OUT_1_4_Init();
    PWM_OUT_5_8_Init();
    PWM_IN_1_4_Init();
    PWM_IN_5_8_Init();
    
    PWM_OUT_5_8_out(0xff,800);
    while(1)
    {
         vTaskDelay(2000);
//          RGB_data++;
//          switch(RGB_data%3)
//          {
//              case 0:
//                  RGB_LED_Set(1,0,0);
//                    OLED_ShowString(2,2,(uint8_t *)"ST RGB R    ",16);
//                
//                  break;
//              case 1:
//                  RGB_LED_Set(0,1,0);
//                    OLED_ShowString(2,2,(uint8_t *)"ST RGB G    ",16);
//                  break;
//              case 2:
//                  RGB_LED_Set(0,0,1);
//                    OLED_ShowString(2,2,(uint8_t *)"ST RGB B    ",16);
//                  break;
//              default:
//                  RGB_data=0;
//                  RGB_LED_Set(0,0,0);
//                OLED_ShowString(2,2,(uint8_t *)"ST RGB OFF ",16);
//                  break;
//          }
           OLED_ShowNum( 2,18, getPWM_IN_1_4_ICValue(3),8,12);
           OLED_ShowNum( 2,28, getPWM_IN_1_4_ICValue(2),8,12);
           OLED_ShowNum( 2,38, getPWM_IN_1_4_ICValue(1),8,12);
           OLED_ShowNum( 2,48, getPWM_IN_1_4_ICValue(0),8,12);
           OLED_ShowNum( 70,18, getPWM_IN_5_8_ICValue(0),8,12);
           OLED_ShowNum( 70,28, getPWM_IN_5_8_ICValue(1),8,12);
           OLED_ShowNum( 70,38, getPWM_IN_5_8_ICValue(2),8,12);
           OLED_ShowNum( 70,48, getPWM_IN_5_8_ICValue(3),8,12);
           OLED_Refresh_Gram();         

    }
}
