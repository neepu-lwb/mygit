#ifndef COLOR_H
#define COLOR_H
#include "math.h"

class Color
{
public:
	float r;
	float g;
	float b;



	Color() {}
	Color(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	Color copy()
	{
		return Color(this->r, this->g, this->b);
	}

	Color add(Color c)
	{
		return Color(this->r + c.r, this->g + c.g, this->b + b);
	}

	Color multiply(float s)
	{
		return Color(this->r*s, this->g*s, this->b*s);
	}

	Color modulate(Color c)
	{
		return Color(this->r*c.r, this->g*c.g, this->b*c.b);
	}

	void saturate()
	{
		this->r = fminf(this->r, 1.0);
		this->g = fminf(this->g, 1.0);
		this->b = fminf(this->b, 1.0);
	}

	static Color black()
	{
		return Color(0, 0, 0);
	}
	static Color white()
	{
		return Color(1, 1, 1);
	}
	static Color red()
	{
		return Color(1, 0, 0);
	}
	static Color green()
	{
		return Color(0, 1, 0);
	}
	static Color blue()
	{
		return Color(0, 0, 1);
	}
};

#endif // !COLOR_H

