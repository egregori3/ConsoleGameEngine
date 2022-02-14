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
    replace = ' ';
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
void monster::update_eater(const ui_message_t &user_input, const surroundings_t &ws)
{
    if(eater_state != EATING)
    {
        if(!(iterations % 32))
        {
            switch(eater_state)
            {
                case DEAD1:
                    new_c = '^';
                    eater_state = DEAD2;
                    break;
                case DEAD2:
                    new_c = '>';
                    eater_state = DEAD3;
                    break;
                case DEAD3:
                    new_c = 'v';
                    eater_state = DEAD4;
                    break;
                case DEAD4:
                    new_c = '<';
                    eater_state = EATING;
                    game_over = true;
                    break;
                default:
                    eater_state = EATING;
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
        new_row = old_row - 1;
        new_c = 'v';
    }

    if((user_input == UI_DOWN) && (eater_test(ws.bc)))
    {
        new_row = old_row + 1;
        new_c = '^';
    }

    if((user_input == UI_LEFT) && (eater_test(ws.cl)))
    {
        new_col = old_col - 1;
        new_c = '>';
    }

    if((user_input == UI_RIGHT) && (eater_test(ws.cr)))
    {
        new_col = old_col + 1;
        new_c = '<';
    }
}


void monster::collision_eater(int col_id)
{
    debug_message += "collision: " + std::to_string(id) + ", " + std::to_string(col_id);
    if(eater_state == EATING)
        eater_state = DEAD1;
    delay_engine = 1;
}

