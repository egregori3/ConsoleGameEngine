/******************************************************************************
 * @file   MySimpleGameIntro.cc                                               *
 * @author Eric Gregori -  https://github.com/egregori3                       *
 * @data   12/21                                                              *
 *                                                                            *
 * @brief                                                                     *
 *  An example of how to use the SimpleGame class.                            *
 *  You will need to modify this file for your own game.                      *
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
 *  Steps for creating your own game:                                         *
 *  1) Create a class derived from the world class (see MySimpleGame.cc)      *
 *  2) Create a class derived from the character class (see MySimpleGame.cc)  *
 *  3) Instantiate your derived world class.                                  *
 *  4) Instantiate the SimpleGame class and pass it a pointer to your world   *
 *     class.                                                                 *
 *  5) Instantiate your derived character(s) class.                           *
 *  6) Add each character to the SigmpleGame class using the add_character()  *
 *     method.                                                                *
 *  7) Call the SimpleGame start_game() method.                               *
 *                                                                            *
 * @section BUILD                                                             *
 *  g++ MySimpleGameIntro.cc MySimpleGame.cc ./IntroCPP/SimpleGame.cc -I./IntroCPP -I./
 *                                                                            *
 * @section HISTORY                                                           *
 *  12/21 Eric Gegori - File created                                          *
 *                                                                            *
 * @section SOURCES                                                           *
 *  https://github.com/egregori3/ConsoleGameEngine/blob/master/README.md      *
 ******************************************************************************/
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "interfaces.h"
#include "SimpleGame.h"
#include "MySimpleGame.h"


extern std::string arena;

// Game hyper-parameters
const int  loop_rate_ms = 100;
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

    // Instantiate your world class and pass a pointer to the object to the SimpleGame class
    eater_world *p_world = new eater_world();

    {
        SimpleGame sg(p_world, loop_rate_ms);

        // char_state_t monster1 = {0,0,0,'<',true};     // init char_state_t structure
        // monster *p_monster1 = new monster(monster1);  // create a new monster object in memory
        // sg.add_character(p_monster1);
        // I combined the above lines into a single line
        //                \/ Create a new monster object in memory
        //                             \/ Pass the monster custructor a char_state_t structure
        //                                       \/ C trick for structure init
        p_monsters[0] = new monster((char_state_t){EATER_ID,19,15,eater,true});
        p_monsters[1] = new monster((char_state_t){GHOST_TYPE2_ID,17,11,ghost,true});
        p_monsters[2] = new monster((char_state_t){GHOST_TYPE1_ID,18,11,ghost,true});
        p_monsters[3] = new monster((char_state_t){GHOST_TYPE1_ID,19,11,ghost,true});
        p_monsters[4] = new monster((char_state_t){GHOST_TYPE2_ID,20,11,ghost,true});
        p_monsters[5] = new monster((char_state_t){GHOST_TYPE1_ID,21,11,ghost,true});

        // Add each character to the SimpleGame object
        for(int ii=0; ii<(ghosts+1); ii++)
        {
            sg.add_character(p_monsters[ii]); 
        }

        sg.start_game(); // This method will not return until the game is over.
    }

    // When the code gets here, the game is over.
    delete p_world;

    // https://www.cpp-junkie.com/2020/04/c-delete-vs-delete.html
    // If you allocate memory using new keyword make sure to deallocate memory 
    // using delete keyword to avoid memory leaks. If you allocate an array of 
    // memory using new[] deallocate memory using delete[] keyword.
    for(int ii=0; ii<(ghosts+1); ii++)
    {
        delete p_monsters[ii];
    }
}
