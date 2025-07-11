/**
 * @file    gb_speed.h
 * @author  Ricardo J. Furlan
 * @brief   Sets speed values, time tick of the balls movement
 * @version 0.1
 * @date    2025-05-09
 */

#ifndef GP_SPEED_H
#define GP_SPEED_H

#include "pico/stdlib.h"

typedef enum{
    SPEED_500MS,
    SPEED_200MS,
    SPEED_100MS,
    SPEED_50MS,
    SPEED_MAX,
} Speed;

/**
 * @brief Returns the text representing the value
 * 
 * @param speed 
 * @return char* 
 */
char *   gb_speed_string(  Speed speed);
/**
 * @brief Returns the delay in us
 * 
 * @param speed 
 * @return uint64_t 
 */
uint64_t gb_speed_delay_us(Speed speed);
/**
 * @brief Returns the next enum
 * 
 * @param  speed 
 * @return Speed 
 */
Speed    gb_speed_next(    Speed speed);
/**
 * @brief Returns the prior enum
 * 
 * @param  speed 
 * @return Speed 
 */
Speed    gb_speed_prior(   Speed speed);


#endif // GP_SPEED_H