#pragma once
#include "Phong.h"
#include "../BRDF/FresnelReflector.h"
#include "../BTDF/FresnelTransmitter.h"

class Dielectric : public Phong
{
public:
	Dielectric();
	Dielectric(const Dielectric& tp);
	~Dielectric();
	Dielectric& operator=(const Dielectric& rhs);

	std::shared_ptr<Dielectric> Clone() const;

	RGBColor Shade(ShadeRec& sr) override;

	void SetEtaIn(float eta);
	void SetEtaOut(float eta);
	void SetCfIn(const RGBColor& color);
	void SetCfIn(const float color);
	void SetCfIn(const float r, const float g, const float b);
	void SetCfOut(const RGBColor& color);
	void SetCfOut(const float color);
	void SetCfOut(const float r, const float g, const float b);
private:
	RGBColor mCfIn;
	RGBColor mCfOut;

	std::shared_ptr<FresnelReflector> mFresnelBRDF;
	std::shared_ptr<FresnelTransmitter> mFresnelBTDF;
};