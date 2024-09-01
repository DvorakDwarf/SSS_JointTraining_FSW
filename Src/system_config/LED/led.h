/*
 * led.h
 *
 *  - Apr 29, 2023 (Creation)
 *      Author       : Tim S.
 *      Contributors : nithinsenthil , Raphael
 *      Log          : Led Control functions written
 */

#ifndef REALOP1_LED_H_
#define REALOP1_LED_H_

#include <globals.h>
#include <GPIO/gpio.h>

/***************************** LED INITIALIZERS ******************************/

/*
 * Configures the GPIO ports and pins for all the LEDs
 *
 * 	@param   None
 * 	@returns None
 */
void led_init();

/******************************* LED TOGGLERS ********************************/

#if OP_REV == 2

/**
 * Sets the state of an Heart Beat LED
 *
 * @param   b    The value to set the LED to (0 off or 1 on).
 *
 * @returns None
 */
#define led_hb(b) gpio_set(GPIOE, 2, b);

/**
 * Sets the state of the D3 LED
 *
 * @param   b    The value to set the LED to (0 off or 1 on).
 *
 * @returns None
 */
#define led_d3(b) gpio_set(GPIOE, 3, b);

/**
 * Sets the state of the D2 LED
 *
 * @param   b    The value to set the LED to (0 off or 1 on).
 *
 * @returns None
 */
#define led_d2(b) gpio_set(GPIOE, 4, b);

/**
 * Sets the state of the D1 LED
 *
 * @param   b    The value to set the LED to (0 off or 1 on).
 *
 * @returns None
 */
#define led_d1(b) gpio_set(GPIOE, 5, b);

/**
 * Sets the state of the D0 LED
 *
 * @param   b    The value to set the LED to (0 off or 1 on).
 *
 * @returns None
 */
#define led_d0(b) gpio_set(GPIOE, 6, b);

#endif

/**
 * Blinks the heartbeat LED every so often.
 * Meant to be called every 1ms
 */
void blinky();


#endif /* REALOP1_LED_H_ */
