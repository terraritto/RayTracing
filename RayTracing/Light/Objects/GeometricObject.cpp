#include "GeometricObject.h"

GeometricObject::GeometricObject()
	: mColor() //������ǉ�
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
