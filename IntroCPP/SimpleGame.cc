// For a full list of resources see:
// https://github.com/egregori3/ConsoleGameEngine/blob/master/README.md

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <cstring>
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


void SimpleGame::init_collision(void)
{
    std::vector<character *>::iterator it;
//    std::cout << "init collision: " << (rows*cols) << std::endl;
    memset(collision_array, 0, (rows*cols)*sizeof(int));
    for (it = characters.begin(); it != characters.end(); ++it)
    {
        character *p_base = *it;
        char_message_t char_message;
        p_base->message_to_engine(char_message); // fill out char_message
        int row = char_message.row;
        int col = char_message.col;
        int id  = char_message.id;
        uint32_t idx = ((row - row_start)*cols+(col - col_start));
//        std::cout << "idx: " << idx << std::endl;
        collision_array[idx] = id;
    }
}


bool SimpleGame::check_collision(int row, int col, int &id)
{
    uint32_t idx = ((row - row_start)*cols+(col - col_start));
    if(collision_array[idx] != 0)
    {
        id = collision_array[idx];
        return true;
    }

    return false;
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
        init_collision();
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;
            char_message_t  old_char_message;
            char_message_t  new_char_message;
            world_message_t world_message;
            bool updated;

            {   // Get current state of the game
                p_base->message_to_engine(old_char_message);
                p_user_world->tx_message_to_engine(old_char_message.row, 
                                                   old_char_message.col,
                                                   world_message);
            }

            {   // Update character
                ui_message_t ui = get_user_input();
                if(ui == UI_EXIT)
                    running = false;

                if(ui == UI_PAUSE)
                    paused = true;

                p_base->update_message_from_engine((const ui_message_t)ui, 
                        (const world_message_t)world_message, updated); // send message to characer
            }

            {   // Collision detection with updated character info
                int id;
                p_base->message_to_engine(new_char_message);
                if(check_collision(new_char_message.row, new_char_message.col, id))
                {
                    p_base->collision_message_from_engine(new_char_message, id);
                }
            }

            // Get display info from character
            p_base->get_display_info(info_window_list);

            // Graphics
            if(updated && !paused)
            {
                p_user_world->update_message_from_engine((const char_message_t)new_char_message);
                p_graphics->write(new_char_message.row, 
                                  new_char_message.col, 
                                  new_char_message.c);
                if((new_char_message.row != old_char_message.row) ||
                   (new_char_message.col != old_char_message.col))
                {
                    p_graphics->write(old_char_message.row, 
                                  old_char_message.col, 
                                  (new_char_message.replace>0)?new_char_message.replace:world_message.c);
                }
                p_graphics->refresh();
            }
        } // Character loop

        p_user_world->get_display_info(info_window_list);
        update_info_display(info_window_list, p_graphics);

        // Pause
        while(paused && running)
        {
            ui_message_t ui = get_user_input(); 
            if(ui == UI_EXIT)
                running = false;

            if(ui == UI_PAUSE)
            {
                sleep(1);
                paused = false;
            }
        }

        usleep(loop_rate_in_ms*1000);
    } // Game Loop
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
    p_user_world    = p_world;
    loop_rate_in_ms = loop_rate;
}

void SimpleGame::start_game(void)
{
    std::string background;
    p_user_world->get_world(background, row_start, col_start, rows, cols);
    std::cout << "Allocating: " << (rows*cols) << std::endl;
    collision_array = (int *)calloc((rows*cols),sizeof(int));
    if(collision_array == NULL)
        throw "Falied to allocate collision memory";
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

