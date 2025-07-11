/**
 * @file    balls.h
 * @author  Ricardo J. Furlan
 * @brief   Sets values ​​for how many balls will be present simultaneously
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef BALLS_H
#define BALLS_H

typedef enum {
    BALLS_NUMBER_ONLY_ONE = 0,
    BALLS_NUMBER_3_SPACE,
    BALLS_NUMBER_1_SPACE,
    BALLS_NUMBER_BURST,
    BALLS_NUMBER_MAX,
} BallsN;

/**
 * @brief Returns the text representing the value
 * 
 * @param balls_n 
 * @return char* 
 */
char * balls_string(BallsN balls_n);

/**
 * @brief Returns the next enum
 * 
 * @param  balls_n 
 * @return BallsN 
 */
BallsN balls_next(  BallsN balls_n);

/**
 * @brief Returns the prior enum
 * 
 * @param  balls_n 
 * @return BallsN 
 */
BallsN balls_prior( BallsN balls_n);

#endif // BALLS_H
