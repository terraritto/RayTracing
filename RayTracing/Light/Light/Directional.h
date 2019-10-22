#pragma once
#include "Light.h"
#include "../Utility/World.h"

class Directional : public Light
{
public:
	Directional();
	Directional(const Directional& dl);
	~Directional();

	Directional& operator=(const Directional& rhs);

	std::shared_ptr<Directional> Clone() const;

	void SetScaleRadiance(const float b);
	void SetColor(const float c);
	void SetColor(const RGBColor& c);
	void SetColor(const float r, const float g, const float b);
	void SetDirection(Vector3D d);
	void SetDirection(float dx, float dy, float dz);
	Vector3D GetDirection(ShadeRec& sr) override;
	RGBColor L(ShadeRec& sr) override;
private:
	float mLs;
	RGBColor mColor;
	Vector3D mDir;
};