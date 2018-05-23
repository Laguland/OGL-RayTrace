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

class Plane : public Primitive
{
	private:
		Vector4D			m_normal;  //normal of the plane
		double			m_offset;  //displacement along the normal

	public:
						Plane();
						~Plane();

		RayHitResult	IntersectByRay(Ray& ray);

		void SetPlane(const Vector4D& normal, double offset);
};

