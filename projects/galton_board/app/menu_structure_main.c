/**
 * @file menu_structure_main.c
 * @author  Ricardo J. Furlan
 * @brief   Defines the main menu items and actions
 * @version 0.1
 * @date    2025-05-09
 */

#include <stdio.h>
#include <string.h>
#include "menu_structure_main.h"

#include "ball.h"
#include "balls.h"
#include "gb_speed.h"
#include "gb_structure.h"
#include "menu.h"
#include "menu_structure_play.h"
#include "play.h"



static int8_t deep_max(BallSize ballsize){
    return ((64-1)/(ball_size_pixels(ballsize) + 1)) - 1;
}



// ********** Ball Size **********
static void menu_main_ballsize_title(char * char_buffer){
    snprintf(char_buffer, 17, "Ball Size    %3s", ball_size_string(gb_structure.ballsize));
}
static bool menu_main_ballsize_left() {
    gb_structure.ballsize = ball_prior(gb_structure.ballsize);
    return false;
}
static bool menu_main_ballsize_right(){
    gb_structure.ballsize = ball_next(gb_structure.ballsize);
    int8_t dm = deep_max(gb_structure.ballsize);
    if(gb_structure.deep > dm) gb_structure.deep = dm;
    return false;
}



// ********** N of Ball **********
static void menu_main_balls_n_title(char * char_buffer){
    snprintf(char_buffer, 17, "N Balls%9s", balls_string(gb_structure.balls_n));
}
static bool menu_main_balls_n_left(){
    gb_structure.balls_n = balls_prior(gb_structure.balls_n);
    return false;
}
static bool menu_main_balls_n_right(){
    gb_structure.balls_n = balls_next(gb_structure.balls_n);
    return false;
}



// ********** Deep **********
static void menu_main_deep_title(char * char_buffer){
    snprintf(char_buffer, 17, "Deep         %3d", gb_structure.deep);
}
static bool menu_main_deep_left(){
    if(!(--gb_structure.deep)) gb_structure.deep = 1;
    return false;
}
static bool menu_main_deep_right(){
    uint8_t dm = deep_max(gb_structure.ballsize);
    gb_structure.deep++;
    if(gb_structure.deep > dm) gb_structure.deep = dm;
    return false;
}



// ********** Histogram Bars **********
static void menu_main_histogram_bars_title(char * char_buffer){
    snprintf(char_buffer, 17, "Histo Bars%6s", histogram_bars_string(gb_structure.histogram_bars));
}
static bool menu_main_histogram_bars_left(){
    gb_structure.histogram_bars = histogram_bars_prior(gb_structure.histogram_bars);
    return false;
 }
static bool menu_main_histogram_bars_right(){
    gb_structure.histogram_bars = histogram_bars_next(gb_structure.histogram_bars);
    return false;
}



// ********** Histogram Bell **********
static void menu_main_histogram_bell_title(char * char_buffer){
    snprintf(char_buffer, 17, "Histo Bell%6s", histogram_bell_string(gb_structure.histogram_bell));
}
static bool menu_main_histogram_bell_left(){
    gb_structure.histogram_bell = histogram_bell_prior(gb_structure.histogram_bell);
    return false;
}
static bool menu_main_histogram_bell_right(){
    gb_structure.histogram_bell = histogram_bell_next(gb_structure.histogram_bell);
    return false;
}



// ********** Play **********
static void menu_main_play_title(char * char_buffer){
    strcpy(char_buffer, "Play");
}
static bool menu_main_play_action() {
    menu_init("Menu Play", 3, MENU_STRUCTURE_PLAY_N_ITENS, menu_structure_play, menu_structure_play_click);
    return false;    
}



// ********** Random **********
static void menu_main_random_title(char * char_buffer){
    if(gb_structure.rand_factor > 16){
        snprintf(char_buffer, 17, "Random %9s", "Dynamic");
    }else{
        char tmp[10];
        sprintf(tmp,"%d:%d", gb_structure.rand_factor, 16-gb_structure.rand_factor);
        snprintf(char_buffer, 17, "Random %9s", tmp);
    }
}
static bool menu_main_random_left(){
    if(++gb_structure.rand_factor > 17) gb_structure.rand_factor = 17;
    return false;
}
static bool menu_main_random_right(){
    if(gb_structure.rand_factor > 0) gb_structure.rand_factor--;
    return false;
}



// ********** Speed **********
static void menu_main_speed_title(char * char_buffer){
    snprintf(char_buffer, 17, "Speed  %9s", gb_speed_string(gb_structure.speed));
}
static bool menu_main_speed_left() {gb_structure.speed = gb_speed_prior(gb_structure.speed); return false;}
static bool menu_main_speed_right(){gb_structure.speed = gb_speed_next( gb_structure.speed); return false;}



// ********** Search **********
static void menu_main_search_title(char * char_buffer){
    strcpy(char_buffer, "search");
}
static bool menu_main_search_action(){
    play_search(&gb_structure);
    return false;
}



MenuFunctions menu_structure_main[MENU_STRUCTURE_MAIN_N_ITENS] = {
    {menu_main_ballsize_title,       menu_main_ballsize_left,       menu_main_ballsize_right},
    {menu_main_balls_n_title,        menu_main_balls_n_left,        menu_main_balls_n_right},
    {menu_main_deep_title,           menu_main_deep_left,           menu_main_deep_right},
    {menu_main_speed_title,          menu_main_speed_left,          menu_main_speed_right},
    {menu_main_histogram_bars_title, menu_main_histogram_bars_left, menu_main_histogram_bars_right},
    {menu_main_histogram_bell_title, menu_main_histogram_bell_left, menu_main_histogram_bell_right},
    {menu_main_random_title,         menu_main_random_left,         menu_main_random_right},
    {menu_main_search_title,         menu_main_search_action,       menu_main_search_action},
    {menu_main_play_title,           menu_main_play_action,         menu_main_play_action},
};

/**
 * @brief Function that will be called  when the item is clicked
 * 
 * Depending on the item you can: show an example screen, go to a submenu or do do nothing
 * 
 * @param item item clicked
 * @return true  When you need to close the menu
 * @return false when you need to keep the menu
 */
bool menu_structure_main_click(uint8_t item){
    switch(item){
        case 0: // Ball Size
        case 2: // Deep
        case 4: // Histo Bars
        case 5: // Histo Bell
            // show an example screen
            play_demo(gb_structure, true);
            break;
        case 7: // Search
            menu_main_search_action();
            break;
        case 8: // Play
            menu_main_play_action();
            break;
    }
    
    return false;
}