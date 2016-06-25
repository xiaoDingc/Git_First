#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"
#if compileGSM
//*********故障代码*********************************************
void READ_fault_one_else(unsigned int num,unsigned int add)//读一条故障代码
{
	unsigned int i,k;
	
//	 R232_send_data[R232_send_data_num++]=0x0a;	
//	 R232_send_data[R232_send_data_num++]=0x0d;
	 

	  R232_send_data[R232_send_data_num++]=0x32;
	  R232_send_data[R232_send_data_num++]=0x30;
	  i=E2ROM_93LC86C_readdata(add+1);
	  R232_send_data[R232_send_data_num++]=i/10+0x30;
	  R232_send_data[R232_send_data_num++]=i%10+0x30;//年
	  R232_send_data[R232_send_data_num++]=0x5f;
	  
	  i=E2ROM_93LC86C_readdata(add+2);
	  R232_send_data[R232_send_data_num++]=i/10+0x30;
	  R232_send_data[R232_send_data_num++]=i%10+0x30;//月
	  R232_send_data[R232_send_data_num++]=0x5f;	

	  i=E2ROM_93LC86C_readdata(add+3);
	  R232_send_data[R232_send_data_num++]=i/10+0x30;
	  R232_send_data[R232_send_data_num++]=i%10+0x30;//日
	  R232_send_data[R232_send_data_num++]=0x20;
	  
	  i=E2ROM_93LC86C_readdata(add+4);
	  R232_send_data[R232_send_data_num++]=i/10+0x30;
	  R232_send_data[R232_send_data_num++]=i%10+0x30;//时
	  R232_send_data[R232_send_data_num++]=0x3a;
	  
	  i=E2ROM_93LC86C_readdata(add+5);
	  R232_send_data[R232_send_data_num++]=i/10+0x30;
	  R232_send_data[R232_send_data_num++]=i%10+0x30;//分
	  
	  R232_send_data[R232_send_data_num++]=0x20;
	  R232_send_data[R232_send_data_num++]=0x20;
	  
	  	i=E2ROM_93LC86C_readdata(add+7);//模块号
		for(k=0;k<4;k++)
		{
			R232_send_data[R232_send_data_num++]=MODE_num_com[i][k]>>8;
			R232_send_data[R232_send_data_num++]=MODE_num_com[i][k]&0xff;
		}
		
		i=E2ROM_93LC86C_readdata(add+6);//故障代码	
		for(k=0;k<10;k++)
		{
			R232_send_data[R232_send_data_num++]=ERR_code_com[i][k]>>8;
	  		R232_send_data[R232_send_data_num++]=ERR_code_com[i][k]&0xff;
	    } 
}
#endif
void RS232_Config(void)//rs232配置 9600
{
	_U1EIE=0;	//U1,错误中断允许：遇到错误进中断复位
	_U1TXIE=0;	//U1发送器中断允许
	_U1RXIE=0;	//U1接收器中断允许
	
	U1MODE=0x8000;//启动两个串口引脚，8数据，1停止，无校验
//	U1MODE=0x8002;//启动两个串口引脚，8数据，1停止，偶校验
	U1BRG=0x103;   //9600    40M/16/9600-1
	
//	U1BRG=0x81;   //19200    40M/16/19200-1
	
//	U1STA=0x0400; //禁用中断标志，发送使能
	U1STA=0x0400; //禁用中断标志，发送使能
}
#if compileGSM
void RS232_Sdata_debug(void)//发送 一个字符串  暂时备用*************
{	
	while(RS232_Sfifo==0&&R232_send_data_now<R232_send_data_num) //如果不满就往里面加数据
		U1TXREG=R232_send_data[R232_send_data_now++];
}	

void RS232_Rdata_debug(void)//如果有数据就读出来 暂时备用*************
{
	unsigned int i=0,j=0,data[10];
	
	while(1)
	{
			if(RS232_Rfifo==1) 
			{
				data[j++]=U1RXREG;
				if(j==10) 
				i++;//设断点，看收到的数据是否正确
			}	
	}
}	

void RS232_Sdata(void)//发送 一个字符串
{	
	if(R232_Send_sign==0)
	{
		while(RS232_Sfifo==0&&R232_send_data_now<R232_send_data_num) //如果不满就往里面加数据
			U1TXREG=R232_send_data[R232_send_data_now++];
			
		if(R232_send_data_now>=R232_send_data_num)//如果发送完毕
		{	
			R232_Send_sign=1;
			DELAY_GSM=0;
		}
	}
}	

