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
#include "Material.h"

class Light
{
	private:
		Vector4D			m_position;
		Colour			m_colour;

	public:
		Light();
		~Light();

		void InitDefaultLight();
		void SetLightPosition(double x, double y, double z);
		void SetLightColour(double r, double g, double b);

		inline Vector4D& GetLightPosition()
		{
			return m_position;
		}
		inline Colour& GetLightColour()
		{
			return m_colour;
		}
};

