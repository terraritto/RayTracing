#include "ShadeRec.h"
#include "../Maths/Constants.h"

ShadeRec::ShadeRec(World& world)
	: mHitAnObject(false)
	, mMaterialPtr(nullptr)
	, mHitPoint()
	, mLocalHitPoint()
	, mNormal()
	, mRay()
	, mDepth(0)
	, mDir()
	, mWorld(world)
	, mT(0.0)
	, mU(0.0)
	, mV(0.0)
{

}

ShadeRec::ShadeRec(const ShadeRec& sr)
	: mHitAnObject(sr.mHitAnObject)
	, mMaterialPtr(sr.mMaterialPtr)
	, mHitPoint(sr.mHitPoint)
	, mLocalHitPoint(sr.mLocalHitPoint)
	, mNormal(sr.mNormal)
	, mRay(sr.mRay)
	, mDepth(sr.mDepth)
	, mDir(sr.mDir)
	, mColor(sr.mColor)
	, mWorld(sr.mWorld)
	, mT(sr.mT)
	, mU(sr.mU)
	, mV(sr.mV)
{

}

ShadeRec::~ShadeRec()
{

}