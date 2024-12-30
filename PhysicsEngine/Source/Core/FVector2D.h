#pragma once

class FVector2D
{

public:

	float X;
	float Y;

public:

	FVector2D();

	FVector2D(float X, float Y);

public:

	FVector2D operator+(const FVector2D& other) const;
	FVector2D operator-(const FVector2D& other) const;
	FVector2D operator*(float scalar) const;
	FVector2D operator/(float scalar) const;

	FVector2D& operator+=(const FVector2D& other);
	FVector2D& operator-=(const FVector2D& other);

	bool operator==(const FVector2D& other) const;

	float Length() const;
	float LengthSquared() const;
	FVector2D Normalized() const;
	float Dot(const FVector2D& other) const;
	float DistanceTo(const FVector2D& other) const;

};

