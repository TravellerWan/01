#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"
#include "Timer0.h"
#include "Buzzer.h"

unsigned char KeyNum;
unsigned int Password=0000,Count;
unsigned char Sec=8,Min=0,Hour=0;
bit TimerRunning = 1; // 定时器运行标志位 

void main()
{ 
  LCD_Init();
	Timer0Init();          //初始化设定屏幕和定时器
	
	LCD_ShowString(2,1,"Password:");
	LCD_ShowString(1,1,"ct :");             //初始化界面图形
	LCD_ShowString(1,6,"  :  :");
	

	
	while(1)
		 {
					LCD_ShowNum(1,6,Hour,2);
					LCD_ShowNum(1,9,Min,2);         //显示倒计时
					LCD_ShowNum(1,12,Sec,2);
				
			 KeyNum = MatrixKey();
				if(KeyNum)
					{
						if(KeyNum<=10)  //如果S1~s10按下，输入密码
						{
							if(Count<4)//如果输入次数小于4
							{
								Password*=10;         //密码左移一位
								Password+=KeyNum%10;    //获取一位密码
								Count++;  //计次加一
							}
							LCD_ShowNum(2,10,Password,4);   //更新显示
						}
						if(KeyNum==11)                 //确认输入的密码
						{
								if(Password==2887)         //密码比对
								{
									LCD_ShowString(2,14," OK");  //显示OK
//									Password=0;  		//密码清零
									Count=0; 				//计次清零
									LCD_ShowNum(2,10,Password,4);
									
									while(1)
									{  
										LCD_ShowNum(1,6,Hour,2);
										LCD_ShowNum(1,9,Min,2);           //密码正确，但为时已晚
										LCD_ShowNum(1,12,Sec,2);
										if(Sec<4&&Min==0&&Hour==0)
										{ 
											LCD_ShowString(2,1,"                 "); 
											LCD_ShowString(1,1,"Late"); 
											if(Sec<=0&&Min==0&&Hour==0)
											{	
												LCD_Init();
												LCD_ShowString(2,4,"!!!Bomb!!!");
												Buzzer_Time(200);
											}
											
										} 
										 if(Sec>=4&&Min>=0&&Hour>=0)    //及时拆除C4
										{ Sec=4,Min=0,Hour=0;
											while(1)
											{
												LCD_ShowNum(1,6,Hour,2);
												LCD_ShowNum(1,9,Min,2);           
												LCD_ShowNum(1,12,Sec,2);
												LCD_ShowString(1,1,"safe"); 
											}
										}
									}
		
								}
								else
								{
										LCD_ShowString(2,14,"ERR");  //显示ERR   错误
										Password=0;  		//密码清零
										Count=0; 				//计次清零
										LCD_ShowNum(2,10,Password,4);
											 
								}
								
							}
						if(KeyNum==12)         //清零
								{
									Password=0;  		//密码清零
									Count=0; 				//计次清零
									LCD_ShowNum(2,10,Password,4);
									LCD_ShowString(2,14,"   ");
								}
										
					}
					 if(Password==0000&&Sec==0&&Min==0&&Hour==0)		//无人拆弹
						{
							  LCD_Init();
							  LCD_ShowString(1,1,"                 "); 
								LCD_ShowString(2,4,"!!!Bomb!!!");
							  Buzzer_Time(200);
						}	

	  }
}                    //shift+tab  减少一个缩进



void Timer0_Routine()  interrupt 1
{
		static unsigned int T0Count;
		TL0 = 0xCD;		//设置定时初值
		TH0 = 0xD4;		//设置定时初值
		T0Count++;
		if(T0Count>=1000)
			{
				T0Count=0;
				Sec--;
				if(Sec<0)
				{
					Sec=59;
					Min--;
					if(Min<0)
					{
						Min=59;
						Hour--;
						if(Hour<0)
						{
							Hour=0;
							 
						}
				   }
		    }	
				else if(Sec==0&&Min==0&&Hour==0)
				{
				// 禁用定时器
					TimerRunning = 0;
					ET0 = 0; // 禁用定时器0中断
					TR0 = 0; // 停止定时器0
				}
				
			}
		
}	





	
	
	
	
