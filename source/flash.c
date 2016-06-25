#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"
#include "..\include\string_h.h"


#define K9F_CLE   LATDbits.LATD13   //命令锁存使能
#define K9F_ALE   LATDbits.LATD12	 //地址锁存使能
#define K9F_CE	   LATCbits.LATC13   //芯片使能
#define K9F_RE	   LATGbits.LATG2   //读写使能
#define K9F_WE	   LATGbits.LATG3   //写使能实能

#define K9F_RB	   PORTAbits.RA2  //读忙 DSPIC输入

#define  K9F_O_data    LATDbits.LATD0_7  //DSPIC输出
#define  K9F_I_data    PORTDbits.RD0_7   //DSPIC输入
#define  K9F_Idata 	 TRISDbits.TRISD0_7=0xff;//从K9F到DSPIC
#define  K9F_Odata   TRISDbits.TRISD0_7=0x00;//从DSPIC到K9F


unsigned char flash_buffer[512];

void K9F1208_Config(void)//flash 初始化
{
	_TRISD13=0;
	_TRISD12=0;
	_TRISC13=0;
	_TRISG2=0;
	_TRISG3=0;	
	_TRISA2=1;
	
	K9F_CE=1;
	K9F_RE=1;
	K9F_WE=1;
	K9F_CLE=0;
	K9F_ALE=0;
}	

void K9F1208_Wdata(unsigned char data)//写数据
{
	K9F_Odata;//输出
	K9F_CLE=0;
	K9F_ALE=0;
	K9F_WE=0;
	K9F_O_data=data;
	Nop();
	K9F_WE=1;
}	

unsigned char K9F1208_Rdata(void)//读数据
{
	unsigned char data;
	K9F_Idata;//输入
	K9F_CLE=0;
	K9F_ALE=0;
	K9F_RE=1;	
	K9F_RE=0;
	Nop();Nop();
	data=K9F_I_data;
	
	return data;
}	

void K9F1208_Wcmd(unsigned char cmd)//写命令
{
	K9F_Odata;//输出
	K9F_CLE=1;
	K9F_ALE=0;
	K9F_RE=1;
	K9F_WE=0;
	K9F_O_data=cmd;
	Nop();
	K9F_WE=1;	
}

void K9F1208_Wadd(unsigned long page,unsigned char byte)//写地址
{
	unsigned int i;
	K9F_Odata;//输出
	K9F_CLE=0;
	K9F_ALE=1;
	
	K9F_WE=0;
	K9F_O_data=byte;
	Nop();
	K9F_WE=1;

	for(i=0;i<3;i++)
	{
			K9F_ALE=0;
			K9F_ALE=1;
			K9F_WE=0;
			K9F_O_data=page & 0xff;
			page>>=8;
			K9F_WE=1;
	}
}

void K9F1208_Wadd_block(unsigned int addr)//写擦除地址
{
	unsigned int i;
	K9F_Odata;//输出
	K9F_CLE=0;
	K9F_ALE=1;
	
	for(i=0;i<3;i++)
	{			
			K9F_ALE=1;
			K9F_WE=0;
			K9F_O_data=addr & 0xff;
			addr>>=8;
			K9F_WE=1;
			K9F_ALE=0;
	}
}


void K9F1208_Wpage(unsigned long page,unsigned int num,unsigned char *character)//写一页
{
	unsigned int i;
		
	K9F_CE=0;
	K9F1208_Wcmd(0x80);
	K9F1208_Wadd(page,0);
	
	for(i=0;i<num;i++)
		K9F1208_Wdata(*(character+i));
	
	K9F1208_Wcmd(0x10);//结束
	
	while(K9F_RB==0);  //等待写完，这里可以处理成并行的
	
	K9F_CE=1;
}



void K9F1208_Rpage(unsigned long page,unsigned int byte,unsigned int num,unsigned char *character)//读一页
{
	unsigned int i;
	unsigned char data;
	
	K9F_CE=0;
	
	if(byte<256) K9F1208_Wcmd(0x00);
	else         K9F1208_Wcmd(0x01);
		
	data=byte;
	K9F1208_Wadd(page,data);	
	while(K9F_RB==0);
		
	for(i=0;i<num;i++)
			*(character++)=K9F1208_Rdata();	
	K9F_CE=1;
	K9F_Odata;
	K9F_RE=1;
}

void erase_block(unsigned long BLOCK)//擦除块(0--4095)
{
	K9F_CE=0;
	K9F1208_Wcmd(0x60);
	K9F1208_Wadd_block(BLOCK);
	K9F1208_Wcmd(0xD0);
	while(K9F_RB==0);
	K9F_CE=1;
}


void erase_block_all(void)//删除所有块
{
	unsigned int i;	
	for(i=0;i<4096;i++)
		erase_block(i*32);		
}	

