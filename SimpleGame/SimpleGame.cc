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


static char spinner(int loop_count)
{
    switch(loop_count % 4)
    {
        case 0:
            return '|';
        case 1:
            return '/';
        case 2:
            return '-';
        case 3:
            return '\\';
    }

    return '*';
}


int SimpleGame::test_collision(void)
{
    DB4("Test Collision");
    int row_adder = 0;
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
                    debug_message_t msg = p_char1->collision(char2.id);
                    if(msg.valid && !msg.debug_message.empty())
                    {
                        GRAPHIC_WRITE(world_data.collision_debug_row+(row_adder++), 0,
                                      msg.debug_message);
                    }
                }
            }
        }
    }   // collision loop
#if TEST_COLLISION_ROW > 0
    std::string msg = "Test Collision ";
    msg += "(";
    msg += spinner(loop_count); 
    msg += ")";
    p_graphics->write(TEST_COLLISION_ROW, 0, 80, 10, msg);
#endif
    return 0;
}


int SimpleGame::display_text(void)
{
    DB3("Display Text");
    std::vector<character *>::iterator it;
    for (it = characters.begin(); it != characters.end(); ++it)
    {
        character *p_base = *it;
        text_window_t window = p_base->get_text();
        if(window.valid)
        {
            if(p_graphics->write(  window.row_start, window.col_start, 
                                   window.width,     window.height, 
                                   window.message) < 0)
                return -1;
        }
    } 
#if DISPLAY_TEXT_ROW > 0
    std::string msg = "Display Text ";
    msg += "(";
    msg += spinner(loop_count); 
    msg += ")";
    p_graphics->write(DISPLAY_TEXT_ROW, 0, 80, 10, msg);
#endif
    return 0;
}


int SimpleGame::character_update(void)
{
    DB2("Character Update entry");
    int debug_row = 0;
    loop_delay    = 50;
    std::vector<character *>::iterator it;
    for (it = characters.begin(); it != characters.end(); ++it)
    {
        character *p_base = *it;

        const ui_message_t ui = get_user_input();
        if(ui == UI_EXIT)
            running = false;

        if(ui == UI_PAUSE)
            paused = true;

        DB2("user input: "<<ui<<" paused: "<<paused<<" running: "<<running);
        const position_t         pos          = p_base->get_old_position();
        const surroundings_t     surroundings = p_user_world->get_surroundings(pos.row,                                                                               pos.col);
        const debug_message_t    msg          = p_base->update(ui, surroundings);
        if(msg.valid && !msg.debug_message.empty())
        {
            p_graphics->write(world_data.update_debug_row+(debug_row++), 0,
                              80, 10, msg.debug_message);
        }

        graphic_data_t data = p_base->get_graphics(); 
        if(data.display && data.changed)
        {
            p_user_world->update(data.old_pos.row, data.old_pos.col, data.char_write_old_pos);
        }

        const engine_loop_t      engine_loop  = p_base->get_loop_delay();

        DB2("engine_loop.game_over: "<<engine_loop.game_over);
        DB2("engine_loop.delay: "<<engine_loop.delay);
        running = !engine_loop.game_over;
        if(engine_loop.delay > loop_delay)
            loop_delay = engine_loop.delay;
    } 
    DB2("Character Update exit "<<" paused: "<<paused<<" running: "<<running);
#if CHARACTER_UPDATE_ROW > 0
    std::string msg = "Character Update ";
    msg += "(";
    msg += spinner(loop_count); 
    msg += ") runnin: ";
    msg += std::to_string(running);
    GRAPHIC_WRITE(CHARACTER_UPDATE_ROW, 0, msg);
#endif
    return 0;
}


int SimpleGame::display_graphics(void)
{
    uint32_t update_count = 0;
    DB1("Display Graphics");
    std::vector<character *>::iterator it;
    for (it = characters.begin(); it != characters.end(); ++it)
    {
        character *p_base = *it;
        graphic_data_t data = p_base->get_graphics(); 
        DB1("Update Graphics" << data.display << data.changed);
        if(data.display && data.changed)
        {
            update_count++;
            p_graphics->write(  data.new_pos.row, 
                                data.new_pos.col, 
                                data.char_write_new_pos);
            p_graphics->write(  data.old_pos.row, 
                                data.old_pos.col, 
                                data.char_write_old_pos);
        }
    }
    p_graphics->refresh();
#if DISPLAY_GRAPHICS_ROW > 0
    std::string msg = "Display Graphics ";
    msg += "(";
    msg += spinner(loop_count); 
    msg += ") update count: " + std::to_string(update_count);
    GRAPHIC_WRITE(DISPLAY_GRAPHICS_ROW, 0, msg);
#endif
    return 0;
}


void SimpleGame::game_loop(void)
{
    if((p_user_world == NULL) || (p_graphics == NULL))
        throw "SimpleGame::game_loop NULL pointer";

    DB0("Entering game loop");

    while(running)
    {
        if(!paused && running)
        {
            if(character_update() < 0)
                throw "character update graphic write fail";
            if(test_collision() < 0)
                throw "test collision graphic write fail";
            if(display_graphics() < 0)
                throw "display graphics write fail";
            if(display_text() < 0)
                throw "display text graphic write fail";
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
#if GAME_LOOP_ROW > 0
        std::string msg = "Game Loop (";
        msg += spinner(loop_count); 
        msg += ") loop delay: " + std::to_string(loop_delay);
        msg += " paused: " + std::to_string(paused);
        msg += " running: " + std::to_string(running);
        DB0(msg);
        if(p_graphics->write(GAME_LOOP_ROW, 0, 80, 10, msg) < 0)
            throw "game loop graphic write fail";
#endif
        loop_count++;
        usleep(loop_delay*1000);
    } // Game Loop

    DB0("Existing game loop");
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


void SimpleGame::start_game(void)
{
    std::string background;

    p_user_world->get_world(background, world_data);
    int rows      = world_data.background_rows;
    int cols      = world_data.background_cols;
    int row_start = world_data.background_start_row;
    int col_start = world_data.background_start_col;
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
                p_graphics->write(data.new_pos.row, data.new_pos.col, data.char_write_new_pos);
        }
    }
    game_loop();
}


SimpleGame::~SimpleGame()
{
    DB0("SimpleGame destructor");
    delete p_graphics;
}

