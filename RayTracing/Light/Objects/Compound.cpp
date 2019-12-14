#include "Compound.h"

Compound::Compound()
	:GeometricObject()
{
}

Compound::Compound(const Compound& comp)
	: GeometricObject(comp)
{
	for (int i = 0; i < comp.mObjects.size(); i++)
	{
		this->mObjects.emplace_back(comp.mObjects[i]);
	}
}

Compound::~Compound()
{
}

Compound& Compound::operator=(const Compound& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);

	for (int i = 0; i < rhs.mObjects.size(); i++)
	{
		this->mObjects.emplace_back(rhs.mObjects[i]);
	}

	return *this;
}

std::shared_ptr<Compound> Compound::Clone() const
{
	return std::make_shared<Compound>(*this);
}

void Compound::SetMaterial(std::shared_ptr<Material> material_ptr)
{
	for (int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->SetMaterial(material_ptr);
	}
}

void Compound::AddObject(std::shared_ptr<GeometricObject> object_ptr)
{
	mObjects.emplace_back(object_ptr);
}

bool Compound::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	double t;
	Normal normal;
	Point3D local_hit_point;
	bool isHit = false;
	tMin = kHugeValue;
	
	for (int i = 0; i < mObjects.size(); i++)
	{
		if (mObjects[i]->hit(ray, t, sr) && (t < tMin))
		{
			isHit = true;
			tMin = t;
			mMaterial = mObjects[i]->GetMaterial();
			normal = sr.mNormal;
			local_hit_point = sr.mLocalHitPoint;
		}
	}

	if (hit)
	{
		sr.mT = tMin;
		sr.mNormal = normal;
		sr.mLocalHitPoint = local_hit_point;
	}

	return hit;
}

bool Compound::Shadow_hit(const Ray& ray, float& tMin) const
{
	for (int i = 0; i < mObjects.size(); i++)
	{
		if (mObjects[i]->Shadow_hit(ray, tMin))
		{
			return true;
		}
	}
	return false;
}
