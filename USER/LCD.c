

#include "stm32f10x.h"
#include "LCD.h"
#include "Font.h"  
#include "Type.h"

u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色
u16 POINT_DefaultColor=BLACK;  //默认画笔色
u16 BACK_DefaultColor=WHITE;   //默认显示背景色


void LCD_Writ_Bus(char dat)   //串行数据写入
{	
	u8 i;			  
	for(i=0;i<8;i++)
	{			  
		LCD_CLK_L();
		if(dat&0x80)
			//USART_SendData(USART1,'A');
		   LCD_SDIN_H();
		else 
			//USART_SendData(USART1,'B');
		   LCD_SDIN_L();
		 
    LCD_CLK_H();		
		dat<<=1;
	}	
  LCD_CLK_L();	
}

void LCD_WR_DATA8(char da) //发送数据-8位参数
{	
	  LCD_CS_L();
    LCD_DC_H();
	  LCD_Writ_Bus(da);  
	  LCD_CS_H();
}  
 void LCD_WR_DATA(int da)
{	
	  LCD_CS_L();
    LCD_DC_H();
	  LCD_Writ_Bus(da>>8);
    LCD_Writ_Bus(da);
	  LCD_CS_H();
}	  
void LCD_WR_REG(char da)	 
{		
	  LCD_CS_L();
    LCD_DC_L();
	  LCD_Writ_Bus(da);
	  LCD_CS_H();
}
 void LCD_WR_REG_DATA(int reg,int da)
{	
	  LCD_CS_L();
    LCD_WR_REG(reg);
	  LCD_WR_DATA(da);
	  LCD_CS_H();
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	 LCD_WR_REG(0x2a);
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);					 						 
}

