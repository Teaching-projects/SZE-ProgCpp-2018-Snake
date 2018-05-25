#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <sstream>
#include <random>
#include <ctime>
#include <vector>

#include "vector2.hpp"

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

bool isSnake(Element e);

class Map {
	int x, y;
	char **map;
	int wallCount;
	int snakeSize;
	std::mt19937 rng;
	void putRandomCherryBigSnake();
public:
	Map(int n, int m);
	~Map();
	char get(int i, int j);
	char get(Vector2 v);
	void clearMap();
	void createBorder(int edge);
	void createBorder();
	void increaseSnakeSizeByOne();
	void addElement(int i, int j, Element e);
	void addElement(Vector2 v, Element e);
	void putRandomCherry();
	std::string toString();
};

#endif