#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"

//波特率计算
#define FCAN  	40000000 
#define BITRATE 500000  
#define NTQ 	20		// 20 Time Quanta in a Bit Time
#define BRP_VAL		((FCAN/(2*NTQ*BITRATE))-1)

//#define FCAN  	36850000
//#define BITRATE 500000  
//#define NTQ 	20		// 20 Time Quanta in a Bit Time
//#define BRP_VAL		((FCAN/(2*NTQ*BITRATE))-1)

//DMA CAN空间设置
#define  ECAN1_MSG_BUF_LENGTH 	32
typedef unsigned int ECAN1MSGBUF [ECAN1_MSG_BUF_LENGTH][8];	//在RAM空间 定义一个数据组
extern ECAN1MSGBUF  ecan1msgBuf __attribute__((space(dma)));
ECAN1MSGBUF ecan1msgBuf __attribute__((space(dma),aligned(ECAN1_MSG_BUF_LENGTH*16))); //指定变量的最小对齐方式


//
#define ReceiveData   _RBIF  //当接收缓冲区收到数据时，置1，产生中断，手动清零
#define ReceiveBuff0  _RXFUL0//接收缓冲器0,接收标志位
#define ReceiveBuff1  _RXFUL1//接收缓冲器1,接收标志位
#define ReceiveBuff2  _RXFUL2//接收缓冲器2,接收标志位
#define ReceiveBuff3  _RXFUL3//接收缓冲器3,接收标志位
#define ReceiveBuff4  _RXFUL4//接收缓冲器4,接收标志位

void DMA_C1S(void)//DMA配置，CAN1，发送，通道0
{	
	 DMACS0=0;      //所有通道的冲突标志位复位
     DMA0CON=0x2020;//字，从DMA写到外设，所有数据完成中断，正常工作
     				//外设间接寻址模式，禁止连续数据乒乓模式
	 DMA0PAD=0x0442;//CAN1待发送的数据数据寄存器地址，C1TXD
 	 DMA0CNT=0x0007;//DMA 传输计数寄存器位，  这个干嘛要初始化呢，还8次
	 DMA0REQ=0x0046;//CAN1发送 中断地址
	 DMA0STA=  __builtin_dmaoffset(ecan1msgBuf);//DMA RAM起始地址位，不知道用来干嘛的
	 DMA0CONbits.CHEN=1;//使能 通道0
}


void DMA_C1R(void)//DMA配置，CAN1，接收，通道0
{
	 DMACS0=0;
     DMA2CON=0x0020;
	 DMA2PAD=0x0440;	/* ECAN 1 (C1RXD) */
 	 DMA2CNT=0x0007;
	 DMA2REQ=0x0022;	/* ECAN 1 Receive */
	 DMA2STA= __builtin_dmaoffset(ecan1msgBuf);	
	 DMA2CONbits.CHEN=1;
}

