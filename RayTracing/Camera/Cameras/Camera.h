#pragma once
#include <memory>
#include "..//Utility//World.h"
#include "..//Maths//Point3D.h"
#include "..//Maths//Vector3D.h"

class Camera
{
public:
	Camera();
	Camera(const Camera& camera);
	virtual ~Camera();

	virtual std::shared_ptr<Camera> Clone() const { return std::move(std::make_shared<Camera>(*this)); };

	virtual void RenderScene(const World& w) = 0;
	void ComputeUVW();

	void SetEye(const Point3D& p);
	void SetEye(const float x, const float y, const float z);
	void SetLookAt(const Point3D& p);
	void SetLookAt(const float x, const float y, const float z);
	void SetUpVector(const Vector3D& u);
	void SetUpVector(const float x, const float y, const float z);
	void SetRoll(const float ra);
	void SetExposureTime(const float exposure);
protected:
	Point3D mEye;
	Point3D mLookAt;
	float mRollAngle;
	Vector3D mU, mV, mW;
	Vector3D mUp;
	float mExposureTime;

	Camera& operator=(const Camera& camera);
};