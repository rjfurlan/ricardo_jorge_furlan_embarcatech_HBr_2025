/**
 * @file  driver_led_builtin.h
 * @brief Interface for physical(metal) LED control
 * 
 * This module provides functions to initialize and set the state of an LED integrated on the pico board.
 * 
 * @author  Ricardo Jorge Furlan
 * @date    27/04/2025
 * @version 0.1
 */

#ifndef DRIVER_LED_BUILTIN_H
#define DRIVER_LED_BUILTIN_H

#include "pico/stdlib.h"

/**
 * @brief Init LED driver and turn OFF LED
 * 
 * @return error, if == 0 ==> no error
 */
int  led_builtin__init(void);
/**
 * @brief Set LED State
 * 
 * @param on => if true LED is turn ON, else is turn OFF
 */
void led_builtin__set(bool on);

#endif // DRIVER_LED_BUILTIN_H