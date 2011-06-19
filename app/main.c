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
	system_init();

	while (1) {
		gpio_toggle_bit(GPIOA, 1);
		delay(100);
		gpio_toggle_bit(GPIOA, 1);
		printf("Hello, printf ~\r\n");
		delay(1900);
	}

	return 0;
}

