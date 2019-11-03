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
