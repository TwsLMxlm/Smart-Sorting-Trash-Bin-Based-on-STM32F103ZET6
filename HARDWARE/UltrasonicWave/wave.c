#include "wave.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#define Trig GPIO_Pin_4

#define Echo GPIO_Pin_6

float Distance;

void Wave_SRD_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitSture;
	EXTI_InitTypeDef  EXTI_InitSture;
	NVIC_InitTypeDef  NVIC_InitSture;
	//如果外部中断的话则一定使能AFIO复用功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOE,ENABLE);
	
	
	//配置IO端口
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_Out_PP;   //推挽输出模式
	GPIO_InitSture.GPIO_Pin=Trig;                //将PE4于Trig相连
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture);
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //拉输入模式
	GPIO_InitSture.GPIO_Pin=Echo;                //将PE6于Echo相连
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture);
	
	//中断和6端口映射一起
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource6);
	
	//外部中断配置
	EXTI_InitSture.EXTI_Line=EXTI_Line6;
	EXTI_InitSture.EXTI_LineCmd=ENABLE;
	EXTI_InitSture.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSture.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitSture);
	
	
	//中断优先级管理
	NVIC_InitSture.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitSture);
}

void EXTI9_5_IRQHandler(void)
{
	delay_us(10);
	
	
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{
		TIM_SetCounter(TIM3,0);
		TIM_Cmd(TIM3,ENABLE);
		while(GPIO_ReadInputDataBit(GPIOE,Echo));  //等待低电平
		TIM_Cmd(TIM3,DISABLE);
		Distance=TIM_GetCounter(TIM3)*340/200.0;
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

float Wave_SRD_Strat(void)
{
	float percent;
	percent=Distance/100*100;
	if(percent>=100)
	{
		percent=100;
	}
	//LCD_Init();
	POINT_COLOR=BLACK;
	GPIO_SetBits(GPIOE,Trig);   //将Trig设置为高电平
	delay_us(10);               //持续大于10us触发，触发超声波模块工作
	GPIO_ResetBits(GPIOE,Trig); 
	LCD_ShowxNum(160,670,percent,3,24,0);
	if(Distance<10)
	{
		LED0=0;
	}else
	{
		LED0=1;
	}
	return percent;
}











