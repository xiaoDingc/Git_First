#include "..\include\p33FJ128GP708A.h"
#include "..\include\dspicExtern.h"
#include "..\include\character_h.h"
#include "..\include\string_h.h"


void LCD6448_Config(void)//LCD配置，初始化
{
	_TRISC3=0;
	_TRISC4=0;//转换芯片方向控制引脚，输出

	TRISDbits.TRISD0_7=0x00;//数据方向 输出
	_TRISC14=0;
	_TRISD13=0;
	_TRISD12=0;
	_TRISG2=0;
	_TRISG3=0;//控制方向，输出
	
	_LATC3=1;
	_LATC4=1;//转换芯片方向A-B
	
	LCD6448_RD=1;
	LCD6448_WR=1;
}	


void LCD6448_X(unsigned char ADD)//列地址寄存器 X(0-639)
{
	LCD6448_CS=0;
	LCD6448_A1=0;
	LCD6448_A0=0;
	LCD6448_data=ADD;
	LCD6448_WR=0;
	DELAY(1);//>=40ns
	LCD6448_WR=1;
	LCD6448_CS=1;
}	

void LCD6448_Y(unsigned char ADD)//行地址寄存器 Y(0-479)
{
	LCD6448_CS=0;
	LCD6448_A1=0;
	LCD6448_A0=1;
	LCD6448_data=ADD;
	LCD6448_WR=0;
	DELAY(1);//>=40ns
	LCD6448_WR=1;
	LCD6448_CS=1;
}	

void LCD6448_Wcmd(unsigned char CMD)//写控制寄存器 CMD
{
	LCD6448_CS=0;
	LCD6448_A1=1;
	LCD6448_A0=0;
	LCD6448_data=CMD;
	LCD6448_WR=0;
	DELAY(1);//>=40ns
	LCD6448_WR=1;
	LCD6448_CS=1;
}

void LCD6448_Wdata(unsigned char DAT)//写数据寄存器DAT
{
	LCD6448_CS=0;
	LCD6448_A1=1;
	LCD6448_A0=1;
	LCD6448_data=DAT;
	LCD6448_WR=0;
	DELAY(1);//>=40ns
	LCD6448_WR=1;
	LCD6448_CS=1;
}

void LCD6448_light(unsigned int light)
{
	LCD6448_Wcmd(0x06);
	LCD6448_Wdata(light);	
}	

void LCD6448_Waddr(unsigned int x,unsigned int y)//写地址639*479
{
	LCD6448_X(x%256);
	LCD6448_X(x/256);
	LCD6448_Y(y%256);
	LCD6448_Y(y/256);	
}	

void LCD6448_clear(unsigned char data) //清屏  data清屏颜色
{     
	 LCD6448_Wcmd(0x04);//设置背景色
	 LCD6448_Wdata(data);
	 LCD6448_Wcmd(0x08);//清屏
	 DELAY(65000);//需延时16.6 毫秒  30M//延时***************************************************************
}

void LCD6448_Bcolour(unsigned char colour) //设置背景色
{
	LCD6448_Wcmd(0x04);
	LCD6448_Wdata(colour);
}

void LCD6448_Fcolour(unsigned char colour) //设置前景色
{
	LCD6448_Wcmd(0x02);
	LCD6448_Wdata(colour);
}

void LCD6448_Scolour(unsigned char font,unsigned char back) //设置颜色,前景色在前，背景色在后
{
	LCD6448_Fcolour(font);
	LCD6448_Bcolour(back);
}

void LCD6448_Wbit(unsigned int x,unsigned int y,unsigned char colour)//以colour为颜色在X,Y处写一个点
{  
     LCD6448_Wcmd(0x00);//单点模式
	 LCD6448_Waddr(x,y);
	 LCD6448_Wdata(colour);
}
void LCD6448_line_Wbit(unsigned int x,unsigned int y,unsigned int num,unsigned char colour,unsigned int way)//以colour为颜色在X,Y处写一个点
{  
    unsigned int i;   	 
	 if(way==0)  LCD6448_Wcmd(0x00);//水平
	 else        LCD6448_Wcmd(0x10);//垂直

	 LCD6448_Waddr(x,y);
	 for(i=0;i<num;i++)     //线长
			LCD6448_Wdata(colour);   
}

void LCD6448_Wpicture(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,const unsigned char *character)//在x,y处显示row*tier的图片
{                                   //显示图片
     unsigned int i,j;
	 LCD6448_Wcmd(0x00);//单点模式
	 for(i=0;i<tier;i++)
	 {
		LCD6448_Waddr(x,y++);
		for(j=0;j<row;j++)
			LCD6448_Wdata(*(character++));//写字符需要  350ns		 
     }
}


void LCD6448_Wword(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,const unsigned char *character)//在x,y处显示row*tier的字符
{                        //显示字符
     unsigned int i,j;
	 LCD6448_Wcmd(0x01);//字符模式
	 row=row/8;//写一次跳八个地址

	 for(i=0;i<tier;i++)
	 {       
			 LCD6448_Waddr(x,y++);
			 for(j=0;j<row;j++)
					 LCD6448_Wdata(*(character++));//写字符需要  350ns
     }
}

