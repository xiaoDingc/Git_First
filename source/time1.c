#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"

volatile unsigned long DELAY_TIME;
volatile unsigned long DELAY_SLEEP;//每多长时间采样一次背光触摸
volatile unsigned long DELAY_Blight;//背光
volatile unsigned long DELAY_ASKTIME=500000;//每多长时间询问一下当前时间
volatile unsigned long DELAY_DSIskate;//状态显示
volatile unsigned long DELAY_CAN[8];//CAN通讯延时
volatile unsigned long DELAY_run_time=0;//计算设备运行时间
volatile unsigned long DELAY_refresh_data;//数据刷新时间
volatile unsigned long DELAY_GSM;//发送信息延时
volatile unsigned long DELAY_send_message;//发送信息，读时间延时
volatile unsigned long DELAY_message;
volatile unsigned long DELAY_fist_page=0;
volatile unsigned long DELAY_GSM_error;
volatile unsigned long DELAY_time_test;
volatile unsigned long DELAY_elect_synch;//同步时间控制
volatile unsigned int  MODBUS_TIME;
volatile unsigned long DELAY_GSM_NUM=0;//上电发送短信中心号码延时

volatile unsigned long  DELAY2_time_test;//****
//串口屏*******
volatile unsigned long DELAY_refresh_data_com;

volatile unsigned int run_time_sign=0;//运行时间改变标识


void time1_config(unsigned int time)//us 最大177us
{	
	
	PR1=time*40;;//1us 需要多少个定时器周期
	
	_TSIDL=0;//空闲继续工作
	_TGATE=0;//禁止门控
	_TCKPS=0;//分频1:1
	_TSYNC=0;//不同步外部时钟
	_TCS=0;   //使用内部时钟	
	
	//中断配置
	
	_T1IE=1;//允许中断
	_T1IP=7;//优先级最高
	
}

void time2_config(unsigned int time)//us 最大
{	
	
	PR2=time*40;//1us 需要多少个定时器周期
	
	
	T2CONbits.T32=0; //两个16位
	T2CONbits.TCKPS=0;//分频1:1
	T2CONbits.TCS=0;//内部时钟
	T2CONbits.TGATE=0;//禁止门控
	T2CONbits.TSIDL=0;//空闲继续工作	
	//中断配置
	
	_T2IE=1;//允许中断
	_T2IP=4;//优先级较低
	
	T2CONbits.TON=1;//直接启动
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)//定时器1 中断
{
	unsigned int m;
		DELAY_TIME++;
		DELAY_SLEEP++; //用来问询触摸的延时
		DELAY_Blight++;//背光时间
		DELAY_ASKTIME++;
		DELAY_DSIskate++;
		for(m=0;m<8;m++) DELAY_CAN[m]++;//CAN通讯延时
		DELAY_run_time++;//计算运行时间
		DELAY_refresh_data++;
		DELAY_GSM++;
		DELAY_send_message++;
		DELAY_message++;
		DELAY_fist_page++;
		DELAY_GSM_error++;
		DELAY_elect_synch++;
		MODBUS_TIME++;
		DELAY_GSM_NUM++;
		
		DELAY_time_test++;
		
//串口屏*******
		DELAY_refresh_data_com++;//刷新时间
		
//****************喂狗**********************************************
		clearWdog();
		
//**********modbus**************************************************
//		modbus_in();

//********串口屏指令接收********************************************
		RS232_Slcd();
		RS232_Rlcd();

//*******************GSM短信猫功能*************************************
#if compileGSM
                RS232_Rdata();//接收
		RS232_Sdata();
#endif
//********运行时间**************************************************		
		if(DELAY_run_time>=600000)//100us*600000=60s
		{					
			if(APF_state==1)//如果设备正在运行
			{
				P_E2PROM[3]++;

				if(P_E2PROM[3]>=1440)
				{
					P_E2PROM[4]++;
					P_E2PROM[3]=0;
				}				
				run_time_sign++;//说明运行时间变化过
			}
			
			if(((equipment_skate[0][3]>>2)&0x01)==1)
			{
				P_E2PROM[111]++;

				if(P_E2PROM[111]>=1440)
				{
					P_E2PROM[112]++;
					P_E2PROM[111]=0;
				}
				run_time_sign++;//说明时间变化过	
			}
	
			DELAY_run_time=0;	
		 }
			
	IFS0bits.T1IF=0;//清零，准备下一个中断	
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)//定时器1 中断
{
	DELAY2_time_test++;
#if compilemodbus
	modbus_in();

	modbus_Shandle();
#endif
	IFS0bits.T2IF=0;
} 

