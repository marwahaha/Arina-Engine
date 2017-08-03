#pragma once
class Vector2f
{
public:
	Vector2f();
	Vector2f(float x, float y);
	~Vector2f();

	inline float const getX() { return _x; }
	inline float const getY() { return _y; }
private:
	float _x;
	float _y;
};