void LCD6448_blank(unsigned int x,unsigned int y,unsigned int row,unsigned int tier)//清除 在x,y处显示row*tier的字符 
{                        //显示字符
     unsigned int i,j;
	 LCD6448_Wcmd(0x01);//字符模式
	 row=row>>3;//写一次跳八个地址
	 for(i=0;i<tier;i++)
	 {       
			 LCD6448_Waddr(x,y++);
			 for(j=0;j<row;j++)
					 LCD6448_Wdata(0);//写字符需要  350ns
     }
}



void LCD6448_Wstring(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,unsigned int num,const unsigned int *character)//在x,y处显示row*tier的字符，方形字体
{                        //写一行字符，以flash为字库，character中保存字符的位置，组成一段连续的字，num:数量
     unsigned int i,j,k,row1,m,n=0;
	 LCD6448_Wcmd(0x01);//字符模式
	 row1=row>>3;//写一次跳八个地址

	 for(k=0;k<num;k++)
	 {
			n=0;
			m=y;	
			if(row==32&&tier==32)
				K9F1208_Rpage(character[k] & 0x0fff,(character[k]&0xf000)>>7,128,flash_buffer);//
			else	
			if(row==16&&tier==32)
				K9F1208_Rpage(character[k] & 0x0fff,(character[k]&0xf000)>>7,64,flash_buffer);//
			else
			if(row==48&&tier==32)
				K9F1208_Rpage(character[k] & 0x0fff,(character[k]&0xf000)>>7,192,flash_buffer);//
				
				 for(i=0;i<tier;i++)
				 {       
						 LCD6448_Waddr(x+row*k,m++);
						 for(j=0;j<row1;j++)							 
									LCD6448_Wdata(flash_buffer[n++]);
			     }
	}
}



void LCD6448_num(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,int record,unsigned int point,unsigned int num,unsigned int unit,const unsigned char *character)//在x,y处显示row*tier的字符
{                        //在X,Y,处显示record,保留小数点point；1:一位；10：二位；
						//unit符号0：无，1：A;2：V；3：-；4::5:H,6:z,7:W; num:一共有几位数，1：一位，10：两位   //会自动填满剩下的位置7位
     unsigned int i=0,j,k=0,row1,l,n,m=10000;
     unsigned char data[8],data_num=0;
	 LCD6448_Wcmd(0x01);//字符模式
	 row1=row>>3;//写一次跳八个地址
	 
	 if(record<0) 
	 {
		 data[data_num++]=13;//如果record为负数，前面加负号
		 record*=-1;         //变成正数		 
	 }
	 
	 while(m!=0)
	 {
	//		i=num/m;
			
//			i=point/m;
			
			if(i==0) i=num/m+point/m; //是否需要提前进入
			n=record/m;  //最高位
			record=record%m;  //	
			
			if((n!=0)||(k!=0)||(i!=0))		//如果最高位不为零
			{ 
				if(k==0)  k=1;
				data[data_num++]=n;           //把数据加入数组
				if((m==point)&&(point!=1)) data[data_num++]=10;//保留小数点
			}

			m/=10;  //
	 }	 
	 
	 l=row*tier>>3;	  
	 
	 if((unit & 0x0f)!=0) data[data_num++]=10+(unit & 0x0f);//添加符号 
	 if(((unit >> 4)&0x0f)!=0)   data[data_num++]=10+(((unit >> 4)&0x0f));//添加符号 
	 if((unit >> 8)!=0)   data[data_num++]=10+(unit >> 8);//添加符号    //添加三个符号
	 
	 	
	 for(k=0;k<8;k++)
	 {
			n=0;
			m=y;		
				 for(i=0;i<tier;i++)
				 {       
						 LCD6448_Waddr(x+row*k,m++);
						 for(j=0;j<row1;j++)
						 {
							if(k<data_num)
								 LCD6448_Wdata(character[data[k]*l+n++]);//写字符需要  350ns
							else
								 LCD6448_Wdata(0x00);
						 }
			     }
	}
}

void LCD6448_Wshadow(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,unsigned int shadow,unsigned int colour)
{										//显示一个带阴影的方块，前景色会改成colour,也可以显示一条直线
	 unsigned int i,j,row1,tier1;
	 LCD6448_Wcmd(0x01);//字符模式
	 row1=row>>3;//写一次跳八个地址
     tier1=tier>>3;
	 for(i=0;i<tier;i++)//显示一个方块
	 {       
			 LCD6448_Waddr(x,y+i);
			 for(j=0;j<row1;j++)
					 LCD6448_Wdata(0xff);//写字符需要  350ns 
     }
     
     if(shadow!=0)
     {
     
			     LCD6448_Fcolour(colour); //阴影的颜色，01深蓝
			     LCD6448_Wcmd(0x01);//字符模式
				  for(i=0;i<shadow;i++)//方块的横向 阴影
				  {
					  LCD6448_Waddr(x+i,y+tier+i-1);
						 for(j=0;j<row1;j++)
								 LCD6448_Wdata(0xff);//写字符需要  350ns 
				  } 
				  
				  LCD6448_Wcmd(0x11);//y++,8位  
				  for(i=0;i<shadow;i++)//方块的纵向阴影
				  {
					  LCD6448_Waddr(x+row+i-1,y+i);
						 for(j=0;j<tier1;j++)
								 LCD6448_Wdata(0xff);//写字符需要  350ns
				  }	
	  }
}	


