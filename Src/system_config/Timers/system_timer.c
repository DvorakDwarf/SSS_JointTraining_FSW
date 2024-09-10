/*
 * timers.c
 *
 *	- October 11, 2023
 *		Author	: Darsh
 *		Log		: ...
 *
 *  - September 23, 2023
 *  	Author	: Darsh
 *  	Log		: Initial Setup
 */

#include <globals.h>
#include "timers.h"
#include <LED/led.h>


// Global (external) variables and functions
extern int core_MHz;	// from core_config.h

uint64_t systick_time = 0;

void delay_ms(uint64_t ms) {
	uint64_t start_time = systick_time;
	while (systick_time - start_time < ms);
}

uint64_t getSysTime() {
	return systick_time;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
/*                                 SYSTICK                                   */
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//void systick_init() {
//	// configure for 1 ms period
//	SysTick->LOAD = (core_MHz / 8) * 1000;
//	// use AHB/8 as input clock, and enable counter interrupt
//	SysTick->CTRL = 0x3;
//	NVIC_EnableIRQ(SysTick_IRQn);
//}

void systick_init() {
	// Clock Ticks for 1 SysTick period
	// (10Mhz) * (1ms) = 10^4 ticks
	uint32_t clockTicks = 1000000;

	// subtract 1 because SysTick is an (n-1) to 0 counter
	// That's our reload value
	SysTick->LOAD = (uint32_t)clockTicks - 1;

	// Clear current SysTick counter value
	SysTick->VAL = (uint32_t) 0;



	// Program Control and Status Register
	// SysTick->CTRL[2]: CLKSOURCE to AHB/8
	// SysTick->CTRL[1]: enable TICKINT to enable SysTick exception
	// SysTick->CTRL[0]: enable counter
	SysTick->CTRL = (0b011);
}

static int led_num = 0;

void SysTick_Handler() {
	led_num++;
	if(led_num > 5) led_num = 0;

	if(led_num > 0) { led_d0(1) }
	else { led_d0(0); }

	if(led_num > 1) { led_d1(1) }
	else { led_d1(0); }

	if(led_num > 2) { led_d2(1) }
	else { led_d2(0); }

	if(led_num > 3) { led_d3(1) }
	else { led_d3(0); }

	if(led_num > 4) { led_hb(1) }
	else { led_hb(0); }
}


/**
 * Interrupt handler for the SysTick timer.
 * Increments the systick_time variable and
 * updates the status of the heartbeat and activity LEDs.
 *
 * @param None
 * @returns None
 */
//void SysTick_Handler() {
//	systick_time++;
//	blinky();
//}
