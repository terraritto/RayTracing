#pragma once
#include "Camera.h"
#include "..//Maths/Point2D.h"

class Spherical : public Camera
{
public:
	Spherical();
	Spherical(const Spherical& sphere);
	~Spherical();

	std::shared_ptr<Camera> Clone() const override;
	Spherical& operator=(const Spherical& rhs);

	Vector3D GetDirection(const Point2D& pp, const int hRes,
		const int vRes, const float s) const;
	void RenderScene(const World& w) override;

	void SetPsiMax(float psi) { mPsiMax = psi; }
	void SetLambdaMax(float lambda) { mLambdaMax = lambda; }
private:
	float mLambdaMax;
	float mPsiMax;
};