#pragma once
#include "ViewPlane.h"
#include "RGBColor.h"
#include "Sphere.h"
#include "Tracer.h"
#include <memory>
class Tracer;

class World
{
public:
	ViewPlane mViewPlane;
	RGBColor mBackGroundColor;
	Sphere mSphere;
	std::shared_ptr<Tracer> mTracerPtr;

	World();
	~World();
	
	void Build();
	void RenderScene() const;
	void OpenWindow(const int hres, const int vres) const;
	void DisplayPixel(const int row, const int column, const RGBColor& pixelColor) const;
};