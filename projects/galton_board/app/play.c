/**
 * @file    play.c
 * @author  Ricardo J. Furlan
 * @brief   Displays or runs the Galton Board in various modes
 * @version 0.1
 * @date    2025-05-09
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/rand.h"
#include "play.h"
#include "ball.h"
#include "conf.h"
#include "histogram_data.h"
#include "input.h"
#include "lib_bitdoglab/oled/display.h"


#define COL_HEIGHT       (127-10)
#define HYPER_REFRESH_US   100000     // Refresh display time in us
#define MAX_BALLS              34

typedef struct {
    bool    fall;
    int16_t pos_horizontal;
    int16_t pos_vertical;
} BallPos;

typedef struct {
    BallSize ballsize;
    uint8_t  deep;
    uint8_t  x0;
    uint8_t  delta;
    uint32_t ball_tick;
    uint32_t ball_tick_min;
    uint16_t ball_pos_last;
    uint16_t ball_pos_last_decision;
} BallUpdateParameters;

static BallPos balls[MAX_BALLS];

/**
 * @brief Updates the ball's position, places it in the histogram when applicable and draws it on the screen
 * 
 * @param ball 
 * @param bup system parameters
 * @param rand_factor 
 */
void ball_update_pos(BallPos * ball, BallUpdateParameters * bup, int8_t rand_factor){
    // Check if the ball is falling
    if(!ball->fall){
        // If it is not falling, check if it is time to release a new one.
        if(bup->ball_tick >= bup->ball_tick_min){
            bup->ball_tick = 0;
            ball->fall = true;
            ball->pos_horizontal = 0;
            ball->pos_vertical = -6;
        } else return;
    }

    if(ball->pos_vertical >= bup->ball_pos_last){
        // the ball reached the end
        ball->fall = false;
        // add to histogram
        histogram_add_ball((ball->pos_horizontal + bup->deep)/2);
    }else{
        // the ball did not reach the end, move down one position
        ball->pos_vertical++;
        // Check if the ball is in the pin region
        if((ball->pos_vertical >= 0) && (ball->pos_vertical <= bup->ball_pos_last_decision)){
            // Check if the ball is on a pin, and if it should go to the right or left
            if(!(ball->pos_vertical & 0x01)){
                if((get_rand_32() & 0x0F) >= rand_factor) ball->pos_horizontal++;
                                                     else ball->pos_horizontal--;
            }
        }
        ball_draw(bup->ballsize, bup->x0 - (ball->pos_vertical * bup->delta), CENTER_Y + (ball->pos_horizontal * bup->delta));
    }
}

/**
 * @brief Draw the Galton Board pin triangle
 * 
 * @param deep  Number of lines
 * @param x0    X position of the first pin (top of the triangle)
 * @param delta half the distance between the pins
 */
static void draw_triangle(uint8_t deep, uint8_t x0, uint8_t delta){;
    uint8_t y = CENTER_Y;
    for(int i=0;i<deep;i++){
        for(int j=0;j<=i;j++)
            display_set_point(true, false, x0, y + (j * delta * 2));
        y  -= delta;
        x0 -= delta * 2;
    }
}

/**
 * @brief Updates rand_factor based on joystick position
 * 
 * @param rand_factor 
 */
static void    update_rand_factor(uint8_t * rand_factor){
    *rand_factor = input_last_y() / 241;
}




/**
 * @brief Shows a static Galton Board for reference
 * 
 * @param gb_structure 
 */
void play_demo(  GbStructure gb_structure, bool demo){
    uint8_t x0              = 127 - 8 - (6 * ((ball_size_pixels(gb_structure.ballsize) + 1) / 2));
    uint8_t histogram_x_max = x0 - (((gb_structure.deep - 1) * 2 + 4) * ((ball_size_pixels(gb_structure.ballsize) + 1) / 2));

    display_fill(false, false);
    display_top_number(1234567890);     // draw Balls Count

    if(demo){
        ball_draw(gb_structure.ballsize, x0 - (-5 * (ball_size_pixels(gb_structure.ballsize) + 1) / 2), CENTER_Y );
        ball_draw(gb_structure.ballsize, x0 - (-1 * (ball_size_pixels(gb_structure.ballsize) + 1) / 2), CENTER_Y );
    }
    draw_triangle(gb_structure.deep, x0, (ball_size_pixels(gb_structure.ballsize) + 1) / 2);

    // draw balls_down

    // Draw Histogram
    
    histogram_data_draw(                             gb_structure.deep + 1, CENTER_Y, ball_size_pixels(gb_structure.ballsize), histogram_x_max);
    histogram_bars_draw(gb_structure.histogram_bars, gb_structure.deep + 1, CENTER_Y, ball_size_pixels(gb_structure.ballsize), histogram_x_max);
    histogram_bell_draw(gb_structure.histogram_bell, gb_structure.deep + 1, CENTER_Y, ball_size_pixels(gb_structure.ballsize), histogram_x_max);

    display_update();

    if(demo){
        while(!input_get()) sleep_ms(50);
    }
}




/**
 * @brief Run the Galton Board in Normal mode
 * 
 * @param gb_structure 
 */
