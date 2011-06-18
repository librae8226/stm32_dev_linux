#include "misc.h"
#include "delay.h"

void delay(uint32 ms)
{
	uint32 i;
	for (i = 0; i < ms; i++) {
		delayMicroseconds(1000);
	}
}

void delayMicroseconds(uint32 us)
{
	delay_us(us);
}
