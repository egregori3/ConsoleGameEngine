#ifndef GRAPHICS_H
#define GRAPHICS_H

/******************************************************************************
 * @file   graphics.h                                                         *
 * @author Eric Gregori -  https://github.com/egregori3                       *
 * @data   12/21                                                              *
 *                                                                            *
 * @brief  Linux ncurses based "graphics".                                    *
 *                                                                            *
 * @section DESCRIPTION                                                       *
 *  This class MUST support the following public methods.                     *
 *   graphics(int rows, int cols)                                             *
 *   clear(string background)                                                 *
 *   int write(int x, int y, int c)                                           *
 *   int get_input(void)                                                      *
 *   int refresh()                                                            *
 *                                                                            *
 * @section HISTORY                                                           *
 *  12/21 Eric Gegori - File created                                          *
 *                                                                            *
 ******************************************************************************/
#include <ncurses.h>
#include <string>
#include "interfaces.h"

class graphics
{
    private:
        int     previous_debug_width = 0;
        int     width, height;
        int     write(int row_start, int col_start, std::string bg, int cols);

    public:
        graphics(int rows, int cols);
        ~graphics();
        int write(int row_start, int col_start, std::string bg);
        int write(int x, int y, int c);
        ui_message_t get_input(void);
        int refresh(void);
        int write(int row, int col, int width, int height, std::string info);
};

#endif
