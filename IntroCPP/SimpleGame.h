#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "interfaces.h"


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
 *  Smart Pointers:                                                           *
 *  https://en.cppreference.com/w/cpp/memory/shared_ptr                       *
 *  Pointers: with great power comes great responsibility.                    *
 *  Although powerful, pointers have been the cause of many bugs.             *
 *  In response, C++11 introduced smart pointers.                             *
 *  std::shared_ptr is a smart pointer that retains shared ownership of an    *
 *  object through a pointer. Several shared_ptr objects may own the same     *
 *  object. A shared_ptr can share ownership of an object while storing a     *
 *  pointer to another object.                                                *
 *                                                                            *
 *  Vectors:                                                                  *
 *  https://linuxhint.com/use_cpp_vector/                                     *
 *  www.dreamincode.net/forums/topic/63358-store-class-objects-in-vector/     *
 *  An array is a series of same object types in consecutive memory locations.*
 *  An array cannot increase ore reduce in length. A vector is like an array, *
 *  but its length can be increased or reduced. A vector, therefore,          *
 *  has many more operations than an array.                                   *
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
 *  @see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines          *
 *  @see https://www.modernescpp.com                                          *
 *  @see https://isocpp.org/wiki/faq/abcs                                     *
 *  @see https://www.learncpp.com/                                            *
 *  @see https://www.guru99.com/                                              *
 *  @see https://www.fluentcpp.com/                                           *
 *  @see https://en.cppreference.com/                                         *
 *  @see https://www.cs.fsu.edu/                                              *
 *  @see https://www.tutorialspoint.com/                                      *
 *  @see https://www.drdobbs.com/                                             *
 *  @see https://www.cplusplus.com/                                           *
 *  @see https://www.dreamincode.net/                                         *
 *  @see https://linuxhint.com/                                               *
 ******************************************************************************/

class SimpleGame
{
    private:
        // https://www.dreamincode.net/forums/topic/63358-store-class-objects-in-vector/
        std::vector<character *> characters;
        world *p_user_world;
        std::string background;
        int loop_rate_in_ms;

    private:
        ui_t get_user_input(void);
        int  init_background(std::string bg);
        int  update_display(int x, int y, char c);
        int game_loop(void);

    public:
        SimpleGame( world *p_world, int loop_rate);
        int add_character(character *p_user_char);
        int start_game(void);
};

#endif

