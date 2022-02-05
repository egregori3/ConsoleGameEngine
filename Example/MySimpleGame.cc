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

const info_window_message_t score  = {0,0,40,1};
const info_window_message_t debug1 = {25,40,40,1};
const info_window_message_t debug2 = {25,0,40,1};


/******************************************************************************/
/*                                                                            */
/*                         eater_world public methods                         */
/*                                                                            */
/******************************************************************************/

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


void eater_world::tx_message_to_engine(int lrow, int lcol, world_message_t &wm)
{
    if((lrow >= (wrow_start+wrows)) || (lcol >= (wcol_start+wcols))
        || (lrow < wrow_start) || (lcol < wcol_start))
        throw "eater_world::get_message value error";

    int row = lrow - wrow_start;
    int col = lcol - wcol_start;

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
}


void eater_world::update_message_from_engine(const char_message_t &char_message)
{
    int row = char_message.row - wrow_start;
    int col = char_message.col - wcol_start;
    int idx = (row*wcols+col);

    if(char_message.replace > 0)
        arena_cpy[idx] = char_message.replace;
}


void eater_world::get_display_info(std::vector<info_window_message_t> &info_window_list)
{
}


/******************************************************************************/
/*                                                                            */
/*                         monster public methods                             */
/*                                                                            */
/******************************************************************************/

monster::monster(int lid, int lrow, int lcol, int lc, bool ldisplay)
{
    eng        = std::default_random_engine(rd());
    distr      = std::uniform_real_distribution<float>(0.0, 1.0);
    id         = lid;
    row        = lrow;
    col        = lcol;
    c          = lc;
    iterations = 0;
    score      = 0;
    state      = 0;
    replace    = 0;
    game_over  = false;
    display    = ldisplay;
    old_motion = NONE;
}


void monster::message_to_engine(char_message_t &char_message)
{
//    std::cout << "monster: get_state" << std::endl;
    // Create message
    char_message.id        = id;        // id of character - the user can use for whatever they want
    char_message.row       = row;       // row position of character
    char_message.col       = col;       // col position of character
    char_message.c         = c;         // character to display
    char_message.replace   = replace;   // character to put into old position
    char_message.display   = display;   // set to true to display the character
    char_message.game_over = game_over; // set to end the game
}


void monster::update_message_from_engine(const ui_message_t &user_input, 
                                         const world_message_t &world_message,
                                         bool &updated)
{
    bool update = false;

    if(id == EATER_ID)
    {
        update_eater(user_input, world_message, update);
    }
    else
    {
        update_monster(world_message, update);
    }

    iterations++;
    updated = update;
}


void monster::get_display_info(std::vector<info_window_message_t> &info_window_list)
{
    std::stringstream score_string;
    score_string << "Score: " << score;
    info_window_message_t score_message = {
                                    .row_start = 0,
                                    .col_start = 0,
                                    .width     = 40,
                                    .height    = 1,
                                    .message   = score_string.str()
                                  };
    std::stringstream state_string;
    state_string << "state: " << state << "  row: " << row << "  col: " << col << "   die: " << die;
    info_window_message_t info_message = {
                                    .row_start = 25,
                                    .col_start = 0,
                                    .width     = 40,
                                    .height    = 1,
                                    .message   = state_string.str()
                                  };
    if(id == EATER_ID)
    {
        info_window_list.push_back(score_message);
        info_window_list.push_back(info_message);
    }
    else
    {
        int row = 26;
        while (!debug_message.empty())
        {
            std::string message_string = debug_message.back();
            info_window_message_t message = {
                                                .row_start = (5*(id-GHOST_ID))+row,
                                                .col_start = 0,
                                                .width     = 80,
                                                .height    = 1,
                                                .message   = message_string.c_str()
                                            };
            info_window_list.push_back(message);
            debug_message.pop_back();
            row++;
        }
    }
}


void monster::collision_message_from_engine(char_message_t &char_message, int id)
{
    die   = true;
    if(state == 0)
        state = 1;
}


/******************************************************************************/
/*                                                                            */
/*                     monster::eater private methods                         */
/*                                                                            */
/******************************************************************************/

bool monster::eater_test(const int input)
{
    bool move = false;
    replace = ' ';
    switch(input)
    {
        case ' ':
            move = true;
            break;
        case '*':
            inc_score = true;
            move = true;
            break;
    }
    return move;
}

