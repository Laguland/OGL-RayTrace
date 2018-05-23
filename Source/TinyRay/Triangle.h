/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#pragma once
#include "Primitive.h"
#include "Vector4D.h"
#include "Ray.h"
#include <vector>

class Triangle : public Primitive
{
private:
	Vector4D m_vertices[3];
	Vector4D m_normal;

public:
	Triangle();
	Triangle(Vector4D pos1, Vector4D pos2, Vector4D pos3);
	~Triangle();
	
	void SetTriangle(Vector4D v0, Vector4D v1, Vector4D v2);

	RayHitResult IntersectByRay(Ray& ray);
};

