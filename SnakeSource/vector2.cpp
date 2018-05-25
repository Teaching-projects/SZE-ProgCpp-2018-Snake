#include "vector2.hpp"

Vector2 Vector2::operator+(const Vector2 & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator+=(const Vector2 & v)
{
	*this = *this + v;
	return *this;
}

Vector2 Vector2::operator-() const
{
	Vector2 v(-x, -y);
	return v;
}

Vector2 Vector2::operator-(const Vector2 & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2 & v)
{
	*this = *this - v;
	return *this;
}

bool Vector2::operator==(const Vector2 & v) const
{
	return x == v.x ? y == v.y ? true : false : false;
}

Vector2 const Vector2::up(-1, 0);
Vector2 const Vector2::right(0, 1);

int Vector2::getX()
{
	return x;
}

int Vector2::getY()
{
	return y;
}
