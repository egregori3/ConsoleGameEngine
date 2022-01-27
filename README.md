# Overview

The internet provides a wealth of valuable resources for a student learning object-oriented programming. This projected started as a resource guide with the goal of connecting students to on-line resources: https://github.com/egregori3/C-Plus-Plus_Article                          
                                                                            
Student feedback about the on-line resources indicated a need for better "more interesting" examples. That feedback drove this project. The code for this project was written to demonstrate various aspects of C++ and OOP, not necassarily to demonstrate best programming practices. In some cases, I know I swayed from best practices in order to demonstrate as many C++ and OOP techniques as possible. I note these decisions in the comments. When selecting resources to reference, the goal is quality and variety (exposing the students to as many resources as possible). The ZC in the notes reference chapters in the Zybook textbook.            
                                                                           
The comments in the code reference Zybook chapters using the following notation: ZC7.1 referres to Zybooks chapter 7, section 1                  

https://gcc.gnu.org/projects/cxx-status.html

https://en.cppreference.com/w/cpp/11

https://en.cppreference.com/w/cpp/14

There are 2 "identical" projects: one written using basic C++ (C++98) and the other written using advanced C++ (C++11, C++14).

## IntroCPP demonstrates

 * const (ZC2.9)
 * strings (ZC2.15)
 * class/struct (ZC7.2 to 7.3) 
 * new/delete (ZC10.3)
 * constructors (ZC7.6)
 * access specifiers (ZC7.5)
 * Encapsulation (ZC7.1)
 * Abstraction (ZC7.1)
 * Polymorphism (virtual functions) (ZC8.4)
 * Inheritance (base class / derived class) (ZC8.1)
 * Interface (abstract class) (ZC8.6)
 * Virtual Functions (ZC8.4)
 * vectors (ZC6.2)
 * pointers (ZC10.2)
 * pass by reference (ZC4.8)

## AdvCPP (everything in Intro plus)

The advanced CPP project does the same thing as the intro project but is written to take advantage of some C++11/14 features. 

 * smart pointers
 * List-initialization
 * map containers


About the Game "Engine"






# Files

|Have to modify|Directory|Filename|Description|
|--------------|---------|--------|-----------|
||Graphics||The SimpleGame "engine" is graphics system independent (although it is only designed for 2D)|
|no|Graphics/LinuxText|graphics.x|ncurses based ascii graphics|
|no|AbstractClasses|interfaces.h|These abstract classes define the interfaces for the SimpleGame "engine".|
||IntroCPP||The SimpleGame "engine" written using C++98|
||AdvCPP||The SimpleGame "engine" written to take advantage of modern C++|
|no|IntroCPP or AdvCPP|SimpleGame.x|The SimpleGame "engine"|
|yes|Example|MySimpleGameIntro.cc|This is an introCPP example of how to instantiate and initialize the SimpleGame "engine"|
|yes|Example|MySimpleGame.x|Examples of how to create classes for your game world and game characters.|

Files listed as Have to modify - no:  Do not need to be modified to create your own game. If you want to improve the game engine,
please fork, modify, and commit.
I encourage you to fork this repsitory and commit your own games to share with others or, submit your games to share with others.


# Program Flow

```
 *  SimpleGame game loop                                                      *
 *   Init:                                                                    *
 *      call world.init_world() with background string and size               *
 *   Loop:                                                                    *
 *      for each character:                                                   *
 *          call char_state  = character.get_state()                          *
 *          call world_state = world.get_state(char_state)                    *
 *          call new_char_state = character.update_state(ui, world_state)     *
 *          call world.update_state(new_char_state)                           *
 

egregori:~/Development/ConsoleGameEngine $ ./a.out
eater_world: constructor
SimpleGame: constructor
eater_world: get_world
SimpleGame: init_background
monster: constructor
SimpleGame: add_character

SimpleGame: start_game
SimpleGame: game_loop
SimpleGame: in_loop
SimpleGame: run_char
monster: get_state          - call char_state  = character.get_state()
eater_world: get_state      - call world_state = world.get_state(char_state)
SimpleGame: get_user_input
monster: update_state       - call new_char_state = character.update_state(ui, world_state)
eater_world: update_state   - call world.update_state(new_char_state)

SimpleGame: in_loop
SimpleGame: run_char
monster: get_state
eater_world: get_state
SimpleGame: get_user_input
monster: update_state
eater_world: update_state
SimpleGame: in_loop
SimpleGame: run_char
monster: get_state
eater_world: get_state
SimpleGame: get_user_input
monster: update_state
eater_world: update_state
```

# Code to init SimpleGame with a world and 6 characters (note above output shows only 1 character init)

# Resources

 * http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines          
 * https://www.modernescpp.com                                          
 * https://isocpp.org/wiki/faq/abcs                                     
 * https://www.learncpp.com/                                            
 * https://www.guru99.com/                                              
 * https://www.fluentcpp.com/                                           
 * https://en.cppreference.com/                                         
 * https://www.cs.fsu.edu/                                              
 * https://www.tutorialspoint.com/                                      
 * https://www.drdobbs.com/                                             
 * https://www.cplusplus.com/                                           
 * https://www.dreamincode.net/                                         
 * https://linuxhint.com/   
 * https://gcc.gnu.org/  
 * https://www.educative.io/
 * http://pages.cs.wisc.edu/~hasti/cs368/CppTutorial
 * https://www.codesdope.com/
 * https://www.cpp-junkie.com/
                       
