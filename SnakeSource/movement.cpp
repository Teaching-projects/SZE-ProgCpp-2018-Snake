#include "movement.hpp"


Movement::Movement(std::string chars) :
	up(chars[0]), left(chars[1]),
	down(chars[2]), right(chars[3]) {}

bool Movement::isMovement(char c)
{
	if(c == up || c == right ||
		c == down || c == left)
	{
		return true;
	}
	return false;
}

Direction Movement::CharToDirection(char c) const
{
	if (c == up) {
		return Direction::UP;
	}
	else if (c == left) {
		return Direction::LEFT;
	}
	else if (c == down) {
		return Direction::DOWN;
	}
	else if (c == right) {
		return Direction::RIGHT;
	}
	else {
		return Direction::NONE;
	}

	/*
	switch (c) {
	case up:
		return Direction::UP;
	case right:
		return Direction::RIGHT;
	case down:
		return Direction::DOWN;
	case left:
		return Direction::LEFT;
	default:
		return Direction::NONE;
	}
	*/
}

Vector2 Movement::DirectionToVector2(Direction d)
{
	switch (d) {
	case Direction::UP:
		return Vector2::up;
	case Direction::RIGHT:
		return Vector2::right;
	// Note minus signs.
	case Direction::DOWN:
		return -Vector2::up;
	case Direction::LEFT:
		return -Vector2::right;
	default:
		return Vector2(0, 0);
	}
}

Direction Movement::Vector2ToDirection(Vector2 v)
{
	if (v == Vector2::up) {
		return Direction::UP;
	}
	else if (v == Vector2::right) {
		return Direction::RIGHT;
	}
	// Note minus signs.
	else if (v == -Vector2::up) {
		return Direction::DOWN;
	}
	else if (v == -Vector2::right) {
		return Direction::LEFT;
	}
	else {
		return Direction::NONE;
	}
}

Direction Movement::OppositeDirection(Direction d)
{
	return Vector2ToDirection(-DirectionToVector2(d));
}
