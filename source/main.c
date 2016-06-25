#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"


_FGS(GWRP_OFF & GCP_OFF);//用户程序不被写保护，
_FOSCSEL(FNOSC_PRIPLL);    //初始振荡器选择，带PLL的主振荡器
_FOSC(POSCMD_XT);		   //禁止时钟切换，XT晶振模式
_FWDT(FWDTEN_OFF & WDTPRE_PR128 & WDTPRE_PR128 & WDTPOST_PS256);//用户可通过SWDTEN位来使能禁止WDT//256*4=1.024s
_FICD(JTAGEN_OFF & ICS_PGD1);	 //禁止JTAGEN，选择通道1
																
volatile unsigned int yuan1=0;
volatile unsigned int zhongyuan=0;//调试用******

//版本号设置**************
#if compileGSM
volatile unsigned int soft_APF_SVG[][2]=
{
	{0xd102,0x2018},//APF显示版本
	{0x0302,0x0100},//SVG显示版本
	{0x1002,0x0100}//SVG++版本
};
#endif
#if compilemodbus
volatile unsigned int soft_APF_SVG[][2]=
{
	{0xc102,0x2018},//APF显示版本
	{0x0302,0x0100},//SVG显示版本
	{0x1002,0x0100}//SVG++版本
};
#endif
//***************************************************************************
//***************************************************************************
volatile int record_wave[12][64];//发送的波形数据 需要初始化，不然第一次发送的数据会是乱码
//0:A项电网电压  	1:B项电网电压 	2:C相电网电压
//3:A项电网电流  	4:B项电网电流 	5:C相电网电流
//6:A项负载电流  	7:B项负载电流 	8:C相负载电流
//9:A项补偿电流 	10:B项补偿电流	11:C相补偿电流

volatile int record_single[][3]=
{
	{0,0,0},//12 0 A相频率，软件版本号2，提示信息
	{0,0,0},//13 1 直流侧电压，功率模块一温度，软件版本号1
	{0,0,0},//14 2 0：装置损耗 模块二温度，显示容量
	{0,0,0},//15 3 投切状态，SRC组数
	{0,0,0},//16 4 投切状态，SRC组数
	{0,0,0},//17 5 直流侧电压二,风机风量
	{0,0,0},//18 6 备用,备用,主控版本号1//&&&&
	{0,0,0},//19 7 主控版本号2,备用,备用//&&&&
	{0,0,0},//20 6 备用
	{0,0,0},//21 7 备用
	
	
};

//******串口屏变量****************************
volatile unsigned char __attribute__((__far__))  LCD_Rbuffer[256];
volatile unsigned char __attribute__((__far__))  LCD_Tbuffer[1200];
volatile unsigned int LCD_Rbuffer_now=0,LCD_Rbuffer_num=0,LCD_Rbuffer_sign=0;
volatile unsigned int LCD_Tbuffer_now=0,LCD_Tbuffer_num=0,LCD_Tbuffer_sign=1;

volatile int __attribute__((__far__))  record_wave_b[64];//备份
volatile int __attribute__((__far__))  record_wave_b1[64];//另外两项
volatile int __attribute__((__far__))  record_wave_b2[64];//另外两项

volatile int __attribute__((__far__))  MAX_data[4][2];//0:频次；1:有效值
//****************************************************************************
//****************************************************************************
volatile unsigned long DELAY_BLIGHT_SIGN;//背光时间

volatile unsigned int WIRE_cost[][3]=//APF 系统数据
{
  {223,222,234},	 //0电网电压 1
  {685,1123,2345},   //1电网电流//1
  {23,123,434}, 	 //2负载电流//1
  {234,23,23},       //3补偿电流//1
  {9810,96,8},		 //4电网功率kVA
  {3,96,886},		 //5负载功率kVA//大于10保留小数一位，大于100零位
  {0,0,0},           //6电网零相电流，负载零相电流，补偿零相电流
  {0,0,0}, 			 //7 已消耗滤波补偿能力
};