void LCD6448_line(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,unsigned int way)
{				//0:横向直线；1：纵向直线，用于显示网格
	 unsigned int i,j,row1,tier1;

     if(way==0)
     {
	     LCD6448_Wcmd(0x01);//字符模式
	 	 row1=row>>3;//写一次跳八个地址
	 	 
	 	 for(i=0;i<tier;i++)//显示一个方块
	 	 {       
			 LCD6448_Waddr(x,y+i);
			 for(j=0;j<row1;j++)
					 LCD6448_Wdata(0xff);//写字符需要  350ns 
     	 } 
	 }
	 else
	 {
		 LCD6448_Wcmd(0x11);
		 tier1=tier>>3;
		 
		 for(i=0;i<row;i++)//显示一个方块
	 	 {       
			 LCD6448_Waddr(x+i,y);
			 for(j=0;j<tier1;j++)
					 LCD6448_Wdata(0xff);//写字符需要  350ns 
     	 } 
	  } 
}	

void LCD6448_button(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,unsigned int shadow,unsigned int F_colour,unsigned int button)
{										//显示按钮的阴影，button=0，没有按下，    colour: 代表按钮的颜色;  改变颜色
	 unsigned int i,j,row1,tier1,k,l;
	 LCD6448_Wcmd(0x01);//字符模式
	 row1=row>>3;//写一次跳八个地址
	 tier1=tier>>3;

     //下方			        			     
			     

    for(l=0;l<2;l++)
    {
			if(l==0)
			{
				if(button==0) k=1;
				else          k=0;	
			}
			else
			{
				if(button==0) k=0;
				else          k=1;	
			}	

	        
	        if(k==0)
			{     
			     if(button==0) LCD6448_Fcolour(64); //阴影的颜色 下方
			     else          LCD6448_Fcolour(F_colour); 
			     
					  LCD6448_Wcmd(0x01);//字符模式
					  for(i=0;i<shadow;i++)//方块的横向 阴影
					  {
						     if(i==shadow-1 && button!=0) {LCD6448_Fcolour(255);LCD6448_Wcmd(0x01);}//最后一条线改成白色的线	     
						     LCD6448_Waddr(x+i,y+tier+i-1);
							 for(j=0;j<row1;j++)
									 LCD6448_Wdata(0xff);//写字符需要  350ns 
					  } 		  
					  
				if(button==0) LCD6448_Fcolour(64); //阴影的颜色  右侧
			     else          LCD6448_Fcolour(F_colour); 
					  
					  LCD6448_Wcmd(0x11);//y++,8位  
					  for(i=0;i<shadow;i++)//方块的纵向阴影
					  {
						     if(i==shadow-1 && button!=0) {LCD6448_Fcolour(255);LCD6448_Wcmd(0x011);}//最后一条线改成白色的线
						     LCD6448_Waddr(x+row+i-1,y+i);
							 for(j=0;j<tier1;j++)
									 LCD6448_Wdata(0xff);//写字符需要  350ns
					  }   		
			}	
							  	
//上方				
			if(k==1)
			{		  

				 if(button==0) LCD6448_Fcolour(F_colour); //阴影的颜色上侧
			     else          LCD6448_Fcolour(64); 
			     
			     LCD6448_Wcmd(0x01);//字符模式
				  for(i=shadow;i>0;i--)//方块的横向 阴影
				  {
					     if(i==1 && button==0) {LCD6448_Fcolour(255);LCD6448_Wcmd(0x01);}//最后一条线改成白色的线
					     LCD6448_Waddr(x+i-1,y+i-1);
						 for(j=0;j<row1;j++)
								 LCD6448_Wdata(0xff);//写字符需要  350ns 
				  } 
				  
				  
				 if(button==0) LCD6448_Fcolour(F_colour); //阴影的颜色左侧
			     else          LCD6448_Fcolour(64); 				 
				  LCD6448_Wcmd(0x11);//y++,8位  
				  for(i=shadow;i>0;i--)//方块的纵向阴影
				  {					     
					     if(i==1 && button==0) {LCD6448_Fcolour(255);LCD6448_Wcmd(0x011);}//最后一条线改成白色的线
					     LCD6448_Waddr(x+i-1,y+i-1);
						 for(j=0;j<tier1;j++)
								 LCD6448_Wdata(0xff);//写字符需要  350ns
				  }	  
			}
			
		  }
}


