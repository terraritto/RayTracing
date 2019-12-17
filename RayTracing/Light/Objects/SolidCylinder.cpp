#include "SolidCylinder.h"
#include "Disk.h"
#include "OpenCylinder.h"

SolidCylinder::SolidCylinder()
	: Compound()
{
	mObjects.emplace_back(
		std::make_shared<Disk>(Point3D(0, 1, 0), Normal(0, 1, 0), 1)
	);
	mObjects.emplace_back(
		std::make_shared<OpenCylinder>(0, 1, 1)
	);
	mObjects.emplace_back(
		std::make_shared<Disk>(Point3D(0, 0, 0), Normal(0, -1, 0), 1)
	);

	//bbox
	Point3D center(0, 0, 0);
	float r = 1.0f;
	mBbox.mP0 = Point3D(center.mPosX - r, center.mPosY, center.mPosZ - r);
	mBbox.mP1 = Point3D(center.mPosX + r, 1, center.mPosZ + r);
}

SolidCylinder::SolidCylinder(const double bottom, const double top, const double radius)
	: Compound()
{
	mObjects.emplace_back(
		std::make_shared<Disk>(Point3D(0, top, 0), Normal(0, 1, 0), radius)
	);
	mObjects.emplace_back(
		std::make_shared<OpenCylinder>(bottom, top ,radius)
	);
	mObjects.emplace_back(
		std::make_shared<Disk>(Point3D(0, bottom, 0), Normal(0, -1, 0), 1)
	);

	//bbox
	Point3D center(0, bottom, 0);
	mBbox.mP0 = Point3D(center.mPosX - radius, center.mPosY, center.mPosZ - radius);
	mBbox.mP1 = Point3D(center.mPosX +radius, top, center.mPosZ + radius);
}

SolidCylinder::SolidCylinder(const SolidCylinder& cc)
	: Compound(cc)
{
	for (auto& obj : cc.mObjects)
	{
		mObjects.emplace_back(obj->Clone());
	}
	
	mBbox = cc.mBbox;
}

SolidCylinder::~SolidCylinder()
{
}

SolidCylinder& SolidCylinder::operator=(const SolidCylinder& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	
	mObjects.clear();
	Compound::operator=(rhs);
	
	for (auto& obj : rhs.mObjects)
	{
		mObjects.emplace_back(obj->Clone());
	}

	mBbox = rhs.mBbox;

	return *this;
}

std::shared_ptr<SolidCylinder> SolidCylinder::Clone() const
{
	return std::make_shared<SolidCylinder>(*this);
}

bool SolidCylinder::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	if (mBbox.hit(ray))
	{
		return (Compound::hit(ray, tMin, sr));
	}
	return false;
}

bool SolidCylinder::Shadow_hit(const Ray& ray, float& tMin) const
{
	return Compound::Shadow_hit(ray, tMin);
}
