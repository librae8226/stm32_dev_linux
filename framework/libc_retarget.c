#include "libc_retarget.h"
#include "usart.h"

#define USARTx	USART1

PUTCHAR_PROTOTYPE
{
	usart_putc(USARTx, ch);
	return ch;
}

