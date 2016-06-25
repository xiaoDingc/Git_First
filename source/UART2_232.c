#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"

void RS232dis_Config(void)//串口屏配置
{
	_U2EIE=0;	//U1,错误中断允许：遇到错误进中断复位
	_U2TXIE=0;	//U1发送器中断允许
	_U2RXIE=0;	//U1接收器中断允许
	
	U2MODE=0x8000;//启动两个串口引脚，8数据，1停止，无校验
//	U2MODE=0x8002;//启动两个串口引脚，8数据，1停止，偶校验
//	U2BRG=0x103;   //9600    40M/16/9600-1
	U2BRG=21;   //115200   40M/16/115200-1
	
//	U1BRG=0x81;   //19200    40M/16/19200-1
	
//	U1STA=0x0400; //禁用中断标志，发送使能
	U2STA=0x0400; //禁用中断标志，发送使能
}

void RS232dis_Sdata(void)//发送
{	
	while(RS232dis_Sfifo==0) //如果不满就往里面加数据
		U2TXREG=0xaa;	
}	

void RS232dis_Rdata(void)//如果有数据就读出来
{
	unsigned int i=0,j=0,data[10];	
	while(1)
	{
			if(RS232dis_Rfifo==1) 
			{
				data[j++]=U2RXREG;
				if(j==10) 
				i++;//设断点，看收到的数据是否正确
			}	
	}
}	

















