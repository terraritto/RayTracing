#pragma once
#include "../Utility/RGBColor.h"
#include "../Material/Material.h"
#include <memory>

class Material;

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);
	virtual ~GeometricObject();

	virtual bool hit(const class Ray& ray, double& t, class ShadeRec& s) const = 0;
	RGBColor GetColor();
	void SetColor(RGBColor color) { mColor = color; };
	std::shared_ptr<Material> GetMaterial();
	void SetMaterial(std::shared_ptr<Material> material);
protected:
	RGBColor mColor;
	std::shared_ptr<Material> mMaterial;
};