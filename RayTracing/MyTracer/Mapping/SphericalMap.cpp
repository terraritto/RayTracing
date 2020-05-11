#include "SphericalMap.h"
#include "../Maths/Constants.h"

void SphericalMap::GetTexelCoordinates(const Point3D& localHitPoint, const int hres, const int vres, int& row, int& column)
{
	float theta = std::acos(localHitPoint.mPosY);
	float phi = std::atan2(localHitPoint.mPosX, localHitPoint.mPosZ);
	if (phi < 0.0)
	{
		phi += TWO_PI;
	}

	float u = phi * INVTWOPI;
	float v = 1 - theta * INVPI;

	row = static_cast<int>((hres - 1) * u);
	column = static_cast<int>((vres - 1) * v);
}
