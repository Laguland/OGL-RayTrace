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
#include <gl/GL.h>
#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#include "RayTracer.h"
#include "Ray.h"
#include "Scene.h"
#include "Camera.h"

RayTracer::RayTracer()
{
	m_buffHeight = m_buffWidth = 0.0;
	m_renderCount = 0;
	SetTraceLevel(5);
	m_traceflag = (TraceFlag)(TRACE_AMBIENT | TRACE_DIFFUSE_AND_SPEC |
		TRACE_SHADOW | TRACE_REFLECTION | TRACE_REFRACTION);
}

RayTracer::RayTracer(int Width, int Height)
{
	m_buffWidth = Width;
	m_buffHeight = Height;
	m_renderCount = 0;
	SetTraceLevel(5);
	
	m_traceflag = (TraceFlag)(TRACE_AMBIENT | TRACE_DIFFUSE_AND_SPEC |
		TRACE_SHADOW | TRACE_REFLECTION | TRACE_REFRACTION);
}

RayTracer::~RayTracer()
{

}

void RayTracer::DoRayTrace( Scene* pScene )
{
	Camera* cam = pScene->GetSceneCamera();
	
	Vector4D camRightVector = cam->GetRightVector();
	Vector4D camUpVector = cam->GetUpVector();
	Vector4D camViewVector = cam->GetViewVector();
	Vector4D centre = cam->GetViewCentre();
	Vector4D camPosition = cam->GetPosition();

	double sceneWidth = pScene->GetSceneWidth();
	double sceneHeight = pScene->GetSceneHeight();

	double pixelDX = sceneWidth / m_buffWidth;
	double pixelDY = sceneHeight / m_buffHeight;
	
	int total = m_buffHeight*m_buffWidth;
	int done_count = 0;
	
	Vector4D start;

	start[0] = centre[0] - ((sceneWidth * camRightVector[0])
		+ (sceneHeight * camUpVector[0])) / 2.0;
	start[1] = centre[1] - ((sceneWidth * camRightVector[1])
		+ (sceneHeight * camUpVector[1])) / 2.0;
	start[2] = centre[2] - ((sceneWidth * camRightVector[2])
		+ (sceneHeight * camUpVector[2])) / 2.0;
	
	Colour scenebg = pScene->GetBackgroundColour();

	if (m_renderCount == 0)
	{
		fprintf(stdout, "Trace start.\n");

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < m_buffHeight; i++) {
			for (int j = 0; j < m_buffWidth; j++) {

				//calculate the metric size of a pixel in the view plane (e.g. framebuffer)
				Vector4D pixel;

				pixel[0] = start[0] + (i + 0.5) * camUpVector[0] * pixelDY
					+ (j + 0.5) * camRightVector[0] * pixelDX;
				pixel[1] = start[1] + (i + 0.5) * camUpVector[1] * pixelDY
					+ (j + 0.5) * camRightVector[1] * pixelDX;
				pixel[2] = start[2] + (i + 0.5) * camUpVector[2] * pixelDY
					+ (j + 0.5) * camRightVector[2] * pixelDX;

				/*
				* setup view ray
				* In perspective projection, each view ray originates from the eye (camera) position 
				* and pierces through a pixel in the view plane
				*
				* TODO: For a little extra credit, set up the view rays to produce orthographic projection
				*/
				Ray viewray;
				viewray.SetRay(camPosition,	(pixel - camPosition).Normalise());
				
				//trace the scene using the view ray
				//the default colour is the background colour, unless something is hit along the way
				Colour colour = this->TraceScene(pScene, viewray, scenebg, m_traceLevel);

				/*
				* The only OpenGL code we need
				* Draw the pixel as a coloured rectangle
				*/
				glColor3f(colour.red, colour.green, colour.blue);
				glRecti(j, i, j + 1, i + 1);
			}
			glFlush();
		}

		fprintf(stdout, "Done!!!\n");
		m_renderCount++;
	}
	glFlush();
}

