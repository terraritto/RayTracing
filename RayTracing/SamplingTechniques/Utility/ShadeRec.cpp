#include "ShadeRec.h"
#include "../Maths/Constants.h"

ShadeRec::ShadeRec(World& world)
	: mHitAnObject(false)
	, mLocalHitPoint()
	, mNormal()
	, mColor(black)
	, mWorld(world)
{

}

ShadeRec::ShadeRec(const ShadeRec& sr)
	: mHitAnObject(sr.mHitAnObject)
	, mLocalHitPoint(sr.mLocalHitPoint)
	, mNormal(sr.mNormal)
	, mColor(sr.mColor)
	, mWorld(sr.mWorld)
{

}

ShadeRec::~ShadeRec()
{

}