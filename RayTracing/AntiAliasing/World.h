#pragma once
#include "ViewPlane.h"
#include "RGBColor.h"
#include "Sphere.h"
#include "Tracer.h"
#include "GeometricObject.h"
#include "Ray.h"
#include <memory>
#include <vector>
class Tracer;

class World
{
public:
	ViewPlane mViewPlane;
	RGBColor mBackGroundColor;
	std::vector<std::shared_ptr<GeometricObject>> mObjects;
	std::shared_ptr<Tracer> mTracerPtr;

	World();
	~World();
	
	void Build();
	void RenderScene() const;
	void AddObject(std::shared_ptr<GeometricObject> objectPtr);
	ShadeRec HitBareBonesObjects(const Ray& ray);
	void OpenWindow(const int hres, const int vres) const;
	void DisplayPixel(const int row, const int column, const RGBColor& pixelColor) const;
};