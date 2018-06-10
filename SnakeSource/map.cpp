#include "map.hpp"

#ifdef __linux__
void ChangeColor(Element e)
{
	switch(e){
	case Element::WALL:
		ChangeTrueColor(40, 40, 180);
		break;
	case Element::SNAKE_HEAD:
		ChangeTrueColor(0, 180, 40);
		break;
	case Element::SNAKE_BODY:
		ChangeTrueColor(0, 140, 30);
		break;
	case Element::SNAKE_TAIL:
		ChangeTrueColor(80, 140, 20);
		break;
	case Element::CHERRY:
		ChangeTrueColor(240, 20, 20);
		break;
	default:
		break;
	}
}
#elif _WIN32
void ChangeColor(Element e)
{
	switch (e) {
	case Element::WALL:
		Change16Color(9);
		break;
	case Element::SNAKE_HEAD:
		Change16Color(10);
		break;
	case Element::SNAKE_BODY:
		Change16Color(2);
		break;
	case Element::SNAKE_TAIL:
		Change16Color(6);
		break;
	case Element::CHERRY:
		Change16Color(12);
		break;
	default:
		break;
	}
}
#else
void ChangeColor(Element e) {}
#endif

bool isSnake(Element e)
{
	if (e == Element::SNAKE_TAIL || e == Element::SNAKE_BODY || e == Element::SNAKE_HEAD) {
		return true;
	}
	return false;
}

// If the snake is too big, finding a free spot is hard randomly.
// Different handling in this case is desired.
void Map::putRandomCherryBigSnake(bool printOnScreen)
{
	if(countEmpty() <= 0){
		return;
	}

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

	addElement(xVector[rx], yVector[rx][ry], Element::CHERRY, printOnScreen);
}

Map::Map(int n, int m, int _offset) : x(n), y(m), offset(_offset)
{
	// Allocating the map.
	map = new char*[x];
	for (int i = 0; i < x; i++) {
		map[i] = new char[y];
	}

	// Set each element to the default value.
	clearMap();
}

Map::Map(int n, int m) : Map(n, m, 0) {}

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

int Map::countEmpty()
{
	return x * y - wallCount - snakeSize;
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

void Map::addElement(int i, int j, Element e, bool printOnScreen)
{
	if (i >= 0 && i < x && j >= 0 && j < y) {
		map[i][j] = (char)e;
	
		if(printOnScreen){
			printElement(i, j);
		}
	}
}

void Map::addElement(Vector2 v, Element e, bool printOnScreen)
{
	addElement(v.getX(), v.getY(), e, printOnScreen);
}

void Map::putRandomCherry(bool printOnScreen)
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

		addElement(rx, ry, Element::CHERRY, printOnScreen);
	}
	else {
		putRandomCherryBigSnake(printOnScreen);
	}
}

void Map::updateScore(int score)
{
	CursorToPosition(offset, y + 2);
	std::cout << score;
	std::cout.flush();
}


void Map::printElement(int i, int j)
{
	ChangeColor((Element)map[i][j]);
	CursorToPosition(i + offset, j);
	std::cout << map[i][j];
	ResetText();
	CursorToPosition(x + offset, y);
	std::cout.flush();
}

void Map::printElement(Vector2 v){
	printElement(v.getX(), v.getY());
}

void Map::print()
{
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			if(map[i][j] != (char)Element::EMPTY){
				printElement(i, j);
			}
		}
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
}
