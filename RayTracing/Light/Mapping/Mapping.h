#pragma once
#include "../Maths/Point3D.h"

class Mapping
{
public:
	virtual void GetTexelCoordinates(
		const Point3D& localHitPoint,
		const int hres,
		const int vres,
		int& row,
		int& column
	) = 0;
};