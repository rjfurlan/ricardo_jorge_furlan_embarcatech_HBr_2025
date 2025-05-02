/**
 * @file    functions.c
 * @author  Ricardo Jorge Furlan
 * @brief   function library
 * @version 0.1
 * @date    2025-05-02
 */
#include <math.h>
#include "functions.h"

/*
 * returns the CPU temperature, in Celsius, based on the sensor value converted by AD
 * 
 * Use the conversion function:
 *   Tc = 27 - (((adc_val * 3.3 / 4095) - 0.706) / 0.001721)
 * 
 * Valid adc_val range: 613 to 1041
 * 
 * Max temperature = 150 Celsius ==> adc_val =  613
 * Min temperature = -50 Celsius ==> adc_val = 1041
 */
float adc_to_celsius(uint16_t adc_val){
    if(adc_val > 1041) return NAN;  // return -INFINITY;    // temperature < -50 
    if(adc_val <  613) return NAN;  // return  INFINITY;    // temperature > 150
    

    return 27 - (((adc_val * 3.3 / 4095) - 0.706) / 0.001721);
}