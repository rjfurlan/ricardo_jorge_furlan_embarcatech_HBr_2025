/**
 * @file    histogram_bell.h
 * @author  Ricardo J. Furlan
 * @brief   Sets the visual mode ​​for how the bell will be displayed in the histogram
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef HISTOGRAM_BELL_H
#define HISTOGRAM_BELL_H


#include "pico/stdlib.h"

typedef enum {
    HISTOGRAM_BELL_NO = 0,
    HISTOGRAM_BELL_DOT,
    HISTOGRAM_BELL_BAR,
    HISTOGRAM_BELL_LINE,
} HistogramBell;


/**
 * @brief Returns the visual mode as a string
 * 
 * @param histogram_bell 
 * @return char* 
 */
char * histogram_bell_string(HistogramBell histogram_bell);

/**
 * @brief Returns the next enum
 * 
 * @param histogram_bell 
 * @return HistogramBell 
 */
HistogramBell histogram_bell_next( HistogramBell histogram_bell);

/**
 * @brief Returns the prior enum
 * 
 * @param histogram_bell 
 * @return HistogramBell 
 */
HistogramBell histogram_bell_prior(HistogramBell histogram_bell);

/**
 * @brief Draws histogram bell
 * 
 * @param histogram_bell 
 * @param n_cols 
 * @param cy 
 * @param ball_size  (is always an odd value)
 * @param col_height 
 */
void   histogram_bell_draw(HistogramBell histogram_bell, uint8_t n_cols, uint8_t cy, uint8_t ball_size, uint8_t col_height);


#endif // HISTOGRAM_BELL_H