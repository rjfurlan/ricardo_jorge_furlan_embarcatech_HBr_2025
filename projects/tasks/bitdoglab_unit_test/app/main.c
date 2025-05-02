/**
 * @file    main.c
 * @author  Ricardo Jorge Furlan
 * @brief   Main function
 * @version 0.1
 * @date    2025-05-02
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "functions.h"


int main()
{
    stdio_init_all();

    int count = 0;
    while (true) {
        printf("Test concept program! %d\n", count++);
        sleep_ms(500);
    }
    float x = adc_to_celsius(123);
}