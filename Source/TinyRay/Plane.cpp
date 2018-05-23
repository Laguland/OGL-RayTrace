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
#include "Plane.h"


Plane::Plane()
{
	//The default plane is the xz plane with normal pointing towards positive y
	// the offset is zero,
	m_normal.SetVector(0.0, 1.0, 0.0);
	m_offset = 0.0;
	m_primtype = PRIMTYPE_Plane;
}


Plane::~Plane()
{
}

RayHitResult Plane::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;
	double t = FARFAR_AWAY;
	Vector4D intersection_point;
	
	//TODO: Calculate the intersection the input ray and this plane
	// Store the parametric result in t
	// The plane equation is a*x + a*y + a*z + d = 0, where
	// a = m_normal[0], b = m_normal[1], c = m_normal[2] and d = m_offset
	//
	// Note: 
	// Some additional checks can make the test more robust
	// 1. You should check if the ray is parallel to plane
	// 2. Check if the ray intersects the plane from the front or the back

	double result1 = m_normal.DotProduct(ray.GetRayStart()) + m_offset;
	double result2 = m_normal.DotProduct(ray.GetRay());
	t = -(result1 / result2);

	//Calculate the exact location of the intersection using the result of t
	intersection_point = ray.GetRayStart() + ray.GetRay()*t;
	
	if (t>0.0 && t < FARFAR_AWAY)
	{
		result.normal = m_normal;
		result.t = t;
		result.data = this;
		result.point = intersection_point;
	}

	return result;
}

void Plane::SetPlane(const Vector4D& normal, double offset)
{
	m_normal = normal;
	m_offset = -offset;
}