void play_normal(GbStructure gb_structure){
    uint8_t rand_factor = gb_structure.rand_factor;
    if(rand_factor > 16) update_rand_factor(&rand_factor);    // Dynamic random
    
    // Stops all balls
    for(int i = 0;i<MAX_BALLS;i++){
        balls[i].fall = false;
    }

    BallUpdateParameters bup;
    // Defines how many balls will be available and the spacing between them
    uint8_t max_balls = MAX_BALLS;
    switch(gb_structure.balls_n){
        case BALLS_NUMBER_ONLY_ONE:
            max_balls = 1;
            bup.ball_tick_min = 2;
            break;
        case BALLS_NUMBER_3_SPACE:
            bup.ball_tick_min = 8;
            break;
        case BALLS_NUMBER_1_SPACE:
            bup.ball_tick_min = 4;
            break;
        case BALLS_NUMBER_BURST:
            max_balls = 5;
            bup.ball_tick_min = 2;
            break;
        case BALLS_NUMBER_MAX:
            bup.ball_tick_min = 2;
            break;
    }

    uint8_t ballsizel_pixels = ball_size_pixels(gb_structure.ballsize);
    
    bup.ballsize               = gb_structure.ballsize;
    bup.deep                   = gb_structure.deep;
    bup.delta                  = (ballsizel_pixels + 1) / 2;
    bup.x0                     = 127 - 8 - (6 * bup.delta);
    bup.ball_pos_last_decision = (gb_structure.deep - 1) * 2;
    bup.ball_pos_last          = bup.ball_pos_last_decision + 4;
    
    uint8_t  histogram_x_max = bup.x0 - (((gb_structure.deep - 1) * 2 + 4) * bup.delta);

    // DeltaTime to update the display
    uint64_t click_time = gb_speed_delay_us(gb_structure.speed);

    uint64_t t = time_us_64();

    bool play = true;
    while(play){
        bup.ball_tick++;
        display_fill(false, false);
        
        // Update Balls position
        for(int i = 0;i<max_balls;i++){
             ball_update_pos(&balls[i], &bup, rand_factor);
        }

        // Update Display
        display_top_number(histogram_get_n_balls());
        draw_triangle(gb_structure.deep, bup.x0, bup.delta);
        histogram_data_draw(                             gb_structure.deep + 1, CENTER_Y, ballsizel_pixels, histogram_x_max);
        histogram_bars_draw(gb_structure.histogram_bars, gb_structure.deep + 1, CENTER_Y, ballsizel_pixels, histogram_x_max);
        histogram_bell_draw(gb_structure.histogram_bell, gb_structure.deep + 1, CENTER_Y, ballsizel_pixels, histogram_x_max);
        display_update();

        // Update time controll (ball speed)
        while(time_us_64() < t);
        t += click_time;

        // Check if it is to return to the menu
        if(input_get()==IN_CMD_PRESS) play = false;
        
        if(gb_structure.rand_factor > 16) update_rand_factor(& rand_factor);      // Dynamic random
    }    
}

/**
 * @brief Run the Galton Board in Hypersonic mode
 * 
 * @param gb_structure 
 */
void play_hyper( GbStructure gb_structure){
    uint8_t rand_factor = gb_structure.rand_factor;
    if(rand_factor > 16) update_rand_factor(&rand_factor);  // Dynamic random

    uint64_t t = time_us_64();      // time fir display update
    bool play = true;
    while(play){
        // makes the ball go through all the "pins"
        uint pos = 0;
        for(int deep = 0; deep < gb_structure.deep; deep++){
            if((get_rand_32() & 0x0F) >= rand_factor) pos++;
        }
        histogram_add_ball(pos);

        // Refresh display
        if(time_us_64() >= t){
            t += HYPER_REFRESH_US;

            display_fill(false, false);
            
            display_top_number(histogram_get_n_balls());
            uint8_t ball_size =  ball_size_pixels(gb_structure.ballsize);
            histogram_data_draw(                             gb_structure.deep + 1, CENTER_Y, ball_size, COL_HEIGHT);
            histogram_bars_draw(gb_structure.histogram_bars, gb_structure.deep + 1, CENTER_Y, ball_size, COL_HEIGHT);
            histogram_bell_draw(gb_structure.histogram_bell, gb_structure.deep + 1, CENTER_Y, ball_size, COL_HEIGHT);

            display_update();
            
            // Checks if it is to return to the menu
            if(input_get()==IN_CMD_PRESS) play = false;

            if(gb_structure.rand_factor > 16) update_rand_factor(&rand_factor);   // Dynamic random
        }
    }
}




static int8_t deep_max(BallSize ballsize){
    return ((64-1)/(ball_size_pixels(ballsize) + 1)) - 1;
}

/**
 * @brief Run the search model
 * 
 * @param gb_structure 
 */
void play_search(GbStructure * gb_structure){
    uint8_t  deep     = gb_structure->deep;
    BallSize ballsize = gb_structure->ballsize;

    uint8_t max_deep;

    bool scan= true;
    while(scan){
        play_demo(*gb_structure, false);

        switch(input_get()){
            case IN_CMD_UP:
            case IN_CMD_LEFT:
                max_deep = deep_max(ballsize);
                if(deep > 1) deep--;
                else{
                    if(ballsize != BALL_SIZE_1){
                        ballsize = ball_prior(ballsize);
                        deep = deep_max(ballsize);
                    }                    
                }
                gb_structure->deep     = deep;
                gb_structure->ballsize = ballsize;
                break;
            case IN_CMD_DOWN:
            case IN_CMD_RIGHT:
                max_deep = deep_max(ballsize);
                if(deep < max_deep) deep++;
                else{
                    if(ballsize != BALL_SIZE_7_PLUS){
                        deep = 1;
                        ballsize = ball_next(ballsize);
                    }                    
                }
                gb_structure->deep     = deep;
                gb_structure->ballsize = ballsize;
                break;
            case IN_CMD_PRESS: scan = false; break;
        }
    }
}
