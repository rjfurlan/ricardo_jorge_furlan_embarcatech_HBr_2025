/**
 * @file    bell.h
 * @author  Ricardo J. Furlan
 * @brief   Bell values, Gaussian
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef BELL_H
#define BELL_H


#include "pico/stdlib.h"

#define BELL_MAX_DEEP 32
extern const uint32_t *bell_deep[BELL_MAX_DEEP+1];


#endif // BELL_H