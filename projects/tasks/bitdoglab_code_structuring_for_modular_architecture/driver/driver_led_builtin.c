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


#include "pico/stdlib.h"
#include "../include/board_def.h"
#include "../include/driver_led_builtin.h"


#ifdef PRJ_BOARD_PICO

#define LED_PIN 25

// Initializes the built-in LED driver and turns it off
int led_builtin__init(void){
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    return 0;
}

// set the built-in LED state to on or off
void led_builtin__set(bool on){
    gpio_put(LED_PIN, on);
}

#elif defined(PRJ_BOARD_PICO_W)

#include "pico/cyw43_arch.h"


// Initializes the built-in LED driver and turns it off
int led_builtin__init(void){
    return cyw43_arch_init();
}

// set the built-in LED state to on or off
void led_builtin__set(bool on){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
}

#endif
