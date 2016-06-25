#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"

//#define SPI_send_over SPI1STATbits.SPITBF   //发送缓冲器满状态1
//#define SPI_receive_over SPI1STATbits.SPIRBF  //接收缓冲器满状态1

volatile unsigned int CH432T_reset=0;// 为1 则串口复位
volatile unsigned int RS485_receive=0;// DATARDY 为1 则说明有数据可以读出  0无收到数据
volatile unsigned int RS485_send_fifo=1;// THRE 1可以继续向fifo发送数据，0,fifo已满 16级
volatile unsigned int RS485_send_over=1;// TEMT 1发送全部发完， 0
volatile unsigned int BSP_reset=0;

volatile unsigned int  MODBUS_T1_5=20;  
volatile unsigned int  MODBUS_T3_5=40;  

void RS485_Config(void)
{
//*****SPI配置**********
	SPI1CON1bits.SPRE=7; //辅分频1:1
	SPI1CON1bits.PPRE=2; //主分频 4:1 //10M 波特率

	SPI1CON1bits.MSTEN=1;//主动模式时能
	SPI1CON1bits.MODE16=1; //16位数据
	SPI1CON1bits.CKE=1;//
	SPI1CON1bits.SMP=1;
	
	SPI1STATbits.SPIROV=0;//清空溢出标志
	SPI1STATbits.SPIEN=1;//使能引脚
	
//*********引脚控制*****************	
	_TRISB2=0;
	
//****SPI中断禁止*******
	_SPI1IE=0;
	_SPI1IP=0;
}

void CH432T_config(void)//初始化 CH432T
{
	unsigned int i;	
	unsigned int sp,r_bit;
	unsigned long num=115200,speed;
	
	speed=P_E2PROM[117];
	speed<<=16;
	speed+=P_E2PROM[118];	
	sp=num/speed;
	
	if(speed<=19200)
	{
		num=165000;	
		MODBUS_T1_5=num/speed;
		
		num=385000;	
		MODBUS_T3_5=num/speed;
	}
	else
	{
		MODBUS_T1_5=8;
		MODBUS_T3_5=18;	
	}	
	
	
	  if(P_E2PROM[119]==0)    r_bit=0x07;
	else if(P_E2PROM[119]==1) r_bit=0x0b;
	else 				      r_bit=0x1b;

			while(SPI1STATbits.SPITBF==1);
			SS1=0;
			SPI1BUF=CN_IER_reset;
			while(SPI1STATbits.SPIRBF==0);
			i=SPI1BUF;
			SS1=1;
			
			while(SPI1STATbits.SPITBF==1);
			SS1=0;
			SPI1BUF=CN_LCR_write_hz|r_bit;
			while(SPI1STATbits.SPIRBF==0);
			i=SPI1BUF;
			SS1=1;
			
			while(SPI1STATbits.SPITBF==1);
			SS1=0;
			SPI1BUF=CN_DLL|(sp&0xff);
			while(SPI1STATbits.SPIRBF==0);
			i=SPI1BUF;
			SS1=1;
			
			while(SPI1STATbits.SPITBF==1);
			SS1=0;
			SPI1BUF=CN_DLM|(sp>>8);
			while(SPI1STATbits.SPIRBF==0);
			i=SPI1BUF;
			SS1=1;	
			
			while(SPI1STATbits.SPITBF==1);
			SS1=0;
			SPI1BUF=CN_LCR_write|r_bit;
			while(SPI1STATbits.SPIRBF==0);
			i=SPI1BUF;
			SS1=1;
			
			while(SPI1STATbits.SPITBF==1);
			SS1=0;
			SPI1BUF=CN_FCR_write;
			while(SPI1STATbits.SPIRBF==0);
			i=SPI1BUF;
			SS1=1;	
}	

