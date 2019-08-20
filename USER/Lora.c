
#include "Lora.h"
#include "stm32f1xx_hal.h"

UART_HandleTypeDef huart2;
uint8_t LoraDataRecvComplete=1;
#define MODE_1_PORT GPIOD
#define MODE_2_PORT GPIOD
#define MODE_1_PIN GPIO_PIN_3
#define MODE_2_PIN GPIO_PIN_4

#define MODE_1_H()	    HAL_GPIO_WritePin(MODE_1_PORT, MODE_1_PIN,GPIO_PIN_SET)
#define MODE_1_L()      HAL_GPIO_WritePin(MODE_1_PORT, MODE_1_PIN,GPIO_PIN_RESET)
#define MODE_2_H()      HAL_GPIO_WritePin(MODE_2_PORT, MODE_2_PIN,GPIO_PIN_SET)
#define MODE_2_L()      HAL_GPIO_WritePin(MODE_2_PORT, MODE_2_PIN,GPIO_PIN_RESET)

#define    NORMALMODE       0
#define    AWAKE            1
#define    POWERSAVING      2
#define    SLEEP            3 

uint8_t Lora_Rx_data[3];//格式为AA xx xx BB
uint8_t  *Lora_Rx_dataBuf=Lora_Rx_data; 
static void MX_USART2_UART_Init(void);
static void Lora_GPIO_Init(void);
static void Lora_SetMode(uint8_t mode);
static void Lora_Config(uint16_t addr);
void LoraInit(void)
{
    Lora_GPIO_Init();
    MX_USART2_UART_Init();
     HAL_Delay(200);
    Lora_Config(0x0000);
    HAL_UART_Receive_IT(&huart2, (uint8_t *)Lora_Rx_data, 3); //开启第一次中断
}
static void Lora_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pins : PE0 PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
        while(1);//Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
}

static void Lora_SetMode(uint8_t mode)
{
      switch(mode)
      {
          case NORMALMODE :
              MODE_1_L();
              MODE_2_L();
              break;
          case AWAKE :
              MODE_1_H();
              MODE_2_L();
              break;
          case POWERSAVING:
              MODE_1_L();
              MODE_2_H();
              break;
          case SLEEP:
              MODE_1_H();
              MODE_2_H();
              break;
          default:break; 
      }
}
static void Lora_Config(uint16_t addr)
{
    uint8_t config[6]={0};

    Lora_SetMode(SLEEP);
    HAL_Delay(500);
    config[0]=0xc0;
    config[1]=addr>>8;
    config[2]=addr&0xff;
    config[3]=0x1A;
    config[4]=0x17;
    config[5]=0x44;
   // LoraSendCmd(config,6);
    HAL_UART_Transmit_IT(&huart2, config, 6);
    HAL_Delay(200);
  Lora_SetMode(NORMALMODE);  
    
}
void LoraSendCmd(uint8_t *pCmd,uint8_t size)
{
    HAL_UART_Transmit_IT(&huart2, pCmd, size);
    HAL_Delay(20);
}
uint8_t RxDataCount=0;
void LoraDataDeal(UART_HandleTypeDef *huart)
{
    uint8_t ret = HAL_OK;
    Lora_Rx_dataBuf++;
    RxDataCount++;
    
    do  
    {  
        ret = HAL_UART_Receive_IT(huart,(uint8_t *)Lora_Rx_dataBuf,1);            
    }while(ret != HAL_OK);
    if(RxDataCount>=3)
    {
        RxDataCount=0;
    LoraDataRecvComplete=1;
        
     for(uint8_t i=0;i<3;++i)
     {
         Lora_Rx_data[i]=Lora_Rx_dataBuf[i];
     }
    Lora_Rx_dataBuf=Lora_Rx_data;
    }
}
void LoraSendData(uint16_t addr ,uint8_t *pData,uint8_t size)
{
    uint8_t config[3];
    config[0]=addr>>8;
    config[1]=addr&0xff;
    config[2]=0x17;
    HAL_UART_Transmit_IT(&huart2, pData, size);
    HAL_Delay(10);
}
void LoraRecvData(void)
{
       HAL_UART_Transmit_IT(&huart2, Lora_Rx_data, 3); HAL_Delay(10);

}
/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}