#include "watchdog.h"
//---------------------global variables-----------------------------------
volatile unsigned char data wdt_intval;
//------------------------------------------------------------------------
void WDT_Init(unsigned char interval) //using 0//��������� ��������� ������������ ����������� �������, ������	//������������
{
	wdt_intval=interval;	
	WDWR=1;//WDWR=1-���������� ������ � �������
	WDCON=wdt_intval;
	return;
}
//------------------------------------------------------------------------
void WDT_Clear(void) //using 0//����� �������� ����������� �������
{
	EA=0;

	WDWR=1;//WDWR=1-���������� ������ � �������
	WDCON=wdt_intval;	

	EA=1;
	return;
}
//------------------------------------------------------------------------
