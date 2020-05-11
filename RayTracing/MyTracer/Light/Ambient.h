#pragma once
#include "Light.h"

class Ambient : public Light
{
public:
	Ambient();
	Ambient(const Ambient& a);
	~Ambient();
	Ambient& operator=(const Ambient& rhs);

	std::shared_ptr<Ambient> Clone() const;
	Vector3D GetDirection(ShadeRec& s) override;
	RGBColor L(ShadeRec& s) override;
	
	void SetScaleRadiance(const float b);
	void SetColor(const float c);
	void SetColor(const RGBColor& c);
	void SetColor(const float r, const float g, const float b);
private:
	float mLs;
	RGBColor mColor;
};