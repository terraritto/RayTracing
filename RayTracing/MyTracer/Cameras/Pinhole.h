#pragma once
#include "Camera.h"
#include "..//Maths//Point2D.h"
//multithread
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>

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
	void RenderScene(World& w) override;
	void RenderStereo(World& w, float x, int offset) override;
private:
	void CalculateMultiThread(World& w, std::mutex& mtx, std::condition_variable& cv, std::atomic<int>& completed, int start, int end);

	float mDistance;
	float mZoom;
	int mThreadNum;
};