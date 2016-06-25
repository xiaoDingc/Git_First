#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"

volatile unsigned int TEST_SIGN;

void Ecan1_Config_test(void)//CAN1模块配置
{
	C1CTRL1bits.REQOP=4;		 //请求配置模式
	while(C1CTRL1bits.OPMODE!=4);//等待进入配置模式
	
//波特率配置
	C1CTRL1bits.CANCKS = 0x1;  //CAN时钟为FCY
	C1CFG1bits.SJW = 0x3;	   //同步跳转宽度
	C1CFG1bits.BRP = 19;       //50K 波特率
	C1CFG2bits.SEG1PH=0x7; //相位缓冲段1：8 TQ
	C1CFG2bits.SEG2PHTS = 0x1;//相位缓冲段2：可自由编程
	C1CFG2bits.SEG2PH = 0x5;//相位缓冲段2：6 TQ
	C1CFG2bits.PRSEG = 0x4; //传播时间段位：5 TQ
	C1CFG2bits.SAM = 0x1;   //总线被采样三次
	
//分配缓冲区
	C1FCTRLbits.FSA=0b01000;	//FIFO区域从第8个缓冲区开始
	C1FCTRLbits.DMABS=0b110;	//使用DMA中的32个缓冲器
	
//配置接收缓冲区
	ecan1WriteRxAcptFilter(0,0x206,1,15,0);//过滤器配置，地址0x206，，fifo，屏蔽0
	
	ecan1WriteRxAcptMask(0,0x00,1,0);//屏蔽器配置
	
	C1CTRL1bits.REQOP=0;		  //请求正常工作模式
	while(C1CTRL1bits.OPMODE!=0); //等待进入正常工作模式
	
//**********************接收发送消息的控制******************
	C1RXFUL1=C1RXFUL2=C1RXOVF1=C1RXOVF2=0x0000;//接收缓冲器，满寄存器标志位，溢出寄存器标志位 清零
	
	//TR0~TR3为发送缓冲器，需要增加在这里加上
	C1TR01CONbits.TXEN0=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
	
	//优先级设为最高
	C1TR01CONbits.TX0PRI=0b11; 		/* Message Buffer 0 Priority Level */

	
//******中断设置***********************************************
	IEC2bits.C1IE = 1;//ECAN1事件中断使能位
	C1INTEbits.TBIE = 1;//发送缓冲区允许位
	C1INTEbits.RBIE = 1;//接收缓冲区允许位
	
}

void UART232_receive(void)//接收数据，如果接收到为1，则转发出去
{
	unsigned char receive;	

	while(1)
	{
		if(RS232_Rfifo==1)
		{
		   receive=U1RXREG;
		   if(receive==1)
		   {
                U1TXREG=1;//回发01  232正常
				break;
		   }
		}
	}
}

void CAN_TEST(void)
{
	TEST_SIGN=0;
	ecan1WriteTxMsgBufId(0,0x0555AAA0,1,0);
	ecan1WriteTxMsgBufData(0,8,0xaaaa,0xaaaa,0xaaaa,0xaaaa);
	C1TR01CONbits.TXREQ0=1;
	
	DELAY_TIME=0;
	while(1)
	{
		if(TEST_SIGN==1)   break;
		else
		if(DELAY_TIME>=5000)//大概500ms
		{
			U1TXREG=7;//can收不到数据
			break;
		}
	}	
}	

void E2PROM_test(void)
{
	E2ROM_93LC86C_writedata(1023,0xaaaa);
	if(E2ROM_93LC86C_readdata(1023)==0xaaaa) 
	{
		U1TXREG=14;
		LED_light(2);
	}	
	else                                     
	{
		U1TXREG=15;	
		LED_light_ray(2);
	}	
}	

void SCI485_receive(void)//接收数据，并把最后一个数据转发出去
{
	unsigned char receive,num=0,SCI_erro=0;
	unsigned char xu[8],xu_num=0,k;
	

	while(num<=6)//发六个数据
	{	
		while(SPI1STATbits.SPITBF==1);
		SS1=0;
		SPI1BUF=CN_THR|0xaa;
		while(SPI1STATbits.SPIRBF==0);
		k=SPI1BUF;
		SS1=1;
					
		num++;
 	}   

	num=0;
	DELAY_TIME=0;//计时清零
	while(1)
	{
		//*****接收一个数据****************************		
			while(SPI1STATbits.SPITBF==1);
			SS1=0;
			SPI1BUF=CN_LSR;
			while(SPI1STATbits.SPIRBF==0);
			k=SPI1BUF;
			SS1=1;
			
			CH432T_reset=(k>>7)&0x01;
			RS485_receive=k&0x01;// DATARDY 为1 则说明有数据可以读出  0无收到数据
			RS485_send_fifo=(k>>5)&0x01;// THRE 1可以继续向fifo发送数据，0,fifo已满 16级
			RS485_send_over=(k>>6)&0x01;// TEMT 1发送全部发完		
		
		if(RS485_receive==1)
		{
				while(SPI1STATbits.SPITBF==1);
				SS1=0;
				SPI1BUF=0;
				while(SPI1STATbits.SPIRBF==0);
				receive=SPI1BUF;
				SS1=1;			
				xu[xu_num++]=receive;
				
				if(receive==0x55)
				{
					num++;		
					if(num>=5)
					{
						U1TXREG=2;//485链路正常			
						break;
					}
				}
				else
				{
							SCI_erro++;
							if(SCI_erro>=3)
							{
								U1TXREG=3;//485通讯错误，
								break;
							}
				}
			
		}
	    
	      	if(DELAY_TIME>=10000)//大概1000ms
			{
					U1TXREG=4;//485 通讯 无数据 建议换光耦
					break;
			}
	}
}

void TEST_ALL(void)//所有的测试
{	
 	unsigned char name[]=
 	{
	  0xCC,0xDD,0x04,0x80,0x03,0x00,0x02,0xCC,0xDD,0x11,0x82,0x1A,0xF4,0xB4,0xAE,0xBF,0xDA,0xC6,0xC1,0xCD,0xA8,0xD0,0xC5,0xD5,0xFD,0xB3,0xA3 	 	
	};
	unsigned int i=0;
 	
 	Ecan1_Config_test();//测试CAN配置
	      
   while(1)
   {
		    UART232_receive();//232
		    CAN_TEST();       //CAN	
		    SCI485_receive();//485		
	
		E2PROM_test();
		
		while(i<27)
		{
			if(RS232dis_Sfifo==0)
					U2TXREG=name[i++];	
		}
		
		U1TXREG=8;
	
		i=0;
		U1TXREG=255;//结束标志				
	}
}


