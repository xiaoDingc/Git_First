#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"
#if compilemodbus
 volatile unsigned int MODBUS_SIGN=4; 	//发送标识
								//0：从未收到数据
                    			//1:收到数据
	                   			//2：一个帧接收数据完毕
 volatile unsigned int Modbus_mortize=0;     //用于发送缓冲

 volatile unsigned char __attribute__((__far__))   MODBUS_RECEIVE[64];//接收数据缓冲区
 volatile unsigned int MODBUS_RECEIVE_LENGTH=0;     //接收数据缓冲区中的数据的个数

 volatile unsigned char __attribute__((__far__))   MODBUS_SEND[256];//发送数据缓冲区
 volatile unsigned int MODBUS_SEND_LENGTH=0;     //发送数据缓冲区中的数据的个数


volatile int  __attribute__((__far__))  Modbus_electric[ELECTRIC_N];	   //  电气量  30001~~39999
 volatile int  __attribute__((__far__))  Modbus_parameter[PARAMETER_N][2];  // 参数    40001~~49999
 		  
 volatile unsigned int Modbus_write_sign=0;//是否有开关量或者参数被写入


void modbus_init()//初始化，数据变量清零******
{
   int i,j;
   for(i=0;i<2;i++)
   {		
		for(j=0;j<PARAMETER_N;j++)
			Modbus_parameter[j][i]=0;	
   }
	for(i=0;i<ELECTRIC_N;i++)	
   			Modbus_electric[i]=0; 
}

