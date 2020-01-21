#pragma once
#include "Phong.h"
#include "../BRDF/PerrfectSpecular.h"
#include "../BTDF/PerfectTransmitter.h"

class Transparent : public Phong
{
public:
	Transparent();
	Transparent(const Transparent& tp);
	~Transparent();
	Transparent& operator=(const Transparent& rhs);

	std::shared_ptr<Transparent> Clone() const;

	RGBColor Shade(ShadeRec& sr) override;

	void SetIor(float ior);
	void SetKr(float kr);
	void SetKt(float kt);
private:
	std::shared_ptr<PerfectSpecular> mReflectiveBRDF;
	std::shared_ptr<PerfectTransmitter> mSpecularBTDF;
};