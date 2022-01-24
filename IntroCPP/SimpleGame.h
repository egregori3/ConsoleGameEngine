#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "interfaces.h"
#include "graphics.h"


/******************************************************************************
 * @file   SimpleGame.h                                                       *
 * @author Eric Gregori -  https://github.com/egregori3                       *
 * @data   12/21                                                              *
 *                                                                            *
 * @brief                                                                     *
 *  interfaces (Abstract Base Classes)                                        *
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
 *  The ZC in the notes reference chapters in the Zybook textbook.            *
 *                                                                            *
 *  The comments in the code reference Zybook chapters using the following    *
 *  notation: ZC7.1 referres to Zybooks chapter 7, section 1                  *
 *                                                                            *
 * @section DESCRIPTION                                                       *
 *  Demonstrated topics                                                       *
 *                                                                            *
 *  class/struct:  binding data together and with functions (ZC7.2)           *
 *  Encapsulation: data hiding, scope management (ZC7.1)                      *
 *  Abstraction:   Once you learn to use the interface, you do not need to    *
 *                 understand how the black box works in order to use it.     *
 *  Polymorphism:  function overloading and virtual functions (ZC8.4)         *
 *  Inheritance:   code reuse (ZC8.1)                                         *
 *  Interface:     the use of inheritance to separate users from              *
 *                 implementations (ZC8.6)                                    *
 *                                                                            *
 *  Virtual Functions:                                                        *
 *  @see https://isocpp.org/wiki/faq/virtual-functions   (ZC8.4)              *
 *  A virtual function allows derived classes to replace the implementation   *
 *  provided by the base class. A pure virtual function is a function that    *
 *  must be overridden in a derived class and need not be defined.            *
 *                                                                            *
 *  Vectors:                                                                  *
 *  https://linuxhint.com/use_cpp_vector/                                     *
 *  www.dreamincode.net/forums/topic/63358-store-class-objects-in-vector/     *
 *  An array is a series of same object types in consecutive memory locations.*
 *  An array cannot increase ore reduce in length. A vector is like an array, *
 *  but its length can be increased or reduced. A vector, therefore,          *
 *  has many more operations than an array.                                   *
 *                                                                            *
 *  Pointers:   (ZC10.2)                                                      *
 *  https://www.educative.io/edpresso/differences-between-pointers-and-references-in-cpp
 *  A pointer in C++ is a variable that holds the memory address of another   *
 *  variable.                                                                 *
 *                                                                            *
 *  References: (ZC4.8)                                                       *
 *  A reference is an alias for an already existing variable.                 *
 *  Once a reference is initialized to a variable, it cannot be changed to    *
 *  refer to another variable. Hence, a reference is similar to a const       *
 *  pointer.                                                                  *
 *                                                                            *
 *  Strings:    (ZC2.15)                                                      *
 *  http://pages.cs.wisc.edu/~hasti/cs368/CppTutorial/NOTES/STRING.html       *
 *  The string class is part of the C++ standard library. A string represents *
 *  a sequence of characters.                                                 *
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
 *  https://github.com/egregori3/ConsoleGameEngine/blob/master/README.md      *
 ******************************************************************************/

class SimpleGame
{
    private:
        std::vector<character *> characters;
        world *p_user_world  = NULL;
        graphics *p_graphics = NULL;
        int *collision_array = NULL;
        int loop_rate_in_ms;
        int rows;
        int cols;
        int row_start;
        int col_start;

    private:
        ui_message_t get_user_input(void);
        void game_loop(void);

    public:
        SimpleGame( world *p_world, int loop_rate);
        ~SimpleGame();
        void add_character(character *p_user_char);
        void start_game(void);
        void init_collision(void);
        bool check_collision(int row, int col, int &id);
};

#endif