void modbus_change()//监测参数，开关量的变化，根据实际的数据修改
{
	Modbus_electric[2] =WIRE_cost[0][0];
	Modbus_electric[3] =WIRE_cost[0][1];
	Modbus_electric[4] =WIRE_cost[0][2];//
	Modbus_electric[5] =WIRE_cost[1][0];
	Modbus_electric[6] =WIRE_cost[1][1];
	Modbus_electric[7] =WIRE_cost[1][2];//
	Modbus_electric[8] =WIRE_cost[2][0];
	Modbus_electric[9] =WIRE_cost[2][1];
	Modbus_electric[10]=WIRE_cost[2][2];//
	Modbus_electric[11]=WIRE_cost[3][0];
	Modbus_electric[12]=WIRE_cost[3][1];
	Modbus_electric[13]=WIRE_cost[3][2];
	Modbus_electric[14]=WIRE_cost[4][0];
	Modbus_electric[15]=WIRE_cost[4][1];
	Modbus_electric[16]=WIRE_cost[4][2];
	Modbus_electric[17]=WIRE_cost[5][0];
	Modbus_electric[18]=WIRE_cost[5][1];	
	Modbus_electric[19]=WIRE_cost[5][2];//
	
	Modbus_electric[20]=LOAD_cost[0][0];
	Modbus_electric[21]=LOAD_cost[0][0];
	Modbus_electric[22]=LOAD_cost[0][0];
	
	Modbus_electric[23]=LOAD_cost[1][0];
	Modbus_electric[24]=LOAD_cost[1][1];
	Modbus_electric[25]=LOAD_cost[1][2];
	Modbus_electric[26]=LOAD_cost[2][0];
	Modbus_electric[27]=LOAD_cost[2][1];
	Modbus_electric[28]=LOAD_cost[2][2];
	Modbus_electric[29]=LOAD_cost[3][0];
	Modbus_electric[30]=LOAD_cost[3][1];
	Modbus_electric[31]=LOAD_cost[3][2];
	Modbus_electric[32]=LOAD_cost[4][0];
	Modbus_electric[33]=LOAD_cost[4][1];
	Modbus_electric[34]=LOAD_cost[4][2];
	Modbus_electric[35]=LOAD_cost[5][0];
	Modbus_electric[36]=LOAD_cost[5][1];
	Modbus_electric[37]=LOAD_cost[5][2];
	Modbus_electric[38]=WIRE_cost[6][0];
	Modbus_electric[39]=WIRE_cost[6][1];
	Modbus_electric[40]=WIRE_cost[6][2];
	
	Modbus_electric[41]=equipment_skate[0][2];
	Modbus_electric[42]=0;
	Modbus_electric[43]=0;
	Modbus_electric[44]=0;
	Modbus_electric[45]=0;
	Modbus_electric[46]=0;
	Modbus_electric[47]=0;
	Modbus_electric[48]=0;
	
	Modbus_electric[49]=(equipment_skate[0][3]>>2)&0x01;
	Modbus_electric[50]=0;
	Modbus_electric[51]=0;
	Modbus_electric[52]=0;
	Modbus_electric[53]=0;
	Modbus_electric[54]=0;
	Modbus_electric[55]=0;
	Modbus_electric[56]=0;
	
	Modbus_electric[57]=record_single[1][0];
	Modbus_electric[58]=0;
	Modbus_electric[59]=0;
	Modbus_electric[60]=0;
	Modbus_electric[61]=0;
	Modbus_electric[62]=0;
	Modbus_electric[63]=0;
	Modbus_electric[64]=0;

	Modbus_electric[65]=record_single[1][1];
	Modbus_electric[66]=0;
	Modbus_electric[67]=0;
	Modbus_electric[68]=0;
	Modbus_electric[69]=0;
	Modbus_electric[70]=0;
	Modbus_electric[71]=0;
	Modbus_electric[72]=0;
	Modbus_electric[73]=WIRE_cost[7][0];
	Modbus_electric[74]=WIRE_cost[7][1];
	Modbus_electric[75]=WIRE_cost[7][2];

        Modbus_electric[76]=1<<equipment_skate[0][2];
	Modbus_electric[77]=1<<equipment_skate[1][2];
	Modbus_electric[78]=1<<equipment_skate[2][2];
	Modbus_electric[79]=1<<equipment_skate[3][2];
	Modbus_electric[80]=1<<equipment_skate[4][2];
	Modbus_electric[81]=1<<equipment_skate[5][2];
	Modbus_electric[82]=1<<equipment_skate[6][2];
	Modbus_electric[83]=1<<equipment_skate[7][2];

	if(Modbus_electric[0] == 0)
	{
		Modbus_electric[84] = 0;
		Modbus_electric[85] = 0;
		Modbus_electric[86] = 0;
		Modbus_electric[87] = 0;
                Modbus_electric[88] = 0;
	}
	else
	if(Modbus_electric[0]<=16)
	{
		Modbus_electric[84] = 1<<(Modbus_electric[0]-1);
		Modbus_electric[85] = 0;
		Modbus_electric[86] = 0;
		Modbus_electric[87] = 0;
                Modbus_electric[88] = 0;
	}
	else
	if(Modbus_electric[0]<=32)
	{
		Modbus_electric[84] = 0;
		Modbus_electric[85] = 1<<(Modbus_electric[0]-17);
		Modbus_electric[86] = 0;
		Modbus_electric[87] = 0;
                Modbus_electric[88] = 0;

	}
	else
	if(Modbus_electric[0]<=48)
	{
		Modbus_electric[84] = 0;
		Modbus_electric[85] = 0;
		Modbus_electric[86] = 1<<(Modbus_electric[0]-33);
		Modbus_electric[87] = 0;
                Modbus_electric[88] = 0;

	}
	else
	if(Modbus_electric[0]<=64)
	{
		Modbus_electric[84] = 0;
		Modbus_electric[85] = 0;
		Modbus_electric[86] = 0;
		Modbus_electric[87] = 1<<(Modbus_electric[0]-49);
                Modbus_electric[88] = 0;
	}
        else
	if(Modbus_electric[0]<=80)
	{
		Modbus_electric[84] = 0;
		Modbus_electric[85] = 0;
		Modbus_electric[86] = 0;
		Modbus_electric[87] = 0;
                Modbus_electric[88] = 1<<(Modbus_electric[0]-65);
	}
	else
	{
		Modbus_electric[84] = 0;
		Modbus_electric[85] = 0;
		Modbus_electric[86] = 0;
		Modbus_electric[87] = 0;
                Modbus_electric[88] = 0;
	}
	
	Modbus_parameter[0][0]=0xffff;
	Modbus_parameter[1][0]=equipment_skate[0][2];
	Modbus_parameter[2][0]=0;
	Modbus_parameter[3][0]=0;
	Modbus_parameter[4][0]=0;
	Modbus_parameter[5][0]=0;
	Modbus_parameter[6][0]=0;
	Modbus_parameter[7][0]=0;
	Modbus_parameter[8][0]=0;
}

