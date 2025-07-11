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
#include <stdio.h>
#include "menu_structure_histogram.h"

#include "conf.h"
#include "histogram_data.h"
#include "menu.h"

/**
 * @brief Always returns true, so that when the user clicks on the item, the menu closes.
 * 
 * @param item No efect
 * @return true always to close menu
 */
static bool menu_click(uint8_t item){return true;}

/**
 * @brief Where the text will bi written, size = 17
 * 
 * Generates a string with the ball numbers in each column
 * 
 * @param char_buffer 
 * @param cal
 */
void menu_text_item(char* char_buffer, uint8_t col){
    snprintf(char_buffer, 17, "Col%02d:%10u", col, histogram_get_balls_at(col));
}    

// Functions for each column that will call the string generator function with the corresponding parameter
void menu_text_item00(char* char_buffer){ menu_text_item(char_buffer,  0);}
void menu_text_item01(char* char_buffer){ menu_text_item(char_buffer,  1);}
void menu_text_item02(char* char_buffer){ menu_text_item(char_buffer,  2);}
void menu_text_item03(char* char_buffer){ menu_text_item(char_buffer,  3);}
void menu_text_item04(char* char_buffer){ menu_text_item(char_buffer,  4);}
void menu_text_item05(char* char_buffer){ menu_text_item(char_buffer,  5);}
void menu_text_item06(char* char_buffer){ menu_text_item(char_buffer,  6);}
void menu_text_item07(char* char_buffer){ menu_text_item(char_buffer,  7);}
void menu_text_item08(char* char_buffer){ menu_text_item(char_buffer,  8);}
void menu_text_item09(char* char_buffer){ menu_text_item(char_buffer,  9);}

void menu_text_item10(char* char_buffer){ menu_text_item(char_buffer, 10);}
void menu_text_item11(char* char_buffer){ menu_text_item(char_buffer, 11);}
void menu_text_item12(char* char_buffer){ menu_text_item(char_buffer, 12);}
void menu_text_item13(char* char_buffer){ menu_text_item(char_buffer, 13);}
void menu_text_item14(char* char_buffer){ menu_text_item(char_buffer, 14);}
void menu_text_item15(char* char_buffer){ menu_text_item(char_buffer, 15);}
void menu_text_item16(char* char_buffer){ menu_text_item(char_buffer, 16);}
void menu_text_item17(char* char_buffer){ menu_text_item(char_buffer, 17);}
void menu_text_item18(char* char_buffer){ menu_text_item(char_buffer, 18);}
void menu_text_item19(char* char_buffer){ menu_text_item(char_buffer, 19);}

void menu_text_item20(char* char_buffer){ menu_text_item(char_buffer, 20);}
void menu_text_item21(char* char_buffer){ menu_text_item(char_buffer, 21);}
void menu_text_item22(char* char_buffer){ menu_text_item(char_buffer, 22);}
void menu_text_item23(char* char_buffer){ menu_text_item(char_buffer, 23);}
void menu_text_item24(char* char_buffer){ menu_text_item(char_buffer, 24);}
void menu_text_item25(char* char_buffer){ menu_text_item(char_buffer, 25);}
void menu_text_item26(char* char_buffer){ menu_text_item(char_buffer, 26);}
void menu_text_item27(char* char_buffer){ menu_text_item(char_buffer, 27);}
void menu_text_item28(char* char_buffer){ menu_text_item(char_buffer, 28);}
void menu_text_item29(char* char_buffer){ menu_text_item(char_buffer, 29);}

void menu_text_item30(char* char_buffer){ menu_text_item(char_buffer, 30);}
void menu_text_item31(char* char_buffer){ menu_text_item(char_buffer, 31);}

/**
 * @brief does nothing with the left and right commands
 * 
 * @return false 
 */
bool menu_action() {return false;};

static MenuFunctions menu_structure_histogram[MAX_HISTOGRAM] = {
    {menu_text_item00, menu_action, menu_action},
    {menu_text_item01, menu_action, menu_action},
    {menu_text_item02, menu_action, menu_action},
    {menu_text_item03, menu_action, menu_action},
    {menu_text_item04, menu_action, menu_action},
    {menu_text_item05, menu_action, menu_action},
    {menu_text_item06, menu_action, menu_action},
    {menu_text_item07, menu_action, menu_action},
    {menu_text_item08, menu_action, menu_action},
    {menu_text_item09, menu_action, menu_action},

    {menu_text_item10, menu_action, menu_action},
    {menu_text_item11, menu_action, menu_action},
    {menu_text_item12, menu_action, menu_action},
    {menu_text_item13, menu_action, menu_action},
    {menu_text_item14, menu_action, menu_action},
    {menu_text_item15, menu_action, menu_action},
    {menu_text_item16, menu_action, menu_action},
    {menu_text_item17, menu_action, menu_action},
    {menu_text_item18, menu_action, menu_action},
    {menu_text_item19, menu_action, menu_action},

    {menu_text_item20, menu_action, menu_action},
    {menu_text_item21, menu_action, menu_action},
    {menu_text_item22, menu_action, menu_action},
    {menu_text_item23, menu_action, menu_action},
    {menu_text_item24, menu_action, menu_action},
    {menu_text_item25, menu_action, menu_action},
    {menu_text_item26, menu_action, menu_action},
    {menu_text_item27, menu_action, menu_action},
    {menu_text_item28, menu_action, menu_action},
    {menu_text_item29, menu_action, menu_action},

    {menu_text_item30, menu_action, menu_action},
    {menu_text_item31, menu_action, menu_action},

};

/**
 * @brief Creates the menu with the histogram data
 * 
 * @param deep 
 */
void menu_structure_histogram_show(uint8_t deep){
    menu_init("Histogram Data", 2, deep+1, menu_structure_histogram, menu_click);
}