void LCD6448_button_state(unsigned char colour)//根据KEY_list 显示按钮状态 改变颜色
{ 
	 unsigned int i;
	 
	 LCD6448_Fcolour(colour);//前景色	紫红色
	 LCD6448_Wshadow(534,50,96,64,0,64);//影子方块
	 LCD6448_button(534,50,96,64,4,colour,KEY_list[0]==0);//外框
	 
	 LCD6448_Fcolour(colour);//前景色	紫红色
	 LCD6448_Wshadow(534,128,96,64,0,64);//影子方块
	 LCD6448_button(534,128,96,64,4,colour,KEY_list[1]==0);//外框
	 
	 LCD6448_Fcolour(colour);//前景色	紫红色
	 LCD6448_Wshadow(534,206,96,64,0,64);//影子方块
	 LCD6448_button(534,206,96,64,4,colour,KEY_list[2]==0);//外框
	 
	 LCD6448_Fcolour(colour);//前景色	紫红色
	 LCD6448_Wshadow(534,284,96,64,0,64);//影子方块
	 LCD6448_button(534,284,96,64,4,colour,KEY_list[3]==0);//外框
	 
	 LCD6448_Fcolour(colour);//前景色	紫红色
	 LCD6448_Wshadow(534,362,96,64,0,64);//影子方块
	 LCD6448_button(534,362,96,64,4,colour,KEY_list[4]==0);//外框
	 
	 LCD6448_Scolour(255,colour);//白字，子背景
	 for(i=0;i<5;i++)
	 {	 
		 if(KEY_list[i]!=0)
		 LCD6448_Wstring(550,66+i*78,32,32,2,KEY_LIST[KEY_list[i]-1]);//显示字符
	 } 
}	

void LCD6448_button_down(unsigned int x,unsigned int y,unsigned int num)//按钮按下时显示 改变颜色
{	
	LCD6448_button(x,y,96,64,4,colour_button,1);//外框	
	LCD6448_Scolour(255,colour_button);//白字，紫色背景
	LCD6448_blank(x+16,y+16,64,32);//清空
	LCD6448_Wstring(x+20,y+20,32,32,2,KEY_LIST[KEY_list[num]-1]);//显示	 按钮从1开始，0：认为未使能
}	


void LCD6448_button_up(unsigned int x,unsigned int y,unsigned int num)//按钮松开时显示 改变颜色
{	
	LCD6448_button(x,y,96,64,4,colour_button,0);//外框	
	LCD6448_Scolour(255,colour_button);//白字，紫色子背景
	LCD6448_blank(x+20,y+20,64,32);//清空
	LCD6448_Wstring(x+16,y+16,32,32,2,KEY_LIST[KEY_list[num]-1]);//显示	
}


void LCD6448_list(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,unsigned int begin,unsigned int end,unsigned int interval,unsigned int Align,unsigned int unit,unsigned int num,const unsigned int character[][num])//显示菜单
{  //x,y:起始坐标，row，tier一个字符的长宽；begin,end:开始结束，第一行0；interval:上下间隔,
   //Align：0左对齐，1，右对齐，2：中间对齐;num:多少字符的数组，*character：数据首地址,
   unsigned int i;
   unsigned int x_align=0;
   
   for(i=begin;i<=end;i++)
   {
	   if(Align==1)  x_align=(num-character[i][0]-1)*row;
	   else
	   if(Align==2)	 x_align=((num-character[i][0]-1)>>1)*row;
	   	   
	   LCD6448_Wstring(x+x_align,y+i*interval,row,tier,character[i][0],character[i]+1);//显示字符,第一个字符用于显示数量了
	   
	   if(unit!=0)  LCD6448_Wword(x+x_align+character[i][0]*row,y+i*interval,16,32,Num16_32+896);//冒号
	   
	} 
	
}

void LCD6448_num_list(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,unsigned num,unsigned int interval,unsigned int record[][3],const unsigned char *character)//在x,y处显示row*tier的字符
{  //num：一共几行，interval每行间距多少， record：显示的数据指针，一维数据，二维小数点，三维符号,character:使用的数字数组
	unsigned int i;
	for(i=0;i<num;i++)
	{
		LCD6448_num(x,y+i*interval,row,tier,record[i][0],record[i][1],0,record[i][2],character);//在x,y处显示row*tier的字符
	}
}

	
void LCD6448_clear_menu(unsigned int num,const unsigned int *character)
{//删除主框内所有的数据，并改变菜单栏的数据
	unsigned int i;
	
	LCD6448_Scolour(colour_num,colour_window);
	LCD6448_blank(26,60,502,365);//清除区域
	i=num<<5;
	LCD6448_Scolour(colour_button,colour_window);//   主框内的一条直线
	LCD6448_Wshadow(30,100,i,8,0,64);//影子方块
	LCD6448_button(30,100,i,8,2,colour_button,0);

	LCD6448_Scolour(colour_num,colour_window);
	LCD6448_Wstring(30,62,32,32,num,character);		
}

