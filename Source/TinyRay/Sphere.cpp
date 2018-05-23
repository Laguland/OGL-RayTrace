/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include <math.h>
#include "Sphere.h"

Sphere::Sphere()
{
	//the default sphere is centred around the origin of the world coordinate
	//default radius is 2.0

	m_centre.SetZero();
	m_radius = 2.0;
	m_primtype = PRIMTYPE_Sphere;
}

Sphere::Sphere(double x, double y, double z, double r)
{
	m_centre.SetVector(x, y, z);
	m_radius = r;
	m_primtype = PRIMTYPE_Sphere;
}

Sphere::~Sphere()
{
}

RayHitResult Sphere::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;

	double t = FARFAR_AWAY;
	Vector4D normal;
	Vector4D intersection_point;

	//TODO: Calculate the intersection between the input ray and this sphere
	// Store the parametric result in t
	// The algebraic form of a sphere is  (x - cx)^2 + (y - cy)^2 + (z - cz)^2 = r^2 where
	// (x,y,z) is a point on the sphere
	// (cx, cy, cz) is the centre of the sphere.,i.e. m_centre
	// r is the radius of the sphere
	//
	// Note, the solution to ray-sphere intersection is the root(s) of a quadratic equation
	// therefore, there will be three scenarios
	// 1. Two real roots, the ray intersects the sphere twice. In this case, we are only interested in the closest intersection
	// 2. One real root, the ray tangentially intersects the sphere
	// 3. No real root, no intersection
	
	Vector4D v = ray.GetRay();
	Vector4D vectorStart = ray.GetRayStart();
	Vector4D DifferenceSC = ray.GetRayStart() - m_centre;

	double result1 = -v.DotProduct(DifferenceSC);
	double result2 = v.DotProduct(DifferenceSC) * v.DotProduct(DifferenceSC);
	double result3 = v.Norm_Sqr();
	double result4 = DifferenceSC.DotProduct(DifferenceSC) - pow(m_radius, 2.0);
	double result5 = result2 - (result3 * result4);

	if (result5 != 0)
	{
		double t1 = (result1 - sqrt(result2 - (result3 * result4)) / result3);
		double t2 = (result1 + sqrt(result2 - (result3 * result4)) / result3);

		if (t1 > t2)
		{
			t = t2;
		}
		else
		{
			t = t1;
		}
	}
	else
	{
		t = 0;
	}
	
	//Calculate the exact location of the intersection using the result of t
	intersection_point = ray.GetRayStart() + ray.GetRay()*t;
	
	//TODO: Calculate normal
	//Normals vary across the surface of a sphere
	//You need to calculate the normal based on the location of the intersection

	normal = intersection_point - m_centre;
	normal.Normalise();
	if (t>0.0 && t < FARFAR_AWAY)
	{
		result.t = t;
		result.data = this;
		result.point = intersection_point;
		result.normal = normal;
	}

	return result;
}
