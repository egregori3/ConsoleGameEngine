/******************************************************************************
 * @file   graphics.h                                                         *
 * @author Eric Gregori -  https://github.com/egregori3                       *
 * @data   12/21                                                              *
 *                                                                            *
 * @brief  Linux ncurses based "graphics" implementation.                     *
 *                                                                            *
 * @section DESCRIPTION                                                       *
 *                                                                            *
 *                                                                            *
 * @section HISTORY                                                           *
 *  12/21 Eric Gegori - File created                                          *
 *                                                                            *
 * @section SOURCES                                                           *
 *  https://github.com/egregori3/ConsoleGameEngine/blob/master/README.md      *
 *  https://opensource.com/article/21/8/ncurses-linux                         *
 *  https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html             *
 ******************************************************************************/
#include <string>
#include <ncurses.h>
#include <iostream>
#include "interfaces.h"
#include "graphics.h"


graphics::graphics(int rows, int cols)
{
    std::cout << "LinuxText graphics init" << " Rows: " << rows << " Cols: " << cols << std::endl;
    initscr(); // Start curses mode 
    cbreak();  // Line buffering disabled, Pass on everty thing to me
    keypad(stdscr, TRUE);   /* I need that nifty F1 */
    my_win = newwin(rows, cols, 0, 0);
    curs_set(0);
    width  = cols;
    height = rows;
}

graphics::~graphics()
{
    delwin(my_win);
    endwin(); /* End curses mode */
    std::cout << "LinuxText graphics shutdown" << std::endl;
}

int graphics::write( int row_start, int col_start, std::string bg, int cols)
{
    int row = row_start;
    int col = col_start;
    for (auto it = bg.cbegin() ; it != bg.cend(); ++it)
    {
        mvaddch(row, col++, *it);
        if(col == cols)
        {
            row++;
            col = 0;
        }
    }

    return 0;        
}

int graphics::write(std::string bg)
{
    write(0, 0, bg, width);
    wrefresh(my_win);
    write(0, 0, bg, width);
    wrefresh(my_win);

    return 0;
}

int graphics::write(int row, int col, int c)
{
    mvaddch(row, col, (char)c);
    return 0;
}

ui_t graphics::get_input(void)
{
    int ch = getch();
    ui_t output = UI_NONE;

    switch(ch)
    {
        case KEY_LEFT:
            output = UI_LEFT;
            break;

        case KEY_RIGHT:
            output = UI_RIGHT;
            break;

        case KEY_UP:
            output = UI_UP;
            break;

        case KEY_DOWN:
            output = UI_DOWN;
            break;

        default:
            break;
    }

    return output;
}

int graphics::refresh(void)
{
    wrefresh(my_win);

    return 0;
}

