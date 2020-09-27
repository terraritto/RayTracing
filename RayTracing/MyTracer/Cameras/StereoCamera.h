#pragma once
#include "Camera.h"
#include <cmath>

enum class EViewingType
{
	EParallel,
	ETransverse
};

class StereoCamera : public Camera
{
public:
	StereoCamera();
	StereoCamera(const StereoCamera& stereo);
	~StereoCamera();

	std::shared_ptr<Camera> Clone() const override;
	StereoCamera& operator=(const StereoCamera& rhs);

	void SetupCameras();
	void RenderScene(World& w) override;

	void SetLeftCamera(std::shared_ptr<Camera> camera) { mLeftCameraPtr = camera; }
	void SetRightCamera(std::shared_ptr<Camera> camera) { mRightCameraPtr = camera; }
	void SetPixelGap(int gap) { mPixelGap = gap; }
	void SetStereoAngle(float beta) { mBeta = beta; }
	void UseParallelViewing() { mViewing = EViewingType::EParallel; }
	void UseTransverseViewing() { mViewing = EViewingType::ETransverse; }

private:
	EViewingType mViewing;
	int mPixelGap;
	float mBeta;
	std::shared_ptr<Camera> mLeftCameraPtr;
	std::shared_ptr<Camera> mRightCameraPtr;
};