#pragma once
#include "Camera.h"
#include "..//Maths//Point2D.h"
#include "..//Sampler//Sampler.h"
#include <memory>

class ThinLens : public Camera
{
public:
	ThinLens();
	ThinLens(const ThinLens& tl);
	~ThinLens();

	std::shared_ptr<Camera> Clone() const override;
	ThinLens& operator=(const ThinLens& rhs);

	Vector3D GetDirection(const Point2D& pixelPoint, Point2D& lensPoint) const;
	void RenderScene(World& w) override;

	void SetSampler(std::shared_ptr<Sampler> sp);
	void SetViewDistance(float distance);
	void SetFocalLength(float length);
	void SetLensRadius(float rad);
private:
	float mLensRadius;
	float mDistance;
	float mFocalLength;
	float mZoom;
	std::shared_ptr<Sampler> mSamplerPtr;
};