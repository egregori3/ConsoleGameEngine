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

// update_message_from_engine
const debug_message_t monster::update_monster(const surroundings_t &ws)
{
    debug_message_t msg = {.valid = false};
    std::string debug;

    char_write_old_pos = ws.c;

    // https://www.geeksforgeeks.org/set-find-function-in-c-stl/
    // https://www.cplusplus.com/reference/set/set/
    std::set<motion_t> available_motion_list;

    DB6("Update Ghost: "<<iterations);
    if(iterations % 16)
    {
        return msg; // Only update the ghost's position once every 16 calls
    }

    DB6("Update Ghost position");
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
        if(available_motion_list.find(old_motion) == available_motion_list.end())
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
    debug += std::to_string(old_row);
    debug += ", ";
    debug += std::to_string(old_col);
    debug += ", ";
    debug += std::to_string(char_write_old_pos);
    debug += ")";

    // Save current position
    old_row = new_row;
    old_col = new_col;

    switch(old_motion)
    {
        case UP:
            new_row = new_row - 1;
            break;
        case DOWN:
            new_row = new_row + 1;
            break;
        case LEFT:
            new_col = new_col - 1;
            break;
        case RIGHT:
            new_col = new_col + 1;
            break;
    }

    debug += "(";
    debug += std::to_string(new_row);
    debug += ", ";
    debug += std::to_string(new_col);
    debug += ", ";
    debug += std::to_string(char_write_new_pos);
    debug += ")";

    msg.valid = true;
    msg.debug_message = debug;

    return msg;
}


const debug_message_t monster::collision_monster(int col_id)
{
    debug_message_t msg = {.valid = false};
    return msg;
}
