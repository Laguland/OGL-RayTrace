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

#include "Material.h"
#include "Ray.h"
#include "Scene.h"

class RayTracer
{
	private:
		int				m_buffWidth;
		int				m_buffHeight;
		int				m_renderCount;
		int				m_traceLevel;

	public:
		
		enum TraceFlag
		{
			TRACE_AMBIENT = 0x1,
			TRACE_DIFFUSE_AND_SPEC = 0x1 << 1,
			TRACE_SHADOW = 0x1 << 2,
			TRACE_REFLECTION = 0x1 << 3,
			TRACE_REFRACTION = 0x1 << 4,
		};

		TraceFlag m_traceflag;

		RayTracer();
		RayTracer(int width, int height);
		~RayTracer();

		inline void SetTraceLevel(int level)
		{
			m_traceLevel = level;
		}

		inline void ResetRenderCount()
		{
			m_renderCount = 0;
		}

		void DoRayTrace( Scene* pScene );
		Colour TraceScene(Scene* pScene, Ray& ray, Colour incolour, int tracelevel, bool shadowray = false);
		Colour CalculateLighting(std::vector<Light*>* lights, Vector4D* campos, RayHitResult* hitresult);
};

