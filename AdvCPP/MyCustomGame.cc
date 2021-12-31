#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "interfaces.h"
#include "SimpleGame.h"


/******************************************************************************
 * @file   MyCustomGame                                                       *
 * @author Eric Gregori -  https://github.com/egregori3                       *
 * @data   12/21                                                              *
 *                                                                            *
 * @brief                                                                     *
 *  An example of how to use the SimpleGame class.                            *
 *                                                                            *
 * @section PURPOSE                                                           *
 *  The internet provides a wealth of valuable resources for a student        *
 *  learning object-oriented programming. This projected started as a resource*
 *  guide with the goal of connecting students to on-line resources:          *
 *  https://github.com/egregori3/C-Plus-Plus_Article                          *
 *                                                                            *
 *  Student feedback about the on-line resources indicated a need for better  *
 *  "more interesting" examples. That feedback drove this project.            *
 *  The code for this project was written to demonstrate various aspects of   *
 *  C++ and OOP, not necassarily to demonstrate best programming practices.   *
 *  In some cases, I know I swayed from best practices in order to demonstrate*
 *  as many C++ and OOP techniques as possible. I note these decisions in the *
 *  comments. When selecting resources to reference, the goal is quality and  *
 *  variety (exposing the students to as many resources as possible).         *
 *                                                                            *
 * @section DESCRIPTION                                                       *
 *                                                                            *
 *  SimpleGame game loop                                                      *
 *   Init:                                                                    *
 *      call world.init_world() with background string and size               *
 *   Loop:                                                                    *
 *      for each character:                                                   *
 *          call char_state  = character.get_state()                          *
 *          call world_state = world.get_state(char_state)                    *
 *          call new_char_state = character.update_state(ui, world_state)     *
 *          call world.update_state(new_char_state)                           *
 *                                                                            *
 *                                                                            *
 * @section HISTORY                                                           *
 *  12/21 Eric Gegori - File created                                          *
 *                                                                            *
 * @section SOURCES                                                           *
 *  @see https://www.cs.bu.edu/                                               *
 ******************************************************************************/


const int loop_rate_500ms = 500;

static const std::string arena =
  // 0                                      3
  // 0123456789012345678901234567890123456789
    "|======================================|" // 00
    "|                  |                   |" // 01
    "| |======| |=====| | |=====| |=======| |" // 02
    "|                                      |" // 03
    "| |======| |=| |=======| |=| |=======| |" // 04
    "|          |=|    |=|    |=|           |" // 05
    "|========| |====| |=| |====| |=========|" // 06
    "         | |=|           |=| |          " // 07
    "|========| |=| |=======| |=| |=========|" // 08
    "               |       |                " // 09
    "|========| |=| |=======| |=| |=========|" // 10
    "         | |=|           |=| |          " // 11
    "|========| |=| |=======| |=| |=========|" // 12
    "|                 |=|                  |" // 13
    "| |======| |====| |=| |====| |=======| |" // 14
    "|      |=|                   |=|       |" // 15
    "|====| |=| |=| |=======| |=| |=| |=====|" // 16
    "|          |=|    |=|    |=|           |" // 17
    "| |=============| |=| |==============| |" // 18
    "|                                      |" // 19
    "|======================================|";// 20


// https://www.cs.bu.edu/fac/gkollios/cs113/Slides/lect13.pdf
class eater_world : public world
{
    private:
        world_state_t ws;

    public:
        eater_world()
        {
        }

        int get_world(const std::string &background, int &rows, int &cols)
        {
           background = arena;
           rows       = 21;
           cols       = 40;
        }

        const world_state_t get_state(const char_state_t char_state)
        {
                ws.x = char_state.x;
                ws.y = char_state.y;
                ws.upper_left_constraint    = 0;
                ws.upper_middle_constraint  = 0;
                ws.upper_right_constraint   = 0;
                ws.middle_left_constraint   = 0;
                ws.character                = char_state.c;
                ws.lower_left_constraint    = 0;
                ws.lower_middle_constraint  = 0;
                ws.lower_right_constraint   = 0;

            return ws;
        }

        void update_state(const char_state_t char_state)
        {
                ws.x = char_state.x,
                ws.y = char_state.y,
                ws.character                = char_state.c,
        }
};

class monster1 : public character
{
    private:
        char_state_t my_state = {0,0,0,'<',true};

    public:
        char_state_t get_state(void)
        {
            return my_state;
        }

        char_state_t update_state( const ui_t user_input, 
                                   const world_state_t *world_state)
        {
            if((user_input == UI_UP) && (world_state->upper_middle_constraint == ' '))
                return my_state;
        }

};


int main()
{
    // https://www.learncpp.com/cpp-tutorial/stdunique_ptr/
    std::unique_ptr<eater_world> my_word{new eater_world{}};
    SimpleGame sg(eater_world, arena, loop_rate_500ms);

    auto p_monster1{ std::make_unique<monster1>() };
    sg.add_character(std::move(p_monster1));

    sg.start_game();
}
