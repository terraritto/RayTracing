#pragma once
#include "Camera.h"
#include "..//Maths//Point2D.h"

class Pinhole : public Camera
{
public:
	Pinhole();
	Pinhole(const Pinhole& ph);
	~Pinhole();

	std::shared_ptr<Camera> Clone() const override;
	Pinhole& operator=(const Pinhole& rhs);

	void SetViewDistance(const float vpd);
	void SetZoom(const float zoomFactor);
	Vector3D GetDirection(const Point2D& p) const;
	void RenderScene(const World& w) override;
	void RenderStereo(const World& w, float x, int offset) override;
private:
	float mDistance;
	float mZoom;
};