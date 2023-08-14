#include "Mat4x4.h"
#include <iostream>
#include <cmath>  // For trigonometric functions

Mat4x4::Mat4x4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			elements[i][j] = 0;

			elements[i][j] = i == j ? 1.0f : 0.0f;
		}
	}
}


Mat4x4 Mat4x4::Scale(float x, float y, float z)
{
	Mat4x4 scaleMat; 
	scaleMat.elements[0][0] = x;
	scaleMat.elements[1][1] = y;
	scaleMat.elements[2][2] = z;
	return scaleMat;
}

Mat4x4 Mat4x4::Translate(float x, float y, float z)
{
	Mat4x4 translateMat;
	translateMat.elements[0][3] = x;
	translateMat.elements[1][3] = y;
	translateMat.elements[2][3] = z;
	return translateMat;
}

Mat4x4 Mat4x4::operator*(const Mat4x4& other) const
{
	Mat4x4 result;

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			float sum = 0.0f;
			for (int k = 0; k < 4; ++k) {
				sum += elements[row][k] * other.elements[k][col];
			}
			result.elements[row][col] = sum;
		}
	}

	return result;
}

Mat4x4 Mat4x4::RotateX(float angle)
{
	Mat4x4 identity;
	identity.elements[1][1] = cos(angle);
	identity.elements[1][2] = -sin(angle);
	identity.elements[2][1] = sin(angle);
	identity.elements[2][2] = cos(angle);
	return identity;
}

Mat4x4 Mat4x4::RotateY(float angle)
{
	Mat4x4 identity;
	identity.elements[0][0] = cos(angle);
	identity.elements[0][2] = sin(angle);
	identity.elements[2][0] = -sin(angle);
	identity.elements[2][2] = cos(angle);
	return identity;
}

Mat4x4 Mat4x4::RotateZ(float angle)
{
	Mat4x4 identity;
	identity.elements[0][0] = cos(angle);
	identity.elements[0][1] = -sin(angle);
	identity.elements[1][0] = sin(angle);
	identity.elements[1][1] = cos(angle);
	return identity;
}

Mat4x4 Mat4x4::Rotate(float pitch, float roll, float yaw)
{
	// Calculate the rotation matrices for each axis
	Mat4x4 pitchMatrix;
	pitchMatrix.RotateX(pitch); 

	Mat4x4 rollMatrix;
	rollMatrix.RotateY(roll);

	Mat4x4 yawMatrix;
	yawMatrix.RotateZ(yaw);
	// Apply the rotations in sequence (pitch -> roll -> yaw)
	Mat4x4 rotationMatrix = yawMatrix * rollMatrix * pitchMatrix;
	return rotationMatrix;
}