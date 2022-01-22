#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <sstream>
#include <random>
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
const int wrow_start = 1;
const int wcol_start = 0;

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

const info_window_t score  = {0,0,40,1};
const info_window_t debug1 = {25,40,40,1};
const info_window_t debug2 = {25,0,40,1};

// https://www.cs.bu.edu/fac/gkollios/cs113/Slides/lect13.pdf
eater_world::eater_world()
{
    arena_cpy.assign(arena);
}


void eater_world::get_world(std::string &background, 
                            int &row_start, int &col_start, int &rows, int &cols)
{
   background = arena;
   rows       = wrows;
   cols       = wcols;
   row_start  = wrow_start;
   col_start  = wcol_start;
}


void eater_world::get_message(int row, int col, world_message_t &wm)
{
    if((row >= (row_start+wrows)) || ((col >= (col_start+wcols)
        || (row < row_start) || (col < col_start))
        throw "eater_world::get_message value error";

    wm.c  = arena[row*wcols+col];
    wm.tl = arena[(row-1)*wcols+(col-1)];
    wm.tc = arena[(row-1)*wcols+(col+0)];
    wm.tr = arena[(row-1)*wcols+(col+1)];

    wm.cr = arena[(row-0)*wcols+(col+1)];
    wm.cl = arena[(row+0)*wcols+(col-1)];

    wm.br = arena[(row+1)*wcols+(col+1)];
    wm.bc = arena[(row+1)*wcols+(col+0)];
    wm.bl = arena[(row+1)*wcols+(col-1)];
}


void eater_world::update(const char_message_t &char_message,
                         world_message_t &world_message)
{
    int row = char_message.row - wrow_start;
    int col = char_message.col - wcol_start;
    int idx = (row*wcols+col);

    arena_cpy[idx] = char_state.replace;

    return ERROR_NONE;
}

void eater_world::get_display_info(std::vector<info_window_t> &info_window_list)
{
}

/******************************************************************************/
/******************************************************************************/

monster::monster(char_state_t initial_state)
{
    eng        = std::default_random_engine(rd());
    distr      = std::uniform_real_distribution<float>(0.0, 1.0);
    my_state   = initial_state;
    iterations = 0;
    score      = 0;
    state      = 0;
}

char_state_t monster::get_state(void)
{
//    std::cout << "monster: get_state" << std::endl;
    return my_state;
}

bool monster::eater_test(int input, eater_state_t &retdata)
{
    bool move = false;
    switch(input)
    {
        case ' ':
            move = true;
            break;
        case '*':
            retdata.inc_score = true;
            move = true;
            break;
        case 'H':
            retdata.die = true;
            move = false;
            break;
    }
    return move;
}

void monster::update_eater( const ui_t user_input, const world_state_t ws)
{
    eater_state_t retdata = {   .inc_score = false,
                                .die       = false};

//    oss << "test: " << my_state.row << ","
//                    << my_state.col << ","
//                    << ws.tc << "," 
//                    << ws.bc << "," 
//                    << ws.cl << "," 
//                    << ws.cr;
    if((user_input == UI_UP) && (eater_test(ws.tc,   retdata)))
        my_state.row = my_state.row - 1;

    if((user_input == UI_DOWN) && (eater_test(ws.bc, retdata)))
        my_state.row = my_state.row + 1;

    if((user_input == UI_LEFT) && (eater_test(ws.cl, retdata)))
        my_state.col = my_state.col - 1;

    if((user_input == UI_RIGHT) && (eater_test(ws.cr,retdata)))
        my_state.col = my_state.col + 1;

    if(retdata.inc_score == true)
    {
        score++;
    }

    if(retdata.die == true)
    {
        state = 1;
    }

}

bool monster::monster_test(int input)
{
    bool move = false;
    switch(input)
    {
        case ' ':
            move = true;
            my_state.replace = ' ';
            break;
        case '*':
            move = true;
            my_state.replace = '*';
            break;
    }
    return move;
}

void monster::update_monster( const world_state_t ws)
{
        if((monster_test(ws.tc) == true) && (distr(eng) > 0.5))
            my_state.row = my_state.row - 1;
        if((monster_test(ws.bc) == true) && (distr(eng) > 0.5))
            my_state.row = my_state.row + 1;
        if((monster_test(ws.cl) == true) && (distr(eng) > 0.5))
            my_state.col = my_state.col - 1;
        if((monster_test(ws.cr) == true) && (distr(eng) > 0.5))
            my_state.col = my_state.col + 1;
}

char_state_t monster::update_state( const ui_t user_input, 
                                    const world_state_t world_state)
{
    if(my_state.id == EATER_ID)
    {
        if(state == 0)
        {
            update_eater( user_input, world_state );
        }
        else
        {
            if(!(iterations % 8))
            {
                switch(state)
                {
                    case 1:
                        my_state.c = '^';
                        state += 1;
                        break;
                    case 2:
                        my_state.c = '>';
                        state += 1;
                        break;
                    case 3:
                        my_state.c = 'v';
                        state += 1;
                        break;
                    case 4:
                        my_state.c = '<';
                        state += 1;
                        break;
                    default:
                        state = 0;
                }
            }
        }
    }
    else
    {
        if(!(iterations % 16))
        {
            update_monster( world_state );
        }
    }

    iterations++;

    return my_state;
}

void monster::get_display_info(std::vector<info_window_t> &info_window_list)
{
    std::stringstream score_string;
    score_string << "Score: " << score;
    info_window_t score_message = {
                                    .row_start = 0,
                                    .col_start = 0,
                                    .width     = 40,
                                    .height    = 1,
                                    .message   = score_string.str()
                                  };
    std::stringstream state_string;
    state_string << "state: " << state;
    info_window_t debug_message = {
                                    .row_start = 25,
                                    .col_start = 0,
                                    .width     = 40,
                                    .height    = 1,
                                    .message   = state_string.str()
                                  };
    if(my_state.id == EATER_ID)
    {
        info_window_list.push_back(score_message);
        info_window_list.push_back(debug_message);
    }
}

