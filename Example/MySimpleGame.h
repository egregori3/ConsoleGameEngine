#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <sstream>
#include <random>
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


// Character ID's can be any integer, but each ID MUST be unique.
#define EATER_ID          0
#define GHOST_ID          10

#define ROW_ERROR  std::string("start_row: ") + std::to_string(wrow_start) + ", "\
                   + "last_row: " + std::to_string(wrow_start+wrows) + ", "\
     
#define COL_ERROR  std::string("start_col: ") + std::to_string(wcol_start) + ", "\
                   + "last_col: " + std::to_string(wcol_start+wcols) + ", "\

typedef enum
{
    EATING,
    DEAD1,
    DEAD2,
    DEAD3,
    DEAD4
}   eater_state_t;


typedef enum
{
    CHASE,
    RUN
}   ghost_state_t;


typedef enum
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
}   motion_t;


// https://www.cs.bu.edu/fac/gkollios/cs113/Slides/lect13.pdf
class eater_world : public world
{
    private:
        world_data_t world_data;
        // https://www.cplusplus.com/reference/sstream/ostringstream/str/
        std::ostringstream oss; 
        std::string arena_cpy;

    public:
        eater_world();

        void  get_world(std::string &background, world_data_t &world_data);
        const surroundings_t get_surroundings(graphic_data_t data);
        void                 update(graphic_data_t data);
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
        // Initalized by constructor
        int             id;        // id of character - the user can use for whatever they want
        int             char_write_current_pos;
        int             char_write_next_pos;
        bool            display;   // set to true to display the character
        position_t      posa;
        position_t      posb;
        motion_t        old_motion;

        int             iterations;
        int             score;
        int             delay_engine;
        bool            game_over;
        bool            char_changed;
        eater_state_t   eater_state;
        ghost_state_t   ghost_state;

        // https://www.cplusplus.com/reference/sstream/ostringstream/str/
        std::ostringstream oss; 
        std::random_device rd;
        std::default_random_engine eng;
        std::uniform_real_distribution<float> distr;

    private:
        const debug_message_t update_eater(const ui_message_t &user_input, 
                                           const surroundings_t &surroundings);
        const debug_message_t update_monster(const surroundings_t &surroundings);
        bool  eater_test(int user_input);
        bool  monster_test(int user_input);
        const debug_message_t collision_eater(int id);
        const debug_message_t collision_monster(int id);

    public:
        monster(int id, int row, int col, int c, bool display);

        const graphic_data_t  get_graphics(void);
        const text_window_t   get_text(void);
        const engine_loop_t   get_loop_delay(void);
        const debug_message_t collision(int id);
        const debug_message_t update(const ui_message_t &ui, 
                                     const surroundings_t &surroundings);
};


