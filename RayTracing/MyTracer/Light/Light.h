#pragma once
#include "../Maths/Vector3D.h"
#include "../Utility/RGBColor.h"
#include "../Maths/Ray.h"
#include "../Utility/ShadeRec.h"
#include <memory>

class ShadeRec;

class Light
{
public:
	Light();
	Light(const Light& ls);
	~Light();

	Light& operator=(const Light& rhs);

	virtual Vector3D GetDirection(ShadeRec& sr) = 0;
	virtual RGBColor L(ShadeRec& sr);
	virtual float G(const ShadeRec& sr) const;
	virtual float pdf(const ShadeRec& sr) const;
	virtual bool InShadow(const Ray& ray, const ShadeRec& sr) const;
	virtual bool InShadowAlpha(const Ray& ray, ShadeRec& sr) { return false; } //for alpha

	bool GetIsShadow() { return mIsShadow; }
	void SetIsShadow(bool shadow) { mIsShadow = shadow; }
protected:
	bool mIsShadow;
};