#pragma once
#include "GeometricObject.h"
#include <vector>

class Compound :public GeometricObject
{
public:
	Compound();
	Compound(const Compound& comp);
	virtual ~Compound();
	
	Compound& operator=(const Compound& comp);

	std::shared_ptr<Compound> Clone() const;

	virtual void SetMaterial(std::shared_ptr<Material> material_ptr) override;
	void AddObject(std::shared_ptr<GeometricObject> object_ptr) override;
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) override;
	virtual bool Shadow_hit(const Ray& ray, float& tmin) const override;
protected:
	std::vector <std::shared_ptr<GeometricObject>> mObjects;
};