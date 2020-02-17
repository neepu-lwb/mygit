#ifndef SPHERE_H
#define SPHERE_H
#include "vecter3.h"
#include "phongMaterial.h"
#include "intersectResult.h"

class Sphere
{
public:
	Vector3 center;
	float radius;
	float sqrRadius;
	PhongMaterial material;


	Sphere() {}
	Sphere(Vector3 center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}

	Sphere copy()
	{
		return Sphere(this->center, this->radius);
	}

	void initialize()
	{
		this->sqrRadius = this->radius*this->radius;
	}

	IntersectResult intersect(Ray3 ray)
	{
		Vector3 v = ray.origin.subtract(this->center);
		float a0 = v.sqrLength() - this->sqrRadius;
		float DdotV = ray.direction.dot(v);

		if (DdotV <= 0)
		{
			float discr = DdotV*DdotV - a0;
			if (discr >= 0)
			{
				IntersectResult result = IntersectResult();
				result.geometry = 1;
				result.distance = (-1)*DdotV - sqrt(discr);
				result.position = ray.getPoint(result.distance);
				result.normal = result.position.subtract(this->center).normalize();
				return result;
			}
		}

		return IntersectResult::noHit();
	}


};


#endif // !SPHERE_H
