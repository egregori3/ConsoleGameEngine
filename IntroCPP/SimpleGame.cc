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


void SimpleGame::update_constraint_display(int row, int col)
{
    char_state_t cs;
    cs.row = row;
    cs.col = col.
    world_state_t world_state = p_user_world->get_state(char_state);
    p_graphics->write(old.row,  old.col,  news.replace);

}

error_code_t SimpleGame::game_loop(void)
{
    if((p_user_world == NULL) || (p_graphics == NULL))
        return ERROR_NULL_PTR;

    for(bool running=true; running; )
    {
        ui_t ui;

        // https://limbioliong.wordpress.com/2012/12/25/storing-c-objects-in-a-stl-vector-part-2/
        // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch06s05.html
        // https://www.dreamincode.net/forums/topic/63358-store-class-objects-in-vector/
        // https://linuxhint.com/use_cpp_vector/
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;

            char_state_t char_state     = p_base->get_state();
            world_state_t world_state   = p_user_world->get_state(char_state);
            ui                          = get_user_input();
            char_state_t new_char_state = p_base->update_state(ui, world_state);
            bool changed = update_display(char_state, new_char_state);
            if(changed == true)
                p_user_world->update_state(new_char_state);
        }

        if(ui == UI_EXIT)
            running = false;

        usleep(loop_rate_in_ms*1000);
    }

    return ERROR_NONE;
}

ui_t SimpleGame::get_user_input(void)
{
    ui_t result = UI_NONE;
//    std::cout << "SimpleGame: get_user_input" << std::endl;
    result = p_graphics->get_input();
    return result;
}

bool SimpleGame::update_display(char_state_t old, char_state_t news)
{
    bool changed = ((old.row != news.row) || (old.col != news.col) || (old.c != news.c));

    if(changed == true)
    {
        p_graphics->write(old.row,  old.col,  news.replace);
        p_graphics->write(news.row, news.col, news.c);
        p_graphics->refresh();
    }

    return ERROR_NONE;
}

error_code_t SimpleGame::add_character(character *p_user_char)
{
    // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch06s05.html

    char_state_t new_char = p_user_char->get_state();
    {
        // If the character ID is already registered, return error
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;
            char_state_t old_char = p_base->get_state();
            if(new_char.id == old_char.id)
                return ERROR_INIT;
        }
    }
    characters.push_back(p_user_char);
    return ERROR_NONE;
}

SimpleGame::SimpleGame(world *p_world, int loop_rate)
{
    p_user_world = p_world;
    loop_rate_in_ms = loop_rate;
}

error_code_t SimpleGame::start_game(void)
{
    std::string background;
    int rows;
    int cols;

    p_user_world->get_world(background, rows, cols);
    p_graphics = new graphics(rows, cols);
    p_graphics->write(background);
    {
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            character *p_base = *it;
            char_state_t init = p_base->get_state();
            if(init.display == true)
                p_graphics->write(init.row, init.col, init.c);
        }
    }
    error_code_t result = game_loop();
    return result;
}

SimpleGame::~SimpleGame()
{
    delete p_graphics;
}

