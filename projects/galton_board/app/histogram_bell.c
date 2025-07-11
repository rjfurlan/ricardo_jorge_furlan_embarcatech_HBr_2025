/**
 * @file    histogram_bell.c
 * @author  Ricardo J. Furlan
 * @brief   Sets the visual mode ​​for how the bell will be displayed in the histogram
 * @version 0.1
 * @date    2025-05-09
 */
#include "histogram_bell.h"
#include "bell.h"
#include "lib_bitdoglab/oled/display.h"


/**
 * @brief Returns the visual mode as a string
 * 
 * @param histogram_bell 
 * @return char* 
 */
char * histogram_bell_string(HistogramBell histogram_bell){
    switch(histogram_bell){
        case HISTOGRAM_BELL_NO:   return "NO";
        case HISTOGRAM_BELL_DOT:  return "DOT";
        case HISTOGRAM_BELL_BAR:  return "BAR";
        case HISTOGRAM_BELL_LINE: return "LINE";
        
        default: return "ERROR";
    }
}

/**
 * @brief Returns the next enum
 * 
 * @param histogram_bell 
 * @return HistogramBell 
 */
HistogramBell histogram_bell_next(HistogramBell histogram_bell){
    switch(histogram_bell){
        case HISTOGRAM_BELL_NO:   return HISTOGRAM_BELL_DOT;
        case HISTOGRAM_BELL_DOT:  return HISTOGRAM_BELL_BAR;
        case HISTOGRAM_BELL_BAR:  return HISTOGRAM_BELL_LINE;
        case HISTOGRAM_BELL_LINE: return HISTOGRAM_BELL_LINE;
        default: return histogram_bell;
    }
}

/**
 * @brief Returns the prior enum
 * 
 * @param histogram_bell 
 * @return HistogramBell 
 */
HistogramBell histogram_bell_prior(HistogramBell histogram_bell){
    switch(histogram_bell){
        case HISTOGRAM_BELL_NO:   return HISTOGRAM_BELL_NO;
        case HISTOGRAM_BELL_DOT:  return HISTOGRAM_BELL_NO;
        case HISTOGRAM_BELL_BAR:  return HISTOGRAM_BELL_DOT;
        case HISTOGRAM_BELL_LINE: return HISTOGRAM_BELL_BAR;
        default: return histogram_bell;
    }
}

/**
 * @brief Draws histogram bell
 * 
 * @param histogram_bell 
 * @param n_cols 
 * @param cy 
 * @param ball_size  (is always an odd value)
 * @param col_height 
 */
void histogram_bell_draw(HistogramBell histogram_bell, uint8_t n_cols, uint8_t cy, uint8_t ball_size, uint8_t col_height){
    if(n_cols > (BELL_MAX_DEEP + 1)) return;
    ball_size++;
    
    const uint32_t * bell_values = bell_deep[n_cols - 1];

    int8_t y;
    col_height--;
    switch(histogram_bell){
        //case HISTOGRAM_BELL_NO: return;
        case HISTOGRAM_BELL_DOT:
            y = cy - (ball_size * (n_cols - 1)) / 2;
            for(int i = 0; i < n_cols; i++){
                uint8_t x = ((uint64_t)col_height) * bell_values[i+1] /  bell_values[0] ;
                display_set_point(true, false, x, y);
                y += ball_size;
            }
            break;
        case HISTOGRAM_BELL_BAR:
            y = cy - (ball_size * n_cols) / 2;
            for(int i = 0; i < n_cols; i++){
                uint8_t x = ((uint64_t)col_height) * bell_values[i+1] /  bell_values[0] ;

                display_set_line(true, false, x, y, x, y + ball_size);
                y += ball_size;
            }
            break;
        case HISTOGRAM_BELL_LINE:
            y = cy - (ball_size * (n_cols - 1)) / 2;
            uint8_t x0 = ((uint64_t)col_height) * bell_values[1] /  bell_values[0];
            for(int i = 1; i < n_cols; i++){
                uint8_t x = ((uint64_t)col_height) * bell_values[i+1] /  bell_values[0];
                display_set_line(true, false, x0, y, x, y + ball_size);
                x0 = x;
                y += ball_size;
            }
        break;
    }
}