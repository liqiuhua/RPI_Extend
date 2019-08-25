#ifndef __RCCAR_H_
#define __RCCAR_H_

#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#define THROTTLE_CH                 1    
#define LEFT_CH                     2
#define RIGHT_CH                    3
#define TRAVEL_DIRECTION_CH         4

extern TaskHandle_t xHandleTaskRC;

void vRCStart(void *pvParameters);   
void vInteractionStart(void *pvParameters);
uint16_t getRCControlData(uint8_t ch);
#endif
