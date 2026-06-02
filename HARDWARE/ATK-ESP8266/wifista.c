#include "common.h"
#include "stdlib.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//ATK-ESP8266 WIFI模块 WIFI STA驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2015/4/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//ATK-ESP8266 WIFI STA测试
//用于测试TCP/UDP连接
//返回值:0,正常
//    其他,错误代码
u8 netpro=1;	//网络模式
u8 atk_8266_wifista_test(void)
{
    u8 *p;
		p=mymalloc(SRAMIN,32);							//申请32字节内存
		printf("WIFI STA模式...\r\n");
    atk_8266_send_cmd("AT+CWMODE=1","OK",1000);		//设置WIFI STA模式
		printf("ESP8266复位...\r\n");
    atk_8266_send_cmd("AT+RST","OK",50);		//ESP8266复位
		delay_ms(1000);         //延时3S等待重启成功
    delay_ms(1000);
    delay_ms(1000);
		printf("单路连接模式...\r\n");
		atk_8266_send_cmd("AT+CIPMUX=0","OK",1000);
    //设置连接到的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!!
    sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//设置无线参数:ssid,密码
    while(atk_8266_send_cmd(p,"WIFI GOT IP",300))	;				//连接目标路由器,并且获得IP
		printf("连接到TLINK平台...\r\n");
		while(atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"tcp.tlink.io\",8647","OK",800));//连接到TLINK平台 tcp.tlink.io 10.100.38.78
		printf("开启透传...\r\n");
		atk_8266_send_cmd("AT+CIPMODE=1","OK",1000);
		//delay_ms(1000);
		atk_8266_send_cmd("AT+CIPSEND","OK",2000);
		//delay_ms(1000);
		printf("连接到设备：");
    atk_8266_send_data("7Z9P385898WX2967","",500);	//1：7Z9P385898WX2967	2：9HDQFNX7E3PXCU57
		printf("7Z9P385898WX2967\r\n");
		delay_ms(100);
		myfree(SRAMIN,p);		//释放内存
		return 0;
}

