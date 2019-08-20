#include "NumDisplay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
/*******************������ʹ�õ���AIP1628оƬ ������ͨ����************************************/
const unsigned char Num_seg[10]={(~0x3f),~0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//����0-9,С���������һλ,��Ҫ�õ�ʱֱ�ӻ���0x80
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
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10; //
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz

    GPIO_Init(GPIOE,&GPIO_InitStructure);          
    
    AIPcommand(0x03); //������ʾģʽ��7λ10��ģʽ
   //     AIPcommand(0x40); //������������,���õ�ַ�Զ���1ģʽ
    
}

//��AiP1628����8λ����,�ӵ�λ��ʼ------------------------
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
//��AiP1628��������--------------------------------------
static void AIPcommand(uint8_t com)
{
  STB_SET();//STB=1
  nop();

  STB_RESET();//STB=0

  nop();//һС��ʱ�����ʱ,�ȹ��½���,�������½��ص�ʱ�������ݵ������ݷ��ʹ���
  AIP_send_8bit(com);

}

//��ʾ����
void NumDisplay(uint8_t Num , uint8_t data)
{
    AIPcommand(0xc0+Num);
     AIP_send_8bit(0);
    nop();
    AIP_send_8bit(Num_seg[data]);
    AIP_send_8bit(0);
    nop();;
      AIPcommand(0x8b); //��ʾ�����������ʾ������Ϊ���� 
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
         AIPcommand(0xc); //������ʾ��ַ����00H��ʼ
	  for(i=0;i<4;i++) 
	//������ʾ����
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
	  AIPcommand(0x8b); //��ʾ�����������ʾ������Ϊ���� 
	   STB_SET();//STB=1
}
void display(void)
{      
	  uint16_t j;
	  uint8_t bPreTimeBuff[4]={0,1,2,3};

	       LED_Write(bPreTimeBuff[0],bPreTimeBuff[1],bPreTimeBuff[2],bPreTimeBuff[3]);


       
}

