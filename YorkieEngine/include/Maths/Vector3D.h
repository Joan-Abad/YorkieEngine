#pragma once
#include <cmath>
#include <iostream>

struct Vector3D
{
public:
	Vector3D(); 

	Vector3D(float x, float y, float z); 

	Vector3D operator + (const Vector3D& vector3D)
	{
		Vector3D returnValue;
		returnValue.x += vector3D.x;
		returnValue.y += vector3D.y;
		returnValue.z += vector3D.z;
		return returnValue;
	}

	Vector3D operator - (const Vector3D&	 vector3D)
	{
		Vector3D returnValue;
		returnValue.x -= vector3D.x;
		returnValue.y -= vector3D.y;
		returnValue.z -= vector3D.z;
		return returnValue;
	}

	Vector3D operator += (const Vector3D& vector3D)
	{
		x += vector3D.x;
		y += vector3D.y;
		z += vector3D.z;
		return *this;
	}

	Vector3D operator -= (const Vector3D& vector3D)
	{
		x -= vector3D.x;
		y -= vector3D.y;
		z -= vector3D.z;
		return *this;
	}

	// Define a friend function to overload the << operator
	friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}

	static Vector3D Cross(const Vector3D& lhs, const Vector3D& rhs);

	//Calculate the dot product of the vectors, 
	float Dot(const Vector3D& otherVector);
	
	//Length/Magnitude of a vector
	float Length() const;

	//Normalized the vector to have length 1
	Vector3D Normalize();

private:
	float x, y, z;
};