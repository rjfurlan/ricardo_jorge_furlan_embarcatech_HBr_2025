/**
 * @file    play.h
 * @author  Ricardo J. Furlan
 * @brief   Displays or runs the Galton Board in various modes
 * @version 0.1
 * @date    2025-05-09
 */
#ifndef PLAY_H
#define PLAY_H


#include "gb_structure.h"

/**
 * @brief Shows a static Galton Board for reference
 * 
 * @param gb_structure 
 * @param draw_balls 
 */
void play_demo(  GbStructure gb_structure, bool draw_balls);

/**
 * @brief Run the Galton Board in Hypersonic mode
 * 
 * @param gb_structure 
 */
void play_hyper( GbStructure gb_structure);

/**
 * @brief Run the Galton Board in Normal mode
 * 
 * @param gb_structure 
 */
void play_normal(GbStructure gb_structure);


/**
 * @brief Run the search model
 * 
 * @param gb_structure 
 */
void play_search(GbStructure * gb_structure);



#endif // PLAY_H
