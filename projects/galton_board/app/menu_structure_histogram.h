/**
 * @file    menu_structure_histogram.h
 * @author  Ricardo J. Furlan
 * @brief   Defines the histogram menu items
 * 
 * Emulates histogram values ​​as if it were a menu
 * Each menu item will contain the value of a column of the histogram.
 * 
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef MENU_STRUCTURE_HISTOGRAM_H
#define MENU_STRUCTURE_HISTOGRAM_H


#include "pico/stdlib.h"

/**
 * @brief Creates the menu with the histogram data
 * 
 * @param deep number of lines of Galton Board
 */
void menu_structure_histogram_show(uint8_t deep);


#endif // MENU_STRUCTURE_HISTOGRAM_H