#pragma once
#include <vector>

/******************************************************************************/
/*
 * @brief - Virtual Console base class for Windows and Linux
 * http://gameprogrammingpatterns.com/singleton.html
 * https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#samples
 * 
 */


class ConsoleGraphics
{
	private:
		std::vector<Character> Characters;

	protected:
		ConsoleGraphics() {}

	public:
		static ConsoleGraphics& instance(); // Singleton (static instance)
		virtual ~ConsoleGraphics() {}
		virtual void UpdateConsole() = 0;

};

