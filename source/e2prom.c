#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"

#define E_DO   LATDbits.LATD0   //主出  从入
#define E_DI   PORTDbits.RD11
#define E_SCK  LATCbits.LATC13
#define E_CS   LATCbits.LATC14

#define EWEN_CMD    0x1300       // 擦写使能
#define EWDS_CMD    0x1000       // 擦写禁止
#define WRITE_CMD   0x1400       // 写       需要地址
#define READ_CMD    0x1800       // 读       需要地址
#define ERASE_CMD   0x1c00      // 擦除      需要地址
#define ERAL_CMD    0x1200      // 全部擦除 
#define WRAL_CMD    0x1100      // 全部写 

#define E2_SCK_DELAY DELAY(1);  //  SCK 2.5V ≤VCC< 4.5V   200~250ns    平均5个周期
#define E2_CS_DELAY  DELAY(1);  //  CS建立时间 2.5V ≤VCC< 4.5V   100ns

volatile unsigned int __attribute__((__far__)) add_error_data[15][11];//即将保存的0~9故障信息，10:地址，11：写标志
volatile unsigned int error_write=0,error_read=0;

void E2ROM_93LC86C_Config(void)//E2PROM配置
{
	_TRISD0=0;
	_TRISD11=1;
	_TRISC13=0;
	_TRISC14=0;
}

void E2ROM_93LC86C_WCommand(unsigned int data)//写13位的命令
{
  unsigned char i=0;

  E_CS=1;
  E2_CS_DELAY;
  for(i=0;i<13;i++)
  {
     if (data & 0x1000)    E_DO = 1;    //从第13位开始          
     else                E_DO = 0;                       
     data=data << 1;
                  
    E_SCK = 0;                       
    E2_SCK_DELAY;                  
    E_SCK = 1; 
	E2_SCK_DELAY;//写数据 上升沿写入
  }
} 

void E2ROM_93LC86C_Wdata(unsigned int data)//写16位的数据
{
  unsigned char i=0;

  for(i=0;i<16;i++)
  {
     if (data & 0x8000)    E_DO = 1;    //从第16位开始          
     else                E_DO = 0;                       
     data=data << 1;
    
    E_SCK = 0;                       
    E2_SCK_DELAY;                  
    E_SCK = 1; 
	E2_SCK_DELAY;            //上升沿写数据
  }
} 

void E2ROM_93LC86C_Busy(void)//判断读写是否已经结束
{
  E_CS=0;
  E2_SCK_DELAY;//需要250
  E_CS=1;
  E2_SCK_DELAY;//需要300 
  while(E_DI==0){};
  E2_CS_DELAY;
  E_CS=0;
  E2_CS_DELAY;  //需要两百毫秒才能清楚DO位
}

int E2ROM_93LC86C_Read(void)//读数据   虚零该怎么处理, 直接读取
{
  unsigned char i=0;
  int data=0;

  for(i=0;i<16;i++)
  {
    E_SCK = 0;                       
    E2_SCK_DELAY;
	E_SCK = 1;
    E2_SCK_DELAY;

    data = data << 1; 
    if (E_DI == 1) data=data | 0x0001;
  }
  E_CS=0;
  E2_CS_DELAY;  //需要两百毫秒才能清楚DO位
  return data;
}

void E2ROM_93LC86C_writedata(unsigned int addr,int data)//把数据位data，写入地址为addr的地址  
{
  E2ROM_93LC86C_WCommand(EWEN_CMD);//擦写使能
  E_CS=0;
  E2_CS_DELAY;  //延时


  E2ROM_93LC86C_WCommand(addr| WRITE_CMD);
  E2ROM_93LC86C_Wdata(data);
  E2ROM_93LC86C_Busy();

  E2ROM_93LC86C_WCommand(EWDS_CMD);//擦写禁止
  E_CS=0;
  E2_CS_DELAY;  //延时
}

