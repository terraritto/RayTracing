#pragma once
#include "LatticeNoise.h"

class LinearNoise : public LatticeNoise
{
public:
	LinearNoise();
	~LinearNoise() = default;

	float ValueNoise(const Point3D & p) const override;

};