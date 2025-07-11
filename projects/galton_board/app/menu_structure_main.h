/**
 * @file    menu_structure_main.h 
 * @author  Ricardo J. Furlan
 * @brief   Defines the main menu items and actions
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef MENU_STRUCTURE_MAIN_H
#define MENU_STRUCTURE_MAIN_H


#include "menu_structure.h"

#define MENU_STRUCTURE_MAIN_N_ITENS 9

extern MenuFunctions menu_structure_main[MENU_STRUCTURE_MAIN_N_ITENS];

/**
 * @brief Function that will be called  when the item is clicked
 * 
 * Depending on the item you can: show an example screen, go to a submenu or do do nothing
 * 
 * @param item item clicked
 * @return true  When you need to close the menu
 * @return false when you need to keep the menu
 */
bool menu_structure_main_click(uint8_t item);


#endif // MENU_STRUCTURE_MAIN_H
