#pragma once
#include "ViewPlane.h"
#include "RGBColor.h"
#include "ShadeRec.h"
#include "../Objects/GeometricObject.h"
#include "../Tracer/Tracer.h"
#include "../Maths/Ray.h"
#include "..//Cameras/Camera.h"
#include "../Light/Light.h"
#include <memory>
#include <vector>

class Camera;
class Light;
class GeometricObject;
class Material;
class Tracer;

class World
{
public:
	ViewPlane mViewPlane;
	RGBColor mBackGroundColor;
	std::vector<std::shared_ptr<GeometricObject>> mObjects;
	std::shared_ptr<Tracer> mTracerPtr;
	std::shared_ptr<Camera> mCameraPtr;
	std::shared_ptr<Light> mAmbientPtr;
	std::vector<std::shared_ptr<Light>> mLights;

	World();
	~World();
	
	void Build();
	void AddObject(std::shared_ptr<GeometricObject> objectPtr);
	void AddLight(std::shared_ptr<Light> lightPtr);
	ShadeRec HitBareBonesObjects(const Ray& ray);
	ShadeRec HitObjects(const Ray& ray);
	void OpenWindow(const int hres, const int vres) const;
	void DisplayPixel(const int row, const int column, const RGBColor& pixelColor) const;

	//for displaypixel
	RGBColor MaxToOne(const RGBColor& c) const;
	RGBColor ClampToColor(const RGBColor& raw) const;

	void SetCamera(std::shared_ptr<Camera> camera);
	void SetAmbientLight(std::shared_ptr<Light> light);
private:
	int mCount;
};