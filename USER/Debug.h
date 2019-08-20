#ifndef __DEBUG_H_
#define __DEBUG_H_

#include "stdint.h"


void DebugPrintf(char *fmt, ...);
void vSystemDebugStart(void *pvParameters);   
void DebugUart(uint32_t bound);


#endif 
