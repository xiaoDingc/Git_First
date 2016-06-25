
extern volatile unsigned int yuan1;
extern volatile unsigned int zhongyuan;//调试用

extern volatile unsigned int soft_APF_SVG[][2];//版本号
//**********选择编译************************************
#define compilemodbus 0
#define compileGSM 1
//************** main ***************************
extern volatile int record_wave[12][64];
extern volatile int record_single[][3];

extern volatile unsigned char __attribute__((__far__))  LCD_Rbuffer[256];
extern volatile unsigned char __attribute__((__far__))  LCD_Tbuffer[1200];
extern volatile unsigned int LCD_Rbuffer_now,LCD_Rbuffer_num,LCD_Rbuffer_sign;
extern volatile unsigned int LCD_Tbuffer_now,LCD_Tbuffer_num,LCD_Tbuffer_sign;

extern volatile int __attribute__((__far__))  record_wave_b[64];//备份
extern volatile int __attribute__((__far__))  record_wave_b1[64];//另外两项
extern volatile int __attribute__((__far__))  record_wave_b2[64];//另外两项

extern volatile int __attribute__((__far__))  MAX_data[4][2];//0:频次；1:有效值
//****************************************************************************
//****************************************************************************
extern volatile unsigned long DELAY_BLIGHT_SIGN;
extern volatile unsigned int WIRE_cost[][3];
extern volatile unsigned int LOAD_cost[][3];//用来保存显示在界面上的电气量

extern volatile unsigned int WIRE_cost_buffer[7][3][22];//APF 系统数据
extern volatile unsigned int LOAD_cost_buffer[9][3][22];//APF 运行数据

extern volatile unsigned int APF_state;//设备运行状态 0停机 1启动中，2待机，3运行，4故障，
extern volatile unsigned int APF_error;//0：无故障，1：有故障
extern volatile unsigned int APF_CAN;//0:CAN通信终端，1:CAN通讯正常
extern volatile unsigned int P_E2PROM[];//初始化的参数，

extern volatile unsigned int system_parameter_b[45];
extern volatile unsigned int protect_parameter_b[9];
extern volatile unsigned int hide_parameter_b[3][4];
extern volatile unsigned int equipment_skate[8][4];//设备的状态和故障代码
extern volatile unsigned int equiment_set[];//主控的个数
extern volatile unsigned int equipment_ID[8][4];
extern volatile unsigned int electric_receive_sign;//电气量接收标识
extern volatile unsigned int parameter_receive_sign;//参数设置标识
extern volatile unsigned int parameter_receive_SMSsign;

extern volatile unsigned int GSM_NUM_fist;


//*********AUTO_run**************************
extern volatile unsigned int  AUTO_run;
extern volatile unsigned int  AUTO_stop;
extern volatile unsigned int  which_equ;
extern volatile unsigned long ask_time;
void DS1302_AUTO_RUN_STOP(void);
void page_state(void);


//**********DSPIC33F_sys*******************
#define start_GSM LATBbits.LATB10=1
#define stop_GSM  LATBbits.LATB10=0 
void stopWdog(void);
void startWdog(void);
void clearWdog(void);
void oscConfig(void);
void clearIntrflags(void);
void send_elect(void);


//*****E2PROM************************
void E2ROM_93LC86C_Config(void);
void E2ROM_93LC86C_WCommand(unsigned int data);
void E2ROM_93LC86C_Wdata(unsigned int data);
void E2ROM_93LC86C_Busy(void);
int E2ROM_93LC86C_Read(void);
void E2ROM_93LC86C_writedata(unsigned int addr,int data);
int E2ROM_93LC86C_readdata(unsigned int addr);
unsigned int E2ROM_WR(unsigned int add,unsigned int num,volatile unsigned int *character);
void E2ROM_RD(unsigned int add,unsigned int num,volatile unsigned int *character);
void E2ROM_93LC86C_init();
void WRITE_fault_one(unsigned int fault,unsigned int mode);
void WRITE_fault_shadow(unsigned int fault,unsigned int mode);
void CLEAR_fault_all(unsigned int type);

