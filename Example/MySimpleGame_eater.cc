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
/*                     monster::eater private methods                         */
/*                                                                            */
/******************************************************************************/

bool monster::eater_test(const int input)
{
    bool move = false;
    switch(input)
    {
        case ' ':
            move = true;
            break;
        case '*':
            score++;
            move = true;
            break;
    }
    return move;
}

// update_message_from_engine
const debug_message_t monster::update_eater(const ui_message_t &user_input, const surroundings_t &ws)
{
    debug_message_t msg = {.valid=false};

    if(eater_state != EATING)
    {
        if(!(iterations % 32))
        {
            switch(eater_state)
            {
                case DEAD1:
                    char_write_new_pos = '^';
                    eater_state = DEAD2;
                    break;
                case DEAD2:
                    char_write_new_pos = '>';
                    eater_state = DEAD3;
                    break;
                case DEAD3:
                    char_write_new_pos = 'v';
                    eater_state = DEAD4;
                    break;
                case DEAD4:
                    char_write_new_pos = '<';
                    eater_state = EATING;
                    game_over = true;
                    break;
                default:
                    eater_state = EATING;
            }
            char_changed = true;
            
        }

        return msg;
    }

    if(ws.c == '*') char_write_old_pos = ' ';
    if((user_input == UI_UP) && (eater_test(ws.tc)))
    {
        new_row = new_row - 1;
        char_write_new_pos = 'v';
    }

    if((user_input == UI_DOWN) && (eater_test(ws.bc)))
    {
        new_row = new_row + 1;
        char_write_new_pos = '^';
    }

    if((user_input == UI_LEFT) && (eater_test(ws.cl)))
    {
        new_col = new_col - 1;
        char_write_new_pos = '>';
    }

    if((user_input == UI_RIGHT) && (eater_test(ws.cr)))
    {
        new_col = new_col + 1;
        char_write_new_pos = '<';
    }

    return msg;
}


const debug_message_t monster::collision_eater(int col_id)
{
    debug_message_t msg = {.valid = true};
    std::string info = std::string("collision: ") + std::to_string(id) + ", " + std::to_string(col_id);
    if(eater_state == EATING)
        eater_state = DEAD1;
    delay_engine = 1;
    msg.debug_message = info;
    return msg;
}

