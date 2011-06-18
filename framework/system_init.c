#include "system_init.h"

#include "libmaple.h"
#include "libmaple_types.h"

#include "flash.h"
#include "rcc.h"
#include "nvic.h"
#include "systick.h"
#include "gpio.h"
#include "adc.h"
#include "timer.h"
#include "usb.h"

#include "misc.h"

#define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

static void setupFlash(void);
static void setupClocks(void);
static void setupNVIC(void);
static void setupADC(void);
static void setupTimers(void);
static void setupUSART(void);

void system_init(void)
{
	setupFlash();
	setupClocks();
	setupNVIC();
	systick_init(SYSTICK_RELOAD_VAL);
	gpio_init_all();
	afio_init();
	setupADC();
	setupTimers();

	gpio_set_mode(GPIOA, 1, GPIO_OUTPUT_PP);
}

static void setupFlash(void)
{
	flash_enable_prefetch();
	flash_set_latency(FLASH_WAIT_STATE_2);
}

static void setupClocks(void)
{
	rcc_clk_init(RCC_CLKSRC_PLL, RCC_PLLSRC_HSE, RCC_PLLMUL_9);
	rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1);
	rcc_set_prescaler(RCC_PRESCALER_APB1, RCC_APB1_HCLK_DIV_2);
	rcc_set_prescaler(RCC_PRESCALER_APB2, RCC_APB2_HCLK_DIV_1);
}

static void setupNVIC(void)
{
#ifdef VECT_TAB_FLASH
	nvic_init(USER_ADDR_ROM, 0);
#elif defined VECT_TAB_RAM
	nvic_init(USER_ADDR_RAM, 0);
#elif defined VECT_TAB_BASE
	nvic_init((uint32)0x08000000, 0);
#else
#error "You must select a base address for the vector table."
#endif
}

static void adcDefaultConfig(const adc_dev* dev)
{
	adc_init(dev);
	adc_set_extsel(dev, ADC_SWSTART);
	adc_set_exttrig(dev, 1);
	adc_enable(dev);
	adc_calibrate(dev);
	adc_set_sample_rate(dev, ADC_SMPR_55_5);
}
static void setupADC(void)
{
	rcc_set_prescaler(RCC_PRESCALER_ADC, RCC_ADCPRE_PCLK_DIV_6);
	adc_foreach(adcDefaultConfig);
}
static void timerDefaultConfig(timer_dev *dev) {
	timer_adv_reg_map *regs = (dev->regs).adv;
	const uint16 full_overflow = 0xFFFF;
	const uint16 half_duty = 0x8FFF;
	int channel;

	timer_init(dev);
	timer_pause(dev);

	regs->CR1 = TIMER_CR1_ARPE;
	regs->PSC = 1;
	regs->SR = 0;
	regs->DIER = 0;
	regs->EGR = TIMER_EGR_UG;

	switch (dev->type) {
		case TIMER_ADVANCED:
			regs->BDTR = TIMER_BDTR_MOE | TIMER_BDTR_LOCK_OFF;
			// fall-through
		case TIMER_GENERAL:
			timer_set_reload(dev, full_overflow);

			for (channel = 1; channel <= 4; channel++) {
				timer_set_compare(dev, channel, half_duty);
				timer_oc_set_mode(dev, channel, TIMER_OC_MODE_PWM_1, TIMER_OC_PE);
			}
			// fall-through
		case TIMER_BASIC:
			break;
	}

	timer_resume(dev);
}
static void setupTimers(void)
{
	timer_foreach(timerDefaultConfig);
}
