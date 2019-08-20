#ifndef __RGB_LED_H_
#define __RGB_LED_H_

#include "stdint.h"
void RGB_LED_init(void);
void RGB_LED_Set(uint8_t R_data,uint8_t G_data,uint8_t B_data);
void RGB_LED_PWM_init(void);
void RGB_LED_Set_PWM(uint8_t R_data,uint8_t G_data,uint8_t B_data);
#endif
