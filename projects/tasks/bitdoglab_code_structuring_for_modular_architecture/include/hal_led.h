/**
 * @file  driver_led_builtin.h
 * @brief Interface hardware abstraction layer (HAL) to control an LED integrated on the pico board
 * 
 * This module provides functions to initialize and toggle the state of an LED integrated on the pico board.
 *  
 * @author  Ricardo Jorge Furlan
 * @date    27/04/2025
 * @version 0.1
 */


#ifndef HAL_LED_H
#define HAL_LED_H

/**
 * @brief Call Init LED driver and turn OFF LED
 * @return error value, if == 0 ==> no error
 */
int  hal_led_init(void);
/**
 * @brief Change LED state between: ON and OFF
 */
void hal_led_toggle();

#endif // HAL_LED_H