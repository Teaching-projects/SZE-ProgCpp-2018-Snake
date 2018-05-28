#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <vector>

#include "vector2.hpp"
#include "map.hpp"
#include "movement.hpp"


class Snake {
	std::vector<Vector2> snake;
	Direction dir;
	Map& habitat;
	bool dead;
	void makeMove(bool destroyTail);
	void addNewHead(int x, int y);
	void addNewHead(Vector2 v);
	void deleteTail();
public:
	Snake(int x, int y, Map& map);
	~Snake();
	int size();
	Vector2 get(int i);
	Vector2 getHead();
	Vector2 getTail();
	Direction getDirection();
	bool isAlive();

	void changeDirection(Direction d);
	void makeMoveOnMap(bool printOnScreen);
	void paintOnMap();
};

#endif
