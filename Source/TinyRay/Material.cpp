/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include "Material.h"


Material::Material()
{
	SetDefaultMaterial();
}


Material::~Material()
{
}

void Material::SetDefaultMaterial()
{
	//default material
	//black ambient colour
	//white diffuse and specular
	//spec power is 10

	SetAmbientColour(0.0, 0.0, 0.0);
	SetDiffuseColour(1.0, 1.0, 1.0);
	SetSpecularColour(1.0, 1.0, 1.0);
	SetSpecPower(10.0);
	m_castShadow = true;
}

void Material::SetAmbientColour(float r, float g, float b)
{
	m_ambient.red = r;
	m_ambient.green = g;
	m_ambient.blue = b;
}

void Material::SetDiffuseColour(float r, float g, float b)
{
	m_diffuse.red = r;
	m_diffuse.green = g;
	m_diffuse.blue = b;
}

void Material::SetSpecularColour(float r, float g, float b)
{
	m_specular.red = r;
	m_specular.green = g;
	m_specular.blue = b;
}

void Material::SetSpecPower(double spow)
{
	m_specpower = spow;
}
