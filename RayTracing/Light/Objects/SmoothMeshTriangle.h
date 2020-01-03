#pragma once
#pragma once
#include "MeshTriangle.h"

class SmoothMeshTriangle : public MeshTriangle
{
public:
	SmoothMeshTriangle() = default;
	SmoothMeshTriangle(std::shared_ptr<Mesh> mesh_ptr, const int i0, const int i1, const int i2);
	SmoothMeshTriangle(const SmoothMeshTriangle& fmt);
	~SmoothMeshTriangle() = default;
	SmoothMeshTriangle& operator=(const SmoothMeshTriangle& rhs);

	std::shared_ptr<SmoothMeshTriangle> Clone() const;
	bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;
protected:
	Normal InterpolateNormal(const float beta, const float gamma) const;
};