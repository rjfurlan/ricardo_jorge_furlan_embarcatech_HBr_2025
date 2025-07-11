/**
 * @file    ball.c
 * @author  Ricardo J. Furlan
 * @brief   Sets ball size values
 * @version 0.1
 * @date    2025-05-08
 */
#include "ball.h"
#include "lib_bitdoglab/oled/display.h"


/**
 * @brief Draw the ball on the display
 * 
 * @param ballsize 
 * @param cx x-coordinate of the center of the ball
 * @param cy y-coordinate of the center of the ball
 */
void     ball_draw       (BallSize ballsize, uint8_t cx, uint8_t cy){
    switch (ballsize){
        case BALL_SIZE_1:
        case BALL_SIZE_1_PLUS:
        case BALL_SIZE_1_PLUS2:
            display_set_point(true, false, cx, cy);
            break;
        case BALL_SIZE_3:
        case BALL_SIZE_3_PLUS:
            display_set_point(true, false, cx-1, cy);
            display_set_point(true, false, cx+1, cy);
            display_set_point(true, false, cx,   cy-1);
            display_set_point(true, false, cx,   cy+1);
            break;
        case BALL_SIZE_5:
        case BALL_SIZE_5_PLUS:
            //display_set_point(true, false, cx, cy);
    
            display_set_point(true, false, cx-2, cy-1);
            display_set_point(true, false, cx-2, cy);
            display_set_point(true, false, cx-2, cy+1);
    
            display_set_point(true, false, cx+2, cy-1);
            display_set_point(true, false, cx+2, cy);
            display_set_point(true, false, cx+2, cy+1);
    
            display_set_point(true, false, cx-1, cy-2);
            display_set_point(true, false, cx,   cy-2);
            display_set_point(true, false, cx+1, cy-2);
    
            display_set_point(true, false, cx-1, cy+2);
            display_set_point(true, false, cx,   cy+2);
            display_set_point(true, false, cx+1, cy+2);
            break;
        case BALL_SIZE_7:
        case BALL_SIZE_7_PLUS:
            //display_set_point(true, false, cx, cy);
    
            display_set_point(true, false, cx-3, cy-1);
            display_set_point(true, false, cx-3, cy);
            display_set_point(true, false, cx-3, cy+1);
    
            display_set_point(true, false, cx+3, cy-1);
            display_set_point(true, false, cx+3, cy);
            display_set_point(true, false, cx+3, cy+1);
    
            display_set_point(true, false, cx-1, cy-3);
            display_set_point(true, false, cx,   cy-3);
            display_set_point(true, false, cx+1, cy-3);
    
            display_set_point(true, false, cx-1, cy+3);
            display_set_point(true, false, cx,   cy+3);
            display_set_point(true, false, cx+1, cy+3);
    
            display_set_point(true, false, cx-2, cy-2);
            display_set_point(true, false, cx-2, cy+2);
            display_set_point(true, false, cx+2, cy-2);
            display_set_point(true, false, cx+2, cy+2);
            break;
        default:
            break;
        } 
}

/**
 * @brief returns the size of the ball in pixels
 * 
 * @param  ballsize 
 * @return uint8_t returns the size of the ball in pixels
 */
uint8_t  ball_size_pixels(BallSize ballsize){
    switch(ballsize){
        case BALL_SIZE_1:       return 1;
        case BALL_SIZE_1_PLUS:  return 3;
        case BALL_SIZE_1_PLUS2: return 5;
        case BALL_SIZE_3:       return 3;
        case BALL_SIZE_3_PLUS:  return 5;
        case BALL_SIZE_5:       return 5;
        case BALL_SIZE_5_PLUS:  return 7;
        case BALL_SIZE_7:       return 7; 
        case BALL_SIZE_7_PLUS:  return 9;
        default: return 0;
    }
}

/**
 * @brief returns the size of the ball as a string
 * 
 * @param  ballsize 
 * @return uint8_t returns the size of the ball as a string
 */
char *   ball_size_string(BallSize ballsize){
    switch(ballsize){
        case BALL_SIZE_1:       return "1";
        case BALL_SIZE_1_PLUS:  return "1+";
        case BALL_SIZE_1_PLUS2: return "1++";
        case BALL_SIZE_3:       return "3";
        case BALL_SIZE_3_PLUS:  return "3+";
        case BALL_SIZE_5:       return "5";
        case BALL_SIZE_5_PLUS:  return "5+";
        case BALL_SIZE_7:       return "7";
        case BALL_SIZE_7_PLUS:  return "7+";
        default: return 0;
    }
}

/**
 * @brief Returns the next enum
 * 
 * @param  balls_n 
 * @return BallSize 
 */
BallSize ball_next(       BallSize ballsize){
    switch(ballsize){
        case BALL_SIZE_1:       return BALL_SIZE_1_PLUS;    // or BALL_SIZE_7_PLUS;
        case BALL_SIZE_1_PLUS:  return BALL_SIZE_1_PLUS2;
        case BALL_SIZE_1_PLUS2: return BALL_SIZE_3;
        case BALL_SIZE_3:       return BALL_SIZE_3_PLUS;
        case BALL_SIZE_3_PLUS:  return BALL_SIZE_5;
        case BALL_SIZE_5:       return BALL_SIZE_5_PLUS;
        case BALL_SIZE_5_PLUS:  return BALL_SIZE_7;
        case BALL_SIZE_7:       return BALL_SIZE_7_PLUS;
        case BALL_SIZE_7_PLUS:  return BALL_SIZE_7_PLUS;    // or BALL_SIZE_1;
        default: return ballsize;
    }
}

/**
 * @brief Returns the prior enum
 * 
 * @param  balls_n 
 * @return BallSize 
 */
BallSize ball_prior(      BallSize ballsize){
    switch(ballsize){
        case BALL_SIZE_1:       return BALL_SIZE_1;         // or BALL_SIZE_7_PLUS;
        case BALL_SIZE_1_PLUS:  return BALL_SIZE_1; 
        case BALL_SIZE_1_PLUS2: return BALL_SIZE_1_PLUS;
        case BALL_SIZE_3:       return BALL_SIZE_1_PLUS2;
        case BALL_SIZE_3_PLUS:  return BALL_SIZE_3;
        case BALL_SIZE_5:       return BALL_SIZE_3_PLUS;
        case BALL_SIZE_5_PLUS:  return BALL_SIZE_5;
        case BALL_SIZE_7:       return BALL_SIZE_5_PLUS;
        case BALL_SIZE_7_PLUS:  return BALL_SIZE_7;         // or BALL_SIZE_1;
        default: return ballsize;
    }
}