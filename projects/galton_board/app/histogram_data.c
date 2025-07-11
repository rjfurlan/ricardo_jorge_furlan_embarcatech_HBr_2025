/**
 * @file    histogram_data.c
 * @author  Ricardo J. Furlan
 * @brief   Update data and draw histogram
 * @version 0.1
 * @date    2025-05-09
 */
#include "histogram_data.h"
#include "conf.h"
#include "lib_bitdoglab/oled/display.h"

static uint32_t histogram[MAX_HISTOGRAM] = {0};

static uint32_t h_total_count     = 0;
static uint32_t h_max_col_count   = 0;
static uint32_t h_limit_column    = 999999999;
static uint32_t h_limit_total     = 999999999;



/**
 * @brief Sets the maximum number of balls values: total and column
 * 
 * @param max_total_ball 
 * @param max_column_ball 
 */
void histogram_set_max_values(uint32_t max_total_ball, uint32_t max_column_ball){
    h_limit_column = max_column_ball;
    h_limit_total  = max_total_ball;
}

/**
 * @brief Adds a ball to a given column.
 * 
 * Returns true if the total number of balls or the number of balls in a given column has been reached.
 * 
 * @param col 
 * @return true 
 * @return false 
 */
bool histogram_add_ball(uint32_t col){
    if(col >= MAX_HISTOGRAM) return true;
    h_total_count++;
    histogram[col]++;
    if(h_max_col_count < histogram[col]) h_max_col_count = histogram[col];

    return (h_total_count >= h_limit_total) || (histogram[col] >= h_limit_column);
}

/**
 * @brief Clear(set as zero) histogram data
 * 
 */
void histogram_data_clear(){
    for(int i=0;i<MAX_HISTOGRAM;i++) histogram[i] = 0;
    h_total_count     = 0;
    h_max_col_count   = 0;
}

/**
 * @brief Draw the histogram
 * 
 * @param n_pos 
 * @param cy 
 * @param ball_size  (is always an odd value)
 * @param col_height 
 */
void histogram_data_draw(uint8_t n_pos, uint8_t cy, uint8_t ball_size, uint8_t col_height){
    if(!h_max_col_count) return;

    int8_t y = cy - ((ball_size + 1) * n_pos) / 2;

    for(int i = 0; i < n_pos; i++){
        if(histogram[i]){
            uint8_t x = (((uint64_t)(histogram[i])) * col_height) / h_max_col_count;
            display_set_ret(true, false,  0, y+1, x, y + ball_size);
        }
        y += ball_size + 1;
    }
}

/**
 * @brief Returns the total number of balls in the histogram
 * 
 * @return uint32_t 
 */
uint32_t histogram_get_n_balls(){
    return h_total_count ;
}

/**
 * @brief Returns the number of balls in a given column
 * 
 * @param col 
 * @return uint32_t 
 */
uint32_t histogram_get_balls_at(uint8_t col){
    if(col >= MAX_HISTOGRAM) return 0;
    return histogram[col];
}