void Lcd_Init(void)
{
	/*初始化SPI引脚*/
	GPIO_InitTypeDef  GPIO_InitStruct={0};   
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  //使用前打开相应的时钟
      /*Configure GPIO pins : PE0 PE1 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
    

	 LCD_CS_L();
	 LCD_RESET_L();     //RESET复位不成功或者不复位，LCD屏显示不正常，所以延时尽量长一点
	 delayms(200);
	 LCD_RESET_H();
	 delayms(200);
	 
	 LCD_BLK_H();//打开背光
	
//************* Start Initial Sequence **********// 
LCD_WR_REG(0xCF);  
LCD_WR_DATA8(0x00); 
LCD_WR_DATA8(0xD9); 
LCD_WR_DATA8(0X30); 
 
LCD_WR_REG(0xED);  
LCD_WR_DATA8(0x64); 
LCD_WR_DATA8(0x03); 
LCD_WR_DATA8(0X12); 
LCD_WR_DATA8(0X81); 
 
LCD_WR_REG(0xE8);  
LCD_WR_DATA8(0x85); 
LCD_WR_DATA8(0x10); 
LCD_WR_DATA8(0x78); 
 
LCD_WR_REG(0xCB);  
LCD_WR_DATA8(0x39); 
LCD_WR_DATA8(0x2C); 
LCD_WR_DATA8(0x00); 
LCD_WR_DATA8(0x34); 
LCD_WR_DATA8(0x02); 
 
LCD_WR_REG(0xF7);  
LCD_WR_DATA8(0x20); 
 
LCD_WR_REG(0xEA);  
LCD_WR_DATA8(0x00); 
LCD_WR_DATA8(0x00); 
 
LCD_WR_REG(0xC0);    //Power control 
LCD_WR_DATA8(0x21);   //VRH[5:0] 
 
LCD_WR_REG(0xC1);    //Power control 
LCD_WR_DATA8(0x12);   //SAP[2:0];BT[3:0] 
 
LCD_WR_REG(0xC5);    //VCM control 
LCD_WR_DATA8(0x32); 
LCD_WR_DATA8(0x3C); 
 
LCD_WR_REG(0xC7);    //VCM control2 
LCD_WR_DATA8(0XC1); 
 
LCD_WR_REG(0x36);    // Memory Access Control 
//LCD_WR_DATA8(0x08);  //竖屏显示
//LCD_WR_DATA8(0x78);  //横屏显示， 改变显示方向的同时交换LCD_H和LCD_W的位置或者值
LCD_WR_DATA8(0xB8);    //根据自己的需要，可以任意更改屏幕的显示方向，ILI9341芯片资料中的0x36h指令
 
LCD_WR_REG(0x3A);   
LCD_WR_DATA8(0x55); 

LCD_WR_REG(0xB1);   
LCD_WR_DATA8(0x00);   
LCD_WR_DATA8(0x18); 
 
LCD_WR_REG(0xB6);    // Display Function Control 
LCD_WR_DATA8(0x0A); 
LCD_WR_DATA8(0xA2); 

 
 
LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
LCD_WR_DATA8(0x00); 
 
LCD_WR_REG(0x26);    //Gamma curve selected 
LCD_WR_DATA8(0x01); 
 
LCD_WR_REG(0xE0);    //Set Gamma 
LCD_WR_DATA8(0x0F); 
LCD_WR_DATA8(0x20); 
LCD_WR_DATA8(0x1E); 
LCD_WR_DATA8(0x09); 
LCD_WR_DATA8(0x12); 
LCD_WR_DATA8(0x0B); 
LCD_WR_DATA8(0x50); 
LCD_WR_DATA8(0XBA); 
LCD_WR_DATA8(0x44); 
LCD_WR_DATA8(0x09); 
LCD_WR_DATA8(0x14); 
LCD_WR_DATA8(0x05); 
LCD_WR_DATA8(0x23); 
LCD_WR_DATA8(0x21); 
LCD_WR_DATA8(0x00); 
 
LCD_WR_REG(0XE1);    //Set Gamma 
LCD_WR_DATA8(0x00); 
LCD_WR_DATA8(0x19); 
LCD_WR_DATA8(0x19); 
LCD_WR_DATA8(0x00); 
LCD_WR_DATA8(0x12); 
LCD_WR_DATA8(0x07); 
LCD_WR_DATA8(0x2D); 
LCD_WR_DATA8(0x28); 
LCD_WR_DATA8(0x3F); 
LCD_WR_DATA8(0x02); 
LCD_WR_DATA8(0x0A); 
LCD_WR_DATA8(0x08); 
LCD_WR_DATA8(0x25); 
LCD_WR_DATA8(0x2D); 
LCD_WR_DATA8(0x0F); 
 
LCD_WR_REG(0x11);    //Exit Sleep 
delayms(120); 
LCD_WR_REG(0x29);    //Display on 

LCD_Clear(WHITE); //清屏
BACK_COLOR=WHITE;;POINT_COLOR=BLACK; 
//for(int i=0;i<5;i++)
//showhanzi_english(50+16*i,50,i);
//showimage();
//delayms(1200);
//delayms(1200);
//delayms(1200);
//delayms(1200);
//delayms(1200);
LCD_ClearPicture(WHITE);
LCD_Background();
LCD_Background();
LCD_BLK_H();
 
} 

//清屏函数
//Color:要清屏的填充色
void LCD_Clear(u16 Color)
{
	 u16 i,j;  	
	 Address_set(1,1,LCD_H-1,LCD_W-1);  //原来Address_set(0,0,LCD_H-1,LCD_W-1);修改2018.0828
   for(i=0;i<LCD_W;i++)
	 {
	    for (j=0;j<LCD_H;j++)
	   	{
        	LCD_WR_DATA(Color);	 			 
	    }

	 }
}

void LCD_ClearPicture(u16 Color)
{
	 u16 i,j;  	
	 Address_set(50,50,219,149);  //原来Address_set(0,0,LCD_H-1,LCD_W-1);修改2018.0828
   for(i=0;i<310;i++)
	 {
	    for (j=0;j<182;j++)
	   	{
        	LCD_WR_DATA(Color);	 			 
	    }

	 }
}

void showimage() //显示170*100图片
{
  	int i; 
		Address_set(50,50,219,149);  
		for(i=0;i<170*100;i++)      //*2数据减少一半
		{ 	
				LCD_WR_DATA8(gImage_GG[i*2+1]);	
				LCD_WR_DATA8(gImage_GG[i*2]);				  				
		}	
		
}

