#include "Maths/Vector2D.h"

Vector2D::Vector2D() : x(0), y(0)
{
}

Vector2D::Vector2D(float x, float y) : x(x), y(y)
{
}

float Vector2D::Dot(const Vector2D& otherVector)
{
	return x * otherVector.x + y * otherVector.y;
}

float Vector2D::Length() const
{
	return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::Normalize()
{
	float length = Length();
	if (length != 0.0f)
	{
		x /= length;
		y /= length;
	}
	return *this;
}
