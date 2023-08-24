#include "Maths/Vector3D.h"

Vector3D::Vector3D() : x(0), y(0), z(0)
{
}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3D Vector3D::Cross(const Vector3D& lhs, const Vector3D& rhs)
{
	Vector3D returnValue;
	returnValue.x = lhs.y * rhs.z - lhs.z * rhs.y;
	returnValue.x = lhs.z * rhs.x - lhs.x * rhs.z;
	returnValue.x = lhs.x * rhs.y - lhs.y * rhs.x;
	return returnValue;
}

float Vector3D::Dot(const Vector3D& otherVector)
{
	return x * otherVector.x + y * otherVector.y + z * otherVector.z;
}

float Vector3D::Length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::Normalize()
{
	float length = Length();
	if (length != 0.0f)
	{
		x /= length;
		y /= length;
		z /= length;
	}
	return *this;
}
