#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"
#include "..\include\string_h.h"


unsigned int page_sign=1;
unsigned int page1_sign=0;//
unsigned int page2_sign=0;//
unsigned int page3_sign=0;//
unsigned int page4_sign=0;//
unsigned int page5_sign=0;//
unsigned int page6_sign=0;//	
unsigned int page7_sign=0;//
unsigned int page8_sign=0;//
unsigned int page9_sign=0;//
unsigned int page10_sign=0;//
unsigned int page11_sign=0;//
unsigned int page12_sign=0;//
unsigned int page13_sign=0;//
unsigned int page14_sign=0;//
unsigned int page15_sign=0;//
unsigned int page15_1_sign=0;//
unsigned int page15_2_sign=0;//
unsigned int page15_3_sign=0;//
unsigned int page15_4_sign=0;//
unsigned int page15_5_sign=0;//
unsigned int page15_6_sign=0;//
unsigned int page15_7_sign=0;//
unsigned int page16_sign=0;//
unsigned int page17_sign=0;//
unsigned int page18_sign=0;//

unsigned int LAST_PAGE=0;

unsigned int command_state;//和按钮保持一致，按下按钮执行的状态，1:运行;0:停止
unsigned int command_send;//即将发送的是什么量：1：发送开关信号，2：欠压过压值保护参数值，
                          //3：校准参数值，4：系统参数值，5：通信参数值，6，隐藏的参数
                          //7,清空故障，8：清空当月发电量，9：恢复出厂设置
unsigned int fault_data_num;//当前显示的故障代码的地址,

unsigned int tell_stop=0xffff;//如果等于1，说明提示过了

unsigned int tran_data=0;//过渡用
