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
 *  https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/                         *
 *  https://www.cplusplus.com/doc/tutorial/preprocessor/                      *
 *  https://gcc.gnu.org/onlinedocs/cpp/                                       *
 *                                                                            *
 ******************************************************************************/
#include <string>
#include <ncurses.h>
#include <iostream>
#include "interfaces.h"
#include "graphics.h"


graphics::graphics(int rows, int cols)
{
    std::cout << "LinuxText graphics init" << " Rows: " << rows << " Cols: " << cols << std::endl;
    std::cout << "Press ANY KEY to start game" << std::endl;
    std::cin.get();
#ifndef DISABLE_GRAPHICS
    initscr(); // Start curses mode 
    cbreak();  // Line buffering disabled, Pass on everty thing to me
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);   /* I need that nifty F1 */
//    my_win = newwin(rows, cols, 0, 0);
    curs_set(0);
#endif
    width  = cols;
    height = rows;
}

graphics::~graphics()
{
    std::cout << "LinuxText graphics shutdown" << std::endl;
#ifndef DISABLE_GRAPHICS
    endwin(); /* End curses mode */
#endif
}

int graphics::write( int row_start, int col_start, std::string bg, int cols)
{
#ifndef DISABLE_GRAPHICS
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
#endif
    return 0;        
}

int graphics::write(int row_start, int col_start, std::string bg)
{
#ifndef DISABLE_GRAPHICS
    write(row_start, col_start, bg, width);
    refresh();
    write(row_start, col_start, bg, width);
    refresh();
#endif
    return 0;
}

int graphics::write(int row, int col, int width, int height, std::string info)
{

#ifndef DISABLE_GRAPHICS
    for(int ii=0; ii<width; ii++)
        mvaddch(row, col+ii, ' ');
    mvaddstr(row, col, info.c_str());
#else
    std::cout << "(" << row << "," << col << "," << width << "," << height << ")";
    std::cout << "  info: "<< info << std::endl;
#endif
}

int graphics::write(int row, int col, int c)
{
#ifndef DISABLE_GRAPHICS
    mvaddch(row, col, (char)c);
#else
    std::cout << "graphics::write(" << row << " , " << col << " = " << c << std::endl;
#endif
    return 0;
}

ui_message_t graphics::get_input(void)
{
    ui_message_t output = UI_NONE;
    int ch = getch();

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
//    refresh();  This is disabled because it causes a seg fault
    return 0;
}

