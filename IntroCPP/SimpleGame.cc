// For a full list of resources see:
// https://github.com/egregori3/ConsoleGameEngine/blob/master/README.md

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <unistd.h>
#include "interfaces.h"
#include "SimpleGame.h"
#include "graphics.h"


void update_info_display(std::vector<info_window_message_t> &info_window_list, graphics *p_graphics)
{
        std::vector<info_window_message_t>::iterator it;
        for (it = info_window_list.begin(); it != info_window_list.end(); ++it)
        {
            info_window_message_t info_window = *it;
            p_graphics->write(  info_window.row_start, info_window.col_start, 
                                info_window.width,     info_window.height, 
                                info_window.message);
        }

        info_window_list.clear();
}

void SimpleGame::game_loop(void)
{
    if((p_user_world == NULL) || (p_graphics == NULL))
        throw "SimpleGame::game_loop NULL pointer";

    std::vector<info_window_message_t> info_window_list;
    for(bool running=true; running; )
    {
        // https://limbioliong.wordpress.com/2012/12/25/storing-c-objects-in-a-stl-vector-part-2/
        // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch06s05.html
        // https://www.dreamincode.net/forums/topic/63358-store-class-objects-in-vector/
        // https://linuxhint.com/use_cpp_vector/
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;
            char_message_t  char_message;
            world_message_t world_message;
            bool updated;

            p_base->message_to_engine(char_message); // fill out char_message
            p_user_world->tx_message_to_engine(char_message.row, char_message.col,world_message);
            const ui_message_t ui = get_user_input();
            if(ui == UI_EXIT)
                running = false;

            p_base->update_message_from_engine(ui, world_message, updated); // send message to characer
            if(updated)
            {
                char_message_t new_char_message; // Get updated message from character
                p_base->message_to_engine(new_char_message); // fill out char_message
                p_user_world->update_message_from_engine((const char_message_t)new_char_message);
                p_graphics->write(new_char_message.row, new_char_message.col, new_char_message.c);
                p_graphics->refresh();
            }
            p_base->get_display_info(info_window_list);
        }
        p_user_world->get_display_info(info_window_list);
        update_info_display(info_window_list, p_graphics);


        usleep(loop_rate_in_ms*1000);
    }
}

ui_message_t SimpleGame::get_user_input(void)
{
    ui_message_t result = UI_NONE;
//    std::cout << "SimpleGame: get_user_input" << std::endl;
    result = p_graphics->get_input();
    return result;
}


void SimpleGame::add_character(character *p_user_char)
{
    // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch06s05.html

    char_message_t new_char;
    p_user_char->message_to_engine(new_char);
    {
        // If the character ID is already registered, return error
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;
            char_message_t old_char;
            p_base->message_to_engine(old_char);
            if(new_char.id == old_char.id)
                throw "SimpleGame::add_character duplicate id's";
        }
    }
    characters.push_back(p_user_char);
}

SimpleGame::SimpleGame(world *p_world, int loop_rate)
{
    p_user_world = p_world;
    loop_rate_in_ms = loop_rate;
}

void SimpleGame::start_game(void)
{
    std::string background;
    int rows;
    int cols;
    int row_start;
    int col_start;

    p_user_world->get_world(background, row_start, col_start, rows, cols);
    p_graphics = new graphics(rows, cols);
    p_graphics->write(row_start, col_start, background);
    {
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;
            char_message_t init;
            p_base->message_to_engine(init);
            if(init.display == true)
                p_graphics->write(init.row, init.col, init.c);
        }
    }
    game_loop();
}

SimpleGame::~SimpleGame()
{
    delete p_graphics;
}

