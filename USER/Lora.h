#ifndef __LORA_H_
#define __LORA_H_


#include "stdint.h"
#include "main.h"
extern uint8_t Lora_Rx_data[3];
extern uint8_t LoraDataRecvComplete;
void LoraInit(void);
void LoraSendCmd(uint8_t *pCmd,uint8_t size);
void LoraSendData(uint16_t addr ,uint8_t *pData,uint8_t size);
void LoraRecvData(void);
void LoraDataDeal(UART_HandleTypeDef *huart);

#endif