/*英语字体8*16*/
void showhanzi_english(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j;
	unsigned char *temp=jewoo;    
  Address_set(x,y,x+7,y+15); //设置区域    
	temp+=index*16;	
	for(j=0;j<16;j++)
	{
		for(i=0;i<8;i++)
		{ 		     
		 	if((*temp&(1<<i))!=0)
			{
				LCD_WR_DATA(POINT_COLOR);
			} 
			else
			{
				LCD_WR_DATA(BACK_COLOR);
			}   
		}
		temp++;
  }
}

//在指定位置显示一个汉字(32*33大小)
//dcolor为内容颜色，gbcolor为背静颜色
void showhanzi(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j,*temp;
//	unsigned char *temp=hanzi;    
  Address_set(x,y,x+31,y+31); //设置区域      
	temp+=index*128;	
	for(j=0;j<128;j++)
	{
		for(i=0;i<8;i++)
		{ 		     
		 	if((*temp&(1<<i))!=0)
			{
				LCD_WR_DATA(POINT_COLOR);
			} 
			else
			{
				LCD_WR_DATA(BACK_COLOR);
			}   
		}
		temp++;
 }
}
//画点
//POINT_COLOR:此点的颜色
void LCD_DrawPoint(u16 x,u16 y)
{
	Address_set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(POINT_COLOR); 	    
} 	 
//画一个大点
//POINT_COLOR:此点的颜色
void LCD_DrawPoint_big(u16 x,u16 y)
{
	LCD_Fill(x-1,y-1,x+1,y+1,POINT_COLOR);
} 
//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//设置光标位置 	    
	} 					  	    
}  
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 Color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	POINT_COLOR=Color;                //当前画笔色

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)
		incx=1; //设置单步方向 
	else if(delta_x==0)
		incx=0;//垂直线 
	else 
  {
	    incx=-1;
	    delta_x=-delta_x;
	} 
	
	if(delta_y>0)
		incy=1; 
	else if(delta_y==0)
		incy=0;//水平线 
	else
  {
	    incy=-1;
	    delta_y=-delta_y;
	} 
	
	if( delta_x>delta_y)
		distance=delta_x; //选取基本增量坐标轴 
	else 
		distance=delta_y; 
	
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}
  POINT_COLOR=POINT_DefaultColor;    //默认画笔色  
}   

//光标显示
void LCD_CursorDisplay(u16 x1, u16 y1, u16 x2, u16 y2, u16 Color)
{
    POINT_COLOR=Color;                //当前画笔色
    LCD_DrawLine(x1,y1,x2,y2,Color);
    POINT_COLOR=POINT_DefaultColor;    //默认画笔色
}

//画矩形，Color代表画笔的颜色
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 Color)
{
    POINT_COLOR=Color;                //当前画笔色
	  LCD_DrawLine(x1,y1,x2,y1,Color);
	  LCD_DrawLine(x1,y1,x1,y2,Color);
	  LCD_DrawLine(x1,y2,x2,y2,Color);
	  LCD_DrawLine(x2,y1,x2,y2,Color);
    POINT_COLOR=POINT_DefaultColor;    //默认画笔色
}

//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a);             //3           
		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0-a,y0+b);             //1       
		LCD_DrawPoint(x0-b,y0-a);             //7           
		LCD_DrawPoint(x0-a,y0-b);             //2             
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0-b);             //5
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-b,y0+a);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b);
	}
} 
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"
//mode:叠加方式(1)还是非叠加方式(0)
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"