volatile unsigned int LOAD_cost[][3]=//APF 运行数据
{
  {501,499,500},	//0频率，软件版本号2，提示信息
  {99,91,95},       //1电网功率因数
  {9,9,5},       	//2负载功率因数
  {12,12,12},       //3电网电压畸变率
  {23,123,434},     //4电网电流畸变率
  {34,234,999},  	//5负载电流畸变率
  
  {0,0,0},          //6直流侧电压，功率模块温度一，软件版本号1
  {0,0,0},          //7装置损耗，模块温度二，显示容量
  
  {0,0,0},          //8 共补投切状态1 1~15，SRC共补组数，投切状态2 16~31
  {0,0,0},          //9 分补投切状态1 A0~4,B5~9,C10~14
  					//分补组数
  					//分补充投切状态2 A5~9,B10~14,C15~19
};

volatile unsigned int WIRE_cost_buffer[7][3][22];	 //APF 系统数据
volatile unsigned int LOAD_cost_buffer[9][3][22];	 //APF 运行数据
//所有数据的第二十位，否是一开始的数据
//在数据小于某个范围内也需要复位，
//第二十一位是这个数据的指针；


volatile unsigned int APF_state=0;//设备运行状态 0停机 1运行，2故障，
volatile unsigned int APF_error=0;//0：无故障，1：有故障
volatile unsigned int APF_CAN=0;//0：不正常，1：正常                 暂时备用****