void LCD6448_time_num(unsigned int x,unsigned int y,unsigned char record)//在x,y处显示row*tier的字符
{                        //修改时间参数，十六进制 显示
	unsigned int i;
	  i=record;
	 LCD6448_Wword(x,y,16,32,Num16_32+((i&0xf0)<<2));
	 LCD6448_Wword(x+16,y,16,32,Num16_32+((i&0x0f)<<6));
}

void LCD6448_num_set(unsigned int x,unsigned int y,int record,unsigned num)//在x,y处显示row*tier的字符，最小显示两位
{                        //在X,Y, num:后面增加几位空白,最小显示2位，后面加num位空白
     int i,j,k,n,m; 
     unsigned char data[8],data_num=0;
	 LCD6448_Wcmd(0x01);//字符模式
	 
	 while(record!=0)
	 {
			n=record%10; 
			data[data_num++]=n;
			record/=10;
	 }
	
	if(data_num==0) {data[0]=0;data[1]=0;data_num=2;}
	else
	if(data_num==1) {data[1]=0;data_num=2;}
	
	while(data_num<num)//
	{
		data[data_num++]=0;
	}	
	
	 for(k=0;k<data_num;k++)
	 {
		   n=0;
		   m=y;
				 for(i=0;i<32;i++)
				 {       
						 LCD6448_Waddr(x+16*k,m++);
						 for(j=0;j<2;j++)
						 {
							if(k<data_num)
								 LCD6448_Wdata(Num16_32[(data[data_num-k-1]<<6)+n++]);//写字符需要  350ns
							else
								 LCD6448_Wdata(0x00);
						 }
			     }
	}
}

void LCD6448_num_bit(unsigned int x,unsigned int y,unsigned int record,unsigned int num,unsigned int point)//在x,y处显示row*tier的字符,显示1位
{                        //num:第几位反显示
						 //point：保留几位有效数字,是几位
     unsigned int i=0,j,k=0,row1,n,m=10000;
     unsigned char data[8],data_num=0;
     unsigned int num_byte,num_bit,point_bit=1,num_Bbit=1;
	 LCD6448_Wcmd(0x01);//字符模式
	 row1=2;//写一次跳八个地址
	 num_bit=num>>8;       //到第几位了
	 num_byte=num & 0xff;  //一共多少位
	 
	 for(i=0;i<point;i++)    point_bit*=10;
	 for(i=1;i<num_byte;i++) num_Bbit*=10;
	 
	 i=0;
	 while(m!=0)
	 {		
			if(i==0) i=num_Bbit/m+point_bit/m; //是否需要提前进入
			n=record/m;  //最高位
			record=record%m;  //	
			
			if((n!=0)||(k!=0)||(i!=0))		//如果最高位不为零
			{ 
				if(k==0)  k=1;
				data[data_num++]=n;           //把数据加入数组
				if((m==point_bit)&&(point_bit!=1)) data[data_num++]=10;//保留小数点
			}
			m/=10;  //
	 }
	 	 	
	 for(k=0;k<data_num;k++)
	 {
			n=0;
			m=y;		
				if(num==0)//正显
				{
					 
					 LCD6448_Scolour(colour_window,colour_num);//正常
				}
				else
				if(num==0xff)//反显
				{
					 LCD6448_Scolour(colour_num,colour_window);//反显
				}
				else	
				 if(num_byte-num_bit>=point)//在小数点之前
				{
						if(k==num_bit-1) LCD6448_Scolour(colour_window,colour_num);//反显	
						else             LCD6448_Scolour(colour_num,colour_window);//正常
				} 
				else
				{
						if(k==num_bit) LCD6448_Scolour(colour_window,colour_num);//反显	
						else           LCD6448_Scolour(colour_num,colour_window);//正常	
				}
				
				LCD6448_Wcmd(0x01);//字符模式

				 for(i=0;i<32;i++)
				 {       
						 LCD6448_Waddr(x+16*k,m++);
						 for(j=0;j<row1;j++)
						 {
							LCD6448_Wdata(Num16_32[(data[k]<<6)+n++]);//写字符需要  350ns
						 }
			     }
	}
}

