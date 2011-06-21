#include "platform_config.h"
#include "tprintf.h"

#include "libmaple.h"
#include "libmaple_types.h"

#include "system_init.h"
#include "libc_retarget.h"
#include "gpio.h"
#include "usart.h"

int main(void)
{
	int8 ch = 0;
	uint8 i;
	uint32 cnt1 = 0;
	uint32 cnt2 = 0;
		
	system_init();
	printf("Hello, leach ~\r\n");

	while (1) {
		if (cnt1++ % 1000 == 0) {	
			if (cnt2++ % 1000 == 0) {
				gpio_toggle_bit(GPIOA, 1);
			}
		}
#ifdef SERIAL_ECHO
		if (USARTx->flag_trigger) {
			for (i = 0; i < USARTx->cnt_trigger; i++) {
				ch = usart_getc(USARTx);
				if (ch) {
					switch( ch ) {
						case '\r': {
							printf( "\r\n" );
							break;
						}
						case '\b': {
							printf( "\b \b" );	//backspace
							break;
						}
						default: {
							printf( "%c", ch );
							break;
						}
					}
				}
			}
			USARTx->cnt_trigger = 0;
		}
#endif /* SERIAL_ECHO */
	}

	return 0;
}

