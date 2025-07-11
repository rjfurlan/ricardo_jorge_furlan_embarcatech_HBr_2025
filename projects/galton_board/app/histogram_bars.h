/**
 * @file    histogram_bars.h
 * @author  Ricardo J. Furlan
 * @brief   Sets the visual mode of the histogram separation bars
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef HISTOGRAM_BARS_H
#define HISTOGRAM_BARS_H

#include "pico/stdlib.h"

typedef enum {
    HISTOGRAM_BAR_NO = 0,
    HISTOGRAM_BAR_LINE,
    HISTOGRAM_BAR_DOT,
    HISTOGRAM_BAR_DOT_LIGHT,
    HISTOGRAM_BAR_TOP_DOWN
} HistogramBars;


/**
 * @brief Returns the visual mode as a stri
 * 
 * @param  histogram_bars 
 * @return char* 
 */
char * histogram_bars_string(HistogramBars histogram_bars);

/**
 * @brief Returns the next enum
 * 
 * @param  histogram_bars 
 * @return HistogramBars 
 */
HistogramBars histogram_bars_next( HistogramBars histogram_bars);
/**
 * @brief Returns the prior enum
 * 
 * @param  histogram_bars 
 * @return HistogramBars 
 */
HistogramBars histogram_bars_prior(HistogramBars histogram_bars);


/**
 * @brief Draws histogram separation bars
 * 
 * @param histogram_bars 
 * @param n_cols 
 * @param cy 
 * @param ball_size (is always an odd value)
 * @param col_height 
 */
void   histogram_bars_draw(HistogramBars histogram_bars, uint8_t n_cols, uint8_t cy, uint8_t ball_size, uint8_t col_height);


#endif // HISTOGRAM_BARS_H