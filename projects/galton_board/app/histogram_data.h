/**
 * @file    histogram_data.h
 * @author  Ricardo J. Furlan
 * @brief   Update data and draw histogram
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef HISTOGRAM_DATA_H
#define HISTOGRAM_DATA_H

#include "pico/stdlib.h"

#define HISTOGRAM_POS_N_BALLS      MAX_HISTOGRAM
#define HISTOGRAM_POS_N_ITENS     (MAX_HISTOGRAM + 1)


/**
 * @brief Sets the maximum number of balls values: total and column
 * 
 * @param max_total_ball 
 * @param max_column_ball 
 */
void histogram_set_max_values(uint32_t max_total_ball, uint32_t max_column_ball);

/**
 * @brief Adds a ball to a given column.
 * 
 * Returns true if the total number of balls or the number of balls in a given column has been reached.
 * 
 * @param col 
 * @return true 
 * @return false 
 */
bool histogram_add_ball(uint32_t col);

/**
 * @brief Clear(set as zero) histogram data
 * 
 */
void histogram_data_clear();

/**
 * @brief Draw the histogram
 * 
 * @param n_pos 
 * @param cy 
 * @param ball_size  (is always an odd value)
 * @param col_height 
 */
void histogram_data_draw(uint8_t n_pos, uint8_t cy, uint8_t ball_size, uint8_t col_height);

/**
 * @brief Returns the total number of balls in the histogram
 * 
 * @return uint32_t 
 */
uint32_t histogram_get_n_balls();

/**
 * @brief Returns the number of balls in a given column
 * 
 * @param col 
 * @return uint32_t 
 */
uint32_t histogram_get_balls_at(uint8_t col);


#endif // HISTOGRAM_DATA_H