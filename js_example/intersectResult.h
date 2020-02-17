#ifndef INTERSECTRESULT_H
#define INTERSECTRESULT_H
#include "vecter3.h"
#include <iostream>

using namespace std;

class IntersectResult
{
public:
	int geometry;
	float distance;
	Vector3 position;
	Vector3 normal;

	IntersectResult()
	{
		this->geometry = 0;
		this->distance = 0;
		this->position = Vector3::zero();
		this->normal = Vector3::zero();
	}

	static IntersectResult noHit()
	{
		return IntersectResult();
	}
};

#endif // !INTERSECTRESULT_H