void monster::update_eater( const ui_message_t user_input, const world_message_t ws, bool &update)
{
    if(state != 0)
    {
        if(!(iterations % 32))
        {
            update = true;
            switch(state)
            {
                case 1:
                    c = '^';
                    state += 1;
                    break;
                case 2:
                    c = '>';
                    state += 1;
                    break;
                case 3:
                    c = 'v';
                    state += 1;
                    break;
                case 4:
                    c = '<';
                    state += 1;
                    break;
                default:
                    state = 0;
            }
        }

        return;
    }

//    oss << "test: " << my_state.row << ","
//                    << my_state.col << ","
//                    << ws.tc << "," 
//                    << ws.bc << "," 
//                    << ws.cl << "," 
//                    << ws.cr;
    if((user_input == UI_UP) && (eater_test(ws.tc)))
    {
        row = row - 1;
        update = true;
        c = 'v';
    }

    if((user_input == UI_DOWN) && (eater_test(ws.bc)))
    {
        row = row + 1;
        update = true;
        c = '^';
    }

    if((user_input == UI_LEFT) && (eater_test(ws.cl)))
    {
        col = col - 1;
        update = true;
        c = '>';
    }

    if((user_input == UI_RIGHT) && (eater_test(ws.cr)))
    {
        col = col + 1;
        update = true;
        c = '<';
    }

    if(inc_score == true)
    {
        score++;
        inc_score = false;
    }

    if((die == true) && (state == 0))
    {
        state = 1;
    }

}


/******************************************************************************/
/*                                                                            */
/*                     monster::ghost private methods                         */
/*                                                                            */
/******************************************************************************/


/*
    Test if it is OK to move based on the ascii character (input).
    The ghost can move into positions containing ascii characters: ' ' or '*'.
    Setting replace to 0 tells the engine to disable background changes.
 */
bool monster::monster_test(const int input)
{
    bool move = false;
    replace = 0;
    switch(input)
    {
        case ' ':
            move = true;
            break;
        case '*':
            move = true;
            break;
    }
    return move;
}


std::string decode_motion(motion_t in)
{
    switch(in)
    {
        case UP:    return "up, ";
        case DOWN:  return "down, ";
        case LEFT:  return "left, ";
        case RIGHT: return "right, ";
    }

    return "error, ";
}

/*
    
 */
void monster::update_monster(const world_message_t ws, bool &update)
{
    std::string debug = "ID: " + std::to_string(id) + ", ";

    // https://www.geeksforgeeks.org/set-find-function-in-c-stl/
    // https://www.cplusplus.com/reference/set/set/
    std::set<motion_t> available_motion_list;

    if(iterations % 16)
    {
        return; // Only update the ghost's position once every 16 calls
    }

    if(monster_test(ws.tc) == true)
    {
        available_motion_list.insert(UP);
        debug += "up, ";
    }
    if(monster_test(ws.bc) == true)
    {
        available_motion_list.insert(DOWN);
        debug += "down, ";
    }
    if(monster_test(ws.cl) == true)
    {
        available_motion_list.insert(LEFT);
        debug += "left, ";
    }
    if(monster_test(ws.cr) == true)
    {
        available_motion_list.insert(RIGHT);
        debug += "right, ";
    }

    if(old_motion != NONE)
    {
        // https://www.geeksforgeeks.org/set-find-function-in-c-stl/
        // https://www.cplusplus.com/reference/set/set/find/
        // If we cannot find old_motion in the set, we need to find another motion
        if(available_motion_list.find(old_motion) != available_motion_list.end())
        {
            old_motion = NONE;
        }
    }
    

    if(old_motion == NONE)
    {
        float start_slot = 0.0;
        float slot_size  = 1.0 / available_motion_list.size();
        float r_slot     = distr(eng);
        std::set<motion_t>::iterator itr;
        for(itr = available_motion_list.begin(); itr != available_motion_list.end(); itr++)
        {
            if((r_slot>=start_slot) && (r_slot<(start_slot + slot_size)))
            {
                old_motion = *itr;
                break;
            }
            start_slot += slot_size;
        }
        debug += "new, ";
    }

    debug += "[";
    debug += decode_motion(old_motion);
    debug += "], ";

    debug += "(";
    debug += std::to_string(row);
    debug += ", ";
    debug += std::to_string(col);
    debug += ")";

    update = true;
    switch(old_motion)
    {
        case UP:
            row = row - 1;
            break;
        case DOWN:
            row = row + 1;
            break;
        case LEFT:
            col = col - 1;
            break;
        case RIGHT:
            col = col + 1;
            break;
    }

    debug_message.push_back(debug);
}


