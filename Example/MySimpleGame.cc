#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <sstream>
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

const int wrows = 21;
const int wcols = 40;
const std::string arena =
  // 0         1         2         3        3
  // 0123456789012345678901234567890123456789
    "|======================================|" // 00
    "|* * * * * * * *  *|* * * * * * * * * *|" // 01
    "|*|======|*|=====|*|*|=====|*|=======|*|" // 02
    "|* * * *  * * * * * * * * * * * * * * *|" // 03
    "|*|======|*|=|*|=======|*|=|*|=======|*|" // 04
    "|* * * *  *|=|*  *|=|*  *|=|* * * * * *|" // 05
    "|========|*|====|*|=|*|====|*|=========|" // 06
    "         |*|=|*  * * *  *|=|*|          " // 07
    "|========|*|=|*|=======|*|=|*|=========|" // 08
    "* * * * * * * *|       |* * * * * * * * " // 09
    "|========|*|=|*|=======|*|=|*|=========|" // 10
    "         |*|=|* * * * * *|=|*|          " // 11
    "|========|*|=|*|=======|*|=|*|=========|" // 12
    "|* * * *  * * *  *|=|*  * * * * * * * *|" // 13
    "|*|======|*|====|*|=|*|====|*|=======|*|" // 14
    "|*  * *|=|* * *  *   * * *  *|=|* * * *|" // 15
    "|====|*|=|*|=|*|=======|*|=|*|=|*|=====|" // 16
    "|* *  * * *|=|*  *|=|*  *|=|* * * * * *|" // 17
    "|*|=============|*|=|*|==============|*|" // 18
    "|* * * * * * * * * * * * * * * * * *  *|" // 19
    "|======================================|";// 20

const info_window_t debug1 = {25,40,40,1};
const info_window_t debug2 = {25,0,40,1};

// https://www.cs.bu.edu/fac/gkollios/cs113/Slides/lect13.pdf
eater_world::eater_world()
{
}

error_code_t eater_world::get_world(std::string &background, int &rows, int &cols)
{
   background = arena;
   rows       = wrows;
   cols       = wcols;

   return ERROR_NONE;
}

const world_state_t eater_world::get_state(const char_state_t char_state)
{
    world_state_t ws;
    int row = char_state.row;
    int col = char_state.col;

    ws.c  = arena[row*wrows+col];
    ws.tl = arena[(row-1)*wcols+(col-1)];
    ws.tc = arena[(row-1)*wcols+(col+0)];
    ws.tr = arena[(row-1)*wcols+(col+1)];

    ws.cr = arena[(row-0)*wcols+(col+1)];
    ws.cl = arena[(row+0)*wcols+(col-1)];

    ws.br = arena[(row+1)*wcols+(col+1)];
    ws.bc = arena[(row+1)*wcols+(col+0)];
    ws.bl = arena[(row+1)*wcols+(col-1)];

    return ws;
}

error_code_t eater_world::update_state(const char_state_t char_state)
{
        return ERROR_NONE;
}

bool eater_world::get_display_info(info_window_t **pp_iw, std::string &message)
{
    *pp_iw = (info_window_t *)&debug1;
    message = oss.str();
    oss.str("");
    return false;
}

/******************************************************************************/
/******************************************************************************/

monster::monster(char_state_t initial_state)
{
    my_state   = initial_state;
    iterations = 0;
}

char_state_t monster::get_state(void)
{
//    std::cout << "monster: get_state" << std::endl;
    return my_state;
}

bool pok(int input)
{
    if((input == ' ') || (input == '*')) return true;
    return false;
}

void monster::update_eater( const ui_t user_input, const world_state_t ws)
{
    oss << "test: " << my_state.row << ","
                    << my_state.col << ","
                    << ws.tc << "," 
                    << ws.bc << "," 
                    << ws.cl << "," 
                    << ws.cr;
    if((user_input == UI_UP) && (pok(ws.tc)))
        my_state.row = my_state.row - 1;

    if((user_input == UI_DOWN) && (pok(ws.bc)))
        my_state.row = my_state.row + 1;

    if((user_input == UI_LEFT) && (pok(ws.cl)))
        my_state.col = my_state.col - 1;

    if((user_input == UI_RIGHT) && (pok(ws.cr)))
        my_state.col = my_state.col + 1;

}

void monster::update_monster( const world_state_t world_state)
{
    if((iterations % 20) == 0)
    {
    }
}

char_state_t monster::update_state( const ui_t user_input, 
                                    const world_state_t world_state)
{
//    std::cout << "monster: update_state" << std::endl;
    if(my_state.id == EATER_ID)
    {
        update_eater( user_input, world_state );
    }
    else
    {
        update_monster( world_state );
    }

    iterations++;

    return my_state;
}

bool monster::get_display_info(info_window_t **pp_iw, std::string &message)
{
    *pp_iw = (info_window_t *)&debug2;
    oss.clear();
    message = oss.str();
    oss.str("");
    if(my_state.id == EATER_ID)
        return true;
    return false;
}