int E2ROM_93LC86C_readdata(unsigned int addr)//读地址为addr  的数据
{
  int data;
  addr=addr | READ_CMD;  //12,11,10:  110
  E2ROM_93LC86C_WCommand(addr);//写完指令后 直接读取可以吗
  data=E2ROM_93LC86C_Read();

  return data;
}

unsigned int E2ROM_WR(unsigned int add,unsigned int num,volatile unsigned int *character)
{//把character 中num个数写入add起始的地址中
		unsigned i,j=1;	
			for(i=0;i<num;i++)//故障代码初始化
			{
				E2ROM_93LC86C_writedata(i+add,character[i]);
				if(E2ROM_93LC86C_readdata(i+add)!=character[i]) {j=0;break;}
			}  	
	  return j;
}	

void E2ROM_RD(unsigned int add,unsigned int num,volatile unsigned int *character)
{//把地址为add的数据读num个到character中，
	unsigned int i;
			for(i=0;i<num;i++)//
				character[i]=E2ROM_93LC86C_readdata(i+add);//e2prom参数	
}	

void E2ROM_93LC86C_init()//参数的初始化，如果有增加的参数在这里添加****************
{
	unsigned int i,j=0;

	  j=E2ROM_93LC86C_readdata(0);
	  i=0;
	  if(j!=0x9997)//如果没有初始化过，则初始化
	  {			 
			 j=E2ROM_WR(1,98,P_E2PROM+1);//系统设置初始化
			 j=E2ROM_WR(950,39,P_E2PROM+99);//系统设置初始化

			if(j==1)//写入
		   {
				E2ROM_93LC86C_writedata(0,P_E2PROM[0]);//写入标志位
				if(E2ROM_93LC86C_readdata(0)!=P_E2PROM[0]) j=0;
		   }
	  }
	  else
	  {			
			E2ROM_RD(1,98,P_E2PROM+1);//读取E2中的参数
			E2ROM_RD(950,39,P_E2PROM+99);//读取E2中的参数
	  }
	  
	DELAY_BLIGHT_SIGN=P_E2PROM[7];DELAY_BLIGHT_SIGN*=600000;//背光时间
}

void WRITE_fault_one(unsigned int fault,unsigned int mode)//写故障代码
{
	if(P_E2PROM[1]!=0)
	{
	 if(P_E2PROM[2]>=499) P_E2PROM[2]=0;
	 else                   P_E2PROM[2]++;
	}
	else P_E2PROM[2]=0;

	add_error_data[error_write][1]=TIME_NOW[0];
	add_error_data[error_write][2]=TIME_NOW[1];
	add_error_data[error_write][3]=TIME_NOW[2];
	add_error_data[error_write][4]=TIME_NOW[4];
	add_error_data[error_write][5]=TIME_NOW[5];	
	add_error_data[error_write][6]=fault;
	add_error_data[error_write][7]=mode;//模块号码
		
	add_error_data[error_write][10]=P_E2PROM[2];
	
	if(error_write==14) error_write=0;
	else				error_write++;
	
	if(P_E2PROM[1]<500) P_E2PROM[1]++;
	E2ROM_WR(1,2,P_E2PROM+1);//写入E2

	change_data_only=0x5a;//准备读取read
	DELAY_TIME=0;	
}	

void WRITE_fault_shadow(unsigned int fault,unsigned int mode)//写故障代码
{
	 if(P_E2PROM[8]>=892) P_E2PROM[8]=740;
	 else
	 if(P_E2PROM[8]<740)  P_E2PROM[8]=740;
	 else                 P_E2PROM[8]+=8;
	 
	E2ROM_93LC86C_writedata(P_E2PROM[8],0xaaaa);
	E2ROM_93LC86C_writedata(P_E2PROM[8]+1,TIME_NOW[0]);
	E2ROM_93LC86C_writedata(P_E2PROM[8]+2,TIME_NOW[1]);
	E2ROM_93LC86C_writedata(P_E2PROM[8]+3,TIME_NOW[2]);
	E2ROM_93LC86C_writedata(P_E2PROM[8]+4,TIME_NOW[4]);
	E2ROM_93LC86C_writedata(P_E2PROM[8]+5,TIME_NOW[5]);
	E2ROM_93LC86C_writedata(P_E2PROM[8]+6,fault);
	E2ROM_93LC86C_writedata(P_E2PROM[8]+7,mode);//模块号码

	E2ROM_WR(8,1,P_E2PROM+8);//写入E2
}