void modbus_Shandle(void)//
{
	unsigned int i,j;
	
	if(Modbus_write_sign!=0)
	{
		for(i=0;i<2;i++)
		{
			if(Modbus_parameter[i][1]==1)
			{
				if(Modbus_parameter[i][0]==0) {j=1;WRITE_fault_one(43,0);Modbus_electric[0]=43;Modbus_electric[1]=1;}
				else
				if(Modbus_parameter[i][0]==1) {j=2;WRITE_fault_one(42,0);Modbus_electric[0]=42;Modbus_electric[1]=1;}
				else
				if(Modbus_parameter[i][0]==2) {j=5;WRITE_fault_one(54,0);Modbus_electric[0]=54;Modbus_electric[1]=1;}
				else
				if(Modbus_parameter[i][0]==5) {j=6;WRITE_fault_one(53,0);Modbus_electric[0]=53;Modbus_electric[1]=1;}//命令
				else                           j=9;
				
				ecan1WriteTxMsgBufId(1,0x201,0,0);
				ecan1WriteTxMsgBufData(1,8,j,0,0,0);//运行命令
				C1TR01CONbits.TXREQ1=1;
				
				Modbus_parameter[i][1]=0;
			}	
		}
		
		Modbus_write_sign=0;
	}
}

/*********************************************************************/
//函数名: modbus_get_crc16()
//描述:  进行modbus的CRC的计算(非查表)
//日期:2010.12.10
//功能：计算出发送报文的CRC校验，并加在报文的后面 低字节在前，高字节在后
//输入:全局变量：MODBUS_SEND:报文的首地址
//				MODBUS_SEND_LENGTH:报文的长度
//输出:         计算出报文的CRC校验，并加在报文的后面 低字节在前，高字节在后
/*********************************************************************/
 void modbus_get_crc16() 
{
    unsigned int i,j;
    unsigned int c, crc = 0xFFFF;
    for (i = 0; i < MODBUS_SEND_LENGTH; i++)
    {
		c=MODBUS_SEND[i] & 0x00ff;

   		crc^=c;
        	for(j=0;j<8;j++){
             	if (crc & 0x0001)
                 	{crc>>=1;crc^=0xA001;}
             	else crc>>=1;
        	}
    }
	MODBUS_SEND[MODBUS_SEND_LENGTH++]=crc & 0xff;
	MODBUS_SEND[MODBUS_SEND_LENGTH++]=(crc >> 8) & 0xff;
} 

/*********************************************************************/
//函数名: modbus_if_crc16() 
//描述:  进行modbus的CRC的计算(非查表)
//日期:2010.12.10
//功能：判断收到数据的报文是否正确
//输入:全局变量：MODBUS_RECEIVE:报文的首地址
//				MODBUS_RECEIVE_LENGTH:报文的长度
//输出:         判断收到报文CRC校验是否正确，如果正确返回1，如果错误返回0
/*********************************************************************/
int modbus_if_crc16()
{
    unsigned int i,j;
    unsigned int c, crc = 0xFFFF;
    for (i = 0; i < MODBUS_RECEIVE_LENGTH-2; i++)
    {
		c=MODBUS_RECEIVE[i] & 0x00ff;

   		crc^=c;
        	for(j=0;j<8;j++){
             	if (crc & 0x0001)
                 	{crc>>=1;crc^=0xA001;}
             	else crc>>=1;
        	}
    }

	if((MODBUS_RECEIVE[MODBUS_RECEIVE_LENGTH-2]==(crc & 0xff))&&(MODBUS_RECEIVE[MODBUS_RECEIVE_LENGTH-1]==((crc >> 8) & 0xff)))
	     return 1;
	else return 0;
}  


