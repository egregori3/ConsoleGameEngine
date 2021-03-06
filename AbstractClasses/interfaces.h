#ifndef INTERFACES_H
#define INTERFACES_H

/******************************************************************************
 * @file   interfaces.h                                                       *
 * @author Eric Gregori -  https://github.com/egregori3                       *
 * @data   12/21                                                              *
 *                                                                            *
 * @brief                                                                     *
 *  interfaces (Abstract Base Classes)                                        *
 *  YOU SHOULD NOT NEED TO EDIT THIS FILE.
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
 *  Virtual Functions:                                                        *
 *  @see https://isocpp.org/wiki/faq/virtual-functions   (ZC8.4)              *
 *  A virtual function allows derived classes to replace the implementation   *
 *  provided by the base class. A pure virtual function is a function that    *
 *  must be overridden in a derived class and need not be defined.            *
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
#include <string>
#include <sstream>
#include <vector>


//#define DISABLE_GRAPHICS // if DISABLE_GRAPHICS is defined, graphics are disabled
#ifdef  DISABLE_GRAPHICS
    #ifdef  DEBUG0
        #define DB0(X) std::cerr << "Debug 0 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB0(X)
    #endif
    #ifdef  DEBUG1
        #define DB1(X) std::cerr << "Debug 1 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB1(X)
    #endif
    #ifdef  DEBUG2
        #define DB2(X) std::cerr << "Debug 2 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB2(X)
    #endif
    #ifdef  DEBUG3
        #define DB3(X) std::cerr << "Debug 3 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB3(X)
    #endif
    #ifdef  DEBUG4
        #define DB4(X) std::cerr << "Debug 4 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB4(X)
    #endif
    #ifdef  DEBUG5
        #define DB5(X) std::cerr << "Debug 5 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB5(X)
    #endif
    #ifdef  DEBUG6
        #define DB6(X) std::cerr << "Debug 6 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB6(X)
    #endif
    #ifdef  DEBUG7
        #define DB7(X) std::cerr << "Debug 7 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB7(X)
    #endif
    #ifdef  DEBUG8
        #define DB8(X) std::cerr << "Debug 8 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB8(X)
    #endif
    #ifdef  DEBUG9
        #define DB9(X) std::cerr << "Debug 9 >" << X << "< " << __FILE__ << " "<<  __LINE__ << "\n"
    #else
        #define DB9(X)
    #endif
#else
    #define DB0(X)
    #define DB1(X)
    #define DB2(X)
    #define DB3(X)
    #define DB4(X)
    #define DB5(X)
    #define DB6(X)
    #define DB7(X)
    #define DB8(X)
    #define DB9(X)
#endif

// Set to 0 to disable
#define GAME_LOOP_ROW           44
#define TEST_COLLISION_ROW      41
#define DISPLAY_TEXT_ROW        43
#define CHARACTER_UPDATE_ROW    40
#define DISPLAY_GRAPHICS_ROW    42

/**
 * https://en.cppreference.com/w/cpp/language/enum
 * An enumeration is a distinct type whose value is restricted to a range of values, 
 * which may include several explicitly named constants ("enumerators").
 */
typedef enum
{
    UI_NONE,
    UI_UP,
    UI_DOWN,
    UI_LEFT,
    UI_RIGHT,
    UI_EXIT,
    UI_PAUSE
}   ui_message_t;


/**
 * https://www.guru99.com/cpp-structures.html
 * https://www.fluentcpp.com/2017/06/13/the-real-difference-between-struct-class/
 *
 * A struct is a bundle. A struct is several related elements that needed to be 
 * tied up together in a certain context. Such a context can be passing a restricted 
 * number of arguments to a function.
 * Here are some reasons using structure in C++.
 * Use a struct when you need to store elements of different data types under 
 * one data type.
 * C++ structs are a value type rather than being a reference type. Use a struct 
 * if you don???t intend to modify your data after creation.
 */

/**
 * State is defined as the (X,Y) location of a character, the ascii value for
 * the character, and the ascii values surrounding the character (constraints).
 * Bind the data together using a structure (ZC12.11)
 */
