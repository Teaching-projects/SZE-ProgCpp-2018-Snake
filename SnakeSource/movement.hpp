#ifndef __ROTATION_HPP__
#define __ROTATION_HPP__

#include "vector2.hpp"

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

class Movement {
	Movement() {}

	// Buttons pressed for movement.
	static const char up;
	static const char right;
	static const char down;
	static const char left;
public:
	static bool isMovement(char c);
	static Direction CharToDirection(char c);
	static Vector2 DirectionToVector2(Direction d);
	static Direction Vector2ToDirection(Vector2 v);
	static Direction OppositeDirection(Direction d);
};

#endif