volatile unsigned int P_E2PROM[]=//初始化数据，，如果已经初始化，则把E2中的数据加载到这里
{
	0xaaa7, //0 E2使能
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
	0,      //80 是否显示SVG频谱
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
	0000,    //120 短信中心号码1~4              971
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

volatile unsigned int system_parameter_b[45];//系统设置缓冲区域     暂时备用****

volatile unsigned int protect_parameter_b[9];//参数发送备份

volatile unsigned int hide_parameter_b[3][4];//隐藏参数缓冲区

volatile unsigned int equipment_skate[8][4];//设备的状态和故障代码,运行状态，开关状态

volatile unsigned int equipment_ID[8][4]=   //设备ID  生产编号，生产       @@@@@  初始化清零
{
	{0,9,0,0x9000},//第一个位置，用于表示当前有几个数据
	{0,9,0,0x9000},
	{0,9,0,0x9000},
	{0,9,0,0x9000},
	{0,9,0,0x9000},
	{0,9,0,0x9000},
	{0,9,0,0x9000},
	{0,9,0,0x9000}, 
};

volatile unsigned int equiment_set[]=//0:在线主控个数，1:激活地址,2在线主控个数备份
{
	0,0,0
};

volatile unsigned int electric_receive_sign=0;//电气量接收标识，
volatile unsigned int parameter_receive_sign=0;//参数设置标识
volatile unsigned int parameter_receive_SMSsign=0;//sms参数设置标识

volatile unsigned int GSM_NUM_fist=0;//上电读取短信中心号码


int main()
{			
		INTCON1=0x0000;
		INTCON2=0x0000;//关闭CPU中断
		
		oscConfig();//振荡器配置
		stopWdog(); //停止看门狗
		
		_TRISB10=0;//输入
		_TRISB4=1;//输入 停止
		_TRISB5=1;//输入 启动
		start_GSM;//启动短信猫
		
		clearIntrflags();//清中断标志
		
		LED_Config();	 //LED配置
		E2ROM_93LC86C_Config();//E2初始化，系统初始化
	
		time1_config(100);//100us的定时器
		start_time1();//启动定时器
		RS232_Config();//RS232配置
		RS232dis_Config(); //串口屏初始化	
		RS485_Config();	
		DMA_C1S();//CAN1配置
		DMA_C1R();//CAN1配置
		
		K_num=switch_num();//拨码开关变换以后需要重新上电
				
		if(K_num==0x0f)//0X0F 进入测试程序，包括所有
		{		
			P_E2PROM[117]=0;
		    P_E2PROM[118]=9600;
			P_E2PROM[119]=0;
			CH432T_config();
			TEST_ALL();
		}
			
		Ecan1_Config();// 测试过后恢复can配置
		RS232dis_Config(); //串口屏初始化
		E2ROM_93LC86C_init();//e2数据初始化
		Init_array();//系统数据初始化，
		
		CH432T_config();//485
		time2_config(1000);//1ms定时		
		startWdog();//启动看门狗

//CAN调试。。。。。。。。。。。。。。。。。。。。。。				
//	ecan1WriteTxMsgBufId(0,0x201,0,0);
//	ecan1WriteTxMsgBufData(0,8,0x0003,0x0001,0,0);
//	C1TR01CONbits.TXREQ0=1;
//	C1TR01CONbits.TXREQ1=1;
//	C1TR23CONbits.TXREQ2=1;
    	
//    	DS1302_init();
    	

//****232调试************************************
//	RS485_send;
//  RS485_Sdata();
	while(1)
	{					
		//	xu=switch_num();
		//	LED_tube(xu);   //根据拨码开关显示数据
			
//**********数据计算************************
	        if(electric_receive_sign==1)
	        {
		        //DELAY_TIME=0;
//		        if(switch_num()==0x00) //APF 所有版本的计算是一样的
//				{
					ACCOUNT_data();//计算时间，在200ms 内能不能算完，并修改调试时间4ms
					if(P_E2PROM[22]>1)	ACCOUNT_buffer();//缓冲计算		
					
//				}      
				
				electric_receive_sign=2;//可以显示波形
		    } 
		    
//**********读取当前时间*********************
	if(DELAY_send_message>10000)//500ms 是不是有点长
	{
#if compileGSM
		GSM_handle();//GSM处理程序
#endif
#if compilemodbus
                modbus_change();
#endif
		if(TIME_NOW[0]!=0)//防止上电瞬间正好到点
			DS1302_AUTO_RUN_STOP();
			
		if(TIME_NOW[4]==0&&TIME_NOW[5]==0)	stop_GSM;  //错开发送时间
		else 								start_GSM; //定时关闭
		
		DELAY_send_message=0;

               
	}
	
		if(GSM_NUM_fist==1) DELAY_GSM_NUM=0;//短信中心号码如果询问过一次了，以后不再询问
	else if(GSM_NUM_fist==2){E2ROM_WR(971,3,P_E2PROM+120);GSM_NUM_fist=1;}//写入E2
	

//*****状态显示**************************
			if(DELAY_DSIskate>4000)//状态显示 400ms一次
			{
				page_state();//设备状态
					
				DELAY_DSIskate=0;
			}		
				
//********电气量发送命令控制****************  
		send_elect();
		
//*****手动停止运行********
		if(P_E2PROM[114]!=0)
		{
			if(PORTBbits.RB5==0)//手动停止运行
			{
				ecan1WriteTxMsgBufId(1,0x201,0,0);
				ecan1WriteTxMsgBufData(1,8,0x0002,0,0,0);//运行命令
				C1TR01CONbits.TXREQ1=1;
				WRITE_fault_one(37,0);
#if compilemodbus
                                Modbus_electric[0]=37;Modbus_electric[1]=1;
#endif
			}
			else
			if(PORTBbits.RB4==0)
			{
				ecan1WriteTxMsgBufId(1,0x201,0,0);
				ecan1WriteTxMsgBufData(1,8,0x0001,0,0,0);//停止命令
				C1TR01CONbits.TXREQ1=1;
				WRITE_fault_one(38,0);
#if compilemodbus
                                Modbus_electric[0]=38;Modbus_electric[1]=1;
#endif
			}
		}
					
//LCD运行控制*******************************************
				LCD_page_run();//串口屏运行
	
	}//while
	
}
















