#include "BeveledCylinder.h"
#include "Disk.h"
#include "OpenCylinder.h"
#include "Torus.h"
#include "Instance.h"


BeveledCylinder::BeveledCylinder(const double bottom, const double top, const double radius, const double beveled_radius)
	: Compound()
{
	
	mObjects.emplace_back(
		std::make_shared<Disk>(Point3D(0, top, 0), Normal(0, 1, 0), radius - beveled_radius)
	);
	
	mObjects.emplace_back(
		std::make_shared<OpenCylinder>(bottom + beveled_radius, top - beveled_radius, radius)
	);
	
	mObjects.emplace_back(
		std::make_shared<Disk>(Point3D(0, bottom, 0), Normal(0, -1, 0), radius - beveled_radius)
	);
	
	std::shared_ptr<Instance> bottom_bevel_ptr = std::make_shared<Instance>(std::make_shared<Torus>
		(
			radius - beveled_radius, beveled_radius
			)
		);
	bottom_bevel_ptr->Translate(0, bottom + beveled_radius, 0);
	mObjects.emplace_back(bottom_bevel_ptr);

	std::shared_ptr<Instance> top_bevel_ptr = std::make_shared<Instance>(std::make_shared<Torus>
		(
			radius - beveled_radius, beveled_radius
			)
		);
	top_bevel_ptr->Translate(0, top - beveled_radius, 0);
	mObjects.emplace_back(top_bevel_ptr);
	
	//bbox
	Point3D center(0, bottom, 0);
	mBbox.mP0 = Point3D(center.mPosX - radius, center.mPosY, center.mPosZ - radius);
	mBbox.mP1 = Point3D(center.mPosX + radius, top, center.mPosZ + radius);
	
}

BeveledCylinder::BeveledCylinder(const BeveledCylinder& cc)
	: Compound(cc)
{
	for (auto& obj : cc.mObjects)
	{
		mObjects.emplace_back(obj->Clone());
	}

	mBbox = cc.mBbox;
}

BeveledCylinder::~BeveledCylinder()
{
}

BeveledCylinder& BeveledCylinder::operator=(const BeveledCylinder& rhs)
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

std::shared_ptr<BeveledCylinder> BeveledCylinder::Clone() const
{
	return std::make_shared<BeveledCylinder>(*this);
}

bool BeveledCylinder::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	if (mBbox.hit(ray))
	{
		return (Compound::hit(ray, tMin, sr));
	}
	return false;
}

bool BeveledCylinder::Shadow_hit(const Ray& ray, float& tMin) const
{
	return Compound::Shadow_hit(ray, tMin);
}
