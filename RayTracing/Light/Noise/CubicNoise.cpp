#include "CubicNoise.h"

CubicNoise::CubicNoise()
	: LatticeNoise()
{
}

float CubicNoise::ValueNoise(const Point3D& p) const
{
	int ix, iy, iz;
	float fx, fy, fz;
	std::vector<float> xknots(4, 0), yknots(4, 0), zknots(4, 0);
	
	ix = std::floor(p.mPosX);
	fx = p.mPosX - ix;

	iy = std::floor(p.mPosY);
	fy = p.mPosY - iy;

	iz = std::floor(p.mPosZ);
	fz = p.mPosZ - iz;

	for (int k = -1; k <= 2; k++)
	{
		for (int j = -1; j <= 2; j++)
		{
			for (int i = -1; i <= 2; i++)
			{
				xknots[i + 1] = mValueTable[Index(ix + i, iy + j, iz + k)];
			}
			yknots[j + 1] = FourKnotSpline(fx, xknots);
		}
		zknots[k + 1] = FourKnotSpline(fy, yknots);
	}

	return std::clamp(FourKnotSpline(fz, zknots), -1.0f, 1.0f);
}
