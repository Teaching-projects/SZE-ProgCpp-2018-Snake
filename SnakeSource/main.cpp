#include <iostream>
#include <ctime>

#include "snake.hpp"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
// todo: implement CursorToPosition(int, int);
// todo: implement ChangeColor(Element); (in map.hpp yet)
#define CLEAR_SCREEN_STRING "cls"

#elif __linux__
#include "linuxterminalhandler.hpp"
#define CLEAR_SCREEN_STRING "clear"

#else
#define CLEAR_SCREEN_STRING "Unsupported Operating System."
#endif

#define COOLDOWN_SECONDS 0.5

bool gameOver(std::vector<Map*> maps, std::vector<Snake*> snakes);
Snake* whoWon(std::vector<Map*> maps, std::vector<Snake*> snakes);
Snake* whoLost(std::vector<Snake*> snakes);

int main() {
	clock_t t;
	clock_t coolDown = COOLDOWN_SECONDS * CLOCKS_PER_SEC;

	int x, y, playerCount;
	bool oneMap = false;
	x = y = 0;
	playerCount = -1;
	std::string name = "AnonymuS";
	std::string movement = "wasd";

	std::cout << "Number of players? >> ";
	std::cin >> playerCount;

	(playerCount < 1) && (playerCount = 1);

	if(playerCount > 1){
		std::string input = "no";
		std::cout << "All snake on one map? ([y]es, [n]o) >> ";
		std::cin >> input;
		if(input[0] == 'y' || input[0] == 'Y'){
			oneMap = true;
		}
	}

	std::cout << "Size of the map [x y] >> ";
	std::cin >> x >> y;

	(x < 6) && (x = 6);
	(y < 6) && (y = 6);
	
	std::vector<Map*> maps;
	std::vector<Snake*> snakes;

	if(oneMap){
		Map *map = new Map(x, y);
		maps.push_back(map);

		maps[0]->createBorder();
	}

	// No error handling on bad input, be careful ;)
	for (int i = 0; i < playerCount; i++) {
		std::cout << "Name your snake >> ";
		std::cin >> name;
		std::cout << "Movement buttons [up, left, down, right](e.g. \"wasd\")";
		std::cin >> movement;
		std::cout.flush();

		Snake *snake;

		if(!oneMap){
			Map *map = new Map(x, y, i * (x + 3));
			maps.push_back(map);
			snake = new Snake(x / 2, y / 2, *maps[(oneMap ? 0 : i)], name, movement);
		} else {
			snake = new Snake((x / /*(playerCount + 1)) * (i + 1)*/ 2), (y / (playerCount + 1)) * (i + 1), *maps[(oneMap ? 0 : i)], name, movement, 3 * i);
		}
	
		snakes.push_back(snake);

		if(!oneMap){
			maps[i]->createBorder();
		}
		snakes[i]->paintOnMap();
		if(!oneMap){
			maps[i]->putRandomCherry(false);
		}
	}

	if(oneMap){
		maps[0]->putRandomCherry(false);
	}

	std::vector<char> dir;
	system(CLEAR_SCREEN_STRING);
	for (int i = 0; i < maps.size(); i++) {
		maps[i]->print();
		dir.push_back(' ');
	}
	
#ifdef __linux__
	TerminalHandler::initNoBuffering();
#endif

	char c;
	t = clock() + coolDown * 4;
	do {
		if(_kbhit()){
			c = _getch();
			for (int i = 0; i < snakes.size(); i++) {
				if (snakes[i]->movement.isMovement(c)) {
					dir[i] = c;
				}
			}
		}
		if(t < clock()){
			for (int i = 0; i < snakes.size(); i++) {
				snakes[i]->changeDirection(snakes[i]->movement.CharToDirection(dir[i]));
				snakes[i]->makeMoveOnMap(true);
			}
			t = clock() + coolDown;
		}
	} while (!gameOver(maps, snakes));
#ifdef __linux__
	TerminalHandler::resetNoBuffering();
#endif

	CursorToPosition(x + 4, y + 4);
	Snake* snake = whoWon(maps, snakes);
	if(snake != nullptr) {
		std::cout << snake->getName() << " has filled the map :)" << std::endl;
	} else {
		snake = whoLost(snakes);
		if (snake != nullptr) {
			std::cout << snake->getName() << " has died :(" << std::endl;
		}
		else {
			std::cout << "There was an anomaly, couldn't detect what ended the match.." << std::endl;
		}
	}

	for (int i = 0; i < maps.size(); i++) {
		delete maps[i];
	}
	for (int i = 0; i < snakes.size(); i++) {
		delete snakes[i];
	}

	int offSet = oneMap ? 1 : playerCount;
	CursorToPosition(offSet * x + offSet * 6, offSet * y + offSet * 6);
	std::cout << std::endl;
	return 0;
}


bool gameOver(std::vector<Map*> maps, std::vector<Snake*> snakes) {
	for (int i = 0; i < maps.size(); i++) {
		if (maps[i]->countEmpty() <= 0) {
			return true;
		}
	}
	for (int i = 0; i < snakes.size(); i++) {
		if (!snakes[i]->isAlive()) {
			return true;
		}
	}
	return false;
}

Snake* whoWon(std::vector<Map*> maps, std::vector<Snake*> snakes)
{
	for (int i = 0; i < maps.size(); i++) {
		if (maps[i]->countEmpty() == 0) {
			return snakes[i];
		}
	}
	return nullptr;
}

Snake* whoLost(std::vector<Snake*> snakes)
{
	for (int i = 0; i < snakes.size(); i++) {
		if (!snakes[i]->isAlive()) {
			return snakes[i];
		}
	}
	return nullptr;
}

/*
// Solo test input for 2 player.
2
yes
20 20
player1
wasd
player2
ijkl
*/