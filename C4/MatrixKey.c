#include <REGX52.H>
#include "Delay.h"

/**
  * @brief 矩阵键盘
  * @param 无
  * @retval KeyNum 按下按键的键码值
	         如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
  */
unsigned char MatrixKey()
{
	unsigned char KeyNum=0;
	
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNum=1;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNum=5;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNum=9;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNum=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNum=2;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNum=6;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNum=10;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNum=14;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNum=3;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNum=7;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNum=11;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNum=15;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNum=4;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNum=8;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNum=12;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNum=16;}
	
	return KeyNum;
}