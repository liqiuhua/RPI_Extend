#ifndef _KEY_H_
#define _KEY_H_

#include "stdint.h"
#define KEY_THREE_CLICK   0x01
#define KEY_FOUR_CLICK    0x02
void KEY_Init(void);
uint8_t getKeyStatus(void);
#endif