typedef struct
{
    bool        valid;
    int         row_start;
    int         col_start;
    int         width;
    int         height;
    std::string message; 
}   text_window_t;


typedef struct
{
    bool        valid;
    std::string debug_message; 
}   debug_message_t;


typedef struct
{
    int  id;        // id of character - the user can use for whatever they want
    int  row;       // row position of character
    int  col;       // col position of character
    int  char_to_write;
}   position_t;


typedef struct
{
    int         id;        // id of character - the user can use for whatever they want
    bool        display;   // set to true to display the character
    bool        changed;
    position_t  posa;
    position_t  posb;
}   graphic_data_t;


typedef struct
{
    int tl;  // top left
    int tc;  // top center
    int tr;  // top right
    int cl;  // center left
    int c;   // center
    int cr;  // center right
    int bl;  // bottom left
    int bc;  // bottom center
    int br;  // bottom right
}   surroundings_t;


typedef struct
{
    int             delay;
    bool            game_over; // set to end the game
}   engine_loop_t;


typedef struct
{
    int background_rows;
    int background_cols;
    int background_start_row;
    int background_start_col;
    int collision_debug_row;
    int update_debug_row;
}   world_data_t;


/**
 * @class character
 *
 * @brief
 *  Called by SimpleGame class
 *  character interface (Abstract Base Class)  (ABC)                          
 *  The user needs to inherit from this class and implement the virtual       
 *  functions with the character's behaviors. The resulting object            
 *  instantiated from the class is registered with the SimpleGame class.      
 *
 * @section DESCRIPTION
 *  get_state()    needs to return the characters current state
 *  update_state() needs to update the characters state based on the world state
 *                 and (if a user controlled character) user_input or 
 *                 (if an AI controlled character) the user provided AI algorithm 
 *                 input then return the new_state
 *
 * @section USAGE
 *  To create a character for your game, create a derived class that inherites from this ABC.
 *  Your derived class must keep track of the characters state (x,y,c) and
 *  based on the world_state, plus either the user interface or an AI decision, update
 *  the state of the character.
 */
class character
{
    public: // 
        // pure virtual function (ZC8.4)
        virtual const graphic_data_t  get_graphics(void)     = 0;
        virtual const text_window_t   get_text(void)         = 0;
        virtual const engine_loop_t   get_loop_delay(void)   = 0;
        virtual const debug_message_t collision(int id)      = 0;
        virtual const debug_message_t update(const ui_message_t &ui, 
                                             const surroundings_t &surroundings) = 0;
};


/**
 * @class world
 *
 * @brief
 *  Called by SimpleGame class
 *  world interface (Abstract Base Class)  (ABC)
 *  The user needs to inherit from this class and implement the virtual
 *  functions with the world's behaviors. 
 *
 *  pass-by-reference: (ZC4.8)
 *  https://www.cs.fsu.edu/~myers/c++/notes/references.html
 *  https://www.tutorialspoint.com/cplusplus/cpp_function_call_by_reference.htm
 *  The call by reference method of passing arguments to a function copies the 
 *  reference of an argument into the formal parameter. Inside the function, 
 *  the reference is used to access the actual argument used in the call. 
 *  This means that changes made to the parameter affect the passed argument.
 *
 * @section DESCRIPTION
 *  get_world()    needs to return a string representing the background along 
 *                 with the number of rows and columns in the background
 *  get_state()    needs to return the world state based on the character state
 *  update_state() needs to update the world state based on the character state
 *
 * @section USAGE
 *  To create a world for your game, create a derived class that inherites from this ABC.
 *  A world consists of a background and a set of rules that you define by implementing
 *  the interface functions.
 *  
 */
class world
{
    public:
        // pure virtual function (ZC8.4)
        virtual void                 get_world(std::string &background,
                                               world_data_t &world_data) = 0;
        virtual const surroundings_t get_surroundings(graphic_data_t data)  = 0;
        virtual void                 update(graphic_data_t data)         = 0;
};

#endif
