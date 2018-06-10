#include "snake.hpp"

void Snake::makeMove(bool destroyTail)
{
	addNewHead(getHead() + Movement::DirectionToVector2(dir));
	if (destroyTail) {
		deleteTail();
	}
}


Snake::Snake(int x, int y, Map& map, std::string _name, std::string _movement) : habitat(map), name(_name), movement(_movement)
{
	snake.clear();
	addNewHead(Vector2(x, y) + Vector2::up);
	addNewHead(x, y);
	dir = Direction::DOWN;
	score = 0;
	scoreIncrease = 10;
	habitat.increaseSnakeSizeByOne();
	habitat.increaseSnakeSizeByOne();
}

Snake::~Snake()
{
	snake.clear();
}

int Snake::size()
{
	return snake.size();
}

Vector2 Snake::get(int i)
{
	if (i >= 0 && i < snake.size()) {
		return snake[i];
	}
	return Vector2(-1, -1);
}

Vector2 Snake::getHead()
{
	return get(0);
}

Vector2 Snake::getTail()
{
	return get(snake.size() - 1);
}

std::string Snake::getName()
{
	return name;
}

Direction Snake::getDirection()
{
	return dir;
}

bool Snake::isAlive()
{
	return !dead;
}

void Snake::addNewHead(int x, int y)
{
	Vector2 v(x, y);
	snake.insert(snake.begin(), v);
}

void Snake::addNewHead(Vector2 v)
{
	snake.insert(snake.begin(), v);
}

void Snake::deleteTail()
{
	snake.pop_back();
}

void Snake::changeDirection(Direction d)
{
	if (d != Movement::OppositeDirection(dir) && d != Direction::NONE) {
		dir = d;
	}
}

// Updates the attached map, so the snake needs not to be repainted.
void Snake::makeMoveOnMap(bool printOnScreen)
{
	Vector2 nextSpot = getHead() + Movement::DirectionToVector2(dir);
	Element nextElement = (Element)(habitat.get(nextSpot));

	if ((nextElement == Element::WALL || isSnake(nextElement)) && nextElement != Element::SNAKE_TAIL) {
		dead = true;
	}
	else if (nextElement == Element::CHERRY) {
		habitat.addElement(nextSpot, Element::SNAKE_HEAD, printOnScreen);
		habitat.addElement(getHead(), Element::SNAKE_BODY, printOnScreen);
		makeMove(false);
		habitat.increaseSnakeSizeByOne();
		// The score is static, might change later.
		score += scoreIncrease;
		scoreIncrease = 10;
		habitat.updateScore(score);

		// Placing a new cherry.
		habitat.putRandomCherry(printOnScreen);
	}
	else
	{
		habitat.addElement(nextSpot, Element::SNAKE_HEAD, printOnScreen);
		habitat.addElement(getHead(), Element::SNAKE_BODY, printOnScreen);
		if (nextElement != Element::SNAKE_TAIL) {
			habitat.addElement(getTail(), Element::EMPTY, printOnScreen);
		}
		makeMove(true);
		habitat.addElement(getTail(), Element::SNAKE_TAIL, printOnScreen);

		(scoreIncrease > 1) && (scoreIncrease--);
	}
}

void Snake::paintOnMap()
{
	for (int i = 0; i < snake.size(); i++) {
		Element e = Element::SNAKE_BODY;

		if (i == 0) {
			e = Element::SNAKE_HEAD;
		}
		else if (i == snake.size() - 1) {
			e = Element::SNAKE_TAIL;
		}

		habitat.addElement(snake[i].getX(), snake[i].getY(), e, false);
	}
}
