#pragma once
#include "GeometricObject.h"
#include "../Maths/Matrix.h"

class Instance : public GeometricObject
{
public:
	Instance();
	Instance(std::shared_ptr<GeometricObject> obj_ptr);
	Instance(const Instance& instance);
	~Instance();
	Instance& operator=(const Instance& rhs);

	std::shared_ptr<Instance> Clone() const;
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s);
	virtual bool Shadow_hit(const Ray& ray, float& tmin) const override;

	void SetObject(std::shared_ptr<GeometricObject> obj_ptr);
	void SetMaterial(std::shared_ptr<Material> material_ptr) override;

	void ComputeBoundingBox();
	BBox GetBoundingBox() const override;

	// affine transformation
	void Translate(const Vector3D& trans);
	void Translate(const double dx, const double dy, const double dz);
	void Scale(const Vector3D& s);
	void Scale(const double a, const double b, const double c);
	void RotateX(const double r);
	void RotateY(const double r);
	void RotateZ(const double r);
private:
	std::shared_ptr<GeometricObject> mObjectPtr;
	Matrix mInvMatrix;
	bool mTransformTheTexture;
	
	static Matrix mForwardMatrix;
	BBox mBbox;
};