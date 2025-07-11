/**
 * @file    ball.h
 * @author  Ricardo J. Furlan
 * @brief   Sets ball size values
 * @version 0.1
 * @date    2025-05-08
 */
#ifndef BALL_H
#define BALL_H


#include "pico/stdlib.h"

typedef enum {
    BALL_SIZE_1 = 0,
    BALL_SIZE_1_PLUS,
    BALL_SIZE_1_PLUS2,
    BALL_SIZE_3,
    BALL_SIZE_3_PLUS,
    BALL_SIZE_5,
    BALL_SIZE_5_PLUS,
    BALL_SIZE_7,
    BALL_SIZE_7_PLUS,
    BALL_SIZE_N_ITENS,
} BallSize;

/**
 * @brief Draw the ball on the display
 * 
 * @param ballsize 
 * @param cx x-coordinate of the center of the ball
 * @param cy y-coordinate of the center of the ball
 */
void     ball_draw       (BallSize ballsize, uint8_t cx, uint8_t cy);

/**
 * @brief returns the size of the ball in pixels
 * 
 * @param  ballsize 
 * @return uint8_t returns the size of the ball in pixels
 */
uint8_t  ball_size_pixels(BallSize ballsize);

/**
 * @brief returns the size of the ball as a string
 * 
 * @param  ballsize 
 * @return uint8_t returns the size of the ball as a string
 */
char *   ball_size_string(BallSize ballsize);

/**
 * @brief Returns the next enum
 * 
 * @param  balls_n 
 * @return BallSize 
 */
BallSize ball_next(       BallSize ballsize);

/**
 * @brief Returns the prior enum
 * 
 * @param  balls_n 
 * @return BallSize 
 */
BallSize ball_prior(      BallSize ballsize);


#endif // BALL_H