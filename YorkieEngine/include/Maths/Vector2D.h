#pragma once
#include <cmath>
#include <iostream>

struct Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);

	Vector2D operator + (const Vector2D& vector3D)
	{
		Vector2D returnValue;
		returnValue.x += vector3D.x;
		returnValue.y += vector3D.y;
		return returnValue;
	}

	Vector2D operator - (const Vector2D& vector3D)
	{
		Vector2D returnValue;
		returnValue.x -= vector3D.x;
		returnValue.y -= vector3D.y;
		return returnValue;
	}

	Vector2D operator += (const Vector2D& vector3D)
	{
		x += vector3D.x;
		y += vector3D.y;
		return *this;
	}

	Vector2D operator -= (const Vector2D& vector3D)
	{
		x -= vector3D.x;
		y -= vector3D.y;
		return *this;
	}

	// Define a friend function to overload the << operator
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}

	//Calculate the dot product of the vectors, 
	float Dot(const Vector2D& otherVector);

	//Length/Magnitude of a vector
	float Length() const;

	//Normalized the vector to have length 1
	Vector2D Normalize();

private:
	float x, y;
};