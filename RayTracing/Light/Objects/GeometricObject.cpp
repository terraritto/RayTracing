#include "GeometricObject.h"

GeometricObject::GeometricObject()
	: mColor() //‚±‚±‚ð’Ç‰Á
	, mMaterial(nullptr)
{

}

GeometricObject::GeometricObject(const GeometricObject& object)
{
	mColor = object.mColor;
}

GeometricObject& GeometricObject::operator=(GeometricObject& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mColor = rhs.mColor;
	if (rhs.mMaterial)
	{
		mMaterial = rhs.mMaterial;
	}

	return *this;
}

GeometricObject::~GeometricObject()
{

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
