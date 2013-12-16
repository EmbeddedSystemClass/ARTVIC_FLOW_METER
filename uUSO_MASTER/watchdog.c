#include "watchdog.h"

//---------------------global variables-----------------------------------
volatile unsigned char data wdt_intval;
struct watchdog wdt_count[PROCESS_NUM];
volatile struct pt pt_wdt;
//------------------------------------------------------------------------
void WDT_Init(unsigned char interval) //using 0//установка интервала срабатывания сторожевого таймера, запуск	//небезопасная
{
	wdt_intval=interval;	
	WDWR=1;//WDWR=1-разрешение записи в регистр
	WDCON=wdt_intval;
	wdt_count[Proto_Process].process_state=IDLE;
	wdt_count[Proto_Process].count=0;
	wdt_count[Sort_Process].process_state=IDLE;
	wdt_count[Sort_Process].count=0;
	wdt_count[Watch_Process].process_state=IDLE;
	wdt_count[Watch_Process].count=0;
	PT_INIT(&pt_wdt);
	return;
}
//------------------------------------------------------------------------
void WDT_Clear(void) //using 0//сброс счетчика сторожевого таймера
{
	EA=0;

	WDWR=1;//WDWR=1-разрешение записи в регистр
	WDCON=wdt_intval;	

	EA=1;
	return;
}
//------------------------------------------------------------------------
 PT_THREAD(WDT_Process(struct pt *pt))
 {
   
  volatile unsigned char i=0, process_error=0;
  wdt_count[Watch_Process].process_state=RUN;

  PT_BEGIN(pt);

  while(1) 
  {
  		PT_DELAY(pt,100);
		process_error=0;
		
		wdt_count[Watch_Process].count++;

		for(i=0;i<PROCESS_NUM;i++)
		{
			if((wdt_count[i].count|wdt_count[i].process_state)==0)
			{
				process_error=1;
				break;
			}
		}
		
		if(process_error==0)//все процессы работают
		{
				WDT_Clear();
				wdt_count[Proto_Process].count=0;
				wdt_count[Sort_Process].count=0;
				wdt_count[Watch_Process].count=0;	
		}	
  }
  PT_END(pt);
}