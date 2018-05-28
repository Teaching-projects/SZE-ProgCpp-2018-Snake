#include <iostream>
#include <ctime>

#include "snake.hpp"

#ifdef _WIN32
#include <Windows.h>
// todo: implement CursorToPosition(int, int);
// todo: implement ChangeColor(Element); (in map.hpp yet)
void CursorToPosition(int x, int y) { std::cout << "No implementation."; }
#define CLEAR_SCREEN_STRING "cls"

#elif __linux__
#include "linuxterminalhandler.hpp"
#define CLEAR_SCREEN_STRING "clear"

#else
#define CLEAR_SCREEN_STRING "Unsupported Operating System."
#endif

#define COOLDOWN_SECONDS 0.5

int main() {
	clock_t t;
	clock_t coolDown = COOLDOWN_SECONDS * CLOCKS_PER_SEC;

	int x, y;
	x = y = 0;
	std::string name = "AnonymuS";

	std::cout << "Size of the map [x y] >> ";
	std::cin >> x >> y;
	std::cout << "Name your snake >> ";
	std::cin >> name;
	std::cout.flush();

	(x < 6) && (x = 6);
	(y < 6) && (y = 6);

	Map map(x, y);
	Snake snake(x / 2, y / 2, map);

	map.createBorder();
	snake.paintOnMap();
	map.putRandomCherry(false);

	system(CLEAR_SCREEN_STRING);
	map.print();
	
#ifdef __linux__
	TerminalHandler::initNoBuffering();
#endif

	char c, dir;
	t = clock() + coolDown * 4;
	do {
		if(kbhit()){
			c = getch();
			if(Movement::isMovement(c)){
				dir = c;
			}
		}
		if(t < clock()){
			snake.changeDirection(Movement::CharToDirection(dir));
			snake.makeMoveOnMap(true);
			t = clock() + coolDown;
		}
	} while (snake.isAlive() && map.countEmpty() > 0);
#ifdef __linux__
	TerminalHandler::resetNoBuffering();
#endif

	if(snake.isAlive()){
		std::cout << std::endl << name << " has filled the map :)" << std::endl;
	} else {
		std::cout << std::endl << name << " has died :(" << std::endl;
	}

	std::cin >> c;
	return 0;
}