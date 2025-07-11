/**
 * @file    histogram_bars.c
 * @author  Ricardo J. Furlan
 * @brief   Sets the visual mode of the histogram separation bars
 * @version 0.1
 * @date    2025-05-09
 */
#include "histogram_bars.h"
#include "lib_bitdoglab/oled/display.h"

#define BAR_TOP_DOW_SIZE 3

/**
 * @brief Returns the visual mode as a stri
 * 
 * @param  histogram_bars 
 * @return char* 
 */
char * histogram_bars_string(HistogramBars histogram_bars){
    switch(histogram_bars){
        case HISTOGRAM_BAR_NO:        return "NO";
        case HISTOGRAM_BAR_LINE:      return "LINE";
        case HISTOGRAM_BAR_DOT:       return "DOT";
        case HISTOGRAM_BAR_DOT_LIGHT: return "DOT L";
        case HISTOGRAM_BAR_TOP_DOWN:  return "TOP D";
        default: return "ERROR";
    }
}

/**
 * @brief Returns the next enum
 * 
 * @param  histogram_bars 
 * @return HistogramBars 
 */
HistogramBars histogram_bars_next(HistogramBars histogram_bars){
    switch(histogram_bars){
        case HISTOGRAM_BAR_NO:        return HISTOGRAM_BAR_LINE;
        case HISTOGRAM_BAR_LINE:      return HISTOGRAM_BAR_DOT;
        case HISTOGRAM_BAR_DOT:       return HISTOGRAM_BAR_DOT_LIGHT;
        case HISTOGRAM_BAR_DOT_LIGHT: return HISTOGRAM_BAR_TOP_DOWN;
        case HISTOGRAM_BAR_TOP_DOWN:  return HISTOGRAM_BAR_TOP_DOWN;
        default: return histogram_bars;
    }
}

/**
 * @brief Returns the prior enum
 * 
 * @param  histogram_bars 
 * @return HistogramBars 
 */
HistogramBars histogram_bars_prior(HistogramBars histogram_bars){
    switch(histogram_bars){
        case HISTOGRAM_BAR_NO:        return HISTOGRAM_BAR_NO;
        case HISTOGRAM_BAR_LINE:      return HISTOGRAM_BAR_NO;
        case HISTOGRAM_BAR_DOT:       return HISTOGRAM_BAR_LINE;
        case HISTOGRAM_BAR_DOT_LIGHT: return HISTOGRAM_BAR_DOT;
        case HISTOGRAM_BAR_TOP_DOWN:  return HISTOGRAM_BAR_DOT_LIGHT;
        default: return histogram_bars;
    }
}

/**
 * @brief Draws histogram separation bars
 * 
 * @param histogram_bars 
 * @param n_cols 
 * @param cy 
 * @param ball_size (is always an odd value)
 * @param col_height 
 */
void histogram_bars_draw(HistogramBars histogram_bars, uint8_t n_cols, uint8_t cy, uint8_t ball_size, uint8_t col_height){
    ball_size++;
    int8_t y0 = cy - ball_size * n_cols / 2;

    col_height--;
    switch(histogram_bars){
        //case HISTOGRAM_BAR_NO: return;
        case HISTOGRAM_BAR_LINE:
            for(int i = 0; i <= n_cols; i++){
                display_set_line(true, false, 0, y0, col_height, y0);
                y0 += ball_size;
            }
            break;
        case HISTOGRAM_BAR_DOT:
            for(int i = 0; i <= n_cols; i++){
                for(int j=col_height; j >= 0; j-= 2){
                    display_set_point(true, false, j, y0);
                }
                y0 += ball_size;
            }
            break;
        case HISTOGRAM_BAR_DOT_LIGHT:
            for(int i = 0; i <= n_cols; i++){
                for(int j=col_height; j >= 0; j-=4){
                    display_set_point(true, false, j, y0);
                }
                y0 += ball_size;
            }
            break;
        case HISTOGRAM_BAR_TOP_DOWN:
            uint8_t x1 = (col_height - BAR_TOP_DOW_SIZE) / 2;
            uint8_t x2 = x1 + BAR_TOP_DOW_SIZE;
            for(int i = 0; i <= n_cols; i++){
                display_set_line(true, false, 0,                           y0, BAR_TOP_DOW_SIZE, y0);
                display_set_line(true, false, x1,                          y0, x2,               y0);
                display_set_line(true, false, col_height-BAR_TOP_DOW_SIZE, y0, col_height,       y0);
                y0 += ball_size;
            }
            break;

    }
}