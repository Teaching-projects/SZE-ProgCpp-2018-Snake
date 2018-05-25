#include <iostream>

#include "snake.hpp"

#ifdef _WIN32
#include <Windows.h>

#define CLEAR_SCREEN_STRING "cls"
#elif __linux__


#define CLEAR_SCREEN_STRING "clear"
#endif


int main() {

	Map map(10, 10);
	Snake snake(5, 5, map);

	map.createBorder();

	snake.paintOnMap();
	map.putRandomCherry();


	std::cout << map.toString() << std::endl;
	
	char c;
	do {
		std::cin >> c;
		snake.changeDirection(Movement::CharToDirection(c));
		snake.makeMoveOnMap();
		system(CLEAR_SCREEN_STRING);
		std::cout << map.toString() << std::endl;
	} while (snake.isAlive());
	
	std::cout << std::endl << "Your snake has died :(";

	std::cin >> c;
	return 0;
}