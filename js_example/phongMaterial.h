#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include "vecter3.h"
#include "color.h"
#include "ray3.h"

Vector3 lightDir = Vector3(1, 1, 1).normalize();
Color lightColor = Color::white();

class PhongMaterial
{
public:
	Color diffuse;
	Color specular;
	float shininess;
	float reflectiveness;

	PhongMaterial() {}
	PhongMaterial(Color diffuse, Color specular, float shininess, float reflectiveness)
	{
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
		this->reflectiveness = reflectiveness;
	}
	Color sample(Ray3 ray, Vector3 position, Vector3 normal)
	{
		float NDotL = normal.dot(lightDir);
		Vector3 H = (lightDir.subtract(ray.direction)).normalize();
		float NdotH = normal.dot(H);
		Color diffuseTerm = this->diffuse.multiply(fmaxf(NDotL, 0));
		Color specularTerm = this->specular.multiply(powf(fmaxf(NdotH, 0), this->shininess));
		return lightColor.modulate(diffuseTerm.add(specularTerm));
	}
};



#endif // !PHONGMATERIAL_H