Colour RayTracer::TraceScene(Scene* pScene, Ray& ray, Colour incolour, int tracelevel, bool shadowray)
{
	RayHitResult result;
	Colour outcolour = incolour;
	std::vector<Light*>* light_list = pScene->GetLightList();


	if (tracelevel <= 0) // reach the MAX depth of the recursion.
	{
		return outcolour;
	}

	result = pScene->IntersectByRay(ray, shadowray);

	if (result.data) //the ray has hit something
	{
		if (shadowray)
		{
			outcolour.blue *= 0.1;
			outcolour.green *= 0.1;
			outcolour.red *= 0.1;
			return outcolour;
		}

		Vector4D start = ray.GetRayStart();
		outcolour = CalculateLighting(light_list,
			&start,
			&result);
		
		if(m_traceflag & TRACE_REFLECTION)
		{
			//Only consider reflection for spheres and boxes
			if (((Primitive*)result.data)->m_primtype == Primitive::PRIMTYPE_Sphere ||
				((Primitive*)result.data)->m_primtype == Primitive::PRIMTYPE_Box)
			{
				//TODO: Calculate reflection ray based on the current intersection result
				//Recursively call TraceScene with the reflection ray
				//Combine the returned colour with the current surface colour 

				Vector4D rayDir = ray.GetRay() - result.point;
				rayDir.Normalise();

				Ray reflectionRay;

				double result1 = ray.GetRay().DotProduct(result.normal);
				Vector4D result2 = result.normal * (2*result1);
				Vector4D result3 = ray.GetRay() - result2;
				
				reflectionRay.SetRay(result3 + result.point,result3);

				Colour col = TraceScene(pScene, reflectionRay, incolour, --tracelevel, false);
				outcolour.blue *= col.blue;
				outcolour.green *= col.green;
				outcolour.red *= col.red;
			}
		}

		if (m_traceflag & TRACE_REFRACTION)
		{
			//Only consider refraction for spheres and boxes
			if (((Primitive*)result.data)->m_primtype == Primitive::PRIMTYPE_Sphere ||
				((Primitive*)result.data)->m_primtype == Primitive::PRIMTYPE_Box)
			{
				//TODO: Calculate refraction ray based on the current intersection result
				//Recursively call TraceScene with the reflection ray
				//Combine the returned colour with the current surface colour
			}
		}
		
		//////Check if this is in shadow
		if ( m_traceflag & TRACE_SHADOW )
		{
			std::vector<Light*>::iterator lit_iter = light_list->begin();
			while (lit_iter != light_list->end())
			{
				//TODO: Calculate the shadow ray using the current intersection result and the light position
				//Recursively call TraceScene with the shadow ray
				
				Vector4D lightDir = (*lit_iter)->GetLightPosition() - result.point;
				lightDir.Normalise();
				
				Ray shadowRay;
				shadowRay.SetRay(result.point + lightDir, lightDir);

				outcolour = TraceScene(pScene, shadowRay, outcolour, --tracelevel, true);
				
				lit_iter++;
			}
		}
	}
		
	return outcolour;
}

Colour RayTracer::CalculateLighting(std::vector<Light*>* lights, Vector4D* campos, RayHitResult* hitresult)
{
	Colour outcolour;
	std::vector<Light*>::iterator lit_iter = lights->begin();

	//Retrive the material for the intersected primitive
	Primitive* prim = (Primitive*)hitresult->data;
	Material* mat = prim->GetMaterial();

	//the default output colour is the ambient colour
	outcolour = mat->GetAmbientColour();
	
	//This is a hack to set a checker pattern on the planes
	//Do not modify it
	if (((Primitive*)hitresult->data)->m_primtype == Primitive::PRIMTYPE_Plane)
	{
		int dx = (hitresult->point[0]/2.0);
		int dy = (hitresult->point[1]/2.0);
		int dz = (hitresult->point[2]/2.0);

		if (dx % 2 || dy % 2 || dz % 2)
		{
			outcolour.red = 1.0;
			outcolour.green = 1.0;
			outcolour.blue = 1.0;

		}
		else
		{
			outcolour.red = 0.0;
			outcolour.green = 0.0;
			outcolour.blue = 0.0;
		}
	}

	////Go through all the light sources in the scene
	//and calculate the lighting at the intersection point
	if (m_traceflag & TRACE_DIFFUSE_AND_SPEC)
	{
		while (lit_iter != lights->end())
		{

			Vector4D light_pos = (*lit_iter)->GetLightPosition();  //position of the light source
			Vector4D normal = hitresult->normal; //surface normal at intersection
			Vector4D surface_point = hitresult->point; //location of the intersection on the surface
			
			//TODO: Calculate the surface colour using the illumination model from the lecture notes
			// 1. Compute the diffuse term
			// 2. Compute the specular term using either the Phong model or the Blinn-Phong model
			// 3. store the result in outcolour

			Vector4D lightDir = light_pos - surface_point;
			lightDir.Normalise();

			// Cauculate Diffuse

			double dotProd = lightDir.DotProduct(normal);

			double blueD = mat->GetDiffuseColour().blue * dotProd;
			double greenD = mat->GetDiffuseColour().green * dotProd;
			double redD = mat->GetDiffuseColour().red * dotProd;

			outcolour.blue += blueD;
			outcolour.green += greenD;
			outcolour.red += redD;

			// Cauculate Specular, both models working

			Vector4D e = (*campos) - surface_point;
			e.Normalise();
			double n = mat->GetSpecPower();

			// Phong Model

	  //      double result1 = 2 * normal.DotProduct(lightDir);
			//Vector4D result2 = normal * result1;
			//Vector4D rVec = lightDir - result2;
			//rVec.Normalise();
			//dotProd = e.DotProduct(rVec);
			//dotProd = dotProd < 0.0 ? 0.0 : dotProd;
			//double powSpec = pow(dotProd, n);

			//double blueS = mat->GetSpecularColour().blue * (*lit_iter)->GetLightColour().blue * powSpec;
			//double greenS = mat->GetSpecularColour().green * (*lit_iter)->GetLightColour().green * powSpec;
			//double redS = mat->GetSpecularColour().red * (*lit_iter)->GetLightColour().red * powSpec;

			// Blinn-Phong Model

			Vector4D h = lightDir + e;
			h.Normalise();
			dotProd = normal.DotProduct(h);
			dotProd = dotProd < 0.0 ? 0.0 : dotProd;
			double powSpec = pow(dotProd, n);

			double blueS = mat->GetSpecularColour().blue * (*lit_iter)->GetLightColour().blue * powSpec;
			double greenS = mat->GetSpecularColour().green * (*lit_iter)->GetLightColour().green * powSpec;
			double redS = mat->GetSpecularColour().red * (*lit_iter)->GetLightColour().red * powSpec;
			
			outcolour.blue += blueS;
			outcolour.red += redS;
			outcolour.green += greenS;

			lit_iter++;
		}
	}

	return outcolour;
}
