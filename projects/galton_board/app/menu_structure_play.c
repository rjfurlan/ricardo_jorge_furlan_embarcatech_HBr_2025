/**
 * @file    menu_structure_play.c
 * @author  Ricardo J. Furlan
 * @brief   Defines the play menu items
 * @version 0.1
 * @date    2025-05-09
 */
#include <stdio.h>
#include "menu_structure_play.h"
#include "histogram_data.h"
#include "menu_structure_histogram.h"
#include "play.h"


// ********** Clear Histogram Data **********
static void menu_play_clear_title(char * char_buffer){
    snprintf(char_buffer, 17, "Clear Data:%5s", histogram_get_n_balls()?"Durty":"Clean");
}
static bool menu_play_clear_action(){ 
    histogram_data_clear();
    return false;
};



// ********** Play in Hypersonic mode **********
static void menu_play_hyper_title(char * char_buffer){
    snprintf(char_buffer, 17, "Play Hypersonic");
}
static bool menu_play_hyper_action(){
    play_hyper(gb_structure);
    return false;
};



// ********** Play in normal mode **********
static void menu_play_play_title(char * char_buffer){
    snprintf(char_buffer, 17, "Play normal way");
}
static bool menu_play_play_action(){
    play_normal(gb_structure);
    return false;
};



// ********** Show/Open Histograma Menu **********
static void menu_play_histogram_title(char * char_buffer){
    snprintf(char_buffer, 17, "Histogram Data");
}
static bool menu_play_histogram_action(){
    menu_structure_histogram_show(gb_structure.deep);
    return false;
};



// ********** Close Menu **********
static void menu_play_return_title(char * char_buffer){
    snprintf(char_buffer, 17, "Return");
}
static bool menu_play_return_action(){return true;};



MenuFunctions menu_structure_play[MENU_STRUCTURE_PLAY_N_ITENS] = {
    {menu_play_play_title,      menu_play_play_action,      menu_play_play_action},
    {menu_play_hyper_title,     menu_play_hyper_action,     menu_play_hyper_action},
    {menu_play_clear_title,     menu_play_clear_action,     menu_play_clear_action},
    {menu_play_histogram_title, menu_play_histogram_action, menu_play_histogram_action},
    {menu_play_return_title,    menu_play_return_action,    menu_play_return_action},
};


/**
 * @brief Function that will be called  when the item is clicked
 * 
 * Depending on the item you can: update a parameter, performs an action, go to a submenu or close menu
 * 
 * @param item item clicked
 * @return true  When you need to close the menu
 * @return false when you need to keep the menu
 */ 
bool menu_structure_play_click(uint8_t item){
    switch (item){
        case 0: menu_play_play_action();      return false;
        case 1: menu_play_hyper_action();     return false;
        case 2: menu_play_clear_action();     return false;
        case 3: menu_play_histogram_action(); return false;
        case 4: return true;
    }
}