void RS232_Rdata(void)//如果有数据就读出来
{
	unsigned char i;
	unsigned int j,k,l,m;
	
	if(R232_Rbuffer_sign==1)
	{
			while(RS232_Rfifo==1) 
			{
				SOURCE_R[R232_receive_data_now++]=U1RXREG;				
				SOURCE_R_num[R232_receive_Ndata_now++]=SOURCE_R[R232_receive_data_now-1];
				
		//*********短信中心号码接收**************
				if(R232_receive_Ndata_now==1){if(SOURCE_R_num[0]!='"') R232_receive_Ndata_now=0;}
			else if(R232_receive_Ndata_now==2){if(SOURCE_R_num[1]!='+')R232_receive_Ndata_now=0;}
			else if(R232_receive_Ndata_now==3){if(SOURCE_R_num[2]!='8')R232_receive_Ndata_now=0;}
			else if(R232_receive_Ndata_now==4){if(SOURCE_R_num[3]!='6')R232_receive_Ndata_now=0;}
			else if(R232_receive_Ndata_now==16&&SOURCE_R_num[15]=='"')
			{
				j=SOURCE_R_num[4]-'0';k=j*1000;		
				j=SOURCE_R_num[5]-'0';k+=j*100;	
				j=SOURCE_R_num[6]-'0';k+=j*10;	
				j=SOURCE_R_num[7]-'0';k+=j;				
				
				j=SOURCE_R_num[8]-'0';l=j*1000;		
				j=SOURCE_R_num[9]-'0';l+=j*100;	
				j=SOURCE_R_num[10]-'0';l+=j*10;	
				j=SOURCE_R_num[11]-'0';l+=j;					
				
				j=SOURCE_R_num[12]-'0';m=j*100;
				j=SOURCE_R_num[13]-'0';m+=j*10;
				j=SOURCE_R_num[14]-'0';m+=j;
				
				if(k!=P_E2PROM[120]||l!=P_E2PROM[121]||m!=P_E2PROM[122])
				{
					P_E2PROM[120]=k;	
					P_E2PROM[121]=l;	
					P_E2PROM[122]=m;	
					GSM_NUM_fist=2;//修改标识
				}
				R232_receive_Ndata_now=0;	
			}
				
	//**************短信接收********************
				 if(R232_receive_data_now==1){if(SOURCE_R[0]!='0'&&SOURCE_R[0]!=190)R232_receive_data_now=0;}
			else if(R232_receive_data_now==2){if(SOURCE_R[1]!='8'&&SOURCE_R[1]!=191)R232_receive_data_now=0;}
                       // else if(R232_receive_data_now==2){if((SOURCE_R[1]!='7'&&SOURCE_R[1]!='8') &&SOURCE_R[1]!=191)R232_receive_data_now=0;} ////许忠元-增加***********************************
			else if(R232_receive_data_now==3){if(SOURCE_R[2]!='9'&&SOURCE_R[2]!=192)R232_receive_data_now=0;}
			else if(R232_receive_data_now==4)
			{
				if(SOURCE_R[3]!='1'&&SOURCE_R[3]!=193)R232_receive_data_now=0;
				else
				if(SOURCE_R[0]==190&&SOURCE_R[1]==191&&SOURCE_R[2]==192&&SOURCE_R[3]==193)//发送隐藏故障代码
				{
					R232_Rbuffer_sign=0;
					R232_receive_data_now=0;
										
					j=1;
					for(i=0;i<20;i++)
					{
						if(E2ROM_93LC86C_readdata(740+(i<<3))==0xaaaa)
						{
							READ_fault_one_else(j++,740+(i<<3));
						}
					}
					
					R232_send_data_now=0;
					R232_Send_sign=0;
				}	
			}	
			else if(R232_receive_data_now==27){if(SOURCE_R[26]!=P_E2PROM[10]/100%10+'0'){R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==28){if(SOURCE_R[27]!=P_E2PROM[10]/1000+'0')  {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==29){if(SOURCE_R[28]!=P_E2PROM[10]%10+'0')    {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==30){if(SOURCE_R[29]!=P_E2PROM[10]/10%10+'0') {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==31){if(SOURCE_R[30]!=P_E2PROM[11]/100%10+'0'){R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==32){if(SOURCE_R[31]!=P_E2PROM[11]/1000+'0')  {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==33){if(SOURCE_R[32]!=P_E2PROM[11]%10+'0')    {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==34){if(SOURCE_R[33]!=P_E2PROM[11]/10%10+'0') {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==35){if(SOURCE_R[34]!=P_E2PROM[12]/10%10+'0') {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==36){if(SOURCE_R[35]!=P_E2PROM[12]/100+'0')   {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==38){if(SOURCE_R[37]!=P_E2PROM[12]%10+'0')    {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;}}
			else if(R232_receive_data_now==58){R232_receive_data_num=char_hex(SOURCE_R[56],SOURCE_R[57]);R232_receive_data_num*=2;}
			else if(R232_receive_data_now>=256) {R232_Rbuffer_sign=0;R232_receive_data_now=0;GSM_record_sign=0x0300;R232_receive_Ndata_now=0;}
			else
			{
				if(R232_receive_data_now!=0&&SOURCE_R[R232_receive_data_now-1]==0x0d)
				{
					R232_Rbuffer_sign=0;//处理接收到的一帧数据,去把这条信息删掉
					GSM_record_sign=0x0200;//
				}
			}
		   }//while
	}
	else
	{
		i=U1RXREG;//收一些无关数据 不需要收完，这样足够，	
	}		
}
#endif
















