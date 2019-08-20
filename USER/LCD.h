//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : TFT_LCD �ӿ���ʾ����(stm32ϵ��)
//              ˵��: 
//              -�˲���Ϊ���������ӿڣ�BLKΪ���⿪�أ�Ĭ�Ͽ��Բ���---------------------------------------------------------------
//              GND    ��Դ��
//              VCC    3.3v��Դ
//              CLK    ��PD6
//              MOSI   ��PD7
//              RES    ��PD4
//              DC     ��PD5
//              CS1    ��PD3               
//              -����Ϊ�������ƽӿڣ�������ó�û���ܿ��Բ���---------------------------------------------------------------
//              MISO  ��PC2
//              CS2   ��PC0
//              PEN   ��PC10  
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/
#ifndef __LCD_H
#define __LCD_H		

#include "Type.h"

#define LCD_W 240
#define LCD_H 320
#define	u8 unsigned char
#define	u16 unsigned int
#define	u32 unsigned long

//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED�˿ڶ���----------------  					   
#define LCD_BLK_L()  GPIO_ResetBits(GPIOA,GPIO_Pin_3)//����BLK
#define LCD_BLK_H()  GPIO_SetBits(GPIOA,GPIO_Pin_3)

#define LCD_RESET_L() GPIO_ResetBits(GPIOA,GPIO_Pin_8)//��λRES
#define LCD_RESET_H() GPIO_SetBits(GPIOA,GPIO_Pin_8)

#define LCD_DC_L() GPIO_ResetBits(GPIOA,GPIO_Pin_2)//����/����ѡ��DC
#define LCD_DC_H() GPIO_SetBits(GPIOA,GPIO_Pin_2)

#define LCD_CLK_L() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//ʱ��CLK
#define LCD_CLK_H() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define LCD_SDIN_L() GPIO_ResetBits(GPIOA,GPIO_Pin_6)//DIN/MOSI
#define LCD_SDIN_H() GPIO_SetBits(GPIOA,GPIO_Pin_6)

#define LCD_CS_L() GPIO_ResetBits(GPIOA,GPIO_Pin_4)//ƬѡCS
#define LCD_CS_H() GPIO_SetBits(GPIOA,GPIO_Pin_4)

//#define LCD_CS_L() GPIO_ResetBits(GPIOA,GPIO_Pin_9)//ƬѡCS
//#define LCD_CS_H() GPIO_SetBits(GPIOA,GPIO_Pin_9)

//#define LCD_SDOUT_L() GPIO_ResetBits(GPIOB,GPIO_Pin_3)//DOUT/MISO
//#define LCD_SDOUT_H() GPIO_SetBits(GPIOB,GPIO_Pin_3)


extern  u16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ
extern u16 POINT_DefaultColor;  //Ĭ�ϻ���ɫ
extern u16 BACK_DefaultColor;   //Ĭ����ʾ����ɫ

void Lcd_Init(void); 
void LCD_Clear(u16 Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_WR_DATA8(char da); //��������-8λ����
void LCD_WR_DATA(int da);
void LCD_WR_REG(char da);

void LCD_DrawPoint(u16 x,u16 y);//����
void LCD_DrawPoint_big(u16 x,u16 y);//��һ�����
u16  LCD_ReadPoint(u16 x,u16 y); //����
void Draw_Circle(u16 x0,u16 y0,u8 r);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 Color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 Color);
void LCD_CursorDisplay(u16 x1, u16 y1, u16 x2, u16 y2, u16 Color);
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//��ʾ����
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//��ʾ2������
void LCD_ShowString(u16 x,u16 y,const u8 *p);		 //��ʾһ���ַ���,16����
 
void showhanzi(unsigned int x,unsigned int y,unsigned char index);

void delayms(INT16U count);
void LCD_Background(void);
void LCD_AdjustBrightness(void);
void LCD_WakeBrightness(void);
//void showimage();
void LCD_ClearPicture(u16 Color);
void showhanzi_english(unsigned int x,unsigned int y,unsigned char index);
void BatteryDisplay(void);


//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


					  		 
#endif  
	 
	 



