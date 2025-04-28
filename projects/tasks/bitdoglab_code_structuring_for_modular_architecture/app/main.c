/**
 * @file  main.c
 * @brief Application that makes the LED integrated in the pico board switch between On and OFF every 500ms
 *  
 * @author  Ricardo Jorge Furlan
 * @date    27/04/2025
 * @version 0.1
 */


#include <stdio.h>
#include "pico/stdlib.h"
#include "include/hal_led.h"

void fatal_error();

int main()
{
    stdio_init_all();

    // Initialize the LED driver, if error occurs, halt the system
    if(hal_led_init()) fatal_error();

    // Main loop,  toggles the led between on and off every 500 ms
    while (true) {
        hal_led_toggle();
        sleep_ms(500);
    }
}

void fatal_error(){
    printf("FATAL ERROR!. System halted");
    while(1) sleep_ms(100);
}