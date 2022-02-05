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

typedef struct
{
    bool inc_score;
    bool die;
} eater_state_t;


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
        // https://www.cplusplus.com/reference/sstream/ostringstream/str/
        std::ostringstream oss; 
        std::string arena_cpy;

    public:
        eater_world();

        void get_world(std::string &background,
                       int &row_start, int &col_start, int &rows, int &cols);
        void tx_message_to_engine(int row, int col, world_message_t &world_message);
        void update_message_from_engine(const char_message_t &char_message);
        void get_display_info(std::vector<info_window_message_t> &info_window_list);
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
        int         id;        // id of character - the user can use for whatever they want
        int         row;       // row position of character
        int         col;       // col position of character
        int         c;         // character to display
        int         iterations;
        int         score;
        int         state;
        int         replace;   // character to put into old position
        bool        display;   // set to true to display the character
        bool        game_over; // set to end the game
        bool        inc_score;
        bool        die;
        motion_t    old_motion;
        std::vector<std::string> debug_message;
        // https://www.cplusplus.com/reference/sstream/ostringstream/str/
        std::ostringstream oss; 
        std::random_device rd;
        std::default_random_engine eng;
        std::uniform_real_distribution<float> distr;

    private:
        void update_eater(const ui_message_t user_input, 
                          const world_message_t world_message,  bool &update);
        void update_monster(const world_message_t world_message,bool &update);
        bool eater_test(const int user_input);
        bool monster_test(const int user_input);

    public:
        monster(int id, int row, int col, int c, bool display);
        void message_to_engine(char_message_t &char_message);
        void update_message_from_engine(const ui_message_t &user_input_message, 
                                        const world_message_t &world_message,
                                        bool &updated);
        void get_display_info(std::vector<info_window_message_t> &info_window_list);
        void collision_message_from_engine(char_message_t &char_message, int id);
};


