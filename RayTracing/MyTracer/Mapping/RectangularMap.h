#pragma once
#include "Mapping.h"

class RectangularMap : public Mapping
{
public:
	void GetTexelCoordinates(
		const Point3D& localHitPoint,
		const int hres,
		const int vres,
		int& row,
		int& column
	) override;
};