/**
 * @file    functions.h
 * @author  Ricardo Jorge Furlan
 * @brief   function library
 * @version 0.1
 * @date    2025-05-02
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "pico/stdlib.h"

/**
 * @brief returns the CPU temperature, in Celsius, based on the sensor value converted by AD
 * 
 * Use the conversion function:
 *   Tc = 27 - (((adc_val * 3.3 / 4095) - 0.706) / 0.001721)
 * 
 * Max temperature = 150 Celsius ==> adc_val =  613
 * 
 * Min temperature = -50 Celsius ==> adc_val = 1024
 * 
 * @param  adc_val (613 to 1041)
 * @return float, Celsius temperature 
 */
float adc_to_celsius(uint16_t adc_val);


#endif // FUNCTIONS_H