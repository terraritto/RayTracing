#pragma once
#include "Mapping.h"

class LightProbeMap : public Mapping
{
public:
	enum class MapType
	{
		ELightProbe,
		EPanoramic
	};

	void GetTexelCoordinates(
		const Point3D& localHitPoint,
		const int hres,
		const int vres,
		int& row,
		int& column
	) override;

	void SetMapType(MapType type);
private:
	MapType mMapType;
};