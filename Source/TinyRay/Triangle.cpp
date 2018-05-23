/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
* 
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include "Triangle.h"

Triangle::Triangle()
{
	m_vertices[0] = Vector4D(-1.0, 0.0, -5.0);
	m_vertices[1] = Vector4D(0.0, 1.0, -5.0);
	m_vertices[2] = Vector4D(1.0, 0.0, -5.0);
	m_normal = Vector4D(0.0, 0.0, 1.0);
	m_primtype = PRIMTYPE_Triangle;
}

Triangle::Triangle(Vector4D pos1, Vector4D pos2, Vector4D pos3)
{
	SetTriangle(pos1, pos2, pos3);

	m_primtype = PRIMTYPE_Triangle;
}


Triangle::~Triangle()
{
}

void Triangle::SetTriangle(Vector4D v0, Vector4D v1, Vector4D v2)
{
	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;

	//Calculate Normal
	Vector4D NormalA = m_vertices[1] - m_vertices[0];
	Vector4D NormalB = m_vertices[2] - m_vertices[0];
	Vector4D Norm = NormalA.CrossProduct(NormalB);
	Norm.Normalise();
	m_normal = Norm;
}


RayHitResult Triangle::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;
	double t = FARFAR_AWAY;
	Vector4D intersection_point;
	
	Vector4D e1, e2;
	Vector4D P, Q, T;
	double det, inv_det, u, v;

	// TODO: Calculate the intersection between in the input ray and this triangle
	// If you have implemented ray-plane intersection, you have done half the work for ray-triangle intersection.
	// The remaining test is to check if the intersection point is inside the triangle
	//
	// Similar to the plane case, you should check if the ray is parallel to the triangle
	// and check if the ray intersects the triangle from the front or the back

	e1 = m_vertices[1] - m_vertices[0];
	e2 = m_vertices[2] - m_vertices[0];

	P = ray.GetRay().CrossProduct(e2);

	det = e1.DotProduct(P);

	if (det > -DBL_EPSILON && det < DBL_EPSILON)
	{
		return result;
	}
	
	inv_det = 1.f / det;

	T = ray.GetRayStart() - m_vertices[0];

	u = T.DotProduct(P) * inv_det;

	if (u < 0.f || u > 1.f)
	{
		return result;
	}

	Q = T.CrossProduct(e1);

	v = ray.GetRay().DotProduct(Q)*inv_det;

	if (v < 0.f || u + v > 1.f)
	{
		return result;
	}

	t = e2.DotProduct(Q)*inv_det;

	//Calculate the exact location of the intersection using the result of t
	intersection_point = ray.GetRayStart() + ray.GetRay()*t;

	if (t > 0 && t < FARFAR_AWAY) { //ray intersection
		result.t = t;
		result.normal = this->m_normal;
		result.point = intersection_point;
		result.data = this;
		return result;
	}
	
	return result;
}
