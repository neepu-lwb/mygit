#ifndef RAY3_H
#define RAY3_H
#include "vecter3.h"

class Ray3
{
public:
	Vector3 origin;
	Vector3 direction;

	Ray3::Ray3()
	{

	}

	Ray3::Ray3(Vector3 origin, Vector3 direction)
	{
		this->origin = origin;
		this->direction = direction;
	}

	Vector3 Ray3::getPoint(float t)
	{
		return this->origin.add(this->direction.multiply(t));
	}
};


#endif // !RAY3_H