extern volatile unsigned int __attribute__((__far__)) add_error_data[15][11];//即将保存的0~9故障信息，10:地址，11：写标志
extern volatile unsigned int error_write,error_read;

//***********CAN1**************************************
void DMA_C1R(void);
void DMA_C1S(void);
void ecan1WriteRxAcptFilter(int n, long identifier, unsigned int exide, unsigned int bufPnt,unsigned int maskSel);
void ecan1WriteRxAcptMask(int m, long identifier, unsigned int mide, unsigned int exide);
void ecan1WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit);
void ecan1WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4);
void ecan1DisableRXFilter(int n);
void Ecan1_Config(void);//CAN1模块配置
void CAN1_examp(void);


//*****************fft*************************
extern volatile unsigned int coordinate_now;
extern volatile int zero_wave[3][64];

void find_max(volatile int *data);
void find_max_plus(volatile int *data);
void fft_calculation (volatile int *data);
void fft_effective_all(void);
void fft_effective_one(void);
unsigned int effective_c(volatile int *data);
void ACCOUNT_data(void);
void ACCOUNT_Sdata(void);
void ACCOUNT_buffer_one(volatile unsigned int *data_buffer,volatile unsigned int *data);
void ACCOUNT_buffer(void);

void LCD_wave_calculation(volatile unsigned int coor,volatile int *data_dir,volatile int *data,volatile int *data_b,volatile int *data1,volatile int *data_b1,volatile int *data2,volatile int *data_b2,volatile int *data_n,volatile int *data_bn);
void LCD_histogram_calculation(volatile unsigned int coor,volatile int *data,volatile int *data_b,volatile int *data1,volatile int *data_b1,volatile int *data2,volatile int *data_b2);


//*********init******************************
void Init_data_buffer(void);
void Init_array(void);


//*************LED******************************
void DELAY(unsigned long time);
void LED_Config(void);
void LED_ray(void);//流水灯，临时用，删除
void LED_light(unsigned char data);
void LED_light_ray(unsigned data);
unsigned char switch_num(void);


//**test**********************
extern volatile unsigned int TEST_SIGN;

void TEST_ALL(void);


//*******time1***************
#define start_time1() _TON=1    //启动定时器	
#define stop_time1()  _TON=0;	  //启动定时器	
extern volatile unsigned long DELAY_TIME;
extern volatile unsigned long DELAY_SLEEP;
extern volatile unsigned long DELAY_Blight;
extern volatile unsigned long DELAY_ASKTIME;
extern volatile unsigned long DELAY_DSIskate;//状态显示
extern volatile unsigned long DELAY_CAN[8];//CAN通讯延时
extern volatile unsigned long DELAY_run_time;//计算设备运行时间
extern volatile unsigned long DELAY_refresh_data;//数据刷新时间
extern volatile unsigned long DELAY_GSM;//   暂时备用******
extern volatile unsigned long DELAY_send_message;//发送信息用
extern volatile unsigned long DELAY_message;     //提示信息延时
extern volatile unsigned long DELAY_fist_page;//上电加载
extern volatile unsigned long DELAY_GSM_error;
extern volatile unsigned long DELAY_elect_synch;
extern volatile unsigned int  MODBUS_TIME;
extern volatile unsigned long DELAY_GSM_NUM;

extern volatile unsigned long DELAY_refresh_data_com;
extern volatile unsigned int run_time_sign;//运行时间改变标识

//extern char R232_send_data[20];         //暂时备用*****
extern volatile unsigned int R232_send_data_num; //暂时备用*****
extern volatile unsigned int R232_send_data_now; //暂时备用*****

void time1_config(unsigned int time);
void time2_config(unsigned int time);


