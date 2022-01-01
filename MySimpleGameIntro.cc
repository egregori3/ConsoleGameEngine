#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "interfaces.h"
#include "SimpleGame.h"
#include "MySimpleGame.h"


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
 * @section BUILD                                                             *
 *  g++ MySimpleGameIntro.cc MySimpleGame.cc ./IntroCPP/SimpleGame.cc -I./IntroCPP -I./
 *                                                                            *
 * @section HISTORY                                                           *
 *  12/21 Eric Gegori - File created                                          *
 *                                                                            *
 * @section SOURCES                                                           *
 *  @see https://www.cs.bu.edu/                                               *
 ******************************************************************************/

extern std::string arena;

// Game hyper-parameters
const int  loop_rate_500ms = 500;
const int  ghosts = 5;
const char ghost = 'H'; // Initial "graphic" - can be overrriden by your derived class
const char eater = '>';

int main()
{
    // https://www.codesdope.com/cpp-array/
    // https://www.learncpp.com/cpp-tutorial/null-pointers/
    // https://en.cppreference.com/w/c/language/array_initialization
    // https://en.cppreference.com/w/cpp/language/aggregate_initialization
    // https://isocpp.org/wiki/faq/freestore-mgmt#null-or-zero
    //
    // This is dangerous!!!!
    // int array[5] = {0}; will fill the array with 0.
    // int array[5] = {3}; will ONLY set a[0] to 3, all others will be 0
    // GCC provides a workaround for this, but it is compiler specific.
    // monster *p_monsters[6] = { NULL }; // will work, but could burn you
    monster *p_monsters[ghosts+1] = { NULL, NULL, NULL, NULL, NULL, NULL }; // safer

    eater_world *p_world = new eater_world();
    SimpleGame sg(p_world, loop_rate_500ms);

    // char_state_t monster1 = {0,0,0,'<',true};     // init char_state_t structure
    // monster *p_monster1 = new monster(monster1);  // create a new monster object in memory
    // sg.add_character(p_monster1);
    // I combined the above lines into a single line
    //                \/ Create a new monster object in memory
    //                             \/ Pass the monster custructor a char_state_t structure
    //                                       \/ C trick for structure init
    p_monsters[0] = new monster((char_state_t){99,19,15,eater,true});
    p_monsters[1] = new monster((char_state_t){1,19,11,ghost,true});
    p_monsters[2] = new monster((char_state_t){2,19,11,ghost,true});
    p_monsters[3] = new monster((char_state_t){3,19,11,ghost,true});
    p_monsters[4] = new monster((char_state_t){4,19,11,ghost,true});
    p_monsters[5] = new monster((char_state_t){5,19,11,ghost,true});

    for(int ii=0; ii<(ghosts+1); ii++)
    {
        sg.add_character(p_monsters[ii]);
    }

    sg.start_game();

    // https://www.cpp-junkie.com/2020/04/c-delete-vs-delete.html
    // If you allocate memory using new keyword make sure to deallocate memory 
    // using delete keyword to avoid memory leaks. If you allocate an array of 
    // memory using new[] deallocate memory using delete[] keyword.
    for(int ii=0; ii<(ghosts+1); ii++)
    {
        delete p_monsters[ii];
    }
}
