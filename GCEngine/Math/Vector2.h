#pragma once
#include "../GCEngine.h"

class GCENGINE_API Vector2
{
public:
	Vector2();
	Vector2(const float X, const float Y);

	Vector2& Add(const Vector2& Other);
	Vector2& Subtract(const Vector2& Other);
	Vector2& Multiply(const Vector2& Other);
	Vector2& Divide(const Vector2& Other);

	friend Vector2 operator+(Vector2 Left, const Vector2& Right);
	friend Vector2 operator-(Vector2 Left, const Vector2& Right);
	friend Vector2 operator*(Vector2 Left, const Vector2& Right);
	friend Vector2 operator/(Vector2 Left, const Vector2& Right);

	bool operator==(const Vector2& Other);
	bool operator!=(const Vector2& Other);

	Vector2& operator+=(const Vector2& Other);
	Vector2& operator-=(const Vector2& Other);
	Vector2& operator*=(const Vector2& Other);
	Vector2& operator/=(const Vector2& Other);

public:
	float X, Y;
};
