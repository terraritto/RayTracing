#pragma once
#include "../Maths/Point3D.h"
#include "../Maths/Normal.h"
#include "RGBColor.h"
#include "World.h"
class World;

class ShadeRec
{
public:
	bool mHitAnObject; //did the ray hit an object?
	Point3D mLocalHitPoint; // world coordinate of hit point
	Normal mNormal; //normal at hit point
	RGBColor mColor; //used in short
	World& mWorld; //world reference for shading

	ShadeRec(World& world);
	ShadeRec(const ShadeRec& sr);
	~ShadeRec();
	//ShadeRec& operator=(const ShadeRec& rhs);
};