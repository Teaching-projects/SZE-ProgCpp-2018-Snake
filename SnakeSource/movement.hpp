#ifndef __ROTATION_HPP__
#define __ROTATION_HPP__

#include <string>

#include "vector2.hpp"

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

class Movement {

	// Buttons pressed for movement.

	const char up;
	const char left;
	const char down;
	const char right;
public:
	Movement(std::string chars);

	bool isMovement(char c);
	Direction CharToDirection(char c) const;
	static Vector2 DirectionToVector2(Direction d);
	static Direction Vector2ToDirection(Vector2 v);
	static Direction OppositeDirection(Direction d);
};

#endif