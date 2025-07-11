/**
 * @file    menu_structure.h
 * @author  Ricardo J. Furlan
 * @brief   Define a structure that contains functions for a given menu item.
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef MENU_STRUCTURE_H
#define MENU_STRUCTURE_H


#include "pico/stdlib.h"

typedef void (*menu_text_t)(char* char_buffer);     // char* char_buffer size = 16 + 1;
typedef bool (*menu_left_t)(void);
typedef bool (*menu_right_t)(void);

typedef struct {
    menu_text_t  menu_text;
    menu_left_t  menu_left;
    menu_right_t menu_right;
} MenuFunctions;


#endif // MENU_STRUCTURE_H