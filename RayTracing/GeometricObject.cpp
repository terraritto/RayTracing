#include "GeometricObject.h"

GeometricObject::GeometricObject()
	: mColor() //ここを追加
{

}

GeometricObject::GeometricObject(const GeometricObject& object)
{
	mColor = object.mColor;
}

GeometricObject::~GeometricObject()
{

}