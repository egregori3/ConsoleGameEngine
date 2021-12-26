#include <string>

/******************************************************************************
 * @file   interfaces.h                                                       *
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
 *  Virtual Functions:                                                        *
 *  @see https://isocpp.org/wiki/faq/virtual-functions   (ZC8.4)              *
 *  A virtual function allows derived classes to replace the implementation   *
 *  provided by the base class. A pure virtual function is a function that    *
 *  must be overridden in a derived class and need not be defined.            *
 *                                                                            *
 *  SimpleGame game loop                                                      *
 *  Init:                                                                     *
 *      call world.init_world() with background string and size               *
 *  Loop:                                                                     *
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
 ******************************************************************************/

/**
 * https://en.cppreference.com/w/cpp/language/enum
 * An enumeration is a distinct type whose value is restricted to a range of values, 
 * which may include several explicitly named constants ("enumerators").
 */
typedef enum
{
    UI_UP,
    UI_DOWN,
    UI_LEFT,
    UI_RIGHT
}   ui_t;

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
 * if you don’t intend to modify your data after creation.
 */

/**
 * State is defined as the (X,Y) location of a character, the ascii value for
 * the character, and the ascii values surrounding the character (constraints).
 * Bind the data together using a structure (ZC12.11)
 */
typedef struct
{
    int  x;
    int  y;
    char c;
} char_state_t;

typedef struct
{
    int  x;
    int  y;
    char upper_left_constraint;
    char upper_middle_constraint;
    char upper_right_constraint;
    char middle_left_constraint;
    char character;
    char lower_left_constraint;
    char lower_middle_constraint;
    char lower_right_constraint;
} world_state_t;

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
 *  get_state() needs to return the characters current state
 *  update_state() needs to update the characters state based on the world state
 *   and (if a user controlled character) user_input or (if an AI controlled character)
 *   the user provided AI algorithm input then return the new_state
 *
 * @section USAGE
 *  To create a character for your game, Create a derived class that inherites from this ABC.
 *  Your derived class must keep track of the characters state (x,y,c) and
 *  based on the world_state, plus either the user interface or an AI decision, update
 *  the state of the character.
 */
class character
{
    public: // 
        // pure virtual function (ZC8.4)
        virtual char_state_t get_state(void);
        virtual char_state_t update_state( const ui_t user_input, 
                                           const world_state_t world_state) = 0;
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
 * @section DESCRIPTION
 *
 * @section USAGE
 */
class world
{
    public:
        // pure virtual function (ZC8.4)
        virtual int init( const std::string background, 
                          const int rows, const int cols) = 0;
        virtual const world_state_t get_state(const char_state_t char_state) = 0; 
        virtual void update_state(const char_state_t char_state) = 0;
};

