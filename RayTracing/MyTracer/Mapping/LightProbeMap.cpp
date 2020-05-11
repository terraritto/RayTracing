#include "LightProbeMap.h"
#include "../Maths/Constants.h"

void LightProbeMap::GetTexelCoordinates(const Point3D& localHitPoint, const int hres, const int vres, int& row, int& column)
{
	float x = localHitPoint.mPosX;
	float y = localHitPoint.mPosY;
	float z = localHitPoint.mPosZ;

	float d = std::sqrt(x * x + y * y);
	double sin_beta = y / d;
	double cos_beta = x / d;
	float alpha;

	if (mMapType == MapType::ELightProbe)
	{
		alpha = std::acos(z);
	}

	if (mMapType == MapType::EPanoramic)
	{
		alpha = std::acos(-z);
	}

	float r = alpha * INVPI;
	float u = (1.0 + r * cos_beta) * 0.5;
	float v = (1.0 + r * sin_beta) * 0.5;
	row = static_cast<int>((hres - 1) * u);
	column = static_cast<int>((vres - 1) * v);
}

void LightProbeMap::SetMapType(MapType type)
{
	mMapType = type;
}
