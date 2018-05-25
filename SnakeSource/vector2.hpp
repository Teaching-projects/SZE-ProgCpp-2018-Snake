#ifndef __VECTOR2_HPP__
#define __VECTOR2_HPP__

class Vector2 {
	int x, y;
public:
	Vector2(int _x, int _y) : x(_x), y(_y) {}

	Vector2 operator+(const Vector2& v);
	Vector2 operator+=(const Vector2& v);
	Vector2 operator-() const;
	Vector2 operator-(const Vector2& v);
	Vector2 operator-=(const Vector2& v);
	bool operator==(const Vector2& v) const;

	static const Vector2 up;
	static const Vector2 right;

	int getX();
	int getY();
};

#endif
