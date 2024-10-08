#include <print_scan.h>
#include "platform_init.h"

#include <TestDefinition.h>

void my_main();

int main() {
    init_init();
    init_platform();

    my_main();
}


void my_main() {
	while (1) {
		printMsg("Hello There!\r\n");
		nop(1000000);
	}
}

/*
void pwm_init() {
	// setting up time-base
	// For 80Mhz clock, need 20000 ticks to get a 4kHz timer
	TIM2->ARR = 20000;

	// 1a. set CC2 channel as output
	// TIM2->CCMR1[9:8](CC2S) = 00
	uint32_t tim2_ccmr1 = TIM2->CCMR1;
	TIM2->CCMR1 = tim2_ccmr1 & ~(0b11 << 8);

	// 1b. Set polarity to active high
	// TIM2->CCER[7](CC2P) = 0
	uint32_t tim2_ccer = TIM2->CCER;
	TIM2->CCER = time2_ccer & ~(0b1 << 7);

	// 2. Set PWM Mode to PWM mode 1
	// TIME2->CCMR1[24, 14:12](OC2M[3,2:0]) = 0110
	tim2_ccmr1 = TIM2->CCMR1;
	tim2_ccmr1 &= ~(0b1 << 24); // clear ccmr1[24]  ( oc2m[3]   )
	tim2_ccmr1 |= (0b11 << 12); // set   ccmr1[3:1] ( oc2m[2:1] )
	tim2_ccmr1 &= ~(0b1);		// clear ccmr1[0]   ( oc2m[0]   )
	TIM2->CCMR1 = tim2_ccmr1;

	// 3. Program period in ARR
	// for 4kHz pwm from 80Mhz, need 2 * 10^4 count (or maybe 2*10^4 - 1?)
	TIM2->ARR = 20000;

	// 3. Program duty cycle in CCRx register
	// Default to 50% duty cycle, which is 10000
	TIM2->CCR2 = 10000;

	// 4. Set preload bit in CCMRx
	// TIM2->CCMR1[11] (OC2PE) = 1
	tim2_ccmr1 = TIM2->CCMR1;
	TIM2->CCMR1 = tim2_ccmr1 | (0b1 << 11);

	// 4. Set auto-reload preload enable bit in CR1
	// TIM2->CR1[7] (ARPE) = 1
	uint32_t tim2_cr1 = TIM2->CR1;
	TIM2->CR1 = tim2_cr1 | (0b1 << 7);

	// 5.
}

*/
