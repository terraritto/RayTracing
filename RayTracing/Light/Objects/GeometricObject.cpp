#include "GeometricObject.h"

GeometricObject::GeometricObject()
	: mColor() //‚±‚±‚ð’Ç‰Á
	, mMaterial(nullptr)
	, mIsShadow(true)
{

}

GeometricObject::GeometricObject(const GeometricObject& object)
{
	mColor = object.mColor;
}

GeometricObject::~GeometricObject()
{

}

std::shared_ptr<GeometricObject> GeometricObject::Clone() const
{
	return std::make_shared<GeometricObject>(*this);
}

bool GeometricObject::Shadow_hit(const Ray& ray, float& tmin) const
{
	return false;
}

RGBColor GeometricObject::GetColor()
{
	return mColor;
}

std::shared_ptr<Material> GeometricObject::GetMaterial()
{
	return mMaterial;
}

void GeometricObject::SetMaterial(std::shared_ptr<Material> material)
{
	if (mMaterial)
	{
		mMaterial.reset();
		mMaterial = nullptr;
	}
	mMaterial = material;
}

void GeometricObject::SetIsShadow(bool is)
{
	mIsShadow = is;
}

bool GeometricObject::GetIsShadow()
{
	return mIsShadow;
}

void GeometricObject::AddObject(std::shared_ptr<GeometricObject> object_ptr)
{
}

Point3D GeometricObject::Sample()
{
	return Point3D();
}

float GeometricObject::pdf(const ShadeRec& sr)
{
	return 1.0f;
}

Normal GeometricObject::GetNormal(const Point3D& p)
{
	return Normal();
}

Normal GeometricObject::GetNormal()
{
	return Normal();
}

BBox GeometricObject::GetBoundingBox() const
{
	return BBox();
}
