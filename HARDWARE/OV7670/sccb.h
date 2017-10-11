#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ο�������guanfu_wang���롣
//ALIENTEKս��STM32������
//SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/14
//�汾��V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////

//#define SCCB_SDA_IN       {GPIOG->MODER&=0xF3FFFFFF;GPIOG->PUPDR&=0XF7FFFFFF;GPIOG->PUPDR|=0X04000000;}
//#define SCCB_SDA_OUT      {GPIOG->MODER&=0XF7FFFFFF;GPIOG->MODER|=0X04000000;GPIOG->OTYPER&=0XFFFFDFFF;}


//IO��������	 
#define SCCB_SCL    		PEout(5)	 	//SCL
#define SCCB_SDA    		PEout(6) 		//SDA	 

#define SCCB_READ_SDA    	PEin(6)  		//����SDA    
#define SCCB_ID   			0X42  			//OV7670��ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
void SCCB_SDA_OUT(void);
void SCCB_SDA_IN(void);
#endif













