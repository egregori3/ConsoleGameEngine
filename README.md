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

 * smart pointers
 * List-initialization

The advanced CPP project does the same thing as the intro project but is written to take advantage of some C++11/14 features. 

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

```C++

const std::string arena =
  // 0         1         2         3        4
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
    p_monsters[0] = new monster((char_state_t){EATER_ID,19,15,eater,true});
    p_monsters[1] = new monster((char_state_t){GHOST_TYPE2_ID,19,11,ghost,true});
    p_monsters[2] = new monster((char_state_t){GHOST_TYPE1_ID,19,11,ghost,true});
    p_monsters[3] = new monster((char_state_t){GHOST_TYPE1_ID,19,11,ghost,true});
    p_monsters[4] = new monster((char_state_t){GHOST_TYPE2_ID,19,11,ghost,true});
    p_monsters[5] = new monster((char_state_t){GHOST_TYPE1_ID,19,11,ghost,true});
    
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

```

# How to make your own game

MySimpleGame.h

MySimpleGame.cc - Create your world and characters by deriving from the world and character abstract classes (inheritance)
  
MySimpleGameIntro.cc - Instantiate the SimplGame class and initialize it with your world and characters objects.
                     
                       The game loop takes control and will call the methods in your world and character objects.
                       
                       Your game is defined by the rules you code in your world and character derived classes.
                       
