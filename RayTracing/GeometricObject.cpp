#include "GeometricObject.h"

GeometricObject::GeometricObject()
	: mColor() //������ǉ�
{

}

GeometricObject::GeometricObject(const GeometricObject& object)
{
	mColor = object.mColor;
}

GeometricObject::~GeometricObject()
{

}