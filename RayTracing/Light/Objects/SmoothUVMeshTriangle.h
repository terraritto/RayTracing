#pragma once
#include "SmoothMeshTriangle.h"

class SmoothUVMeshTriangle : public SmoothMeshTriangle
{
public:
	SmoothUVMeshTriangle() = default;
	SmoothUVMeshTriangle(std::shared_ptr<Mesh> mesh_ptr, const int i0, const int i1, const int i2);
	SmoothUVMeshTriangle(const SmoothUVMeshTriangle& fmt);
	~SmoothUVMeshTriangle() = default;
	SmoothUVMeshTriangle& operator=(const SmoothUVMeshTriangle& rhs);

	std::shared_ptr<SmoothUVMeshTriangle> Clone() const;
	bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;
};