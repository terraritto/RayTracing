#pragma once
#include "Light.h"
#include "../Utility/World.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(const PointLight& pl);
	~PointLight();

	PointLight& operator=(const PointLight& rhs);

	std::shared_ptr<PointLight> Clone() const;

	void SetScaleRadiance(const float b);
	void SetColor(const float c);
	void SetColor(const RGBColor& c);
	void SetColor(const float r, const float g, const float b);
	void SetLocation(Vector3D d);
	void SetLocation(float dx, float dy, float dz);
	Vector3D GetDirection(ShadeRec& sr) override;
	RGBColor L(ShadeRec& sr) override;
	bool InShadow(const Ray& ray, const ShadeRec& sr) const override;
private:
	float mLs;
	RGBColor mColor;
	Vector3D mLocation;
};