#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <sstream>
#include <random>
#include <unistd.h>
#include <set>
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


const int wrows                 = 21;
const int wcols                 = 40;
const int wrow_start            = 1;
const int wcol_start            = 0;
const int collision_debug_row   = 25;
const int update_debug_row      = 32;

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


/******************************************************************************/
/*                                                                            */
/*                         eater_world public methods                         */
/*                                                                            */
/******************************************************************************/

eater_world::eater_world()
{
    arena_cpy.assign(arena);
    world_data.background_rows       = wrows;
    world_data.background_cols       = wcols;
    world_data.background_start_row  = wrow_start;
    world_data.background_start_col  = wcol_start;
    world_data.collision_debug_row   = collision_debug_row;
    world_data.update_debug_row      = update_debug_row;
}


void eater_world::get_world(std::string &background, world_data_t &wd)
{
   background    = arena;
   wd            = world_data;
}


const surroundings_t eater_world::get_surroundings(int lrow, int lcol)
{
    if((lrow < wrow_start) || (lrow >= (wrow_start+wrows)))
    {
        std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) + " "
            + ROW_ERROR + "row: " + std::to_string(lrow);
        throw std::range_error(msg);
    }
    if((lcol < wcol_start) || (lcol >= (wcol_start+wcols)))
    {
        std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) + " "
            + COL_ERROR + "col: " + std::to_string(lcol);
        throw std::range_error(msg);
    }

    int row = lrow - wrow_start;
    int col = lcol - wcol_start;

    surroundings_t wm;
    // Fill out message
    wm.c  = arena_cpy[row*wcols+col];
    wm.tl = arena_cpy[(row-1)*wcols+(col-1)];
    wm.tc = arena_cpy[(row-1)*wcols+(col+0)];
    wm.tr = arena_cpy[(row-1)*wcols+(col+1)];

    wm.cr = arena_cpy[(row-0)*wcols+(col+1)];
    wm.cl = arena_cpy[(row+0)*wcols+(col-1)];

    wm.br = arena_cpy[(row+1)*wcols+(col+1)];
    wm.bc = arena_cpy[(row+1)*wcols+(col+0)];
    wm.bl = arena_cpy[(row+1)*wcols+(col-1)];

    return wm;
}


const int eater_world::update(int lrow, int lcol, int lc)
{
    int row = lrow - wrow_start;
    int col = lcol - wcol_start;
    const int c = (const int)arena_cpy[row*wcols+col];

    arena_cpy[row*wcols+col] = lc;

    // return background character for old position
    return c;
}


/******************************************************************************/
/*                                                                            */
/*                         monster public methods                             */
/*                                                                            */
/******************************************************************************/

monster::monster(int lid, int lrow, int lcol, int lc, bool ldisplay)
{
    id         = lid;
    new_row    = lrow;
    new_col    = lcol;
    new_c      = lc;
    old_row    = lrow;
    old_col    = lcol;
    old_c      = lc;
    display    = ldisplay;

    eng        = std::default_random_engine(rd());
    distr      = std::uniform_real_distribution<float>(0.0, 1.0);
    old_motion = (distr(eng) > 0.5)?RIGHT:LEFT;
}


const position_t monster::get_new_position(void)
{
    const position_t data = {.id=id, .row=new_row, .col=new_col, .c=new_c};
    return data;
}


const position_t monster::get_old_position(void)
{
    const position_t data = {.id=id, .row=old_row, .col=old_col, .c=old_c};
    return data;
}


const graphic_data_t monster::get_graphics(void)
{
    if(    (old_row < wrow_start) || (old_row >= (wrow_start+wrows))
        || (old_col < wcol_start) || (old_col >= (wcol_start+wcols)))
    {
        std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) + " "
            + ROW_ERROR + COL_ERROR
            + "old_row: " + std::to_string(old_row)
            + ", old_col: " + std::to_string(old_col);
        throw std::range_error(msg);
    }
    if(    (new_row < wrow_start) || (new_row >= (wrow_start+wrows))
        || (new_col < wcol_start) || (new_col >= (wcol_start+wcols)))
    {
        std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) + " "
            + ROW_ERROR + COL_ERROR
            + "new_row: " + std::to_string(new_row)
            + ", new_col: " + std::to_string(new_col);
        throw std::range_error(msg);
    }

    graphic_data_t data = {
                                .id          = id,
                                .display     = display,
                                .changed     = false,
                                {.id = id, .row = old_row, .col = old_col, .c = old_c},
                                {.id = id, .row = new_row, .col = new_col, .c = new_c},
                           };

    if((old_row != new_row) || (old_col != new_col) || (old_c != new_c))
    {
        data.changed = true;
        old_row = new_row;
        old_col = new_col;
        old_c   = new_c;
    }

    return data;
}


const text_window_t monster::get_text(void)
{
    std::stringstream   message_string;
    text_window_t       message_window;

    if(game_over)
    {
        message_string << "Game Over";
        message_window = {
                            .row_start = wrows+wrow_start+1,
                            .col_start = 0,
                            .width     = 40,
                            .height    = 1,
                            .message   = message_string.str()
                         };
        return message_window;
    }

    switch(iterations % 4)
    {
        case 0:
            message_string << "Score: " << score;
            message_window = {
                                .row_start = 0,
                                .col_start = 0,
                                .width     = 40,
                                .height    = 1,
                                .message   = message_string.str()
                             };
            break;

    }

    return message_window;
}


const debug_message_t monster::collision(int id)
{
    debug_message_t debug_message;

    if(id == EATER_ID)
    {
        debug_message = collision_eater(id);
    }
    else
    {
        debug_message = collision_monster(id);
    }

    return debug_message;
}


const debug_message_t monster::update(const ui_message_t &user_input,
                                     const surroundings_t &surroundings)
{
    debug_message_t msg;

    if(id == EATER_ID)
    {
        msg = update_eater(user_input, surroundings);
    }
    else
    {
        msg = update_monster(surroundings);
    }

    iterations++;

    return msg;
}


const engine_loop_t monster::get_loop_delay(void)
{
    const engine_loop_t retval = {.delay=50, .game_over=false};
    return retval;
}


