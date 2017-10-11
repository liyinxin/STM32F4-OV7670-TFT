#include "led.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "string.h"
#include "ov7670.h"
#include "tpad.h"
#include "timer.h"
#include "exti.h"
//ALIENTEK战舰STM32开发板实验36
//摄像头 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

extern u8 ov_sta;	//在exit.c里面定义
extern u8 ov_frame;	//在timer.c里面定义	

//更新LCD显示
void camera_refresh(void)
{
	u32 j,i;
 	u16 color;	 
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右 
		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1;  
		
		for(j=0;j<240;j++)
		  for(i=0;i<320;i++)
		 {
			  OV7670_RCK=0;
			  color=GPIOF->IDR&0XFF;	//读数据
			  OV7670_RCK=1; 
			  color<<=8;  
			  OV7670_RCK=0;
			  color|=GPIOF->IDR&0XFF;	//读数据
			  OV7670_RCK=1; 
			  LCD_SetCursor(100+i,100+j);		//设置光标位置 
	      LCD_WriteRAM_Prepare();	//开始写入GRAM
	      LCD->LCD_RAM=color;  
		}   							 
		EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8上的中断标志位
		ov_sta=0;					//开始下一次采集
	} 
}		
 int main(void)
 {	 
	u32 i,j;

	delay_init(168);	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	LCD_Init();	 
	while(OV7670_Init())//初始化OV7670
	{
		LCD_ShowString(60,230,200,16,16,"OV7670 Error!!");
		delay_ms(200);
	    LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(60,230,200,16,16,"OV7670 Init OK");
	delay_ms(1500);	 	   
	
	
	//TIM6_Int_Init(10000,8399);			//10Khz计数频率,1秒钟中断									  
	EXTI8_Init();						//使能定时器捕获
	OV7670_Window_Set(10,174,240,320);	//设置窗口	  
  	OV7670_CS=0;//这个正常工作的时候为0						 	 
 	while(1)
	{	
	
		camera_refresh();//更新显示
 		   
	}	   
}












