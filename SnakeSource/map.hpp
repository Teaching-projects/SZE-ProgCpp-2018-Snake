#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <iostream>
#include <sstream>
#include <random>
#include <ctime>
#include <vector>

#include "vector2.hpp"

#ifdef __linux__
#include "linuxterminalhandler.hpp"
#elif _WIN32
#include "windowsterminalhandler.hpp"
#endif
/*
#define MAP_EMPTY ' '
#define MAP_WALL 'X'
#define MAP_SNAKE_HEAD 'Q'
#define MAP_SNAKE_BODY 'O'
#define MAP_SNAKE_TAIL '0'
#define MAP_CHERRY '6'
*/

enum class Element : char { 
	EMPTY = ' ', 
	WALL = 'X',
	SNAKE_HEAD = 'Q',
	SNAKE_BODY = 'O',
	SNAKE_TAIL = '0',
	CHERRY = '6',
	NONE
};

// todo: move this to a different file?!
void ChangeColor(Element e);

bool isSnake(Element e);

class Map {
	int x, y;
	char **map;
	int wallCount;
	int snakeSize;
	int offset;
	int maxScore;
	std::mt19937 rng;
	void putRandomCherryBigSnake(bool printOnScreen);
public:
	Map(int n, int m, int offset);
	Map(int n, int m);
	~Map();
	char get(int i, int j);
	char get(Vector2 v);
	int countEmpty();
	int getMaxScore();
	void clearMap();
	void createBorder(int edge);
	void createBorder();
	void increaseSnakeSizeByOne();
	void addElement(int i, int j, Element e, bool printOnScreen);
	void addElement(Vector2 v, Element e, bool printOnScreen);
	void putRandomCherry(bool printOnScreen);
	void updateScore(int score, int scoreOffset);
	void printElement(int i, int j);
	void printElement(Vector2 v);
	void print();
	std::string toString();
};

#endif