void LCD6448_SET_focus(unsigned int num,unsigned int num_up,unsigned int character[],const unsigned int record[][4])
{//num：变换到了第几个，record信息存放的地方
 //如果record[num][2]的最高位为1：则num_up为上次显示的位置,高八位为单个数字中显示位的位置，刚进入有效
 //如果record[num][2]的最高位位0：则num_up为上次显示的位置
//	unsigned int place_bit;
	
	if((record[num_up&0xff][2]&0x8000)==0x8000)//如果最高位为1
	{
			LCD6448_num_bit(record[num_up&0xff][0],record[num_up&0xff][1],character[num_up&0xff],(record[num_up&0xff][2]&0xff)|0xff00,record[num_up&0xff][3]);
	}
	else
	{
		LCD6448_Scolour(colour_num,colour_window);//清除上一次的		
		if((record[num_up&0xff][3]&0x8000)==0x8000&&(record[num_up&0xff][3]&0x7fff)==character[num_up&0xff])//如果达到限值
		{
			LCD6448_blank(record[num_up&0xff][0],record[num_up&0xff][1],64,32);//清除区域
			LCD6448_Wstring(record[num_up&0xff][0],record[num_up&0xff][1],32,32,2,always_char);//总是
		}
		else
		{		
			if((record[num_up&0xff][0] & 0xc000)==0)
				LCD6448_num_set(record[num_up&0xff][0],record[num_up&0xff][1],character[num_up&0xff],0);
			else
				LCD6448_num_bit(record[num_up&0xff][0]&0x3fff,record[num_up&0xff][1],character[num_up&0xff],0xff,record[num_up&0xff][0]>>14);		
		}	
	}	
	

	if((record[num][2]&0x8000)==0x8000)//如果最高位为1
	{
		LCD6448_num_bit(record[num][0],record[num][1],character[num],(num_up&0xff00)|(record[num][2]&0xff),record[num][3]);
	}
	else
	{		
		if((record[num&0xff][3]&0x8000)==0x8000&&(record[num&0xff][3]&0x7fff)==character[num&0xff])//如果达到限值
		{
			LCD6448_Scolour(colour_num,colour_window);//清除
			LCD6448_blank(record[num&0xff][0],record[num&0xff][1],64,32);//清除区域
			LCD6448_Scolour(colour_window,colour_num);//反显
			LCD6448_Wstring(record[num&0xff][0],record[num&0xff][1],32,32,2,always_char);//总是
		}
		else
		{
			LCD6448_Scolour(colour_window,colour_num);//反显下一次的
			if((record[num&0xff][0] & 0xc000)==0)
				LCD6448_num_set(record[num][0],record[num][1],character[num],0);
			else
				LCD6448_num_bit(record[num&0xff][0]&0x3fff,record[num&0xff][1],character[num&0xff],0,record[num&0xff][0]>>14);
		}	
	}	
};	
void LCD6448_SET_ADD(unsigned int num,unsigned int ADD_SUB,unsigned int character[],const unsigned int record[][4])
{//num：变换到了第几个，record信息存放的地方 ADD_SUB:0:减，1，加
	unsigned int i=0,j;
	unsigned int num_byte,num_bit;
	
	num_byte=num & 0xff;
	num_bit =num & 0xff00;
	
	if((record[num_byte][2]&0x8000)==0x8000)//如果最高位为1
	{
		LCD6448_Scolour(colour_window,colour_num);//反显
		
		j=1;
		for(i=0;i<(record[num_byte][2]&0x7fff)-(num_bit>>8);i++) j*=10;	
		
		if(ADD_SUB==0)//减
		{	
			if(character[num_byte]%(j*10)/j==0) character[num_byte]+=j*9;
			else  								character[num_byte]-=j;	
		}
		else
		{		
			if(character[num_byte]%(j*10)/j==9) character[num_byte]-=j*9;
			else                                character[num_byte]+=j;		
		}
				
		LCD6448_num_bit(record[num_byte][0],record[num_byte][1],character[num_byte],num_bit|(record[num_byte][2]&0xff),record[num_byte][3]);		
	}
	else
	{		
		j=record[num][3] & 0x7fff;
		if(ADD_SUB==0)//减
		{
			if(character[num]<=record[num][2])  character[num]=j;
			else 
			{    
				character[num]--;
			   if(character[num]==99||character[num]==999||character[num]==9999) i=1;
			}
		}
		else
		{
			if(character[num]>=j) 
			{	
				character[num]=record[num][2];
				while(j>0)
				{
					j/=10;
					i++;
				}	
				i-=2;
			}
			else  character[num]++;	
		}	
		
			j=record[num][3] & 0x8000;
		if(j==0x8000&&(record[num][3]&0x7fff)==character[num])//显示总是
		{
			i=(i+1)/2;	
			LCD6448_Scolour(colour_num,colour_window);//
			LCD6448_blank(record[num][0],record[num][1],32+i*32,32);//清除区域
			LCD6448_Scolour(colour_window,colour_num);//反显
			LCD6448_Wstring(record[num][0],record[num][1],32,32,2,always_char);//总是
		}
		else
		{	
			if(j==0x8000&&(character[num]==record[num][2]||character[num]==(record[num][3]&0x7fff)-1)) i++;//总是后 要多擦一个字节的数据
			i=(i+1)/2;

			if((record[num][0] & 0xc000)==0)
			{
				LCD6448_Scolour(colour_num,colour_window);//
				LCD6448_blank(record[num][0],record[num][1],32+i*32,32);//清除区域
				LCD6448_Scolour(colour_window,colour_num);//反显
				LCD6448_num_set(record[num][0],record[num][1],character[num],0);
			}
			else
			{
				LCD6448_Scolour(colour_num,colour_window);//
				LCD6448_blank(record[num][0],record[num][1],64+i*32,32);//清除区域
				LCD6448_Scolour(colour_window,colour_num);//反显
				LCD6448_num_bit(record[num][0]&0x3fff,record[num][1],character[num],0,record[num][0]>>14);	
			}	
		}
	}
}

