#include "map.hpp"

bool isSnake(Element e)
{
	if (e == Element::SNAKE_TAIL || e == Element::SNAKE_BODY || e == Element::SNAKE_HEAD) {
		return true;
	}
	return false;
}

// If the snake is too big, finding a free spot is hard randomly.
// Different handling in this case is desired.
void Map::putRandomCherryBigSnake()
{
	std::vector<int> xVector;
	std::vector<std::vector<int>> yVector;

	for (int i = 0; i < x; i++) {
		int count = 0;
		std::vector<int> temp;

		for (int j = 0; j < y; j++) {
			if (map[i][j] == (char)Element::EMPTY) {
				count++;
				temp.push_back(j);
			}
		}
		if (count) {
			xVector.push_back(i);
			yVector.push_back(temp);
		}
	}

	std::uniform_int_distribution<uint32_t> xDist(0, xVector.size() - 1);
	int rx = xDist(rng);

	std::uniform_int_distribution<uint32_t> yDist(0, yVector[rx].size() - 1);
	int ry = yDist(rng);

	addElement(xVector[rx], yVector[rx][ry], Element::CHERRY);
}

Map::Map(int n, int m) : x(n), y(m)
{
	// Allocating the map.
	map = new char*[x];
	for (int i = 0; i < x; i++) {
		map[i] = new char[y];
	}

	// Set each element to the default value.
	clearMap();
}

Map::~Map()
{
	if (map && map[0]) {
		for (int i = 0; i < x; i++) {
			delete[] map[i];
		}
		delete[] map;
	}
}

char Map::get(int i, int j)
{
	if (i >= 0 && i < x && j >= 0 && j < y) {
		return map[i][j];
	}
	return -1;
}

char Map::get(Vector2 v)
{
	return get(v.getX(), v.getY());
}

void Map::clearMap()
{
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			map[i][j] = (char)Element::EMPTY;
		}
	}
	wallCount = 0;
	snakeSize = 0;
}

// "edge" represents the distance from the allocated memory edges
// to the actual border positions.
void Map::createBorder(int edge)
{
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (i == 0 + edge || i == x - 1 - edge || j == 0 + edge || j == y - 1 - edge) {
				map[i][j] = (char)Element::WALL;
				wallCount++;
			}
		}
	}
}

void Map::createBorder()
{
	createBorder(0);
}

void Map::increaseSnakeSizeByOne()
{
	snakeSize++;
}

void Map::addElement(int i, int j, Element e)
{
	if (i >= 0 && i < x && j >= 0 && j < y) {
		map[i][j] = (char)e;
	}
}

void Map::addElement(Vector2 v, Element e)
{
	addElement(v.getX(), v.getY(), e);
}

void Map::putRandomCherry()
{
	float magicNumber = .35f;
	uint32_t seed = (uint32_t)time(0);
	rng.seed(seed);

	if (snakeSize < (x * y - wallCount) * magicNumber) {
		std::uniform_int_distribution<uint32_t> xDist(0, x - 1);
		std::uniform_int_distribution<uint32_t> yDist(0, y - 1);

		int rx, ry;
		do {
			rx = xDist(rng);
			ry = yDist(rng);
		} while (map[rx][ry] != (char)Element::EMPTY);

		addElement(rx, ry, Element::CHERRY);
	}
	else {
		putRandomCherryBigSnake();
	}
}

std::string Map::toString()
{
	std::ostringstream oss;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			oss << map[i][j];
		}
		oss << '\n';
	}
	return oss.str();
	/*
	std::ostringstream oss;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			oss << map[j][i];
		}
		oss << '\n';
	}
	return oss.str();
	*/
}
