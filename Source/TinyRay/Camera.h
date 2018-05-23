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

#include "Vector4D.h"

class Camera
{
	private:
		Vector4D				m_position;			//aka eye.
		Vector4D				m_upVector;
		Vector4D				m_viewVector;
		Vector4D				m_rightVector;
		Vector4D				m_viewCentre;		//centre of the near view plane
		double					m_focalLength;	    //you can think of this as the distance between the eye and the near plane of the view frustum

	public:
		
		Camera();
		~Camera();

		void InitDefaultCamera();

		void SetPositionAndLookAt( const Vector4D& pos, const Vector4D& lookat);
		
		inline Vector4D&		GetPosition() 
		{
			return m_position;
		}

		inline Vector4D&		GetUpVector() 
		{
			return m_upVector;
		}

		inline Vector4D&		GetRightVector() 
		{
			return m_rightVector;
		}

		inline Vector4D&		GetViewVector() 
		{
			return m_viewVector;
		}

		inline Vector4D&		GetViewCentre() 
		{
			return m_viewCentre;
		}

		inline double		GetFocalLength() 
		{
			return m_focalLength;
		}
};