void ecan1WriteRxAcptFilter(int n, long identifier, unsigned int exide, unsigned int bufPnt,unsigned int maskSel) 
{//用于配置接收过滤器：n:过滤器号；identifier:SID;exide:0:标准帧，1:扩展帧；bufPnt:缓冲区指针0~14；15fifo；maskSel：11：无屏蔽：else：对应屏蔽器的号码
 //
		unsigned long sid10_0=0, eid15_0=0, eid17_16=0;
		unsigned int *sidRegAddr,*bufPntRegAddr,*maskSelRegAddr, *fltEnRegAddr;

		C1CTRL1bits.WIN=1;
		// Obtain the Address of CiRXFnSID, CiBUFPNTn, CiFMSKSELn and CiFEN register for a given filter number "n"
		sidRegAddr = (unsigned int *)(&C1RXF0SID + (n << 1));
		bufPntRegAddr = (unsigned int *)(&C1BUFPNT1 + (n >> 2));
		maskSelRegAddr = (unsigned int *)(&C1FMSKSEL1 + (n >> 3));
		fltEnRegAddr = (unsigned int *)(&C1FEN1);

	// Bit-filed manupulation to write to Filter identifier register
	if(exide==1) 
	{ 	// Filter Extended Identifier
		eid15_0 = (identifier & 0xFFFF);
		eid17_16= (identifier>>16) & 0x3;
		sid10_0 = (identifier>>18) & 0x7FF;

		*sidRegAddr=(((sid10_0)<<5) + 0x8) + eid17_16;	// Write to CiRXFnSID Register
	    *(sidRegAddr+1)= eid15_0;					// Write to CiRXFnEID Register

	}
	else
	{			// Filter Standard Identifier
		sid10_0 = (identifier & 0x7FF);			
		*sidRegAddr=(sid10_0)<<5;					// Write to CiRXFnSID Register
		*(sidRegAddr+1)=0;							// Write to CiRXFnEID Register
	}

   *bufPntRegAddr = (*bufPntRegAddr) & (0xFFFF - (0xF << (4 *(n & 3)))); // clear nibble
   *bufPntRegAddr = ((bufPnt << (4 *(n & 3))) | (*bufPntRegAddr));       // Write to C1BUFPNTn Register

   *maskSelRegAddr = (*maskSelRegAddr) & (0xFFFF - (0x3 << ((n & 7) * 2))); // clear 2 bits
   *maskSelRegAddr = ((maskSel << (2 * (n & 7))) | (*maskSelRegAddr));      // Write to C1FMSKSELn Register

   *fltEnRegAddr = ((0x1 << n) | (*fltEnRegAddr)); // Write to C1FEN1 Register

   C1CTRL1bits.WIN=0;
}


void ecan1WriteRxAcptMask(int m, long identifier, unsigned int mide, unsigned int exide)
{//配置屏蔽寄存器：m:屏蔽寄存器号；identifier:SID;mide:1,exide:0:标准帧，扩展帧

		unsigned long sid10_0=0, eid15_0=0, eid17_16=0;
		unsigned int *maskRegAddr;

	C1CTRL1bits.WIN=1;

	// Obtain the Address of CiRXMmSID register for given Mask number "m"
	maskRegAddr = (unsigned int *)(&C1RXM0SID + (m << 1));

	// Bit-filed manupulation to write to Filter Mask register
	if(exide==1) 
	{ 	// Filter Extended Identifier
		eid15_0 = (identifier & 0xFFFF);
		eid17_16= (identifier>>16) & 0x3;
		sid10_0 = (identifier>>18) & 0x7FF;

		if(mide==1)
			*maskRegAddr=((sid10_0)<<5) + 0x0008 + eid17_16;	// Write to CiRXMnSID Register
		else
			*maskRegAddr=((sid10_0)<<5) + eid17_16;	// Write to CiRXMnSID Register
	    *(maskRegAddr+1)= eid15_0;					// Write to CiRXMnEID Register
	}
	else
	{			// Filter Standard Identifier
		sid10_0 = (identifier & 0x7FF);			
		if(mide==1)
			*maskRegAddr=((sid10_0)<<5) + 0x0008;					// Write to CiRXMnSID Register
		else
			*maskRegAddr=(sid10_0)<<5;					// Write to CiRXMnSID Register	
		
		*(maskRegAddr+1)=0;							// Write to CiRXMnEID Register
	}

	C1CTRL1bits.WIN=0;	
}


void ecan1WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit)
{//设置发送参数:buf：缓冲区号；txIdentifier:ID;ide：0：标准；1：扩展；remoteTransmit：0：正常消息；1：远程消息；
	
			unsigned long word0=0, word1=0, word2=0;
			unsigned long sid10_0=0, eid5_0=0, eid17_6=0;

		if(ide)
		{
			eid5_0  = (txIdentifier & 0x3F);
			eid17_6 = (txIdentifier>>6) & 0xFFF;
			sid10_0 = (txIdentifier>>18) & 0x7FF;
			word1 = eid17_6;
		}
		else
		{
			sid10_0 = (txIdentifier & 0x7FF);
		}
	
		if(remoteTransmit==1) 
		{ 	// Transmit Remote Frame
			word0 = ((sid10_0 << 2) | ide | 0x2);
			word2 = ((eid5_0 << 10)| 0x0200);
		}
		else 
		{	
			word0 = ((sid10_0 << 2) | ide);
			word2 = (eid5_0 << 10);
		}		
// Obtain the Address of Transmit Buffer in DMA RAM for a given Transmit Buffer number
		if(ide)
			ecan1msgBuf[buf][0] = (word0 | 0x0002);
		else
			ecan1msgBuf[buf][0] = word0;

		ecan1msgBuf[buf][1] = word1;
		ecan1msgBuf[buf][2] = word2;
}

