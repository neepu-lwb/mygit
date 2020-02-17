#include <GL/glut.h>
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "vecter3.h"
#include "plane.h"
#include "sphere.h"
#include "perspectiveCamera.h"
#include <iostream>

using namespace std;

const GLdouble Pi = 3.1415926536;

static int day = 200; // day的变化：从0到359

float pixels[4][10000000] = { 0 };

const float height = 1000;
const float width = 1000;


void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}



//void myDisplay()
//{
//	int i;
//	// glShadeModel(GL_FLAT);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_TRIANGLE_FAN);
//	glColor3f(1.0f, 1.0f, 1.0f);
//	glVertex2f(0.0f, 0.0f);
//	for (i = 0; i <= 8; ++i)
//	{
//		glColor3f(i & 0x04, i & 0x02, i & 0x01);
//		glVertex2f(cos(i*Pi / 4), sin(i*Pi / 4));
//	}
//	glEnd();
//	glFlush();
//}


//void myDisplay()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glColor3ub(250,250,250);
//	glPointSize(10.0f);
//	glBegin(GL_POINTS);
//
//	/*glColor3ub(255,0,0);
//	glVertex2f(0.0f,0.0f);
//	glColor3ub(0,255,0);
//	glVertex2f(0.5f,0.5f);*/
//
//	int x = 0;
//	int y = 0;
//
//	for (x = 0; x <= 255; x++)
//	{
//		for (y = 0; y <= 255; y++)
//		{
//			glColor3ub(x,y,0);
//			glVertex2f(x/255.0f,y/255.0f);
//		}
//	
//	}
//
//	glEnd();
//	glFlush();
//}


void myDisplay()
{
	/*glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 0, 255);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);*/

	glClear(GL_COLOR_BUFFER_BIT);


	glColor3ub(0, 0, 0);
	//glPointSize(1.0f);
	glBegin(GL_POINTS);


	int x = 0;
	int y = 0;
	int i = 0;
	for (x = (-1)*height / 2; x <= height / 2; x++)
	{
		for (y = (-1)*width / 2; y <= width / 2; y++)
		{
			glColor3ub(pixels[0][i], pixels[1][i], pixels[2][i]);
			//glColor3ub(255, 1, 1);
			glVertex2f(y / width * 2, x / height * 2);
			i++;
		}

	}

	glEnd();
	glFlush();
}


IntersectResult intersect_fun(Plane plane1, Sphere sphere1, Sphere sphere2, Ray3 ray)
{
	float minDistance = 1000000.0;
	IntersectResult result = plane1.intersect(ray);
	IntersectResult minResult = result;
	if (result.geometry != 0 && result.distance < minDistance)
	{
		result.geometry = 1;
		minDistance = result.distance;
		minResult = result;
	}
	result = sphere1.intersect(ray);
	if (result.geometry != 0 && result.distance < minDistance)
	{
		result.geometry = 2;
		minDistance = result.distance;
		minResult = result;
	}
	result = sphere2.intersect(ray);
	if (result.geometry != 0 && result.distance < minDistance)
	{
		result.geometry = 3;
		minDistance = result.distance;
		minResult = result;
	}
	return minResult;
}

Color rayTraceRecursive(Plane plane1, Sphere sphere1, Sphere sphere2, Ray3 ray, float maxReflect)
{
	IntersectResult result = intersect_fun(plane1, sphere1, sphere2, ray);
	if (result.geometry != 0)
	{
		float reflectiveness;
		Color color;
		if (result.geometry == 1)
		{
			reflectiveness = plane1.material.reflectiveness;
			color = plane1.material.sample(ray, result.position, result.normal);
			color = color.multiply(1 - reflectiveness);
			if (reflectiveness > 0 && maxReflect > 0)
			{
				Vector3 r = result.normal.multiply((-2) * result.normal.dot(ray.direction)).add(ray.direction);
				Ray3 ray = Ray3(result.position, r);
				Color reflectiveColor = rayTraceRecursive(plane1, sphere1, sphere2, ray, maxReflect - 1);
				color = color.add(reflectiveColor.multiply(reflectiveness));
			}
		}
		if (result.geometry == 2)
		{
			reflectiveness = sphere1.material.reflectiveness;
			color = sphere1.material.sample(ray, result.position, result.normal);
			color = color.multiply(1 - reflectiveness);
			if (reflectiveness > 0 && maxReflect > 0)
			{
				Vector3 r = result.normal.multiply(-2 * result.normal.dot(ray.direction)).add(ray.direction);
				Ray3 ray = Ray3(result.position, r);
				Color reflectiveColor = rayTraceRecursive(plane1, sphere1, sphere2, ray, maxReflect - 1);
				color = color.add(reflectiveColor.multiply(reflectiveness));
			}
		}
		if (result.geometry == 3)
		{
			reflectiveness = sphere2.material.reflectiveness;
			color = sphere2.material.sample(ray, result.position, result.normal);
			color = color.multiply(1 - reflectiveness);
			if (reflectiveness > 0 && maxReflect > 0)
			{
				Vector3 r = result.normal.multiply(-2 * result.normal.dot(ray.direction)).add(ray.direction);
				Ray3 ray = Ray3(result.position, r);
				Color reflectiveColor = rayTraceRecursive(plane1, sphere1, sphere2, ray, maxReflect - 1);
				color = color.add(reflectiveColor.multiply(reflectiveness));
			}
		}
		return color;
	}
	else
		return Color::black();
}



void rayTraceReflection(Plane plane1, Sphere sphere1, Sphere sphere2, PerspectiveCamera perspective1, float maxReflect)
{
	//初始化
	plane1.initialize();
	sphere1.initialize();
	sphere2.initialize();
	perspective1.initialize();

	int i = 0;
	for (int y = 0; y <= width; y++)
	{
		float sy = y / width;
		for (int x = 0; x <= height; x++)
		{
			float sx = 1 - x / height;
			Ray3 ray = perspective1.generateRay(sx, sy);
			Color color1 = rayTraceRecursive(plane1, sphere1, sphere2, ray, maxReflect);
			pixels[0][i] = color1.r * 255;
			pixels[1][i] = color1.g * 255;
			pixels[2][i] = color1.b * 255;
			i++;
		}
	}
}


int main(int argc, char *argv[])
{


	Plane plane1 = Plane(Vector3(0, 1, 0), 1);
	Sphere sphere1 = Sphere(Vector3(10, 10, -10), 10);
	Sphere sphere2 = Sphere(Vector3(-10, 10, -10), 10);
	plane1.material = CheckerMaterial(1, 0.5);
	sphere1.material = PhongMaterial(Color::red(), Color::white(), 16, 0.45);
	sphere2.material = PhongMaterial(Color::green(), Color::white(), 16, 0.55);
	PerspectiveCamera perspective1 = PerspectiveCamera(Vector3(0, 5, 20), Vector3(0, 0, -1), Vector3(0, 1, 0), 120);

	rayTraceReflection(plane1, sphere1, sphere2, perspective1, 1);

	//system("pause");
	glutInit(&argc, argv);								//对GLUT进行初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_MULTISAMPLE);
	//glEnable(GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("太阳");
	init();
	glutDisplayFunc(&myDisplay);
	glutMainLoop();

	/*int x = 0;
	int y = 0;
	int i = 0;
	for (x = 0; x <= 256; x++)
	{
		for (y = 0; y <= 256; y++)
		{
			printf("%f %f %f\n", pixels[0][i], pixels[1][i], pixels[2][i]);
		}
	}

	system("pause\n");*/
	return 0;
}