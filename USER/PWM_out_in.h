#ifndef __PWM_OUT_IN_H_
#define __PWM_OUT_IN_H_
#include "stdint.h"

void PWM_OUT_1_4_Init(void);
void PWM_OUT_1_4_out(uint8_t ch,uint16_t data);
void PWM_OUT_5_8_Init(void);
void PWM_OUT_5_8_out(uint8_t ch,uint16_t data);

void PWM_IN_1_4_Init(void);
uint16_t getPWM_IN_1_4_ICValue(uint8_t channel);

void PWM_IN_5_8_Init(void);
uint16_t getPWM_IN_5_8_ICValue(uint8_t channel);
#endif