/****************************************/
//函数名: unsigned int modbus_read_data()
//描述:  基于DSP2812 SCIB 的 modbus 接收 数据
//日期:2010.12.10
//宏变量：MODBUS_T1_5：需要进入时间中断的次数		
//全局变量：SCIB_NUM:实际进入时间中断的次数
//			MODBUS_RECEIVE:报文的首地址
//			MODBUS_RECEIVE_LENGTH:报文的长度
//输入:RECEIVE_SIGN  0：从未收到数据
//                    1:收到数据
//                    2：一个帧接收数据完毕
//输出:返回RECEIVE_SIGN ，以判断一个帧是否接收完毕
/****************************************/
void modbus_read_data()
{   
	unsigned int k;
	
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
			
		if(RS485_receive==0)
		{
			 if(MODBUS_SIGN==1)  //已经收到过数据，
			 {     
					if(MODBUS_TIME>=MODBUS_T1_5)
					{
							MODBUS_SIGN=2;  //表示可以处理数据了
							MODBUS_TIME=0;     //置位时间，要在T3.5 后发出		
					}
			 }
		}
		else //如果收到了数据，	
	   {				
			MODBUS_SIGN=1;     //已经收到了第一个数据
			MODBUS_TIME=0;			//置位时间

				while(SPI1STATbits.SPITBF==1);
				SS1=0;
				SPI1BUF=0;
				while(SPI1STATbits.SPIRBF==0);
				MODBUS_RECEIVE[MODBUS_RECEIVE_LENGTH++]=SPI1BUF;
				SS1=1;
	   }
}


/****************************************/
//函数名:unsigned int modbus_analysis()
//描述: 分析收到的是什么样报文,并设置回发函数
//日期:2010.12.10

