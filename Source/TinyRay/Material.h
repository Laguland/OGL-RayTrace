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

struct Colour
{
	float red;
	float green;
	float blue;
};

class Material
{
	private:
		Colour m_ambient;
		Colour m_diffuse;
		Colour m_specular;
		double m_specpower;
		bool m_castShadow;

	public:
		
		Material();
		~Material();

		void SetDefaultMaterial();
		void SetAmbientColour(float r, float g, float b);
		void SetDiffuseColour(float r, float g, float b);
		void SetSpecularColour(float r, float g, float b);
		void SetSpecPower(double spow);

		inline void SetCastShadow(bool castShadow)
		{
			m_castShadow = castShadow;
		}

		inline Colour& GetAmbientColour()
		{
			return m_ambient;
		}
		
		inline Colour& GetDiffuseColour()
		{
			return m_diffuse;
		}

		inline Colour& GetSpecularColour()
		{
			return m_specular;
		}

		inline double GetSpecPower()
		{
			return m_specpower;
		}

		inline bool CastShadow()
		{
			return m_castShadow;
		}
};

