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
//ALIENTEKս��STM32������ʵ��36
//����ͷ ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

extern u8 ov_sta;	//��exit.c���涨��
extern u8 ov_frame;	//��timer.c���涨��	

//����LCD��ʾ
void camera_refresh(void)
{
	u32 j,i;
 	u16 color;	 
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������ 
		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK=1;  
		
		for(j=0;j<240;j++)
		  for(i=0;i<320;i++)
		 {
			  OV7670_RCK=0;
			  color=GPIOF->IDR&0XFF;	//������
			  OV7670_RCK=1; 
			  color<<=8;  
			  OV7670_RCK=0;
			  color|=GPIOF->IDR&0XFF;	//������
			  OV7670_RCK=1; 
			  LCD_SetCursor(100+i,100+j);		//���ù��λ�� 
	      LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	      LCD->LCD_RAM=color;  
		}   							 
		EXTI_ClearITPendingBit(EXTI_Line8);  //���LINE8�ϵ��жϱ�־λ
		ov_sta=0;					//��ʼ��һ�βɼ�
	} 
}		
 int main(void)
 {	 
	u32 i,j;

	delay_init(168);	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	LCD_Init();	 
	while(OV7670_Init())//��ʼ��OV7670
	{
		LCD_ShowString(60,230,200,16,16,"OV7670 Error!!");
		delay_ms(200);
	    LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(60,230,200,16,16,"OV7670 Init OK");
	delay_ms(1500);	 	   
	
	
	//TIM6_Int_Init(10000,8399);			//10Khz����Ƶ��,1�����ж�									  
	EXTI8_Init();						//ʹ�ܶ�ʱ������
	OV7670_Window_Set(10,174,240,320);	//���ô���	  
  	OV7670_CS=0;//�������������ʱ��Ϊ0						 	 
 	while(1)
	{	
	
		camera_refresh();//������ʾ
 		   
	}	   
}