//**********RS232***************************
#define RS232_Sfifo   U1STAbits.UTXBF //1：发送缓冲器满；不能再把数据放入发送缓冲区
#define RS232_Rfifo   U1STAbits.URXDA //1：接收缓冲区有数据；已经收到数据，可以去取接收缓冲区
#define RS232_Sover	  U1STAbits.TRMT  //1：发送寄存器为空；一次发送完成

#define RS232_Rbusy     U1STAbits.RIDLE //1:接收器空闲；0：忙
#define RS232_PERR		U1STAbits.PERR  //1:奇偶校验错误
#define RS232_FERR		U1STAbits.FERR  //1:帧错误
#define RS232_OERR		U1STAbits.OERR  //1:接收溢出错误
//	U1TXREG;	//发送寄存器
//	U1RXREG		//接收寄存器 四个缓冲区
void RS232_Config(void);
void RS232dis_Config(void);
void RS232_Sdata(void);
void RS232_Rdata(void);


//**********RS232dis***************************
#define RS232dis_Sfifo   U2STAbits.UTXBF //1：发送缓冲器满；不能再把数据放入发送缓冲区
#define RS232dis_Rfifo   U2STAbits.URXDA //1：接收缓冲区有数据；已经收到数据，可以去取接收缓冲区
#define RS232dis_Sover	  U2STAbits.TRMT  //1：发送寄存器为空；一次发送完成

#define RS232dis_Rbusy     U2STAbits.RIDLE //1:接收器空闲；0：忙
#define RS232dis_PERR		U2STAbits.PERR  //1:奇偶校验错误
#define RS232dis_FERR		U2STAbits.FERR  //1:帧错误
#define RS232dis_OERR		U2STAbits.OERR  //1:接收溢出错误
//	U2TXREG;	//发送寄存器
//	U2RXREG		//接收寄存器 四个缓冲区

void RS232dis_Config(void);
void RS232dis_Sdata(void);
void RS232dis_Rdata(void);

//************串口屏*******************************
extern volatile unsigned long DELAY_refresh_data_com;

extern volatile unsigned int run_time_sign;//运行时间改变标识

extern volatile unsigned int R232_send_data_num;
extern volatile unsigned int R232_send_data_now;

void time1_config(unsigned int time);

#if compileGSM
//********GSM***********
	extern volatile unsigned char __attribute__((__far__)) SOURCE[370];
	extern volatile unsigned char __attribute__((__far__)) SOURCE_data[200];
	extern volatile unsigned char  SEND_CMGS;
	
	extern volatile unsigned char __attribute__((__far__)) SOURCE_R_num[40];//接收短信中心号码
	extern volatile unsigned int  R232_receive_Ndata_now;//接收短信中心号码
	
	extern volatile unsigned char __attribute__((__far__)) SOURCE_R[370];//接受数据监控号码
	extern volatile unsigned char __attribute__((__far__)) SOURCE_data_R[160];//数据
	extern volatile unsigned char  SEND_CMGS_R;
	
	extern volatile unsigned int GSM_send_num;//用于控制GSM发送数据
	extern volatile unsigned int GSM_record_sign;//用于判断发送的数据类型
	
	extern volatile unsigned char __attribute__((__far__)) R232_send_data[1000];
	extern volatile unsigned int R232_send_data_num;
	extern volatile unsigned int R232_send_data_now;
	extern volatile unsigned int R232_Send_sign;//是否正在发送数据
	extern volatile unsigned int R232_receive_data_num;
	extern volatile unsigned int R232_receive_data_now;
	extern volatile unsigned int R232_Rbuffer_sign;
	
	extern volatile unsigned int  send_message_time;
	
