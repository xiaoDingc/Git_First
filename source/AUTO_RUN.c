#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"

volatile unsigned int  AUTO_run=0;//上电初始化
volatile unsigned int  AUTO_stop=0;//上电初始化
volatile unsigned int  Off_line=2;//离线标志//1：离线，0：非离线，2，不处理
volatile unsigned int  which_equ=2;//上电默认APF80

volatile unsigned long ask_time=0;//查看一个周期问询的时间
//*********串口屏程序开始的******************************	

void DS1302_AUTO_RUN_STOP(void)//
{	
		if(TIME_NOW[3]==0) TIME_NOW[3]=7;
		
		if(P_E2PROM[35+(TIME_NOW[3]-1)*6]==1&&TIME_NOW[4]==P_E2PROM[36+(TIME_NOW[3]-1)*6]&&TIME_NOW[5]==P_E2PROM[37+(TIME_NOW[3]-1)*6])//如果定时停止使能
		{
			if(AUTO_stop==0)
			{
					if(P_E2PROM[105]==0)
					{
							ecan1WriteTxMsgBufId(1,0x201,0,0);
							ecan1WriteTxMsgBufData(1,8,0x0001,0,0,0);//停止命令
							C1TR01CONbits.TXREQ1=1;//停止信号
							AUTO_stop=1;
							WRITE_fault_one(40,0);
#if compilemodbus
                                                        Modbus_electric[0]=40;Modbus_electric[1]=1;
#endif
					}
					else
					{
							ecan1WriteTxMsgBufId(1,0x201,0,0);
							ecan1WriteTxMsgBufData(1,8,0x0006,0,0,0);//待机命令
							C1TR01CONbits.TXREQ1=1;//待机信号
							AUTO_stop=1;	
							WRITE_fault_one(52,0);
#if compilemodbus
                                                        Modbus_electric[0]=52;Modbus_electric[1]=1;
#endif
					}	
			}
			
		}
                else if(AUTO_stop!=0&&TIME_NOW[5]!=P_E2PROM[37+(TIME_NOW[3]-1)*6])
		{
			AUTO_stop=0;
		}
                else if(P_E2PROM[32+(TIME_NOW[3]-1)*6]==1&&TIME_NOW[4]==P_E2PROM[33+(TIME_NOW[3]-1)*6]&&TIME_NOW[5]==P_E2PROM[34+(TIME_NOW[3]-1)*6])//如果定时启动使能
		{
			if(AUTO_run==0)
			{
							ecan1WriteTxMsgBufId(1,0x201,0,0);
							ecan1WriteTxMsgBufData(1,8,0x0002,0,0,0);//运行命令
							C1TR01CONbits.TXREQ1=1;//启动信号
							AUTO_run=1;
							WRITE_fault_one(39,0);
#if compilemodbus                 
                                                        Modbus_electric[0]=39;Modbus_electric[1]=1;
#endif
			}

		}
                else if(AUTO_run!=0&&TIME_NOW[5]!=P_E2PROM[34+(TIME_NOW[3]-1)*6])
		{
			AUTO_run=0;
		}
}

	
void page_state(void)//设备状态
{	
	unsigned int n=0,m=0,l=1,p=0,i,z;
	
//***************串口屏程序**********	

//***判断是否离线***********	
	for(i=0;i<P_E2PROM[13];i++)
	{
		if(DELAY_CAN[i]>20000) 
		{
			equipment_skate[i][2]=3;//判断是否离线
		}
			
		if(equipment_skate[0][2]==3&&Off_line==0)//离线后，并且之前是通讯正常写入离线时间代码
		{
			WRITE_fault_one(24,1);
#if compilemodbus
                        Modbus_electric[0]=24;Modbus_electric[1]=1;//设备离线
#endif
			Off_line=1;//通讯中断了
		}
		else	
		if(equipment_skate[0][2]!=3) Off_line=0;//通讯正常
		
		if(record_single[0][2]!=0)//提示信息//&&&&&
			{
					 if(record_single[0][2]==1) message_num=12;//
				else  if(record_single[0][2]==2) message_num=16;//
				else  if(record_single[0][2]==3) message_num=17;//
				else  if(record_single[0][2]==4) message_num=18;//
				else  if(record_single[0][2]==5) message_num=19;//
				else  if(record_single[0][2]==6) message_num=20;//
				else  if(record_single[0][2]==7) message_num=21;//
							
				record_single[0][2]=0;
			}			
			
		if(equipment_skate[i][2]==1)//判断设备是否运行
			n=1;//只要有一个设备是运行的，那么认为运行
		
		if(equipment_skate[i][2]!=2)//判断是否有故障
		   l=0;
		
		if(equipment_skate[i][2]==4)//判断是否有急停
		   p=1;
		 
		if(equipment_skate[i][2]!=3)//几台设备通讯正常
			m++;//有几个设备在线
#if compilemodbus
                if(equipment_skate[i][2] != 2)//由于Modbus_electric[0]的赋值只有在发生故障时发生，所以恢复正常后Modbus_electric[0]值保持上一个故障值（见此页265行），所以此处故障消除后清零modbus数据
                {
                    Modbus_electric[0] = 0;
                    Modbus_electric[1] = 0;
                    Modbus_electric[84] = 0;
                    Modbus_electric[85] = 0;
                    Modbus_electric[86] = 0;
                    Modbus_electric[87] = 0;
                    Modbus_electric[88] = 0;
                }
#endif
	}

	
//**判断在线主控的个数************
		equiment_set[0]=m;
		
//*******判断故障状态************没用
		APF_error=l;

//******记录运行时间******修改按钮状态******
	if(n==1) 
	{
		APF_state=1;

		if(run_time_sign>=2000)//如果设备一直不停，每一千分钟存一次
		{
			E2ROM_WR(3,2,P_E2PROM+3);//写入E2
			E2ROM_WR(962,2,P_E2PROM+111);//写入E2
			run_time_sign=0;
		}	
	}
	else   	 
	{
		if(p==1) APF_state=4;//急停   确定设备当前的总状态：，只要有一个设备是运行的，那么认为运行
		else    APF_state=0;//停止		
		
		if(run_time_sign!=0)//如果在停止状态，并且运行时间已经改变，修改运行时间
		{
			E2ROM_WR(3,2,P_E2PROM+3);//写入E2
			E2ROM_WR(962,2,P_E2PROM+111);//写入E2
			run_time_sign=0;
		}
	}

//****判断设备是否修改，并写入E2************
		m=(equipment_ID[0][2]>>4)&0xff;
		n=equipment_ID[0][2]&0x0f;
		l=equipment_ID[0][3]&0xfff;
		p=equipment_ID[0][3]>>12;//设备类型

		if(p!=3&&p!=4) p=2;//不是SVG,就是APF80
		else  		   p=3;

		if(m!=P_E2PROM[23]||n!=P_E2PROM[24]||l!=P_E2PROM[25]||p!=which_equ)
		{
			 P_E2PROM[23]=m;
			 P_E2PROM[24]=n;
			 P_E2PROM[25]=l;
			 
			 E2ROM_WR(23,3,P_E2PROM+23);
			 
			 which_equ=p;
			 equipment_skate_sign=0xaaaa;
		}
	
//***********写故障代码	*****************************
             
		for(i=0;i<P_E2PROM[13];i++)//写故障代码
		{    
			if(equipment_skate[i][1]!=0)//500ms发生两次故障记录最后的一次
			{				
				if((equipment_skate[i][1]&0x8000)==0)//不是双模块
				{
					if((equipment_skate[i][1]&0xff00)==0x1000)
					{
						WRITE_fault_shadow(equipment_skate[i][1]&0x00ff,i+1);//隐藏的菜单	
					}
					else
					if((equipment_skate[i][1]&0xff00)==0x2000)
					{
							m=equipment_skate[i][1]&0x00ff;								
								if(m==1) message_num=12;//
							else  if(m==2) message_num=16;//
							else  if(m==3) message_num=17;//
							else  if(m==4) message_num=18;//
							else  if(m==5) message_num=19;//
							else  if(m==6) message_num=20;//
							else  if(m==7) message_num=21;//
					}	
					else
					if(equipment_skate[i][1]>0&&equipment_skate[i][1]<=100)//以后增加故障代码需要在这里增加范围
					{
						WRITE_fault_one(equipment_skate[i][1],i+1);
#if compilemodbus
                                                Modbus_electric[0]=equipment_skate[i][1];Modbus_electric[1]=i+1;
#endif
						message_num=equipment_skate[i][1]|0x8000;//在显示区域显示
					}
					else
					{
						WRITE_fault_one(0,i+1);//如果超过范围，写入0
					}
				}
				else
				if((equipment_skate[i][1]&0x8000)==0x8000)
				{
					equipment_skate[i][1]&=0x0fff;
					if(equipment_skate[i][1]>0&&equipment_skate[i][1]<=100)//以后增加故障代码需要在这里增加范围
					{
						WRITE_fault_one(equipment_skate[i][1],i+2);
#if compilemodbus
                                                Modbus_electric[0]=equipment_skate[i][1];Modbus_electric[1]=i+1;
#endif
						message_num=equipment_skate[i][1]|0x8000;//在显示区域显示
					}
					else
					{
						WRITE_fault_one(0,i+2);//如果超过范围，写入0
					}
				}			
				
				equipment_skate[i][1]&=0x00ff;
#if compileGSM
				if(P_E2PROM[131]==1)
                                {
                                    z=0;
                                    if(equipment_skate[i][1]>=1&&equipment_skate[i][1]<=16)
                                    {
                                       if((P_E2PROM[132]&(0x0001<<(equipment_skate[i][1]-1)))!=0) z=1;
                                    }
                                    else
                                    if(equipment_skate[i][1]>=17&&equipment_skate[i][1]<=32)
                                    {
                                        if((P_E2PROM[133]&(0x0001<<(equipment_skate[i][1]-17)))!=0)z=1;
                                    }
                                    else
                                    if(equipment_skate[i][1]>=33&&equipment_skate[i][1]<=48)
                                    {
                                       if((P_E2PROM[134]&(0x0001<<(equipment_skate[i][1]-33)))!=0)z=1;
                                    }
                                    else
                                    if(equipment_skate[i][1]>=49&&equipment_skate[i][1]<=64)
                                    {
                                        if((P_E2PROM[135]&(0x0001<<(equipment_skate[i][1]-49)))!=0)z=1;
                                    }
                                    else
                                    if(equipment_skate[i][1]>=65&&equipment_skate[i][1]<=80)
                                    {
                                        if((P_E2PROM[136]&(0x0001<<(equipment_skate[i][1]-65)))!=0)z=1;
                                    }
                                    else
                                    if(equipment_skate[i][1]>=81&&equipment_skate[i][1]<=96)
                                    {
                                        if((P_E2PROM[137]&(0x0001<<(equipment_skate[i][1]-81)))!=0)z=1;
                                    }
                                    if(z==1)send_message();
                                }
                                else
                                {
                                    send_message();
                                }
#endif
				equipment_skate[i][1]=0;
			}
		}
	
            }
