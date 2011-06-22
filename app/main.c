#include "platform_config.h"
#include "../os/FreeRTOS/MapleFreeRTOS.h"
#include "tprintf.h"

#include "libmaple.h"
#include "libmaple_types.h"

#include "system_init.h"
#include "ulibc.h"
#include "gpio.h"
#include "usart.h"

static void vLEDFlashTask( void *pvParameters )
{
    for (;;) {
        vTaskDelay(1900);
		gpio_toggle_bit(GPIOA, 1);
        vTaskDelay(100);
		gpio_toggle_bit(GPIOA, 1);
    }
}

static void vSerialEchoTask( void *pvParameters )
{
	unsigned int i;
	char ch;
	
    for (;;) {
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

int main(void)
{		
	system_init();
	printf("Hello, leach ~\r\n");
	xTaskCreate( vLEDFlashTask, 
				 ( signed portCHAR * ) "Task1", 
				 configMINIMAL_STACK_SIZE, 
				 NULL, 
				 tskIDLE_PRIORITY + 2, 
				 NULL );
	
	xTaskCreate( vSerialEchoTask, 
				 ( signed portCHAR * ) "Task2", 
				 configMINIMAL_STACK_SIZE, 
				 NULL, 
				 tskIDLE_PRIORITY + 3, 
				 NULL );
	
	vTaskStartScheduler();

	while (1) {
		;
	}

	return 0;
}