void LCD6448_num_32(unsigned int x,unsigned int y,unsigned int data_high,unsigned int data_low,unsigned int unit)//显示32位的整数
{	//unit符号0：无，1：A;2：V；3：-；4::5:H,6:z,7:W;
	 int i,j,k,n,m; 
     unsigned char data[10],data_num=0;
     unsigned char data_unit[3],data_unit_num=0;
     unsigned long record;
	 LCD6448_Wcmd(0x01);//字符模式
	 
	 record=data_high;
	 
	 record=(record<<16)+data_low;
	 
	 while(record!=0)
	 {
			n=record%10; 
			data[data_num++]=n;
			record/=10;
	 }
	
	if(data_num==0) {data[0]=0;data_num=1;}
	
	 if((unit & 0x0f)!=0) 		data_unit[data_unit_num++]=10+(unit & 0x0f);//添加符号 
	 if(((unit >> 4)&0x0f)!=0)  data_unit[data_unit_num++]=10+(((unit >> 4)&0x0f));//添加符号 
	 if((unit >> 8)!=0)   		data_unit[data_unit_num++]=10+(unit >> 8);//添加符号    //添加三个符号
	 

//	 for(k=0;k<data_num+data_unit_num;k++)
	 for(k=0;k<10;k++)
	 {
		   n=0;
		   m=y;
				 for(i=0;i<32;i++)
				 {       
						 LCD6448_Waddr(x+16*k,m++);
						 for(j=0;j<2;j++)
						 {
							if(k<data_num)
								 LCD6448_Wdata(Num16_32[(data[data_num-k-1]<<6)+n++]);//写字符需要  350ns
							else
							if(k<data_num+data_unit_num)
								 LCD6448_Wdata(Num16_32[(data_unit[k-data_num]<<6)+n++]);
							else 
								 LCD6448_Wdata(0x00);
							
						 }
			     }
	}
}
	
	
void LCD6448_num_e(unsigned int x,unsigned int y,unsigned int row,unsigned int tier,unsigned int record,unsigned int point,unsigned int num,const unsigned char *character)//在x,y处显示row*tier的字符
{                        //显示一组字符,后面不带空格的
						//固定五位
     unsigned int i=0,j,k=0,row1,l,n,m=10000;
     unsigned char data[8],data_num=0;
	 LCD6448_Wcmd(0x01);//字符模式
	 row1=row/8;//写一次跳八个地址

	 while(m!=0)
	 {			
			if(i==0) i=point/m; //是否需要提前进入
			n=record/m;  //最高位
			record=record%m;  //	
			
			if((n!=0)||(k!=0)||(i!=0))		//如果最高位不为零
			{ 
				if(k==0)  k=1;
				data[data_num++]=n;           //把数据加入数组
				if((m==point)&&(point!=1)) data[data_num++]=10;//保留小数点
			}
			m/=10;
	 }	 
	 
	 l=row*tier/8;
	 
	 if(num<data_num) num=data_num;
	 	
	 for(k=0;k<num;k++)
	 {
			n=0;
			m=y;		
				 for(i=0;i<tier;i++)
				 {       
						 LCD6448_Waddr(x+row*k,m++);
						 for(j=0;j<row1;j++)
						 {
							if(k<data_num)
								 LCD6448_Wdata(character[data[k]*l+n++]);//写字符需要  350ns
							else
								 LCD6448_Wdata(0x00);
						 }
			     }
	}
}	

void LCD6448_SET_focus_char(unsigned int num,unsigned int num_up,unsigned int character[],const unsigned int record[][4],const unsigned int char_data[][2])
{//num：变换到了第几个，record信息存放的地方
//	unsigned int place_bit;
	
	LCD6448_Scolour(colour_num,colour_window);//清除上一次的
	LCD6448_Wstring(record[num_up][0],record[num_up][1],32,32,2,char_data[character[num_up]]);//
	
	LCD6448_Scolour(colour_window,colour_num);//反显下一次的
	LCD6448_Wstring(record[num][0],record[num][1],32,32,2,char_data[character[num]]);//
};

void LCD6448_Pnum_list(unsigned int row,unsigned int tier,unsigned num,unsigned int *record,const unsigned int place[][4],const unsigned char *character)//在x,y处显示row*tier的字符
{  //num：一共几行，interval每行间距多少， record：显示的数据，place:显示的地址,character:使用的数字数组
	unsigned int i,j,m,n;
	for(i=0;i<num;i++)
	{
		m=1,n=1;
		if((place[i][2]&0x8000)==0x8000)//
		{
		   for(j=1;j<(place[i][2]&0x0fff);j++) m*=10;//point
		   for(j=0;j<place[i][3];j++) 		   n*=10;
			
		}
		else
		if((place[i][0]& 0xc000)!=0)
		{
			m=place[i][0]>>14;
			for(j=0;j<m;j++) n*=10;//point
			m=1;
		}				
		LCD6448_num(place[i][0],place[i][1],row,tier,record[i],n,m,0,character);//在x,y处显示row*tier的字符
	}
}

