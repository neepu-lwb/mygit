#ifndef PLANE_H
#define PLANE_H
#include "vecter3.h"
#include "intersectResult.h"
#include "ray3.h"
#include "checkerMaterial.h"

class Plane
{
public:
	Vector3 normal;
	Vector3 position;
	float d;
	CheckerMaterial material;


	Plane() {}
	Plane(Vector3 normal, float d)
	{
		this->normal = normal;
		this->d = d;
	}

	Plane copy()
	{
		return Plane(this->normal, this->d);
	}

	void initialize()
	{
		this->position = this->normal.multiply(this->d);
	}

	IntersectResult intersect(Ray3 ray)
	{
		float a = ray.direction.dot(this->normal);
		if (a >= 0)
		{
			return IntersectResult::noHit();
		}

		float b = this->normal.dot(ray.origin.subtract(this->position));
		IntersectResult result = IntersectResult();
		result.geometry = 1;
		result.distance = (-1)*b / a;
		result.position = ray.getPoint(result.distance);
		result.normal = this->normal;
		return result;
	}

};


#endif // !PLANE_H
