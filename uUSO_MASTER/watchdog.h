#ifndef WATCHDOG_H
#define WATCHDOG_H
#include <ADuC845.h>
#include "pt/pt.h"
//-------watchdog`s interwals------------
#define WDT_125		0x32
#define WDT_250		0x42
#define WDT_500		0x52
#define WDT_1000 	0x62
#define WDT_2000 	0x72
//---------------------------------------
#define PROCESS_NUM	3
enum
{
	Proto_Process=0,
	Sort_Process= 1,
	Watch_Process=2
};

enum
{
	RUN=0,
	IDLE=1	
};

struct watchdog
{
  unsigned char process_state;
  unsigned int count;
};

extern struct watchdog wdt_count[];

void WDT_Init(unsigned char interval);//установка интервала срабатывания сторожевого таймера, запуск
void WDT_Clear(void);//сброс счетчика сторожевого таймера
 PT_THREAD(WDT_Process(struct pt *pt));

#endif