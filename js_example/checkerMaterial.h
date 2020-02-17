#ifndef CHECKERMATERIAL_H
#define CHECKERMATERIAL_H
#include "vecter3.h"
#include "color.h"
#include "ray3.h"

class CheckerMaterial
{
public:
	float scale;
	float reflectiveness;


	CheckerMaterial() {}
	CheckerMaterial(float scale, float reflectiveness)
	{
		this->reflectiveness = reflectiveness;
		this->scale = scale;
	}

	Color sample(Ray3 ray, Vector3 position, Vector3 normal)
	{
		return abs((int)(floorf(position.x*0.3) + floorf(position.y*0.3) + floorf(position.z*0.3)) % 2) < 1 ? Color::black() : Color::white();
	}
};

#endif // !CHECKERMATERIAL_H

