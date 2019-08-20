#include "NumDisplay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
/*******************此驱动使用的是AIP1628芯片 不具有通用型************************************/
const unsigned char Num_seg[10]={(~0x3f),~0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//段码0-9,小数点是最高一位,需要用到时直接或上0x80
static void AIP_send_8bit(uint8_t dat);
static void AIPcommand(uint8_t com);
void NumDisplay(uint8_t Num , uint8_t data);


#define STB_SET() GPIO_SetBits(GPIOE,GPIO_Pin_8)
#define STB_RESET() GPIO_ResetBits(GPIOE,GPIO_Pin_8)
#define CLK_SET() GPIO_SetBits(GPIOE,GPIO_Pin_10)
#define CLK_RESET() GPIO_ResetBits(GPIOE,GPIO_Pin_10)
#define DIO_SET() GPIO_SetBits(GPIOE,GPIO_Pin_9)
#define DIO_RESET() GPIO_ResetBits(GPIOE,GPIO_Pin_9)

#define nop() __ASM("NOP")

void NumDisplayInit(void)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10; //
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz

    GPIO_Init(GPIOE,&GPIO_InitStructure);          
    
    AIPcommand(0x03); //设置显示模式，7位10段模式
   //     AIPcommand(0x40); //设置数据命令,采用地址自动加1模式
    
}

//向AiP1628发送8位数据,从低位开始------------------------
static void AIP_send_8bit(uint8_t dat)
{
  uint8_t i;
  for(i=0;i<8;i++)
  {
    if(dat&0x01)
      DIO_SET();//DIO=1
    else 
      DIO_RESET();//DIO=0
    CLK_RESET();//CLK=0
    nop();//

    CLK_SET();//CLK=1
    dat=dat>>1;
  }
}
//向AiP1628发送命令--------------------------------------
static void AIPcommand(uint8_t com)
{
  STB_SET();//STB=1
  nop();

  STB_RESET();//STB=0

  nop();//一小段时间的延时,度过下降沿,避免在下降沿的时候发送数据导致数据发送错误
  AIP_send_8bit(com);

}

//显示函数
void NumDisplay(uint8_t Num , uint8_t data)
{
    AIPcommand(0xc0+Num);
     AIP_send_8bit(0);
    nop();
    AIP_send_8bit(Num_seg[data]);
    AIP_send_8bit(0);
    nop();;
      AIPcommand(0x8b); //显示控制命令，打开显示并设置为最亮 
      STB_SET();//STB=1
}



void LED_Write(uint8_t bTimeMorphology0,uint8_t bTimeMorphology1,uint8_t bTimeMorphology2,uint8_t bTimeMorphology3)
{
	   uint8_t i; 
	   uint8_t bPreTimeSoreBuff[4];
	   bPreTimeSoreBuff[0] = bTimeMorphology0;
	   bPreTimeSoreBuff[1] = bTimeMorphology1;
	   bPreTimeSoreBuff[2] = bTimeMorphology2;
	   bPreTimeSoreBuff[3] = bTimeMorphology3;
         AIPcommand(0xc); //设置显示地址，从00H开始
	  for(i=0;i<4;i++) 
	//发送显示数据
	  {
		  AIP_send_8bit(bPreTimeSoreBuff[i]);
		  AIP_send_8bit(0);
	    //AIP_send_8bit(0);
	  }
	    for(i=0;i<3;i++)
	  {
	    AIP_send_8bit(0);
	    AIP_send_8bit(0);
	  }
	  AIPcommand(0x8b); //显示控制命令，打开显示并设置为最亮 
	   STB_SET();//STB=1
}
void display(void)
{      
	  uint16_t j;
	  uint8_t bPreTimeBuff[4]={0,1,2,3};

	       LED_Write(bPreTimeBuff[0],bPreTimeBuff[1],bPreTimeBuff[2],bPreTimeBuff[3]);


       
}

