#include "FVector2D.h"
#include <cmath>

FVector2D::FVector2D() : 
	X(0.f),
	Y(0.f)
{
}

FVector2D::FVector2D(float XValue, float YValue) :
	X(XValue),
	Y(YValue)
{
}

FVector2D FVector2D::operator+(const FVector2D& other) const 
{
    return FVector2D(X + other.X, Y + other.Y);
}

FVector2D FVector2D::operator-(const FVector2D& other) const 
{
    return FVector2D(X - other.X, Y - other.Y);
}

FVector2D FVector2D::operator*(float scalar) const 
{
    return FVector2D(X * scalar, Y * scalar);
}

FVector2D FVector2D::operator/(float scalar) const 
{
    return FVector2D(X / scalar, Y / scalar);
}

FVector2D& FVector2D::operator+=(const FVector2D& other) 
{
    X += other.X;
    Y += other.Y;

    return *this;
}

FVector2D& FVector2D::operator-=(const FVector2D& other) 
{
    X -= other.X;
    Y -= other.Y;

    return *this;
}

bool FVector2D::operator==(const FVector2D& other) const 
{
    return X == other.X && Y == other.Y;
}

float FVector2D::Length() const 
{
    return std::sqrt(X * X + Y * Y);
}

float FVector2D::LengthSquared() const
{
    return X * X + Y * Y;
}

FVector2D FVector2D::Normalized() const 
{
    float len = Length();
    if (len == 0)
    {
        return FVector2D(0, 0);
    }

    return *this / len;
}

float FVector2D::Dot(const FVector2D& other) const 
{
    return X * other.X + Y * other.Y;
}

float FVector2D::DistanceTo(const FVector2D& other) const 
{
    return (*this - other).Length();
}
