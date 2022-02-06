#include "Vector2.h"

Vector2::Vector2() : Vector2(0, 0)
{
}

Vector2::Vector2(const float X, const float Y)
    : X(X)
    , Y(Y)
{
}

Vector2& Vector2::Add(const Vector2& Other)
{
    X += Other.X;
    Y += Other.Y;
    return *this;
}

Vector2& Vector2::Subtract(const Vector2& Other)
{
    X -= Other.X;
    Y -= Other.Y;
    return *this;
}

Vector2& Vector2::Multiply(const Vector2& Other)
{
    X *= Other.X;
    Y *= Other.Y;
    return *this;
}

Vector2& Vector2::Divide(const Vector2& Other)
{
    X /= Other.X;
    Y /= Other.Y;
    return *this;
}

bool Vector2::operator==(const Vector2& Other)
{
    return (X == Other.X) && (Y == Other.Y);
}

bool Vector2::operator!=(const Vector2& Other)
{
    return !(*this == Other);
}

Vector2& Vector2::operator+=(const Vector2& Other)
{
    return Add(Other);
}

Vector2& Vector2::operator-=(const Vector2& Other)
{
    return Subtract(Other);
}

Vector2& Vector2::operator*=(const Vector2& Other)
{
    return Multiply(Other);
}

Vector2& Vector2::operator/=(const Vector2& Other)
{
    return Divide(Other);
}

Vector2 operator+(Vector2 Left, const Vector2& Right)
{
    return Left.Add(Right);
}

Vector2 operator-(Vector2 Left, const Vector2& Right)
{
    return Left.Subtract(Right);
}

Vector2 operator*(Vector2 Left, const Vector2& Right)
{
    return Left.Multiply(Right);
}

Vector2 operator/(Vector2 Left, const Vector2& Right)
{
    return Left.Divide(Right);
}
