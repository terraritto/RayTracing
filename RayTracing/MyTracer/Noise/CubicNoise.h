#pragma once
#include "LatticeNoise.h"
#include <vector>

class CubicNoise : public LatticeNoise
{
public:
	CubicNoise();
	~CubicNoise() = default;

	float ValueNoise(const Point3D& p) const override;
private:
	// Catmull-Rom Splines(Catmull and Rom, 1974)
	template<class T = float>
	auto FourKnotSpline(float x, std::vector<T>& knots) const
	{
		T c3 = -0.5 * knots[0] + 1.5 * knots[1] - 1.5 * knots[2] + 0.5 * knots[3];
		T c2 = knots[0] - 2.5 * knots[1] + 2.0 * knots[2] - 0.5 * knots[3];
		T c1 = 0.5 * (-knots[0] + knots[2]);
		T c0 = knots[1];

		return (((c3 * x + c2) * x + c1) * x + c0);
	}
};