void ecan1WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4)
{//buf：缓冲区号；dataLength:数量;
	ecan1msgBuf[buf][2] = ((ecan1msgBuf[buf][2] & 0xFFF0) + dataLength) ;
	
	ecan1msgBuf[buf][3] = data1;
	ecan1msgBuf[buf][4] = data2;
	ecan1msgBuf[buf][5] = data3;
	ecan1msgBuf[buf][6] = data4;
}

void ecan1DisableRXFilter(int n)//禁止接收过滤使能寄存器
{
	unsigned int *fltEnRegAddr;
   C1CTRL1bits.WIN=1;
   fltEnRegAddr = (unsigned int *)(&C1FEN1);
   *fltEnRegAddr = (*fltEnRegAddr) & (0xFFFF - (0x1 << n));
   C1CTRL1bits.WIN=0;
}

void Ecan1_Config(void)//CAN1模块配置
{
	C1CTRL1bits.REQOP=4;		 //请求配置模式
	while(C1CTRL1bits.OPMODE!=4);//等待进入配置模式
	
//波特率配置
	C1CTRL1bits.CANCKS = 0x1;  //CAN时钟为FCY
	C1CFG1bits.SJW = 0x3;	   //同步跳转宽度
	C1CFG1bits.BRP = BRP_VAL;
	C1CFG2bits.SEG1PH=0x7; //相位缓冲段1：8 TQ
	C1CFG2bits.SEG2PHTS = 0x1;//相位缓冲段2：可自由编程
	C1CFG2bits.SEG2PH = 0x5;//相位缓冲段2：6 TQ
	C1CFG2bits.PRSEG = 0x4; //传播时间段位：5 TQ
	C1CFG2bits.SAM = 0x1;   //总线被采样三次
	
//分配缓冲区
	C1FCTRLbits.FSA=0b01000;	//FIFO区域从第8个缓冲区开始
//	C1FCTRLbits.FSA=0b10000;	//FIFO区域从第16个缓冲区开始
	C1FCTRLbits.DMABS=0b110;	//使用DMA中的32个缓冲器
	
//配置接收缓冲区

//	ecan1WriteRxAcptFilter(1,0x200,0,4,3); //过滤器配置，地址0x201，标准帧，缓冲器4，不屏蔽
//	ecan1WriteRxAcptFilter(1,0x201,0,5,3); //
//	ecan1WriteRxAcptFilter(1,0x202,0,6,3); //
//	ecan1WriteRxAcptFilter(1,0x203,0,7,3);//
//	ecan1WriteRxAcptFilter(1,0x204,0,8,3);//
//	ecan1WriteRxAcptFilter(1,0x205,0,9,3);//
//	ecan1WriteRxAcptFilter(1,0x206,0,10,3);//
//	ecan1WriteRxAcptFilter(1,0x207,0,11,3);//
//	ecan1WriteRxAcptFilter(1,0x208,0,12,3);//

	ecan1WriteRxAcptFilter(0,0x206,0,15,0);//过滤器配置，地址0x206，标准帧，fifo，屏蔽0
	
	ecan1WriteRxAcptMask(0,0x00,1,0);//屏蔽器配置
	
	C1CTRL1bits.REQOP=0;		  //请求正常工作模式
	while(C1CTRL1bits.OPMODE!=0); //等待进入正常工作模式
	
//**********************接收发送消息的控制******************
	C1RXFUL1=C1RXFUL2=C1RXOVF1=C1RXOVF2=0x0000;//接收缓冲器，满寄存器标志位，溢出寄存器标志位 清零
	
	//TR0~TR3为发送缓冲器，需要增加在这里加上
	C1TR01CONbits.TXEN0=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR01CONbits.TXEN1=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR23CONbits.TXEN2=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR23CONbits.TXEN3=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
//	C1TR45CONbits.TXEN4=0;			/* ECAN1, Buffer 0 is a Transmit Buffer */
//	C1TR45CONbits.TXEN5=0;			/* ECAN1, Buffer 0 is a Transmit Buffer */
//	C1TR67CONbits.TXEN6=0;			/* ECAN1, Buffer 0 is a Transmit Buffer */
//	C1TR67CONbits.TXEN7=0;			/* ECAN1, Buffer 0 is a Transmit Buffer */

	//优先级设为最高
	C1TR01CONbits.TX0PRI=0b11; 		/* Message Buffer 0 Priority Level */
	C1TR01CONbits.TX1PRI=0b11; 		/* Message Buffer 0 Priority Level */
	C1TR23CONbits.TX2PRI=0b11; 		/* Message Buffer 0 Priority Level */
	C1TR23CONbits.TX3PRI=0b11; 		/* Message Buffer 0 Priority Level */
//	C1TR45CONbits.TX4PRI=0b11; 		/* Message Buffer 0 Priority Level */
//	C1TR45CONbits.TX5PRI=0b11; 		/* Message Buffer 0 Priority Level */
//	C1TR67CONbits.TX6PRI=0b11; 		/* Message Buffer 0 Priority Level */
//	C1TR67CONbits.TX7PRI=0b11; 		/* Message Buffer 0 Priority Level */
	
	
//******中断使能设置***********************************************
	IEC2bits.C1IE = 1;//ECAN1事件中断使能位
	C1INTEbits.TBIE = 1;//发送缓冲区允许位
	C1INTEbits.RBIE = 1;//接收缓冲区允许位
	
}