unsigned char char_hex(unsigned char D_high,unsigned char D_low);
unsigned int char_int(unsigned int num,volatile unsigned char *character);
unsigned int add_data_string(unsigned int fist_num,unsigned int record,unsigned int point);
unsigned int add_num_string(unsigned int fist_num,unsigned int record,unsigned int num);
void add_num(void);
void send_message(void);
int GSMEncode7bit(volatile unsigned char *pDst,volatile unsigned char *pSrc, int nSrcLength);
int GSMDecode7bit(volatile unsigned char *pDst,volatile unsigned char *pSrc);
void GSM_handle(void);
#endif
//*****串口屏声明*******************
extern volatile unsigned int LCD_page_sign;//初始的时候什么都不显示
extern volatile unsigned int LCD_page_dis;//是否第一次进入
extern volatile unsigned int LCD_page_dis_b;//备用数据
extern volatile unsigned int LCD_page_dis_bb;//备用数据
extern volatile unsigned int LCD_page_dis_bbb;//备用数据
extern volatile unsigned int LCD_page_dis_bbbb;//备用数据
extern volatile int *LCD_page_array;             //地址
extern volatile unsigned int LCD_page101;
extern volatile unsigned int LCD_page102;
extern volatile unsigned int LCD_page103;
extern volatile unsigned int LCD_page201;
extern volatile unsigned int LCD_page202;
extern volatile unsigned int LCD_page203;
extern volatile unsigned int LCD_page204;
extern volatile unsigned int LCD_page205;
extern volatile unsigned int LCD_page206;
extern volatile unsigned int LCD_page301;
extern volatile unsigned int LCD_page401;
extern volatile unsigned int LCD_page501;
extern volatile unsigned int LCD_page502;
extern volatile unsigned int LCD_page503;
extern volatile unsigned int LCD_page504;
extern volatile unsigned int LCD_page505;
extern volatile unsigned int LCD_page601;
extern volatile unsigned int LCD_page602;
extern volatile unsigned int LCD_page603;
extern volatile unsigned int LCD_page604;
extern volatile unsigned int LCD_page605;
extern volatile unsigned int LCD_page606;
extern volatile unsigned int LCD_page701;
extern volatile unsigned int LCD_page702;
extern volatile unsigned int LCD_page703;
extern volatile unsigned int LCD_Ddata_buffer[255];//用于参数显示过度使用
extern volatile unsigned char __attribute__((__far__))  LCD_Ddata_tran[20];//用于过度使用
extern volatile unsigned int KEY_com;//功能按钮
extern volatile unsigned int ERROR_num;//故障的数目，在故障数目改变的时候，显示要随之改变 缓冲用
extern volatile unsigned int change_data;//数据改变时更新变量
extern volatile unsigned int change_data_only;
extern volatile unsigned int message_num;//提示信息在数组中的位置
extern volatile unsigned int LED_state;//背光当前的状态，上电默认为是开启;
extern volatile unsigned int equipment_skate_sign;//上电显示离线  用于离线更新
extern volatile unsigned int RUN_stop;//处理停止运行的页面
extern volatile unsigned int TIME_NOW[];//当前时间 0:年，1：月，2日，3星期  4时 5分
extern volatile unsigned int fault_data_num;//当前显示的故障代码的地址,
extern volatile unsigned long password_one;//第一级密码
extern volatile unsigned long password_two;//第二级密码
extern volatile unsigned char K_num;//拨码开关状态
extern volatile unsigned int  equipment_activate;
extern volatile unsigned int  ALL_cap;

//*****底层发送接收**********************************************
void RS232_Slcd(void);
void RS232_Rlcd(void);
//*****************接收处理**************************************************************************

void RS232_Rlcd_button(void);
//*******数据处理**************************************************************************

void LCD_page_101(void);
void LCD_page_102(void);
void LCD_page_103(void);
void LCD_page_201(void);
void LCD_page_202(void);
void LCD_page_203(void);
void LCD_page_204(void);
void LCD_page_205(void);
void LCD_page_206(void);
void LCD_page_301(void);
void LCD_page_401(void);
void LCD_page_501(void);
void LCD_page_502(void);
void LCD_page_503(unsigned int page,unsigned int order);
void LCD_page_504(void);
void LCD_page_505(void);
void LCD_page_601(unsigned int page,unsigned int order);
void LCD_page_602(unsigned int page,unsigned int order);
void LCD_page_606(unsigned int page,unsigned int order);
void LCD_page_701(void);
void LCD_page_702(void);
void LCD_page_703(void);
void LCD_page_run(void);


