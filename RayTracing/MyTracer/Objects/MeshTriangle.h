#pragma once
#include "GeometricObject.h"
#include "Mesh.h"

class MeshTriangle :public GeometricObject
{
	
public:
	std::shared_ptr<Mesh> mMeshPtr;
	int mIndex0, mIndex1, mIndex2;
	Normal mNormal;
	float mArea;
public:
	MeshTriangle();
	MeshTriangle(std::shared_ptr<Mesh> mesh_ptr, const int i1, const int i2, const int i3);
	MeshTriangle(const MeshTriangle& mt);
	virtual ~MeshTriangle();
	MeshTriangle& operator=(const MeshTriangle& rhs);

	std::shared_ptr<MeshTriangle> Clone() const;

	virtual bool hit(const Ray& ray, double& tMin, ShadeRec& sr) override;
	bool Shadow_hit(const Ray& ray, float& tmin) const override final;

	void ComputeNormal(const bool reverse_normal);
	float InterpolateU(const float beta, const float gamma);
	float InterpolateU(const float beta, const float gamma) const;
	float InterpolateV(const float beta, const float gamma);
	float InterpolateV(const float beta, const float gamma) const;

	Normal GetNormal() override;
	virtual BBox GetBoundingBox() const override;

};