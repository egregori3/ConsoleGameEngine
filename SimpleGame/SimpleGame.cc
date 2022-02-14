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


void SimpleGame::test_collision(void)
{
    DB("Test Collision");
    std::vector<character *>::iterator it1;
    std::vector<character *>::iterator it2;
    for (it1 = characters.begin(); it1 != characters.end(); ++it1)
    {
        character *p_char1 = *it1;
        position_t char1 = p_char1->get_new_position();
        for (it2 = characters.begin(); it2 != characters.end(); ++it2)
        {
            character *p_char2 = *it2;
            if(p_char1 != p_char2)
            {
                position_t char2 = p_char2->get_new_position();
                if((char1.row == char2.row) && (char1.col == char2.col))
                {
                    p_char1->collision(char2.id);
                    p_char2->collision(char1.id);
                }
            }
        }
    }   // collision loop
}


void SimpleGame::display_text(void)
{
    DB("Display Text");
    std::vector<character *>::iterator it;
    for (it = characters.begin(); it != characters.end(); ++it)
    {
        character *p_base = *it;
        text_window_t window = p_base->get_text();
        p_graphics->write(  window.row_start, window.col_start, 
                            window.width,     window.height, 
                            window.message);
    } 
}


void SimpleGame::character_update(void)
{
    DB("Character Update");
    int debug_row = 0;
    std::vector<character *>::iterator it;
    for (it = characters.begin(); it != characters.end(); ++it)
    {
        character *p_base = *it;

        const ui_message_t ui = get_user_input();
        if(ui == UI_EXIT)
            running = false;

        if(ui == UI_PAUSE)
            paused = true;

        const position_t         pos          = p_base->get_old_position();
        const surroundings_t     surroundings = p_user_world->get_surroundings(pos.row,
                                                                               pos.col);
        const game_engine_data_t status       = p_base->update(ui, surroundings);
        if(status.debug_message.length() > 0)
        {
            p_graphics->write(status.debug_row+(debug_row++), status.debug_col,
                              80, 10, status.debug_message);
        }

        if(status.delay > 0)
            sleep(status.delay);

        if(status.game_over)
        {
           running = false;
        }
    }  
}


void SimpleGame::display_graphics(void)
{
    DB("Display Graphics");
    std::vector<character *>::iterator it;
    for (it = characters.begin(); it != characters.end(); ++it)
    {
        character *p_base = *it;
        graphic_data_t data = p_base->get_graphics(); 
        if(data.changed)
        {
            DB("Update Graphics");
            p_graphics->write(  data.new_pos.row, 
                                data.new_pos.col, 
                                data.new_pos.c);
            int background_char = p_user_world->update(data.old_pos.row, data.old_pos.col, (int)' ');
            p_graphics->write(  data.old_pos.row, 
                                data.old_pos.col, 
                                background_char);
        }
    }
    p_graphics->refresh();
}


void SimpleGame::game_loop(int loop_rate_in_ms)
{
    if((p_user_world == NULL) || (p_graphics == NULL))
        throw "SimpleGame::game_loop NULL pointer";

    DB("Entering game loop");

    while(running)
    {
        if(!paused && running)
        {
            character_update();
            test_collision();
            display_graphics();
            display_text();
        }   

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

        usleep(loop_delay*1000);
    } // Game Loop

    DB("Existing game loop");
    sleep(5);
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
    {
        // If the character ID is already registered, return error
        position_t this_char_pos = p_user_char->get_new_position();
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;
            position_t new_char_pos = p_base->get_new_position();
            if(new_char_pos.id == this_char_pos.id)
                throw "SimpleGame::add_character duplicate id's";
        }
    }
    characters.push_back(p_user_char);
}


SimpleGame::SimpleGame(world *p_world)
{
    p_user_world    = p_world;
}


void SimpleGame::start_game(int loop_rate_in_ms)
{
    std::string background;

    p_user_world->get_world(background, row_start, col_start, rows, cols);
    std::cout << "Allocating: " << (rows*cols) << std::endl;
    p_graphics = new graphics(rows, cols);
    p_graphics->write(row_start, col_start, background);
    {
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;
            const graphic_data_t data = p_base->get_graphics();
            if(data.display == true)
                p_graphics->write(data.new_pos.row, data.new_pos.col, data.new_pos.c);
        }
    }
    game_loop(loop_rate_in_ms);
}


SimpleGame::~SimpleGame()
{
    delete p_graphics;
}

