/**
 * @file    gb_speed.c
 * @author  Ricardo J. Furlan
 * @brief   Sets speed values, time tick of the balls movement
 * @version 0.1
 * @date    2025-05-0
 */

#include "gb_speed.h"

/**
 * @brief Returns the text representing the value
 * 
 * @param speed 
 * @return char* 
 */
char * gb_speed_string(Speed speed){
    switch(speed){
        case SPEED_500MS: return "500MS";
        case SPEED_200MS: return "200MS";
        case SPEED_100MS: return "100MS";
        case SPEED_50MS:  return "50MS";
        case SPEED_MAX:   return "MAX";
    }
}

/**
 * @brief Returns the delay in us
 * 
 * @param speed 
 * @return uint64_t 
 */
uint64_t gb_speed_delay_us( Speed speed){
    switch(speed){
        case SPEED_500MS: return 500000;
        case SPEED_200MS: return 200000;
        case SPEED_100MS: return 100000;
        case SPEED_50MS:  return  50000;
        case SPEED_MAX:   return      0;
    }
}

/**
 * @brief Returns the next enum
 * 
 * @param  speed 
 * @return Speed 
 */
Speed  gb_speed_next(  Speed speed){
    switch(speed){
        case SPEED_500MS: return SPEED_200MS;
        case SPEED_200MS: return SPEED_100MS;
        case SPEED_100MS: return SPEED_50MS;
        case SPEED_50MS:  return SPEED_MAX;
        case SPEED_MAX:   return SPEED_MAX;
    }
}

/**
 * @brief Returns the prior enum
 * 
 * @param  speed 
 * @return Speed 
 */
Speed  gb_speed_prior( Speed speed){
    switch(speed){
        case SPEED_500MS: return SPEED_500MS;
        case SPEED_200MS: return SPEED_500MS;
        case SPEED_100MS: return SPEED_200MS;
        case SPEED_50MS:  return SPEED_100MS;
        case SPEED_MAX:   return SPEED_50MS;
    }
}
