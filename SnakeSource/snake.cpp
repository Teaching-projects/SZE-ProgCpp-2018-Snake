#include "snake.hpp"

void Snake::makeMove(bool destroyTail)
{
	addNewHead(getHead() + Movement::DirectionToVector2(dir));
	if (destroyTail) {
		deleteTail();
	}
}


Snake::Snake(int x, int y, Map& map) : habitat(map)
{
	snake.clear();
	addNewHead(Vector2(x, y) + Vector2::up);
	addNewHead(x, y);
	dir = Direction::DOWN;
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
void Snake::makeMoveOnMap()
{
	Vector2 nextSpot = getHead() + Movement::DirectionToVector2(dir);
	Element nextElement = (Element)(habitat.get(nextSpot));

	if ((nextElement == Element::WALL || isSnake(nextElement)) && nextElement != Element::SNAKE_TAIL) {
		dead = true;
	}
	else if (nextElement == Element::CHERRY) {
		habitat.addElement(nextSpot, Element::SNAKE_HEAD);
		habitat.addElement(getHead(), Element::SNAKE_BODY);
		makeMove(false);
		habitat.increaseSnakeSizeByOne();

		// Placing a new cherry.
		habitat.putRandomCherry();
	}
	else
	{
		habitat.addElement(nextSpot, Element::SNAKE_HEAD);
		habitat.addElement(getHead(), Element::SNAKE_BODY);
		if (nextElement != Element::SNAKE_TAIL) {
			habitat.addElement(getTail(), Element::EMPTY);
		}
		makeMove(true);
		habitat.addElement(getTail(), Element::SNAKE_TAIL);
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

		habitat.addElement(snake[i].getX(), snake[i].getY(), e);
	}
}
