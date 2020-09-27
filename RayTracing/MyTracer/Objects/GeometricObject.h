#pragma once
#include "../Utility/RGBColor.h"
#include "../Material/Material.h"
#include "../Utility/ShadeRec.h"
#include "BBox.h"
#include <memory>

class Material;
class ShadeRec;

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);
	virtual ~GeometricObject();

	std::shared_ptr<GeometricObject> Clone() const;
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) { return false; }
	virtual bool Shadow_hit(const Ray& ray, float& tmin) const;
	RGBColor GetColor();
	void SetColor(RGBColor color) { mColor = color; };
	std::shared_ptr<Material> GetMaterial();
	virtual void SetMaterial(std::shared_ptr<Material> material);
	void SetIsShadow(bool is);
	bool GetIsShadow();
	//for Compound Object
	virtual void AddObject(std::shared_ptr<GeometricObject> object_ptr);
	//for area lights......?
	virtual Point3D Sample();
	virtual float pdf(const ShadeRec& sr);
	virtual Normal GetNormal(const Point3D& p);
	//for ply file
	virtual Normal GetNormal();
	//for BBox
	virtual BBox GetBoundingBox() const;
protected:
	RGBColor mColor;
	std::shared_ptr<Material> mMaterial;
	bool mIsShadow;
public:
	std::shared_ptr<ShadeRec> mShadowSr; //for alpha shadow
};