/****************************************/
void modbus_analysis()
{   
//	 char MODBUS_RECEIVE[128]={0};//接收数据缓冲区
// 	unsigned int MODBUS_RECEIVE_LENGTH=0;     //接收数据缓冲区中的数据的个数
  unsigned int addr_begin,data_num,data_value;
  unsigned int i,j;//,k,l; 

		if(MODBUS_RECEIVE[1]==4) //读取电气量@@***********************************************************
	    {
			addr_begin=MODBUS_RECEIVE[2];
			addr_begin=(addr_begin<<8) | MODBUS_RECEIVE[3];//起始地址

			data_num=MODBUS_RECEIVE[4];
			data_num=(data_num<<8) | MODBUS_RECEIVE[5];//数量

			MODBUS_SEND[MODBUS_SEND_LENGTH++]=data_num<<1;//字节数=寄存器数量乘以2

			j=addr_begin-30001;//电气量减去30000  防止溢出待处理

			if((data_num<1)||(data_num>0x007d))     //异常码3
			{
				MODBUS_SEND[MODBUS_SEND_LENGTH-2]=MODBUS_RECEIVE[1]|0x80;//功能码改成差错码
				MODBUS_SEND[MODBUS_SEND_LENGTH-1]=03;   //异常码3
			}
			else if((j+data_num>ELECTRIC_N)||(j+data_num<=0))//异常码2 
			{
				MODBUS_SEND[MODBUS_SEND_LENGTH-2]=MODBUS_RECEIVE[1]|0x80;//功能码改成差错码
				MODBUS_SEND[MODBUS_SEND_LENGTH-1]=02;   //异常码2
			}
			else 
			{ 
				for(i=0;i<data_num;i++)
				{
					MODBUS_SEND[MODBUS_SEND_LENGTH++]=(Modbus_electric[j+i]>>8) & 0xff;//先高字节
					MODBUS_SEND[MODBUS_SEND_LENGTH++]= Modbus_electric[j+i] & 0xff;//后低字节
				}
				
				/*if(j==0)
				{
					Modbus_electric[0]=0;
					Modbus_electric[1]=0;
				}*/
			}	
				modbus_get_crc16();//加入CRC校验
				MODBUS_SIGN=3;//表示可以发送数据
	    		
		}
		else if(MODBUS_RECEIVE[1]==3)//读取参数**************************************************************
	    {
			addr_begin=MODBUS_RECEIVE[2];
			addr_begin=(addr_begin<<8) | MODBUS_RECEIVE[3];//起始地址

			data_num=MODBUS_RECEIVE[4];
			data_num=(data_num<<8) | MODBUS_RECEIVE[5];//数量

			MODBUS_SEND[MODBUS_SEND_LENGTH++]=data_num<<1;//字节数=寄存器数量乘以2

			j=addr_begin-40001;//参数量减去40000

			if((data_num<1)||(data_num>0x007d))     //异常码3
			{
				MODBUS_SEND[MODBUS_SEND_LENGTH-2]=MODBUS_RECEIVE[1]|0x80;//功能码改成差错码
				MODBUS_SEND[MODBUS_SEND_LENGTH-1]=03;   //异常码3
			}
			else if((j+data_num>PARAMETER_N)||(j+data_num<=0))//异常码2
			{
				MODBUS_SEND[MODBUS_SEND_LENGTH-2]=MODBUS_RECEIVE[1]|0x80;//功能码改成差错码
				MODBUS_SEND[MODBUS_SEND_LENGTH-1]=02;   //异常码2
			}
			else 
			{
				for(i=0;i<data_num;i++)
				{
					MODBUS_SEND[MODBUS_SEND_LENGTH++]=(Modbus_parameter[j+i][0]>>8) & 0xff;//先高字节
					MODBUS_SEND[MODBUS_SEND_LENGTH++]= Modbus_parameter[j+i][0] & 0xff;//后低字节
				}
			}
				modbus_get_crc16();//加入CRC校验
				MODBUS_SIGN=3;//表示可以发送数据
		}
		else if(MODBUS_RECEIVE[1]==6)//写单个参数
	    {	
			addr_begin=MODBUS_RECEIVE[2];
			addr_begin=(addr_begin<<8) | MODBUS_RECEIVE[3];//起始地址

			data_value=MODBUS_RECEIVE[4];
			data_value=(data_value<<8) | MODBUS_RECEIVE[5];//值

			j=addr_begin-40001;//参数量减去40000

			 if((j>=PARAMETER_N)||(j<0))//异常码2
			{
				MODBUS_SEND[MODBUS_SEND_LENGTH-2]=MODBUS_RECEIVE[1]|0x80;//功能码改成差错码
				MODBUS_SEND[MODBUS_SEND_LENGTH-1]=02;   //异常码2
			}
			else 
			{
				Modbus_parameter[j][0]=data_value;
				Modbus_parameter[j][1]=1;	
				Modbus_write_sign=1;//改动过
				for(i=2;i<6;i++)
					MODBUS_SEND[MODBUS_SEND_LENGTH++]=MODBUS_RECEIVE[i];
			}
			
			modbus_get_crc16();//加入CRC校验	
			MODBUS_SIGN=3;//表示可以发送数据

		}
		else if(MODBUS_RECEIVE[1]==16)//写多个参数
	    {

			addr_begin=MODBUS_RECEIVE[2];
			addr_begin=(addr_begin<<8) | MODBUS_RECEIVE[3];//起始地址

			data_num=MODBUS_RECEIVE[4];
			data_num=(data_num<<8) | MODBUS_RECEIVE[5];//数量

			//l=MODBUS_RECEIVE[6]>>1;//字节数=寄存器数量除以2

			j=addr_begin-40001;//参数量减去40000


			if((data_num<1)||(data_num>0x007b)||(MODBUS_RECEIVE[6]!=data_num<<1)) //异常码3
			{
				MODBUS_SEND[MODBUS_SEND_LENGTH-2]=MODBUS_RECEIVE[1]|0x80;//功能码改成差错码
				MODBUS_SEND[MODBUS_SEND_LENGTH-1]=03;   //异常码3
			}
			else if((j+data_num>PARAMETER_N)||(j+data_num<=0))//异常码2
			{
				MODBUS_SEND[MODBUS_SEND_LENGTH-2]=MODBUS_RECEIVE[1]|0x80;//功能码改成差错码
				MODBUS_SEND[MODBUS_SEND_LENGTH-1]=02;   //异常码2
			}
			else 
			{
				for(i=0;i<data_num;i++)
				{
					Modbus_parameter[j+i][0]=MODBUS_RECEIVE[2*i+7];
					Modbus_parameter[j+i][0]=(Modbus_parameter[j+i][0]<<8)|MODBUS_RECEIVE[2*i+8];
					Modbus_parameter[j+i][1]=1;
				}
					Modbus_write_sign=1;
					for(i=2;i<6;i++)
						MODBUS_SEND[MODBUS_SEND_LENGTH++]=MODBUS_RECEIVE[i];//发送应答
			}
			
			modbus_get_crc16();//加入CRC校验
			MODBUS_SIGN=3;//表示可以发送数据
		}
		else
		{
			MODBUS_SEND[MODBUS_SEND_LENGTH-1]=MODBUS_RECEIVE[1]|0x80;//功能码改成差错码
			MODBUS_SEND[MODBUS_SEND_LENGTH++]=01;   //无功能类型
			modbus_get_crc16();//加入CRC校验
			MODBUS_SIGN=3;//表示可以发送数据
		}
} 




