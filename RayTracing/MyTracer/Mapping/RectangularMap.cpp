#include "RectangularMap.h"

void RectangularMap::GetTexelCoordinates(const Point3D& localHitPoint, const int hres, const int vres, int& row, int& column)
{
	float u = (localHitPoint.mPosZ + 1) / 2;
	float v = (localHitPoint.mPosX + 1) / 2;

	row = static_cast<int>((hres - 1) * u);
	column = static_cast<int>((vres - 1) * v);
}
