/**
 * @file  driver_led_builtin.c
 * @brief Interface hardware abstraction layer (HAL) to control an LED integrated on the pico board
 * 
 * This module provides functions to initialize and toggle the state of an LED integrated on the pico board.
 *  
 * @author  Ricardo Jorge Furlan
 * @date    27/04/2025
 * @version  0.1
 */

#include "../include/driver_led_builtin.h"

static bool led_state_on = false;

// Call Init LED driver and turn OFF LED
int  hal_led_init(void){
    led_state_on = false;
    int ret = led_builtin__init();
    if(!ret) led_builtin__set(led_state_on);
    return ret;
}

// Change LED state between: ON and OFF
void hal_led_toggle(){
    led_state_on = !led_state_on;
    led_builtin__set(led_state_on);
}