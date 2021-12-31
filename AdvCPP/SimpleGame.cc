#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "interfaces.h"
#include "SimpleGame.h"


int SimpleGame::game_loop(void)
{
    // https://www.dreamincode.net/forums/topic/63358-store-class-objects-in-vector/
    // https://www.cplusplus.com/reference/vector/vector/
    std::vector<character>::iterator it;
    for (it = characters.begin(); it != characters.end(); ++it)
    {
        char_state_t char_state     = it->get_state();
        world_state_t world_state   = p_user_world->get_state(char_state);
        ui_t ui                     = get_user_input();
        char_state_t new_char_state = it->update_state(ui, world_state);
        p_user_world->update_state(new_char_state);

    }
}

int SimpleGame::init_background(std::string bg)
{
    background = bg;
}

ui_t SimpleGame::get_user_input(void)
{
    return UI_UP;
}

int SimpleGame::update_display(int x, int y, char c)
{
    std::cout << x << "," << y << "," << c;
    return 0;
}

int SimpleGame::add_character(std::unique_ptr<character> user_char)
{
    std::cout << "adding character";
}

SimpleGame::SimpleGame( std::unique_ptr<world> p_world, std::string background, 
            int loop_rate)
{
    init_background(background);
    p_user_world = p_world;
}

int SimpleGame::start_game(void)
{
    std::cout << "Starting game";
}

