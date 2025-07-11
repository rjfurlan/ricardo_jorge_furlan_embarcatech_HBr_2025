/**
 * @file    main.c
 * @author  Ricardo J. Furlan
 * @brief   Initialize hardware and call main menu
 * @version 0.1
 * @date    2025-05-09
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "input.h"
#include "menu.h"
#include "menu_structure_main.h"

#include "lib_bitdoglab/oled/display.h"

/**
 * @brief Initialize hardware and call main menu
 * 
 */
void main(){
    stdio_init_all();
    
    //Routines that change the UART port to use the BitdogLab Connector
    gpio_set_function( 0, GPIO_FUNC_SIO);
    gpio_set_function( 1, GPIO_FUNC_SIO);
    gpio_set_function(17, GPIO_FUNC_UART);
    gpio_set_function(16, GPIO_FUNC_UART);
    
    // Init hardware
    input_init();
    display_init();

    // Opening message
    for(int i=0;i<6;i++){
        display_fill(!(i&0x01), true);
        sleep_ms(200);
    }
    printf("Init GaltonBoard\n");
    sleep_ms(1000);
    
    // Start
    menu_init("Galton Board", 2, MENU_STRUCTURE_MAIN_N_ITENS, menu_structure_main, menu_structure_main_click);    
}    