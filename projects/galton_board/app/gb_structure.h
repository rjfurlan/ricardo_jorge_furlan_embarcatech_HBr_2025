/**
 * @file    gb_structure.h
 * @author  Ricardo J. Furlan
 * @brief   Defines the structure (and global data) of the gb configuration data
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef GB_STRUCTURE_H
#define GB_STRUCTURE_H

#include "pico/stdlib.h"
#include "ball.h"
#include "balls.h"
#include "gb_speed.h"
#include "histogram_bars.h"
#include "histogram_bell.h"

typedef struct{
    BallSize      ballsize;
    uint8_t       deep;
    HistogramBars histogram_bars;
    uint8_t       rand_factor;  // betuween: 0 and 16
    HistogramBell histogram_bell;
    Speed         speed;
    BallsN        balls_n;

} GbStructure;

extern GbStructure gb_structure;


#endif // GB_STRUCTURE_H