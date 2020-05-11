#include "LinearNoise.h"

LinearNoise::LinearNoise()
	: LatticeNoise()
{
}

float LinearNoise::ValueNoise(const Point3D& p) const
{
	int ix, iy, iz;
	float fx, fy, fz;
	std::array<std::array<std::array<float, 2>, 2>, 2> d;
	float x0, x1, x2, x3, y0, y1, z0;

	ix = std::floor(p.mPosX);
	fx = p.mPosX - ix;

	iy = std::floor(p.mPosY);
	fy = p.mPosY - iy;

	iz = std::floor(p.mPosZ);
	fz = p.mPosZ - iz;

	for (int k = 0; k <= 1; k++)
	{
		for (int j = 0; j <= 1; j++)
		{
			for (int i = 0; i <= 1; i++)
			{
				d[k][j][i] = mValueTable[Index(ix + i, iy + j, iz + k)];
			}
		}
	}

	x0 = std::lerp(d[0][0][0], d[0][0][1], fx);
	x1 = std::lerp(d[0][1][0], d[0][1][1], fx);
	x2 = std::lerp(d[1][0][0], d[1][0][1], fx);
	x3 = std::lerp(d[1][1][0], d[1][1][1], fx);
	y0 = std::lerp(x0, x1, fy);
	y1 = std::lerp(x2, x3, fy);
	z0 = std::lerp(y0, y1, fz);

	return z0;
}
