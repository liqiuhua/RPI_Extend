#include "Debug.h"
#include "stdio.h"
#include "stm32f10x.h"

static uint8_t EnableDebug=1;

void DebugUart(uint32_t bound)
{
    //GPIO端口设置
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;

        USART_DeInit(USART1);


        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟 
        //串口1对应引脚复用映射
        GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
        //USART1端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //复用功能
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
        GPIO_Init(GPIOA,&GPIO_InitStructure);          //初始化PA9，PA10
        //USART1 初始化设置
        USART_InitStructure.USART_BaudRate = bound;//波特率设置
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
        USART_InitStructure.USART_StopBits = USART_StopBits_1;  //一个停止位
        USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
        USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//收发模式
        USART_Init(USART1, &USART_InitStructure); //初始化串口1	
        USART_Cmd(USART1, ENABLE);  //使能串口1 

        /* Configure USART1 USART_IT_RXNE */
        USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

        USART_ClearFlag(USART1, USART_FLAG_TC);  
        NVIC_InitTypeDef NVIC_InitStructure;
        /*****USART1 interrupt Config****/
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
 
}
#include "stdarg.h"
#define CMD_BUFFER_LEN 255
void DebugPrintf(char *fmt, ...)
{
    if(EnableDebug)
    {
        char buffer[CMD_BUFFER_LEN - 1];
        uint8_t i = 0;
        uint8_t len;

        va_list arg_ptr; //Define convert parameters variable
        va_start(arg_ptr, fmt); //Init variable
        len = vsnprintf(buffer, CMD_BUFFER_LEN+1, fmt, arg_ptr); //parameters list format to buffer
        
        while ((i < CMD_BUFFER_LEN) && (i < len) && (len > 0))
        {
            USART_SendData(USART1, (uint8_t) buffer[i++]);
            while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
        }
        va_end(arg_ptr);
    }
}
int fputc(int ch,FILE *f)
{
    USART_SendData(USART1,(uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
    return 0;
}


static void Send_data(uint8_t *data,uint8_t len)
{
    for(uint8_t i=0;i<len;++i)
    {
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC )==RESET);	
		USART_SendData(USART1,data[i]);

	}
}

void USART1_IRQHandler(void)
{
    uint8_t bRcvByte ;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        bRcvByte=USART_ReceiveData(USART1);
        
        
        USART_ClearFlag(USART1,USART_IT_RXNE);
    }
}