//**RS485***********************
#define CN_RBR        0x0000   //读 接收缓冲器地址
#define CN_THR        0x0200   //写 发送缓冲器的地址


#define CN_IER_reset  0x0680  //写 软复位串口  禁止所有中断
#define CN_IER_read   0x0400  //读 各中断是否使能或禁止   不用

#define CN_IIR_read   0x0800  //只读 中断状态标志地址，最高两位C说明fifi已经启用
							  //0x1无中断，0x6接收到线路状态 ,0x4接收数据达到FIFO设定的值，
							  //0xC 4个数据时间未收到数据  2发送寄存器空 
							  
#define CN_FCR_write  0x0a07  //只写  最高2位:收到1,4,8,14个数据触发中断  	     
							  //接收一字节触发中断，清空发送接收fifo，复位fifo，启用FIFO
							  
#define CN_MCR_write  0x1200  //写 
#define CN_MCR_read   0x1000  //读 5:1允许CTS,RTS;4:1测试模式；3:1允许引脚中断输出；2:1自定义，1:1RTS引脚输出有效，0:1DTR引脚输出有效

#define CN_LCR_write_hz 0x0E80  //写 可以写波特率 开始时用      8数据 偶校验，1停止
#define CN_LCR_write    0x0E00  //写 禁止写波特率，可以读取数据 8数据 偶校验，1停止
#define CN_LCR_read     0x0c00	//读 波特率  不用

#define CN_LSR        0x1400    //读 线路状态：0：1接收fifo中有数据，读取清零
                                          // 1：1接收fifo溢出
                                          // 2：1fifo校验错误
                                          // 3：1fifo帧错误，缺少停止位
                                          // 4：1检测到线路间隔
                                          // 5：1发送保持THR空
                                          // 6：1THR,TSR全部空，数据全部发完
                                          // 7：1线路存在至少一个的错误
  
//内部1.8432                                             
#define CN_DLL        0X0200   //写 波特率 9600
#define CN_DLM        0X0600   //写 波特率 9600

#define SS1			  		_LATB2
#define SPI_send_over 		SPI1STATbits.SPITBF   //发送缓冲器满状态1
#define SPI_receive_over 	SPI1STATbits.SPIRBF  //接收缓冲器满状态1

extern volatile unsigned int CH432T_reset;// 为1 则串口复位
extern volatile unsigned int RS485_receive;// DATARDY 为1 则说明有数据可以读出  0无收到数据
extern volatile unsigned int RS485_send_fifo;// THRE 1可以继续向fifo发送数据，0,fifo已满 16级
extern volatile unsigned int RS485_send_over;// TEMT 1发送全部发完， 0
extern volatile unsigned int BSP_reset;
extern volatile unsigned int  MODBUS_T1_5;  
extern volatile unsigned int  MODBUS_T3_5; 

void RS485_Config(void);
void CH432T_config(void);



//**********modbus************************************
//#define   MODBUS_T1_5  20    //50*100um=2ms的延时    实际应该是 1000/(9600/11)*1.5=1.718ms;
//#define   MODBUS_T3_5  40    //90*100um=3.51ms的延时 实际应该是 1000/(9600/11)*3.5=4.01ms;
#if compilemodbus
#define ELECTRIC_N  250   //电气量
#define PARAMETER_N 9   //参数

//extern char MODBUS_ID;
extern volatile int  __attribute__((__far__))  Modbus_electric[ELECTRIC_N];			//  电气量  30001~~39999
extern volatile int  __attribute__((__far__))  Modbus_parameter[PARAMETER_N][2];		// 参数    40001~~49999
extern volatile unsigned int Modbus_write_sign;//是否有开关量或者参数被写入


void modbus_init();
void modbus_change();
void modbus_in();
void modbus_Shandle(void);

#endif
