#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"
//
#define LED1 LATBbits.LATB12
#define LED2 LATBbits.LATB13
#define LED3 LATBbits.LATB14
#define LED4 LATBbits.LATB15

#define LED5 LATDbits.LATD12
#define LED6 LATDbits.LATD3
#define LED7 LATDbits.LATD2
#define LED8 LATDbits.LATD1

#define SW1 PORTCbits.RC3
#define SW2 PORTCbits.RC2
#define SW3 PORTCbits.RC1
#define SW4 PORTGbits.RG15


void DELAY(unsigned long time)//临时用，单位us
{
	unsigned long i;
	for(i=0;i<time;i++){Nop();}
}

void LED_Config(void)//初始化，LED，数码管，拨位开关的I/O
{
     AD1PCFGH=0xffff;
     AD1PCFGL=0xffff;
     AD2PCFGL=0xffff;
	
	_TRISB12=0;
	_TRISB13=0;
	_TRISB14=0;
	_TRISB15=0;//输出引脚
	
	_TRISD12=0;
	_TRISD3=0;
	_TRISD2=0;
	_TRISD1=0;//输出引脚
	
	
	_TRISC3=1;
	_TRISC2=1;
	_TRISC1=1;
	_TRISG15=1;//输入引脚
	
	LED1=0;
	LED2=0;
	LED3=0; 
	LED4=0;
}


void LED_ray(void)  //流水灯
{
	unsigned int i;
	
	while(1)
	{
				if(i==0) LED1=1;else LED1=0;
				if(i==1) LED2=1;else LED2=0;
				if(i==2) LED3=1;else LED3=0;
				if(i==3) LED4=1;else LED4=0;
				if(i==4) LED5=1;else LED5=0;
				if(i==5) LED6=1;else LED6=0;
				if(i==6) LED7=1;else LED7=0;
				if(i==7) LED8=1;else LED8=0;
		i++;
		if(i>7) i=0;
		DELAY(800000);	
	}
}	

void LED_light(unsigned char data)  //led灯，二进制显示
{
		LED1=data;
		LED2=data>>1;
		LED3=data>>2; 
		LED4=data>>3;
}

void LED_light_ray(unsigned data)
{
	unsigned int i;
	for(i=0;i<10;i++)
	{
		LED_light(data);
		DELAY(800000);
		LED_light(0);
		DELAY(100000);	
	}		
}	

unsigned char switch_num(void)  //二进制返回拨码开关状态
{
		unsigned char num=0;	
		num=num | SW4;
		num=(num<<1)|SW3;
		num=(num<<1)|SW2;
		num=(num<<1)|SW1;	
		num^=0x0f;
		return num;
}











