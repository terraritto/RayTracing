#pragma once
#include "..\Maths\Point3D.h"
#include "..\Maths\Ray.h"
#include <memory>

class BBox {
public:
	BBox(Point3D p0 = Point3D(0), Point3D p1 = Point3D(0));
	BBox(const BBox& bbox);
	std::shared_ptr<BBox> Clone() const;
	BBox& operator=(const BBox& rhs);
	~BBox();

	bool hit(const Ray& ray) const;
	Point3D mP0;
	Point3D mP1;
};