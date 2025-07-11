/**
 * @file    menu.h
 * @author  Ricardo J. Furlan
 * @brief   Manages a generic menu that is described by parameters
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef MENU_H
#define MENU_H

#include "menu_structure.h"

/**
 * @brief Manages a generic menu that is described by parameters
 * 
 * The actions for each menu item are described by a structure, which contains functions for generating the menu text and actions for the left/right commands executed in the menu.
 * To exit the menu, some menu action or click function must return true.
 * 
 * @param title menu title
 * @param start_line display the line number where the first menu item should be
 * @param n_itens how many lines/itens the menu has
 * @param menu_function Array with the functions that should be executed when navigating through the menu
 * @param click_function Function executed when clicking on the menu item
 */
void menu_init(char * title, int8_t start_line, int8_t n_itens, MenuFunctions * menu_function, bool (*click_function)(uint8_t));

#endif // MENU_H