#pragma once
#include "../Maths/Point3D.h"
#include "../Maths/Normal.h"
#include "../Maths/Ray.h"
#include "RGBColor.h"
#include "World.h"
#include "../Material/Material.h"
class World;

class ShadeRec
{
public:
	bool mHitAnObject; //did the ray hit an object?
	std::shared_ptr<Material> mMaterialPtr; //nearest object's material
	Point3D mHitPoint; // world coordinate of hit point
	Point3D mLocalHitPoint; 
	Normal mNormal; //normal at hit point
	RGBColor mColor; //used in short
	Ray mRay; //for specular highlights
	int mDepth; //recursion depth
	Vector3D mDir; //for area lights
	World& mWorld; //world reference for shading
	double mT;

	ShadeRec(World& world);
	ShadeRec(const ShadeRec& sr);
	~ShadeRec();
	//ShadeRec& operator=(const ShadeRec& rhs);
};