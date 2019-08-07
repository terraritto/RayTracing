#pragma once
#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"

class ShadeRec
{
public:
	bool mHitAnObject; //did the ray hit an object?
	Point3D mLocalHitPoint; // world coordinate of hit point
	Normal mNormal; //normal at hit point
	RGBColor mColor; //used in short
	class World& mWorld; //world reference for shading

	ShadeRec(class World& world);
	ShadeRec(const ShadeRec& sr);
	~ShadeRec();
	//ShadeRec& operator=(const ShadeRec& rhs);
};