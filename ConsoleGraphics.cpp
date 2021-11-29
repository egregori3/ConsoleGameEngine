#include "ConsoleGraphics.h"

ConsoleGraphics& ConsoleGraphics::instance()
{
#ifdef WIN32
    static ConsoleGraphics* instance = new WINconsole();
#else
    static ConsoleGraphics* instance = new LINUXconsole();
#endif

    return *instance;
}