void CLEAR_fault_all(unsigned int type)//清除所有故障 出厂设置初始化
{//0：出场设置；1：清除故障;2:清运行时间
	unsigned int i;
unsigned int P_E2PROM_b[]=//出厂设置
{
	0x9997, //0 E2使能
	0,	    //1 故障总数
	0,		//2 最新故障地址
	0,	    //3 设备总运行时数 - 分
	0,	    //4 设备总运行时数 - 天
	64,	    //5 开启亮度
	0,	    //6 关闭亮度
	10,	    //7 背光时间
	740,	//8 最新故障地址
	21,	    //9 modbus站地址
	0000,	//10 短信手机号码1~4
	0000,	//11 短信手机号码5~8
	000,	//12 短信手机号码9~11
	1,      //13 一共多少个主控设备
	0,		//14 0负载，1电网，2全部
	2,		//15 是否显示电网THD值
	3,		//16 是否显示负载THD值
	5,		//17 是否显示电网功率因数
	6,      //18 是否显示负载功率因数
	0,		//19 是否是否优化显示数据 0半优化,1全优化，2不优化 暂时备用********
	1,      //20 是否显示零相电流 对应29*
	800,    //21 数据刷新时间
	0,      //22 数据缓冲大小
	11,      //23 产品编号：年
	1,      //24 产品编号：月
	1, 		//25 产品编号：日
	4,      //26 是否显示电网电压畸变率***
	0,      //27 是否显示装置损耗
	1,      //28 是否显示负载电流波形 1：显示，0：不显示 暂时没有用
	1,      //29 是否显示补偿零相电流*
	0,		//30 是否通讯中断提示急停1：提示，0：不提示     暂时备用****
	0,      //31 是否是双模块，两个温度，两个故障代码
	0,		//32 周一是否定时启动设备
	8,		//33 周一启动设备-时
	30,		//34 周一启动设备-分
	0,		//35 周一是否定时停止设备
	17,		//36 周一停止设备-时
	30,		//37 周一停止设备-分

	0,		//38 周二是否定时启动设备
	8,		//39 周二启动设备-时
	30,		//40 周二启动设备-分
	0,		//41 周二是否定时停止设备
	17,		//42 周二停止设备-时
	30,		//43 周二停止设备-分

	0,		//44 周三是否定时启动设备
	8,		//45 周三启动设备-时
	30,		//46 周三启动设备-分
	0,		//47 周三是否定时停止设备
	17,		//48 周三停止设备-时
	30,		//49 周三停止设备-分

	0,		//50 周四是否定时启动设备
	8,		//51 周四启动设备-时
	30,		//52 周四启动设备-分
	0,		//53 周四是否定时停止设备
	17,		//54 周四停止设备-时
	30,		//55 周四停止设备-分

	0,		//56 周五是否定时启动设备
	8,		//57 周五启动设备-时
	30,		//58 周五启动设备-分
	0,		//59 周五是否定时停止设备
	17,		//60 周五停止设备-时
	30,		//61 周五停止设备-分

	0,		//62 周六是否定时启动设备
	8,		//63 周六启动设备-时
	30,		//64 周六启动设备-分
	0,		//65 周六是否定时停止设备
	17,		//66 周六停止设备-时
	30,		//67 周六停止设备-分

	0,		//68 周日是否定时启动设备
	8,		//69 周日启动设备-时
	30,		//70 周日启动设备-分
	0,		//71 周日是否定时停止设备
	17,		//72 周日停止设备-时
	30,		//73 周日停止设备-分
	0,      //74 电网电压波形 最大坐标
	0,      //75 电网电流波形 最大坐标
	0,      //76 负载电流波形 最大坐标
	0,      //77 电网电压频谱 最大坐标
	0,      //78 电网电流频谱 最大坐标
	0,      //79 负载电流频谱 最大坐标
	0,      //80 电网功率因数范围
	10,     //81 电网功率因数比例
	0,      //82 负载功率因数范围
	10,     //83 负载功率因数比例
	100,    //84 电网电压THD范围
	10,     //85 电网电压THD比例
	100,    //86 电网电流THD范围
	10,     //87 电网电流THD比例
	100,    //88 负载电流THD范围
	10,     //89 负载电流THD比例
	10,     //90 电网零相电流比例
	10,     //91 负载零相电流比例
	5,      //92 模拟显示的最小电流
	10,     //93 各次总补偿比例
	100,     //94 各次总补偿范围
	10,      //95 三次补偿比例
	10,      //96 五次补偿比例
	10,      //97 七次补偿比例
	10,      //98 九次补偿比例

	10,      //99  十一次补偿比例  950
	10,      //100 十三次补偿比例  951
	10,      //101 十五次补偿比例  952
	10,      //102 十七次补偿比例  953
	0,       //103  激活状态0，激活，非零不激活 954
	0,       //104 是否 零线谐波电流    955
	0,       //105 是否 定时待机        956
	1,       //106 是否 显示 频率    957
	1,       //107 是否显示直流侧电压   958
	2,       //108 是否显示一个温度     959
	0,       //109 是否显示双直流电压   960
	0,       //110 是否显示风机风量     961
	0,	     //111 风机总运行时数 - 分  962
	0,	     //112 风机总运行时数 - 天  963
	0,	     //113 补偿电流波形 最大坐标964
	0,	     //114 手动启动停止功能是否使用 965
	400,	 //115  同步收集指令周期         966
	0,		 //116 是否显示已消耗补偿能力    967
	0,	 	 //117 modbus 波特率 h			 968
	9600,	 //118 modbus 波特率 l			 969
	2,		 //119 modbus 校验			     970
	000,    //120 短信中心号码1~4              971
	 000,    //121 短信中心号码5~8              972
	000,     //122 短信中心号码9~11             973
	0,	 //123 是否显示负功率因数            974
	1,      //124 故障隐藏信息使能      975
        0xf7f5, //125 1～16故障信息设置     976
	0x7fff, //126 17～32故障信息设置    977
	0xfff7, //127 33～48故障信息设置    978
        0xffff, //128 49～64故障信息设置    979
        0xfffd, //129 65～80故障信息设置    980
        0xffff, //130 81～96故障信息设置    981
        //GSM故障隐藏
        1,      //131 故障隐藏信息使能      982
        0xf7f5, //132 1～16故障信息设置     983
	0x7fdf, //133 17～32故障信息设置    984
	0x17f7, //134 33～48故障信息设置    985
        0xffff, //135 49～64故障信息设置    986
        0xffff, //136 65～80故障信息设置    987
        0xffff, //137 81～96故障信息设置    988
};
	
	if(type==0)//出厂设置
	{	
		for(i=0;i<=130;i++) P_E2PROM[i]=P_E2PROM_b[i];
		
		E2ROM_WR(1,98,P_E2PROM+1);//系统设置初始化
		E2ROM_WR(950,39,P_E2PROM+99);//系统设置初始化
	}
	else
	if(type==1)//清除故障
	{
		for(i=1;i<=2;i++)
			P_E2PROM[i]=P_E2PROM_b[i];

		E2ROM_WR(1,2,P_E2PROM+1);//写入E2
		
		message_num=2;
	}
}	
