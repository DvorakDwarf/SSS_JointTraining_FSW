// Put implementations of PWM related functions in this file

#include "timers.h"
#include <globals.h>

//Period in microseconds
void init_pwm(uint32_t period_us) {
	//It took me a while to understand how one can "enable" a pin
	//How does one make a chunk of metal able to conduct electricity was my question originally

	//Following detailed comments primarily so I understand wth is going on

	//GPIO A15 is a part of GPIO port A which is part of AHB2, which is a bus, which is somehow necessary to know in order to reach the registers
	//So that the GPIO A15 receives the clock signal, we must change the register so GPIOA gets it
	//It's not on by default because battery saving
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	//Now we need to set the mode the GPIO pin is in
	//Reset the value in case there was anything else there before, from different part of code
	//The registers aren't persistent but if something set it and MCU wasn't off then it stays

	//OR Sets a bit
	//AND and NOT clears a bit
	//XOR toggles a bit

    //Reset pins
    GPIOA->MODER  &= ~GPIO_MODER_MODE15_Msk; //Reset mode
    GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL15_Msk; //Reset alternate function

    //Pin mode
//    GPIOA->MODER  |= (2U << GPIO_MODER_MODE15_Pos);
    GPIOA->MODER |= GPIO_MODER_MODER15_1;
    // Set AF
    //There's a table (Ch.17) for what the alternative function mode is per pin
    GPIOA->AFR[1] |= (1U << GPIO_AFRH_AFSEL15_Pos); //Set to alternative function (10)(0x2)

	//Enable the TIM2, as in give it access to clock signal
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	//Setting timer registers PSC, ARR, EGR, CCMR1, CCER
	TIM2->PSC = 9; //Hardware clock we are getting is 10MHz(?), we divide it by 9(+1) for 1MHz
	TIM2->ARR = period_us - 1; //Period. Always adds 1. GOTTA HAVE THAT DOWN TO THE MICROSECOND ACCURACY
	TIM2->CCMR1 = (6 << TIM_CCMR1_OC1M_Pos); //Select PWM mode (1 or 2) (110 or 111)
	TIM2->CCER |= TIM_CCER_CC1E; //Set polarity. 1 is high, 0 is low

	TIM2->EGR = TIM_EGR_UG; //Tell it to restart, read registers again

	//THE PWM IS NOT WORKING YET, MUST SET CR1 REGISTER TO ENABLE
}

void pwm_set_dutycycle(float percentage) {
	float period = (float) TIM2->ARR;

	//How many clock cycles to go before flipping wave
	int when_to_down = (int)((percentage) * (period/100.0));
	TIM2->CCR1 = when_to_down+1; //GOTTA HAVE THAT DOWN TO THE MICROSECOND ACCURACY
}

