#pragma once
#include "MeshTriangle.h"

class FlatMeshTriangle : public MeshTriangle
{
public:
	FlatMeshTriangle() = default;
	FlatMeshTriangle(std::shared_ptr<Mesh> mesh_ptr, const int i0, const int i1, const int i2);
	FlatMeshTriangle(const FlatMeshTriangle& fmt);
	~FlatMeshTriangle() = default;
	FlatMeshTriangle& operator=(const FlatMeshTriangle& rhs);

	std::shared_ptr<FlatMeshTriangle> Clone() const;
	bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;	
};