//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode)
{
  u8 temp;
  u8 pos,t;
	u16 x0=x;
	u16 colortemp=POINT_COLOR;      
  if(x>LCD_H-16||y>LCD_W-16)
		return;	    
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	Address_set(x,y,x+8-1,y+16-1);      //设置光标位置 
	if(!mode) //非叠加方式
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		  {                 
		      if(temp&0x01)
					    POINT_COLOR=colortemp;
				  else 
						  POINT_COLOR=BACK_COLOR;
				  LCD_WR_DATA(POINT_COLOR);	
				  temp>>=1; 
				  x++;
		  }
			x=x0;
			y++;
		}	
	}
	else//叠加方式
	{
		for(pos=0;pos<16;pos++)
		{
		    temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			  for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//画一个点     
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n函数
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)
		result*=m;    
	return result;
}			 
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//color:颜色
//num:数值(0~4294967295);	
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len)
{         	
	u8 t,temp;
	u8 enshow=0;
	num=(u16)num;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+8*t,y,' ',0);
				continue;
			}
			else 
				enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+8*t,y,temp+48,0); 
	}
} 
//显示2个数字
//x,y:起点坐标
//num:数值(0~99);	 
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len)
{         	
	u8 t,temp;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
	 	LCD_ShowChar(x+8*t,y,temp+'0',0); 
	}
} 
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
void LCD_ShowString(u16 x,u16 y,const u8 *p)
{         
    while(*p!='\0')
    {       
        if(x>LCD_H-16){x=0;y+=16;}
        if(y>LCD_W-16){y=x=0;LCD_Clear(RED);}
        LCD_ShowChar(x,y,*p,0);
        x+=8;
        p++;
    }  
}

void delayms(INT16U count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}


void LCD_Background(void)
{
    LCD_DrawRectangle(5,10,305,230,BLACK);  //外框
    LCD_DrawRectangle(5,10,305,75,BLACK);   //上小框	
    LCD_DrawRectangle(5,10,75,230,BLACK);   //左小框 
	  LCD_DrawRectangle(5,180,305,230,BLACK);   //下小框 
    LCD_ShowString(10,20,"Address");
    LCD_ShowString(10,40,"(0-63)");
	  LCD_DrawRectangle(35,60,45,70,BLACK);    //选中地址方框
    LCD_ShowString(10,110,"Group");
	  LCD_DrawRectangle(35,135,45,145,BLACK);   //选中组方框
	  LCD_ShowString(10,190,"Info");
	  LCD_DrawLine(90,55,110,55,POINT_DefaultColor);    //地址横线
	  LCD_Show2Num(90,35,0,1);
	  LCD_Show2Num(100,35,0,1);
	  LCD_Fill(36,136,44,144,LIGHTBLUE);     //选中组方框
		LCD_Fill(36,61,44,69,LIGHTBLUE);     //选中地址方框
    
    int Groupnum=0;
    for(int y=0;y<2;y++)
    {
        for(int x=0;x<8;x++)
        {
            LCD_DrawRectangle(80+x*25,82+y*40,105+x*25,120+y*40,BACK_DefaultColor);    //开机清除所有的选中方框
            LCD_DrawRectangle(85+x*25,105+y*40,95+x*25,115+y*40,BLACK);     //组0小框，方框大小10*10，横向方框间隔25，竖向方框间隔40
					  
            if(Groupnum<10)
            {
							  LCD_Show2Num(85+x*25,85+y*40,Groupnum,1);
            }
            else
            {
							  LCD_Show2Num(85+x*25,85+y*40,Groupnum,2);
            }          
            Groupnum++;
        }
    }
		
    LCD_DrawRectangle(80,82,105,120,LIGHTGREEN);  //选中组1，显示红色方框
		LCD_ShowString(85,185,"Modify address and group  ");
    
}


//void LCD_AdjustBrightness(void)  //按照频率调节
//{
//	  INT16U i,j,a,b,y=10;
////	  for(i=y;i>0;i--)
//	  {
//			 for(j=7;j>0;j--)
//			{
//				for(b=100-y;b>0;b--)
//				{
//					  LCD_BLK_L();
//				}
//				 for(a=y;a>0;a--)
//				{
//					  LCD_BLK_H();
//				}
//				
//			}
//	  }
//}


void BatteryDisplay(void)
{
	  LCD_DrawRectangle(252,26,260,34,BLACK);  //小框
	  LCD_Fill(253,27,259,33,RED);
	  LCD_DrawRectangle(260,22,290,38,BLACK);  //大框
	  LCD_Fill(261,23,289,37,RED);
//	  LCD_DrawLine(260, 27, 260, 33, RED);
//	  LCD_ShowString(85,210,"Replacing the battery     ");
}



























