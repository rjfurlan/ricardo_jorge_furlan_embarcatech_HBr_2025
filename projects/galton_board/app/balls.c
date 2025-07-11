/**
 * @file    balls.c
 * @author  Ricardo J. Furlan
 * @brief   Sets values ​​for how many balls will be present simultaneously
 * @version 0.1
 * @date    2025-05-09
 */
#include "balls.h"

/**
 * @brief Returns the text representing the value
 * 
 * @param balls_n 
 * @return char* 
 */
char * balls_string(BallsN balls_n){
    switch(balls_n){
        case BALLS_NUMBER_ONLY_ONE:  return "Only One";
        case BALLS_NUMBER_3_SPACE:   return "3 Spaces";
        case BALLS_NUMBER_1_SPACE:   return "1 Space";
        case BALLS_NUMBER_BURST:     return "Burst";
        case BALLS_NUMBER_MAX:       return "MAX";
    }
}

/**
 * @brief Returns the next enum
 * 
 * @param  balls_n 
 * @return BallsN 
 */
BallsN balls_next(  BallsN balls_n){
    switch(balls_n){
        case BALLS_NUMBER_ONLY_ONE:  return BALLS_NUMBER_3_SPACE;
        case BALLS_NUMBER_3_SPACE:   return BALLS_NUMBER_1_SPACE;
        case BALLS_NUMBER_1_SPACE:   return BALLS_NUMBER_BURST;
        case BALLS_NUMBER_BURST:     return BALLS_NUMBER_MAX;
        case BALLS_NUMBER_MAX:       return BALLS_NUMBER_MAX;
    }
}


/**
 * @brief Returns the prior enum
 * 
 * @param  balls_n 
 * @return BallsN 
 */
BallsN balls_prior( BallsN balls_n){
    switch(balls_n){
        case BALLS_NUMBER_ONLY_ONE:  return BALLS_NUMBER_ONLY_ONE;
        case BALLS_NUMBER_3_SPACE:   return BALLS_NUMBER_ONLY_ONE;
        case BALLS_NUMBER_1_SPACE:   return BALLS_NUMBER_3_SPACE;
        case BALLS_NUMBER_BURST:     return BALLS_NUMBER_1_SPACE;
        case BALLS_NUMBER_MAX:       return BALLS_NUMBER_BURST;
    }
}