void CAN1_examp(void)
{
	ecan1WriteTxMsgBufId(0,0x101,0,0);
	ecan1WriteTxMsgBufData(0,8,0x1111,0x1111,0x1111,0x1111);

	ecan1WriteTxMsgBufId(1,0x102,0,0);
	ecan1WriteTxMsgBufData(1,8,0x2222,0x2222,0x2222,0x2222);

	ecan1WriteTxMsgBufId(2,0x103,0,0);
	ecan1WriteTxMsgBufData(2,8,0x3333,0x3333,0x3333,0x3333);
}	

void __attribute__((interrupt, no_auto_psv))_C1Interrupt(void)  
{    	
	int k,xu[12];//debug
    unsigned int id,num,sign;
	
	IFS2bits.C1IF = 0;        // clear interrupt flag
	if(C1INTFbits.TBIF)//发送中断
    { 
    	C1INTFbits.TBIF = 0;	
    	//发送成功，这里需要一个发送缓冲，用于发送数据组
    } 
 
    if(C1INTFbits.RBIF)//接收中断
    {      
		while(C1FIFObits.FNRB!=C1FIFObits.FBP)
		{
			id=(ecan1msgBuf[C1FIFObits.FNRB][0]>>2) & 0x7FF;	
			xu[0]=ecan1msgBuf[C1FIFObits.FNRB][3];
			xu[1]=ecan1msgBuf[C1FIFObits.FNRB][4];
			xu[2]=ecan1msgBuf[C1FIFObits.FNRB][5];
			xu[3]=ecan1msgBuf[C1FIFObits.FNRB][6];

			if(id==0x155)//测试程序
			{
               TEST_SIGN=1;
               if(xu[0]==0xaaaa&&xu[1]==0xaaaa&&xu[2]==0xaaaa&&xu[3]==0xaaaa)  U1TXREG=5;//CAN 正常
               else  U1TXREG=6;   //CAN通讯错误   
			}
			else
			if((id & 0xff0)==0x100)//电气量收
			{
				sign=ecan1msgBuf[C1FIFObits.FNRB][3] & 0xff;//标识
				num=ecan1msgBuf[C1FIFObits.FNRB][3]>>8;//数量
				
				if(sign<=11)  //发送波形数据
				{
					if(num<63)//
					{
						record_wave[sign][num]=ecan1msgBuf[C1FIFObits.FNRB][4];
						record_wave[sign][num+1]=ecan1msgBuf[C1FIFObits.FNRB][5];
						record_wave[sign][num+2]=ecan1msgBuf[C1FIFObits.FNRB][6];
					}
					else//最后一个点
					{
						record_wave[sign][63]=ecan1msgBuf[C1FIFObits.FNRB][4];	
					}		
				}	
				else
				if(sign>=12)//发送非波形数据 暂时到15
				{
					record_single[sign-12][0]=ecan1msgBuf[C1FIFObits.FNRB][4];
					record_single[sign-12][1]=ecan1msgBuf[C1FIFObits.FNRB][5];
					record_single[sign-12][2]=ecan1msgBuf[C1FIFObits.FNRB][6];
					
					if(sign==15) 
					{
						electric_receive_sign=1;//通知界面数据接收完毕可以
						ask_time=DELAY_elect_synch;
	//					DELAY_TIME=0;
					}
				}
			}
			else
			if(id==0x301)//接收召唤的参数，需要一个标识位
			{			
				sign=(ecan1msgBuf[C1FIFObits.FNRB][3]&0xff)%3;//第几组数据
				
				hide_parameter_b[sign][0]=ecan1msgBuf[C1FIFObits.FNRB][3];
				hide_parameter_b[sign][1]=ecan1msgBuf[C1FIFObits.FNRB][4];
				hide_parameter_b[sign][2]=ecan1msgBuf[C1FIFObits.FNRB][5];
				hide_parameter_b[sign][3]=ecan1msgBuf[C1FIFObits.FNRB][6];
				
				parameter_receive_sign=ecan1msgBuf[C1FIFObits.FNRB][3]&0xff;//一共接收了三组参数	
				parameter_receive_SMSsign=parameter_receive_sign;//同样的赋值
				//if(sign==2) 标识位置位	
			}
			else
			if(id==0x001)//0x001,故障代码以及状态
			{
				sign=ecan1msgBuf[C1FIFObits.FNRB][3];

					DELAY_CAN[0]=0;//清零，用于判断设备是否离线**
					
					equipment_skate[0][0]=sign;
					if(ecan1msgBuf[C1FIFObits.FNRB][4]!=0)//如果有故障代码才赋值
				            equipment_skate[0][1]=ecan1msgBuf[C1FIFObits.FNRB][4];//故障代码
					equipment_skate[0][2]=ecan1msgBuf[C1FIFObits.FNRB][5];//运行状态
					equipment_skate[0][3]=ecan1msgBuf[C1FIFObits.FNRB][6];//设备开关量
	
					k++;
			}
			else
			if(id==0x400)//生产编号
			{
				sign=ecan1msgBuf[C1FIFObits.FNRB][4];//ID 设备ID
				equipment_ID[0][1]=sign;
				equipment_ID[0][2]=xu[2];
				equipment_ID[0][3]=xu[3];	
			}
			
	//读取结束，清标识位		
			if(C1FIFObits.FNRB<16)//
				C1RXFUL1=~(0x01<<C1FIFObits.FNRB);
			else
				C1RXFUL2=~(0x01<<(C1FIFObits.FNRB-16));
			C1INTFbits.RBIF = 0;
			
			k++;
		
		}
		
	}
	
	//	IFS2bits.C1IF=0;//不用清零？？
	
}


void __attribute__((interrupt, no_auto_psv))_C2Interrupt(void)  
{
	IFS3bits.C2IF = 0;        // clear interrupt flag
	if(C2INTFbits.TBIF)
    { 
		C2INTFbits.TBIF = 0;
    } 
    
    if(C2INTFbits.RBIF)
     {      
		C2INTFbits.RBIF = 0;
     }
}
 

//------------------------------------------------------------------------------
//    DMA interrupt handlers
//------------------------------------------------------------------------------

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
   IFS0bits.DMA0IF = 0;          // Clear the DMA0 Interrupt Flag;
}

void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
   IFS0bits.DMA1IF = 0;          // Clear the DMA1 Interrupt Flag;
}

void __attribute__((interrupt, no_auto_psv)) _DMA2Interrupt(void)
{
   IFS1bits.DMA2IF = 0;          // Clear the DMA2 Interrupt Flag;
}

void __attribute__((interrupt, no_auto_psv)) _DMA3Interrupt(void)
{
   IFS2bits.DMA3IF = 0;          // Clear the DMA3 Interrupt Flag;
}







