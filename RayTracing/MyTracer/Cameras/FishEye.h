#pragma once
#include "Camera.h"
#include "..//Maths/Point2D.h"

class FishEye : public Camera
{
public:
	FishEye();
	FishEye(const FishEye& eye);
	~FishEye();

	std::shared_ptr<Camera> Clone() const override;
	FishEye& operator=(const FishEye& rhs);

	Vector3D GetDirection(const Point2D& p, const int hRes
		, const int vRes, const float s, float& r) const;
	void RenderScene(World& w) override;

	void SetPsiMax(float psi) { mPsiMax = psi; }
private:
	float mPsiMax;
};