//****指示灯**********************************************************************************
void LCD6448_Blight(unsigned int x,unsigned int y,unsigned int colour)//显示一个32*32的指示灯，
{//colour：0：红色224，0x80浅红色236，1：绿色24，0x81：浅绿色28，2：黄色252，0x82浅黄色254，3:灰色219；
  	unsigned int i,j,n=0;
			 if(colour==0) 	  colour=224;
		else if(colour==0x80) colour=236;//红色  			 
		else if(colour==1)	  colour=24;
		else if(colour==0x81) colour=28;//绿色
		else if(colour==2)    colour=252;
		else if(colour==0x82) colour=254;//黄色
		else if(colour==3)	  colour=219;//灰色
		else if(colour==0x83) colour=219;//
		else if(colour==4)    colour=224;//红色
		else if(colour==0x84) colour=236;//
		
		LCD6448_Fcolour(colour);
		LCD6448_Wcmd(0x01);//字符模式
		for(i=0;i<32;i++)
		{       
			LCD6448_Waddr(x,y++);
			for(j=0;j<4;j++)
				LCD6448_Wdata(LIGHT32_32[n++]);//明天这个地方改
		}
};

void LCD6448_Blight_three(unsigned int place,unsigned int colour)//在三个固定的位置显示大指示灯
{//0:通信指示灯，1:状态指示灯，2：故障指示灯
	unsigned int x,y;
		 if(place==0){x=20;y=440;}
	else if(place==1){x=190;y=440;}
	else if(place==2){x=360;y=440;}
	LCD6448_Blight(x,y,colour);
}	

void LCD6448_Slight(unsigned int place,unsigned int colour)//在八个固定的位置显示小指示灯
{//0:通信指示灯，1:状态指示灯，2：故障指示灯
	unsigned int x=2,y,i,j,n=0;
	
	  		 if(colour==0) 	  colour=128;
		else if(colour==0x80) colour=228;//红色  			 
		else if(colour==1)	  colour=48;
		else if(colour==0x81) colour=28;//绿色
		else if(colour==2)    colour=208;
		else if(colour==0x82) colour=252;//黄色
		else if(colour==3)	  colour=141;//灰色
		else if(colour==0x83) colour=219;//黄色
		else if(colour==4) 	  colour=43;//黄色
		LCD6448_Fcolour(colour);
		LCD6448_Wcmd(0x01);//字符模式
		y=50+(place<<5);
		for(i=0;i<16;i++)
		{       
			LCD6448_Waddr(x,y++);
			for(j=0;j<2;j++)
				LCD6448_Wdata(LIGHT16_16[n++]);//明天这个地方改
		}
}
	
void LCD6448_design_time(unsigned int num)
{
	unsigned int i;
	if(num==0)//第一个
	{
		LCD6448_Scolour(colour_window,colour_num);//反显
		i=num>>3;
		LCD6448_num_e(40+(num-(i<<3))*60,340+i*20,8,16,num*2+1,1,2,Num8_16);
	}
	else
	if(num==24)//最后一个
	{
		LCD6448_Scolour(colour_num,colour_window);//清除上一次的
		i=(num-1)>>3;
		LCD6448_num_e(40+((num-1)-(i<<3))*60,340+i*20,8,16,(num-1)*2+1,1,2,Num8_16);
	}
	else//中间
	{
		LCD6448_Scolour(colour_num,colour_window);//清除上一次的
		i=(num-1)>>3;
		LCD6448_num_e(40+((num-1)-(i<<3))*60,340+i*20,8,16,(num-1)*2+1,1,2,Num8_16);
		
		LCD6448_Scolour(colour_window,colour_num);//反显
		i=num>>3;
		LCD6448_num_e(40+(num-(i<<3))*60,340+i*20,8,16,num*2+1,1,2,Num8_16);	
	}	
}

void LCD6448_design_time_five(unsigned int num)
{
	if(num==0)//第一个
	{
		LCD6448_Scolour(colour_window,colour_num);//反显
		LCD6448_num_e(40+num*60,380,8,16,num+1,1,2,Num8_16);
	}
	else
	if(num==record_single[3][1])//最后一个
	{
		LCD6448_Scolour(colour_num,colour_window);//清除上一次的
		LCD6448_num_e(40+(num-1)*60,380,8,16,num,1,2,Num8_16);
	}
	else//中间
	{
		LCD6448_Scolour(colour_num,colour_window);//清除上一次的
		LCD6448_num_e(40+(num-1)*60,380,8,16,num,1,2,Num8_16);
		
		LCD6448_Scolour(colour_window,colour_num);//反显
		LCD6448_num_e(40+num*60,380,8,16,num+1,1,2,Num8_16);	
	}	
}
     
         
                
                