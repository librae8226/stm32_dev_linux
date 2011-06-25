#include "libmaple.h"
#include "libmaple_types.h"
#include "gpio.h"
#include "usart.h"

#include "MapleFreeRTOS.h"

#include "platform_config.h"
#include "system_init.h"
#include "tprintf.h"
#include "ulibc.h"
#include "misc.h"

#include "misc_task.h"

void vLEDFlashTask( void *pvParameters )
{
	while (1) {
		gpio_toggle_bit(GPIOA, 1);
		vTaskDelay(100);
		gpio_toggle_bit(GPIOA, 1);
		vTaskDelay(1900);
	}
	/*
	 * LED Breath
	 */
	/*
    static int32  slope   = 1;
    static uint32 CC      = 0x0000;
    static uint32 TOP_CNT = 0x0400;
    static uint32 i       = 0;
	
    while (1) {
        if (CC == TOP_CNT)  {
            slope = -1;
        } else if (CC == 0) {
            slope = 1;
        }
	 
        if (i == TOP_CNT)  {
            CC += slope;
            i = 0;
        }
	 
        if (i < CC) {
            gpio_write_bit(GPIOA, 1, 1);
        } else {
            gpio_write_bit(GPIOA, 1, 0);
        }
        i++;
    }
	*/
}

void vSerialEchoTask( void *pvParameters )
{
	unsigned int i;
	char ch;
	
    while (1) {
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
							printf( "\b \b" );
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
        vTaskDelay(10);
    }
}