/****************************************/
//函数名: modbus_in()
//描述:  判断是否 完整的收到了一个报文,设备地址是否一致,RCR是否正确
//日期:2010.12.10
//
// 
//
/****************************************/
 void modbus_in()
{   
  	unsigned int k;
  	
  	if (MODBUS_SIGN==2)//一次数据接收完毕
	{
		if ((MODBUS_RECEIVE[0]==P_E2PROM[9])&&(modbus_if_crc16()==1))
//		if (MODBUS_RECEIVE[0]==P_E2PROM[40])//调试用
		{
			MODBUS_SEND[MODBUS_SEND_LENGTH++]=MODBUS_RECEIVE[0];//发送缓冲区 ID
			MODBUS_SEND[MODBUS_SEND_LENGTH++]=MODBUS_RECEIVE[1];//发送缓冲区类型
			modbus_analysis();
			MODBUS_RECEIVE_LENGTH=0;//清除接收缓冲区			
		}
		else 
		{
			MODBUS_RECEIVE_LENGTH=0;//清空接收缓冲区
			MODBUS_SIGN=4;			// 清零接收标识
		}
	}
 	else  if(MODBUS_SIGN==3)//可以发送数据
	{		
//		 RS485_send;
		 if(MODBUS_TIME>=MODBUS_T3_5)//数据发送
		 {	
			//*****发送状态****************************				
			while(1)
			{	
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
				
			
				if((RS485_send_fifo==1)&&(Modbus_mortize<MODBUS_SEND_LENGTH))
				{
					while(SPI1STATbits.SPITBF==1);
					SS1=0;
					SPI1BUF=CN_THR|MODBUS_SEND[Modbus_mortize++];
					while(SPI1STATbits.SPIRBF==0);
					k=SPI1BUF;
					SS1=1;
				}
				else
				if((Modbus_mortize>=MODBUS_SEND_LENGTH)&&(RS485_send_over==1))
				{
						MODBUS_SIGN=4;//继续等待数据 接收
						Modbus_mortize=0;
						MODBUS_SEND_LENGTH=0;//清空发送缓冲区
						MODBUS_TIME=0;//准备延时
						break;	
				}	
				else
				{
					break;		
				}
			}
		 }		
	}
 	else if(MODBUS_SIGN==4)//发送结束后，下一次接收前的延时，
    {		
			if(MODBUS_TIME>MODBUS_T1_5)//处理的方式得解决
			{
				MODBUS_SIGN=0;//继续等待数据 接收
			}
	}
 	else
 	{                  //等待接收
			modbus_read_data();
			if(CH432T_reset==1||BSP_reset==1)//复位
			{
				CH432T_config();
				CH432T_reset=0;
				BSP_reset=0;
				MODBUS_SIGN=0;
			}
	 }
}  
#endif