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
 ******************************************************************************/

/**
 *
 */
typedef enum
{
    UI_UP,
    UI_DOWN,
    UI_LEFT,
    UI_RIGHT
}   ui_t;

/**
 * C++ supports classes and structs (ZC12.11)
 * Some guidance on when to use a struct versus a class:
 * https://www.fluentcpp.com/2017/06/13/the-real-difference-between-struct-class/
 * An invariant is a relation between the data members of a class that must 
 * hold true for the methods to work correctly. In other words, access to the
 * variables must be grouped. The constraints are invariant. 
 */

// Bind the data together using a structure (ZC12.11)
typedef struct
{
    char upper_left;
    char upper_middle;
    char upper_right;
    char middle_left;
    char character;
    char lower_left;
    char lower_middle;
    char lower_right;
} contraints_t;

typedef struct
{
    int  x;
    int  y;
    char c;
} char_position_t;

/**
 * Use a class to force the constraints to change all at once. (ZC7.1)
 * If multithreading is used in the future, mutex's could be added
 * to the class.
 * Initializer lists (ZC7.6) are discussed here:
 * https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/
 */
class constraint_transport
{
    private:
        constraints_t constraints;

    public: // initializer list
        constraint_transport(constraints_t init_data) : constraints(init_data) {}
        constraints_t get_constraints(void) {return constraints;}
}

/**
 * @class character
 *
 * @brief
 *  character interface (Abstract Base Class)  (ABC)                          
 *  The user needs to inherit from this class and implement the virtual       
 *  functions with the character's behaviors. The resulting object            
 *  instantiated from the class is registered with the SimpleGame class.      
 *
 * @section DESCRIPTION
 *  @see https://isocpp.org/wiki/faq/virtual-functions   (ZC8.4)
 *
 *  A virtual function allows derived classes to replace the implementation 
 *  provided by the base class. A pure virtual function is a function that 
 *  must be overridden in a derived class and need not be defined.
 *
 * @section USAGE
 *  The class variables are used for communicating with the SimpleGame class.
 *  This only works because the app is single threaded.
 *  1) The SimpleGame class calls set_constraint() to set the constraints.
 *  2) The SimpleGame class calls update()
 *  3) The user's update() implementation calls get_constraint() to deterimine
 *     how it can move.
 *  4) The user's update() implementation calls set_character()
 *  5) After update() returns, SimpleGame calls get_character()
 *  6) SimpleGame updates the graphics
 *
 *  To create a character for your game:
 *  1) Create a derived class that inherites from this ABC.
 *  2) Implement the update() method to do the following:
 *     A) User controlled character
 *        1. call get_constraints() for each constraint
 */
class character
{
    private: // these variables are accessed via getters/setters (ZC7.5)
        char c;                           // character symbol
        int  x,y;                         // character position
        constraint_id_t cid[CONSTRAINTS]; // constraints

    protected: // Only the users class can access these (ZC7.5)
        char get_constraint(constraint_id_t cid); // user can read
        void set_character(int x, int y, char c); // user can write

    public: // Called by SimpleGame class
        void set_constraint(constraint_id_t cid, char c); // SG can write
        char get_character(int &x, int &y);               // SG can read
        virtual void update(ui_t user_input) = 0; // pure virtual function (ZC8.4)
};


/**
 * @class world
 *
 * @brief
 *  world interface (Abstract Base Class)  (ABC)
 *  The user needs to inherit from this class and implement the virtual
 *  functions with the world's behaviors. The resulting class will be
 *  used by SimpleGame to instantiated the world object.
 *
 * @section DESCRIPTION
 *  @see https://isocpp.org/wiki/faq/virtual-functions   (ZC8.4)
 *
 *  A virtual function allows derived classes to replace the implementation 
 *  provided by the base class. A pure virtual function is a function that 
 *  must be overridden in a derived class and need not be defined.
 *
 * @section USAGE
 */
class world
{
    public:
        virtual contraints_t get_constraints(int x, int y) = 0; // pure virtual function (ZC8.4)
        virtual void update_background(int x, int y, char c) = 0;
};