//}
void send_elect(void)
{
	unsigned int j;
	//********电气量发送命令控制****************  
    if(equipment_ID[4][0]==0&&(electric_receive_sign==2||electric_receive_sign==0)&&DELAY_elect_synch>=P_E2PROM[115]*10)//发送同步收集命令 500ms
    {    
	    if(which_equ==2) j=record_single[2][2];
	    else			 j=0;
	    
	    ecan1WriteTxMsgBufId(0,0x000,0,0);
		ecan1WriteTxMsgBufData(0,8,0xaaaa,equipment_skate[0][2],0,j);//系统参数
		C1TR01CONbits.TXREQ0=1;	
		
		equipment_ID[4][0]++;
		DELAY_elect_synch=0;
	}
	else
	if(equipment_ID[4][0]==1&&DELAY_elect_synch>200)//发送同步收集命令后10ms 发送一次 电压畸变率
	{	
		ecan1WriteTxMsgBufId(0,0x000,0,0);
		ecan1WriteTxMsgBufData(0,8,0xcccc,LOAD_cost[3][0],LOAD_cost[3][1],LOAD_cost[3][2]);//系统参数
		C1TR01CONbits.TXREQ0=1;	
		
		equipment_ID[4][0]++;
	}
	else
	if(equipment_ID[4][0]==2&&DELAY_elect_synch>400)//发送同步收集命令后40ms 发送一次 允许发送
	{
		if(which_equ==3) j=record_single[2][2];
	    else			 j=0;
	    
					ecan1WriteTxMsgBufId(0,0x000,0,0);
					ecan1WriteTxMsgBufData(0,8,0xbbbb,equipment_ID[0][1],1,j);//允许发送数据指令 全部数据
					C1TR01CONbits.TXREQ0=1;
					
					equipment_ID[4][0]=0;
	}	
}	









