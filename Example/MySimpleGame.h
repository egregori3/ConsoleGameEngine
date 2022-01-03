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


#define EATER_ID          0 // ID's can be any integer
#define GHOST_TYPE1_ID    5 // The ghosts have either type 1
#define GHOST_TYPE2_ID    7 // or type 2 personalities

// https://www.cs.bu.edu/fac/gkollios/cs113/Slides/lect13.pdf
class eater_world : public world
{
    private:
        world_state_t ws;

    public:
        eater_world();

        error_code_t get_world(std::string &background, int &rows, int &cols);
        const world_state_t get_state(const char_state_t char_state);
        error_code_t update_state(const char_state_t char_state);
};

/**
 * A class is just a recipe used to create an object. 
 * Using only one monster (ghost) class, we can instantiate multiple ghost objects.
 * When instantiated, each ghost is initialized with different data. This data
 * is stored in the objects private variable.
 * This makes the data for each object unique even if the code is the same.
 * Even though the eater and ghosts use the same code, they are initialized with 
 * different ID's. This allows the character object code to act as both a
 * eater and a ghost.
 */
class monster : public character
{
    private:
        char_state_t my_state;

    public:
        monster(char_state_t initial_state);
        char_state_t get_state(void);
        char_state_t update_state( const ui_t user_input, 
                                   const world_state_t world_state);
};


