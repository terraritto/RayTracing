#pragma once
#include "FlatMeshTriangle.h"

class FlatUVMeshTriangle : public FlatMeshTriangle
{
public:
	FlatUVMeshTriangle() = default;
	FlatUVMeshTriangle(std::shared_ptr<Mesh> mesh_ptr, const int i0, const int i1, const int i2);
	FlatUVMeshTriangle(const FlatUVMeshTriangle& fmt);
	virtual ~FlatUVMeshTriangle() = default;
	FlatUVMeshTriangle& operator=(const FlatUVMeshTriangle& rhs);

	std::shared_ptr<FlatUVMeshTriangle> Clone() const;
	virtual bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;
};