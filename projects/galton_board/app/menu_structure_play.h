/**
 * @file    menu_structure_play.h
 * @author  Ricardo J. Furlan
 * @brief   Defines the play menu items
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef MENU_STRUCTURE_PLAY_H
#define MENU_STRUCTURE_PLAY_H


#include "menu_structure.h"

#define MENU_STRUCTURE_PLAY_N_ITENS 5

extern MenuFunctions menu_structure_play[MENU_STRUCTURE_PLAY_N_ITENS];

/**
 * @brief Function that will be called  when the item is clicked
 * 
 * Depending on the item you can: update a parameter, performs an action, go to a submenu or close menu
 * 
 * @param item item clicked
 * @return true  When you need to close the menu
 * @return false when you need to keep the menu
 */ 
bool menu_structure_play_click(uint8_t item);


#endif // MENU_STRUCTURE_PLAY_H