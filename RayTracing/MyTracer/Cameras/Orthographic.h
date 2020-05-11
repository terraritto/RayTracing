#pragma once
#include "Camera.h"

class Orthographic : public Camera
{
public:
	Orthographic();
	Orthographic(const Orthographic& og);
	~Orthographic();

	std::shared_ptr<Camera> Clone() const override;
	Orthographic& operator=(const Orthographic& rhs);

	void SetZWindow(const double zw);
	void RenderScene(const World& w) override;
private:
	float mZw;
};