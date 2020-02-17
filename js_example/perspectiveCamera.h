#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H
#include "ray3.h"
#include "math.h"
#define PI 3.141592654

class PerspectiveCamera
{
public:
	Vector3 eye;
	Vector3 front;
	Vector3 refUp;
	float fov;
	Vector3 right;
	Vector3 up;
	float fovScale;

	PerspectiveCamera() {}
	PerspectiveCamera(Vector3 eye, Vector3 front, Vector3 up, float fov)
	{
		this->eye = eye;
		this->front = front;
		this->refUp = up;
		this->fov = fov;
	}

	void initialize()
	{
		this->right = this->front.cross(this->refUp);
		this->up = this->right.cross(this->front);
		this->fovScale = tanf(this->fov*0.5*PI / 180) * 2;
	}

	Ray3 generateRay(float x, float y)
	{
		Vector3 r = this->right.multiply((x - 0.5)*this->fovScale);
		Vector3 u = this->up.multiply((y - 0.5)*this->fovScale);
		return Ray3(this->eye, this->front.add(r).add(u).normalize());
	}
};


#endif // !PERSPECTIVECAMERA_H

