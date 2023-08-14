#include "Rotator.h"

Rotator::Rotator() : pitch(0), roll(0), yaw(0)
{
}

Rotator::Rotator(float pitch, float roll, float yaw)
{
	this->pitch = pitch;
	this->roll = roll;
	this->yaw = yaw;
}
