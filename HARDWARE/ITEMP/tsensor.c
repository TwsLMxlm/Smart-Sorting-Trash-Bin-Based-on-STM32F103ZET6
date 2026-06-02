#include "tsensor.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
#include "lcd.h"
#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//ADC 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/7 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 
		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3	
void T_Adc_Init(void)  //ADC通道初始化
{
	GPIO_InitTypeDef GPIO_Initstructre;   
	ADC_InitTypeDef ADC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE );	  //使能GPIOA,ADC1通道时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能io口
	GPIO_Initstructre.GPIO_Mode=GPIO_Mode_AIN; 
  GPIO_Initstructre.GPIO_Pin=GPIO_Pin_1;
  GPIO_Initstructre.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_Initstructre);
  GPIO_SetBits(GPIOA,GPIO_Pin_1);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //分频因子6时钟为72M/6=12MHz

  ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省值
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
	//ADC_TempSensorVrefintCmd(ENABLE); //开启内部温度传感器
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	ADC_ResetCalibration(ADC1);	//重置指定的ADC1的复位寄存器
  while(ADC_GetResetCalibrationStatus(ADC1));	//获取ADC1重置校准寄存器的状态,设置状态则等待
	ADC_StartCalibration(ADC1);	 //
	while(ADC_GetCalibrationStatus(ADC1));		//获取指定ADC1的校准程序,设置状态则等待
}

u16 T_Get_Adc(u8 ch)   
	{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道3,第一个转换,采样时间为239.5周期	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
	}
	
//取times次,然后平均
u16 T_Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=T_Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	   

//得到温度值
//返回值:温度值(扩大了100倍,单位:℃.)
short Get_Temprate(void)	//获取内部温度传感器温度值
{
	u32 adcx;
	short result;
 	double nongdu;//浓度
	float min=1000.0;
	float max=3800.0;
	adcx=T_Get_Adc_Average(ADC_Channel_1,20);	//读取通道16,20次取平均
	//temperate=(float)adcx*(3.3/4096);		//电压值
  nongdu=(adcx-min)/(max-min)*10000;
	result=nongdu;//*=100;					//扩大100倍.
	return result;
}
float Nsensor(void)
{
  short temp; 
	int ex;
	temp=Get_Temprate();
		LCD_ShowString(30+10*8,670,16,16,16," ");	//无符号		
		ex=temp/100;
		if(ex<0)
		{
			ex=0;
		}			
		LCD_ShowxNum(300+24*4,670,ex,3,24,0);
		if(ex>60)
		{
			BEEP=1;
		}else
		{
			BEEP=0;
		}
		return ex;
		
}
