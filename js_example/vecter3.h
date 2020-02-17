#ifndef VECTER_H
#define VECTER_H

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3::Vector3()
	{

	}

	Vector3::Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 Vector3::add(Vector3 v)
	{
		return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	Vector3 Vector3::copy()
	{
		return Vector3(this->x, this->y, this->z);
	}

	Vector3 Vector3::cross(Vector3 v)
	{
		return Vector3((-1)*this->z*v.y + this->y*v.z, this->z*v.x - this->x*v.z, (-1)*this->y*v.x + this->x*v.y);
	}

	Vector3 Vector3::divide(float f)
	{
		float invf = 1 / f;
		return Vector3(this->x*invf, this->y*invf, this->z*invf);
	}

	float Vector3::dot(Vector3 v)
	{
		return this->x*v.x + this->y*v.y + this->z*v.z;
	}

	float Vector3::length()
	{
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}

	Vector3 Vector3::multiply(float f)
	{
		return Vector3(this->x*f, this->y*f, this->z*f);
	}

	Vector3 Vector3::negate()
	{
		return Vector3(this->x*(-1), this->y*(-1), this->z*(-1));
	}

	Vector3 Vector3::normalize()
	{
		float inv = 1 / this->length();
		return Vector3(this->x*inv, this->y*inv, this->z*inv);
	}

	float Vector3::sqrLength()
	{
		return this->x*this->x + this->y*this->y + this->z*this->z;
	}

	Vector3 Vector3::subtract(Vector3 v)
	{
		return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
	}

	static Vector3 Vector3::zero()
	{
		return Vector3(0, 0, 0);
	}

};

#endif // !VECTER_H
