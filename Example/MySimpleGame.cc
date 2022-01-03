#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "interfaces.h"
#include "SimpleGame.h"
#include "MySimpleGame.h"


/******************************************************************************
 * @file   MyCustomGame                                                       *
 * @author Eric Gregori -  https://github.com/egregori3                       *
 * @data   12/21                                                              *
 *                                                                            *
 * @brief                                                                     *
 *  An example of how to use the SimpleGame class.                            *
 *                                                                            *
 * @section PURPOSE                                                           *
 *  The internet provides a wealth of valuable resources for a student        *
 *  learning object-oriented programming. This projected started as a resource*
 *  guide with the goal of connecting students to on-line resources:          *
 *  https://github.com/egregori3/C-Plus-Plus_Article                          *
 *                                                                            *
 *  Student feedback about the on-line resources indicated a need for better  *
 *  "more interesting" examples. That feedback drove this project.            *
 *  The code for this project was written to demonstrate various aspects of   *
 *  C++ and OOP, not necassarily to demonstrate best programming practices.   *
 *  In some cases, I know I swayed from best practices in order to demonstrate*
 *  as many C++ and OOP techniques as possible. I note these decisions in the *
 *  comments. When selecting resources to reference, the goal is quality and  *
 *  variety (exposing the students to as many resources as possible).         *
 *                                                                            *
 * @section DESCRIPTION                                                       *
 *                                                                            *
 *  SimpleGame game loop                                                      *
 *   Init:                                                                    *
 *      call world.init_world() with background string and size               *
 *   Loop:                                                                    *
 *      for each character:                                                   *
 *          call char_state  = character.get_state()                          *
 *          call world_state = world.get_state(char_state)                    *
 *          call new_char_state = character.update_state(ui, world_state)     *
 *          call world.update_state(new_char_state)                           *
 *                                                                            *
 *                                                                            *
 * @section HISTORY                                                           *
 *  12/21 Eric Gegori - File created                                          *
 *                                                                            *
 * @section SOURCES                                                           *
 *  @see https://www.cs.bu.edu/                                               *
 ******************************************************************************/


const std::string arena =
  // 0         1         2         3        3
  // 0123456789012345678901234567890123456789
    "|======================================|" // 00
    "|                  |                   |" // 01
    "| |======| |=====| | |=====| |=======| |" // 02
    "|                                      |" // 03
    "| |======| |=| |=======| |=| |=======| |" // 04
    "|          |=|    |=|    |=|           |" // 05
    "|========| |====| |=| |====| |=========|" // 06
    "         | |=|           |=| |          " // 07
    "|========| |=| |=======| |=| |=========|" // 08
    "               |       |                " // 09
    "|========| |=| |=======| |=| |=========|" // 10
    "         | |=|           |=| |          " // 11
    "|========| |=| |=======| |=| |=========|" // 12
    "|                 |=|                  |" // 13
    "| |======| |====| |=| |====| |=======| |" // 14
    "|      |=|                   |=|       |" // 15
    "|====| |=| |=| |=======| |=| |=| |=====|" // 16
    "|          |=|    |=|    |=|           |" // 17
    "| |=============| |=| |==============| |" // 18
    "|                                      |" // 19
    "|======================================|";// 20


// https://www.cs.bu.edu/fac/gkollios/cs113/Slides/lect13.pdf
eater_world::eater_world()
{
    std::cout << "eater_world: constructor" << std::endl;
}

error_code_t eater_world::get_world(std::string &background, int &rows, int &cols)
{
   std::cout << "eater_world: get_world" << std::endl;
   background = arena;
   rows       = 21;
   cols       = 40;

   return ERROR_NONE;
}

const world_state_t eater_world::get_state(const char_state_t char_state)
{
//        std::cout << "eater_world: get_state" << std::endl;
        ws.row = char_state.row;
        ws.col = char_state.col;
        ws.upper_left_constraint    = 0;
        ws.upper_middle_constraint  = 0;
        ws.upper_right_constraint   = 0;
        ws.middle_left_constraint   = 0;
        ws.character                = char_state.c;
        ws.lower_left_constraint    = 0;
        ws.lower_middle_constraint  = 0;
        ws.lower_right_constraint   = 0;

    return ws;
}

error_code_t eater_world::update_state(const char_state_t char_state)
{
//        std::cout << "eater_world: update_state" << std::endl;
        ws.row          = char_state.row;
        ws.col          = char_state.col;
        ws.character    = char_state.c;

        return ERROR_NONE;
}

monster::monster(char_state_t initial_state)
{
    std::cout << "monster: constructor" << std::endl;
    my_state = initial_state;
}

char_state_t monster::get_state(void)
{
//    std::cout << "monster: get_state" << std::endl;
    return my_state;
}

char_state_t monster::update_state( const ui_t user_input, 
                           const world_state_t world_state)
{
//    std::cout << "monster: update_state" << std::endl;
    if(my_state.id == EATER_ID)
    {
        if((user_input == UI_UP))
            my_state.row = my_state.row - 1;
        else if((user_input == UI_DOWN))
            my_state.row = my_state.row + 1;
        else if((user_input == UI_LEFT))
            my_state.col = my_state.col - 1;
        else if((user_input == UI_RIGHT))
            my_state.col = my_state.col + 1;
    }

    return my_state;
}



