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

#define VERSION		"v0.0.4"

static xTaskHandle hInitTask;

static void vInitTask( void *pvParameters )
{
	xTaskHandle *phInitTask = &hInitTask;
	uint32 i;
	
	system_init();
	
	/* led flashes -> sign of system reset ok */
	for(i = 0; i < 6; i++)
	{
		gpio_toggle_bit(GPIOA, 12);
		delay(50);
	}
	
	/* Boot Animation */
	usart_putc(USARTx, 0x0C);	//clear screen
	
	printf("Booting...\r\n\r\n");
	printf("                       _\r\n");
	printf("     _                / /\r\n");
	printf("    | |	   ___  __ _ _| |_ __ _ _  __  __ _   _   _\r\n");
	printf("    | |	  / _ \\/ _` |_   _/ _` | \\/ _)/ _` | / / / /\r\n");
	printf("    | |_ _  __( (_| | | |  (_| | | | ( (_| | \\ \\ \\ \\\r\n");
	printf("    |_ _ _\\___|\\__,_| | | \\__, / | |  \\__,_| /_/ /_/\r\n");
	printf("                      /_/ \\_ _/\r\n" );
	printf("\r\n");
	printf("FreeRTOS V7.0.1\r\n");
	printf("Developing Assistant "); printf(VERSION);
	printf("\r\n\tby Librae - g.leafgrass@gmail.com");
	printf("\r\n\r\n");
	printf("Hello, leach ~\r\n");
	
	xTaskCreate( vLEDFlashTask, 
				 (signed portCHAR *) "Task1",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 tskIDLE_PRIORITY + 2,
				 NULL);
	
	xTaskCreate( vSerialEchoTask, 
				 (signed portCHAR *) "Task2",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 tskIDLE_PRIORITY + 3,
				 NULL);
	
	vTaskSuspend(hInitTask);
	
    while (1) {
		/* should not get here */
        vTaskDelay(1000);
		printf("init task\r\n");
    }
}

int main(void)
{
	xTaskHandle *phInitTask = &hInitTask;
	
	delay(10);	/* ensure I/O is ready */
	
	xTaskCreate( vInitTask,
				 (signed portCHAR *) "Init",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 tskIDLE_PRIORITY + 1,
				 phInitTask);
	
	vTaskStartScheduler();

	while (1) {
		asm volatile("nop");
	}

	return 0;
}
