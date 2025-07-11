/**
 * @file    menu.c
 * @author  Ricardo J. Furlan
 * @brief   Manages a generic menu that is described by parameters
 * @version 0.1
 * @date    2025-05-0
 */
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "menu.h"
#include "input.h"
#include "lib_bitdoglab/oled/display.h"

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
void menu_init(char * title, int8_t start_line, int8_t n_itens, MenuFunctions * menu_function, bool (*click_function)(uint8_t)){
    char char_buffer[16+1];     // buffer to temporarily create menu lines

    int8_t menu_selected_item = 0;
    int8_t item_first         = 0;              // menu item that appears in the first menu line of the display
    int8_t item_last          = 7 - start_line; // menu item that appears in the last  menu line of the display
    if(item_last >= n_itens) item_last = n_itens - 1;

    bool ret = false;
    while(!ret){    // Only exit the menu when some menu action returns true
        // Updates the position of menu items
        if(item_first > menu_selected_item){
            int delta = item_first - menu_selected_item;
            item_first -= delta;
            item_last  -= delta;
        } else if(item_last < menu_selected_item){
            int delta = menu_selected_item - item_last;
            item_first += delta;
            item_last  += delta;
        }
        
        // Builds the menu on the display
        display_fill(false, false);
        display_msg(false, (16 - strlen(title)) / 2, 0, title);     // title
        for (int i=item_first; i<=item_last; i++){                  // Menu items
            int py = i - item_first + start_line;
            menu_function[i].menu_text(char_buffer);
            display_msg(false, 0, py, char_buffer);
            if(i == menu_selected_item) {
                for(int j=0; j<16;j++) display_invert_char(false, j, py);
            }
        }
        display_update();

        switch (input_get()){
            //case IN_CMD_NO_CMD: break;
            case IN_CMD_UP:     // Menu UP
                menu_selected_item--;
                if(menu_selected_item < 0) menu_selected_item = 0;  // n_itens - 1;
                break;
            case IN_CMD_DOWN:   // Menu Down
                menu_selected_item++;
                if(menu_selected_item >= n_itens) menu_selected_item = n_itens - 1; //0;
                break;
            case IN_CMD_LEFT:   // Performs an action (Left action) on the menu item
                ret = menu_function[menu_selected_item].menu_left();
                break;
            case IN_CMD_RIGHT:   // Performs an action (Right action) on the menu item
                ret = menu_function[menu_selected_item].menu_right();
                break;
            case IN_CMD_PRESS:  // Performs an action (Click action), the menu item as a action parameter
                if(click_function != NULL){
                    ret = click_function(menu_selected_item);
                }
                break;
        }
        sleep_ms(50);
    }
}