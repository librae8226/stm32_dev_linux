#include "libmaple.h"
#include "libmaple_types.h"

#include "system_init.h"
#include "gpio.h"

int main(void)
{
	system_init();

	while (1) {
		gpio_toggle_bit(GPIOA, 1);
		delay(100);
		gpio_toggle_bit(GPIOA, 1);
		delay(1900);
	}

	return 0;
}

