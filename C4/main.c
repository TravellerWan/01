#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "Nixie.h"
#include "MatrixKey.h"
#include "Buzzer.h"

sbit Buzzer=P2^5;
unsigned int Sec=30;  //炸弹时间为30秒
unsigned char KeyNum;
unsigned int password,Count;
unsigned int flag=0;

void main()
{
	LCD_Init();		//LED1602初始化
	Timer0Init();		//定时器初始化
	LCD_ShowString(1,1,"password");
	
	while(1)
	{
		Nixie(3,Sec/10);  //数码管显示时间
		Delay(1);
		Nixie(4,Sec%10);   //数码管显示时间
		Delay(1);
		KeyNum=MatrixKey();  //矩阵键盘扫描
		if(KeyNum)
		{
			 if(KeyNum<=10)    //如果s1~s10按键按下，输入第一个数
        {
					if(Count<5)   //输入五位拆弹密码
					{
						password*=10;      //输入的数左移一位
						password+=KeyNum%10;   //获取一位数
						Count++;   //按下键盘的次数加一  
					}
        }
			LCD_ShowNum(2,1,password,5);    //LED1602更新显示
		}
		if(KeyNum==11)		//如果s11按键按下，接下来对输入的拆弹密码进行检验
		{
			if(password==12345)    //如果拆弹密码输入正确
			{
				LCD_ShowString(1,1,"        ");  //LED1602更新显示
				LCD_ShowString(2,1,"        ");   //更新显示
				Delay(1000);
				Delay(1000);
				Delay(1000);
				Delay(1000);
				LCD_ShowString(1,1,"success ");   //更新显示，炸弹成功拆除标志	
				Count=0;       //计次清零
				flag=1;
			}
			if(password!=12345)   //如果拆弹密码错误
			{
				password=0;    //密码清零，可以重新再次输入密码
				Count=0;       //计次清零
				LCD_ShowString(1,1,"error   ");   //LED1602更新显示，密码错误
				Delay(1000);
				LCD_ShowString(1,1,"password");   //LED1602更新显示
				LCD_ShowNum(2,1,password,5);    //LED1602更新显示
			}
		}
		if(KeyNum==12)  //如果s12按键按下，重置密码
		{
			password=0;    //密码清零
			Count=0;       //计次清零
			LCD_ShowNum(2,1,password,5);    //LED1602更新显示
		}
	}
}
void Timer0_Routine() interrupt 1  //中断函数
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		if(flag==1)  //炸弹拆除
		{
			Sec=0;
		}
		if(flag==0)  //炸弹还未拆除
		{
			Sec--;
			if(Sec>=20)  
			{
				Buzzer_Time(100);
			}
			if(Sec>=10&&Sec<20)  //炸弹警告声频率加快
			{
				Buzzer_Time(80);
				Delay(1);
				Buzzer_Time(80);
				Delay(1);
			}
			if(Sec>0&&Sec<10)    //炸弹警告声频率更快
			{
				Buzzer_Time(50);
				Delay(1);
				Buzzer_Time(50);
				Delay(1);
				Buzzer_Time(50);
				Delay(1);
			}
			if(Sec==0)		//时间结束，炸弹被引燃
			{
				LCD_ShowString(1,1,"Boom!!! ");  //LED1602更新显示
				Buzzer_Time(100000);   //爆炸声！！！
			}
		}
	}
}