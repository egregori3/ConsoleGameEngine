// For a full list of resources see:
// https://github.com/egregori3/ConsoleGameEngine/blob/master/README.md

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <unistd.h>
#include "interfaces.h"
#include "SimpleGame.h"


int SimpleGame::game_loop(void)
{
    std::cout << "SimpleGame: game_loop" << std::endl;
    for(bool running=true; running; )
    {
        ui_t ui;

        std::cout << "SimpleGame: in_loop" << std::endl;

        // https://limbioliong.wordpress.com/2012/12/25/storing-c-objects-in-a-stl-vector-part-2/
        // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch06s05.html
        // https://www.dreamincode.net/forums/topic/63358-store-class-objects-in-vector/
        // https://linuxhint.com/use_cpp_vector/
        std::vector<character *>::iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            std::cout << "SimpleGame: run_char" << std::endl;
            character *p_base = *it;

            char_state_t char_state     = p_base->get_state();
            world_state_t world_state   = p_user_world->get_state(char_state);
            ui                          = get_user_input();
            char_state_t new_char_state = p_base->update_state(ui, world_state);
            p_user_world->update_state(new_char_state);
        }

        if(ui == UI_EXIT)
            running = false;

        usleep(loop_rate_in_ms*1000);
    }

    return 0;
}

int SimpleGame::init_background(std::string bg)
{
    std::cout << "SimpleGame: init_background" << std::endl;
    background = bg;

    return 0;
}

ui_t SimpleGame::get_user_input(void)
{
    std::cout << "SimpleGame: get_user_input" << std::endl;
    return UI_UP;
}

int SimpleGame::update_display(int x, int y, char c)
{
    std::cout << "SimpleGame: update_display" << std::endl;
    std::cout << x << "," << y << "," << c;
    return 0;
}

int SimpleGame::add_character(character *p_user_char)
{
    // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch06s05.html
    std::cout << "SimpleGame: add_character" << std::endl;
    characters.push_back(p_user_char);

    return 0;
}

SimpleGame::SimpleGame(world *p_world, int loop_rate)
{
    std::string backgound;
    int rows;
    int cols;

    std::cout << "SimpleGame: constructor" << std::endl;
    p_world->get_world(background, rows, cols);
    init_background(background);
    p_user_world = p_world;
    loop_rate_in_ms = loop_rate;
}

int SimpleGame::start_game(void)
{
    std::cout << "SimpleGame: start_game" << std::endl;
    game_loop();

    return 0;
}

