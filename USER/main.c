#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"
#include "beep.h"
#include "timer.h"
#include "wave.h"
#include "sys.h"
#include "lcd.h"
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"
#include "pic.h"
#include "usmart.h"
#include "malloc.h"
#include "usart3.h"
#include "common.h"
#include "Tsensor.h"
//#include "hihih.h"
//#include "step.h"
u8 range=100;		//超声波测距，检测垃圾桶满溢程度
u8 smoke=0;		//烟雾传感器，检测垃圾桶是否自燃
u8 *cate;				//垃圾桶类别
u8 *q;

void Main_menu(void)
{ 
	show_picture(115,198,250,250,(u16*)gImage_hahah2);
	Show_Chinese36(110,115,0,36,POINT_COLOR,0xFFFF,0);
	Show_Chinese36(146,115,1,36,POINT_COLOR,0xFFFF,0);
	Show_Chinese36(182,115,2,36,POINT_COLOR,0xFFFF,0);
	Show_Chinese36(218,115,3,36,POINT_COLOR,0xFFFF,0);
	Show_Chinese36(254,115,4,36,POINT_COLOR,0xFFFF,0);
	Show_Chinese36(290,115,5,36,POINT_COLOR,0xFFFF,0);
	Show_Chinese36(325,115,6,36,POINT_COLOR,0xFFFF,0);
	Show_Chinese(175,518,4,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(199,518,5,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(223,518,6,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(247,518,7,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(271,518,8,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(191,628,11,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(215,628,12,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(239,628,7,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(263,628,8,24,POINT_COLOR,0xFFFF,0);
  Show_Chinese(191,573,28,24,POINT_COLOR,0xFFFF,0);
  Show_Chinese(215,573,29,24,POINT_COLOR,0xFFFF,0);
  Show_Chinese(239,573,7,24,POINT_COLOR,0xFFFF,0);
  Show_Chinese(263,573,8,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(10,763,0,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(34,763,1,24,POINT_COLOR,0xFFFF,0);
	LCD_ShowString(58,763,25*11,24,24," 20191060073");
	Show_Chinese(250,763,24,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(274,763,25,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(298,763,26,24,POINT_COLOR,0xFFFF,0);
	LCD_ShowString(322,763,25*11,24,24," 20191060070");
	LCD_DrawLine(0, 750, 480, 750);
	LCD_DrawLine(240, 750, 240, 800);
	
	while(1)
	{
		u8 i=0;
		for(i;i<100;i++)
		{
			ctp_test();
			delay_ms(10);
		}
		printf("发送数据...\r\n");
		sprintf((char*)cate,"未分类");//垃圾桶类别：未分类
		sprintf((char*)q,"#%s,100,0#",cate);
		atk_8266_send_data(q,"",10);
	}
}
void Back2menu(void)
{
	u8 t=0;
		tp_dev.scan(0);
		for(t=0;t<CT_MAX_TOUCH;t++)
		{
			if((tp_dev.sta)&(1<<t))
			{
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)
				{
					if(tp_dev.x[t]>(lcddev.width-50)&&tp_dev.y[t]<50)
					{
						LCD_Clear(WHITE);	//清屏 
						Main_menu();
					}
				}
			}
		}
}
void Menu_1(void)
{
	LCD_Clear(WHITE);	//清屏 
 
 	POINT_COLOR=BLACK;	//设置字体为蓝色 
	Show_Chinese(lcddev.width-48,0,10,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(lcddev.width-24,0,5,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(40,670,13,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(64,670,14,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(88,670,15,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(112,670,16,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(136,670,17,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(204,670,18,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(280,670,19,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(304,670,20,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(328,670,21,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(352,670,22,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(376,670,17,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(444,670,18,24,POINT_COLOR,0xFFFF,0);
	show_picture(140,150,198,250,(u16*)gImage_hahah); 
	LCD_DrawLine(0, 450, 480, 450);
	LCD_DrawLine(240,450, 240, 800);
	show_picture(70,500,92,100,(u16*)gImage_hihihi2);
	show_picture(314,500,100,99,(u16*)gImage_hihihi1);
	while(1)
	{
		u8 i=0;
		for(i;i<100;i++)
		{
			Back2menu();
			delay_ms(10);
		}
	  range=Wave_SRD_Strat();
		smoke=Nsensor();
		printf("发送数据...\r\n");
		sprintf((char*)cate,"可回收垃圾");//垃圾桶类别：可回收
		sprintf((char*)q,"#%s,%u,%u#",cate,range,smoke);
		atk_8266_send_data(q,"",10);
	}
}
void Menu_2(void)
{
	LCD_Clear(WHITE);	//清屏  
 	POINT_COLOR=BLACK;	//设置字体为蓝色 
	Show_Chinese(lcddev.width-48,0,10,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(lcddev.width-24,0,5,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(40,670,13,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(64,670,14,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(88,670,15,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(112,670,16,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(136,670,17,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(204,670,18,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(280,670,19,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(304,670,20,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(328,670,21,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(352,670,22,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(376,670,17,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(444,670,18,24,POINT_COLOR,0xFFFF,0);
	show_picture(140,150,198,250,(u16*)gImage_hahah1); 
	LCD_DrawLine(0, 450, 480, 450);
	LCD_DrawLine(240,450, 240, 800);
	show_picture(70,500,92,100,(u16*)gImage_hihihi2);
	show_picture(314,500,100,99,(u16*)gImage_hihihi1);
	while(1)
	{
		u8 i=0;
		for(i;i<100;i++)
		{
			Back2menu();
			delay_ms(10);
		}
		range=Wave_SRD_Strat();
		smoke=Nsensor();
		printf("发送数据...\r\n");
		sprintf((char*)cate,"其他垃圾");//垃圾桶类别：其他
		sprintf((char*)q,"#%s,%u,%u#",cate,range,smoke);
		atk_8266_send_data(q,"",10);
	}
}

void Menu_3(void)
{
	LCD_Clear(WHITE);	//清屏  
 	POINT_COLOR=BLACK;	//设置字体为蓝色 
	Show_Chinese(lcddev.width-48,0,10,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(lcddev.width-24,0,5,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(40,670,13,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(64,670,14,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(88,670,15,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(112,670,16,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(136,670,17,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(204,670,18,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(280,670,19,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(304,670,20,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(328,670,21,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(352,670,22,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(376,670,17,24,POINT_COLOR,0xFFFF,0);
	Show_Chinese(444,670,18,24,POINT_COLOR,0xFFFF,0); 
	show_picture(115,150,250,250,(u16*)gImage_hahah2); 
	LCD_DrawLine(0, 450, 480, 450);
	LCD_DrawLine(240,450, 240, 800);
	show_picture(70,500,92,100,(u16*)gImage_hihihi2);
	show_picture(314,500,100,99,(u16*)gImage_hihihi1);
	while(1)
	{
		u8 i=0;
		for(i;i<100;i++)
		{
			Back2menu();
			delay_ms(10);
		}
		range=Wave_SRD_Strat();
		smoke=Nsensor();
		printf("发送数据...\r\n");
		sprintf((char*)cate,"有害垃圾");//垃圾桶类别：其他
		sprintf((char*)q,"#%s,%u,%u#",cate,range,smoke);
		atk_8266_send_data(q,"",10);
	}
}
int main(void)
{	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	usmart_dev.init(72);		//初始化USMART
 	LED_Init();		  		//初始化与LED连接的硬件接口
	BEEP_Init();         	//初始化蜂鸣器端口
	KEY_Init();         	//初始化与按键连接的硬件接口
	LCD_Init();          //初始化lcd
	tp_dev.init();
	usart3_init(115200);		//初始化串口3
  my_mem_init(SRAMIN);		//初始化内部内存池
	T_Adc_Init();
	Timer_SRD_Init(5000,7199);
	Wave_SRD_Init();
	BEEP_Init();
	
	cate=mymalloc(SRAMIN,32);
	q=mymalloc(SRAMIN,32);
	LED1 = 0;
	LCD_Clear(WHITE);
	LCD_ShowString(175,350,24*10,24,24,"LOADING...");
	printf("智能垃圾桶初始化...\r\n");
	atk_8266_test();		//进入ATK_ESP8266测试
	LCD_Clear(WHITE);
	LCD_ShowString(175,350,24*13,24,24,"LOAD COMPLATE");
	delay_ms(1000);
	LCD_Clear(WHITE);
	Main_menu(); 
}

