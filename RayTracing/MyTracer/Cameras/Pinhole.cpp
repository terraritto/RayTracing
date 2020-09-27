#include "Pinhole.h"
#include "..//Utility//RGBColor.h"
#include "..//Maths//Ray.h"
#include "..//Utility//ViewPlane.h"

Pinhole::Pinhole()
	: Camera()
	, mDistance(500)
	, mZoom(1.0)
	, mThreadNum(std::thread::hardware_concurrency())
{
}

Pinhole::Pinhole(const Pinhole& c)
	: Camera(c)
	, mDistance(c.mDistance)
	, mZoom(c.mZoom)
	, mThreadNum(c.mThreadNum)
{

}

Pinhole::~Pinhole()
{

}

std::shared_ptr<Camera> Pinhole::Clone() const
{
	return std::move(std::make_shared<Pinhole>(*this));
}

Pinhole& Pinhole::operator=(const Pinhole& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);

	mDistance = rhs.mDistance;
	mZoom = rhs.mZoom;

	return *this;
}
/*
void Pinhole::RenderScene(const World& w)
{
	RGBColor L;
	ViewPlane vp(w.mViewPlane);
	Ray ray;
	int depth = 0; //recursion depth
	Point2D sp;
	Point2D pp;

	w.OpenWindow(vp.mHRes, vp.mVRes);
	vp.mPixelSize /= mZoom;
	ray.mOrigin = mEye;

	for (int r = 0; r < vp.mVRes; r++)
	{
		for (int c = 0; c < vp.mHRes; c++)
		{
			L = black;

			for (int j = 0; j < vp.mNumSamples; j++)
			{
				sp = vp.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = vp.mPixelSize * (c - 0.5 * vp.mHRes + sp.mPosX);
				pp.mPosY = vp.mPixelSize * (r - 0.5 * vp.mVRes + sp.mPosY);
				ray.mDirection = GetDirection(pp);
				// TraceRay output black pixel now
				// so if you run any programs, image is all black.
				// if you use TraceRay(ray);, you can output ideal images. 
				L += w.mTracerPtr->TraceRay(ray, depth);
			}
			L /= vp.mNumSamples;
			L *= mExposureTime;
			w.DisplayPixel(r, c, L);
		}
	}
}
*/

void Pinhole::RenderScene(World& w)
{
	RGBColor L;
	ViewPlane vp(w.mViewPlane);
	Ray ray;
	int depth = 0; //recursion depth

	w.OpenWindow(vp.mHRes, vp.mVRes);
	vp.mPixelSize /= mZoom;
	ray.mOrigin = mEye;

	//multi thread setting
	int rowsPerThread = vp.mVRes / mThreadNum;
	int leftOver = vp.mVRes % mThreadNum;

	//std::mutex mtx;
	std::condition_variable cv;
	std::atomic<int> completedThreads = { 0 };
	std::vector<std::thread> threads;

	for (int i = 0; i < mThreadNum; ++i)
	{
		int rowStart = i * rowsPerThread;
		int rowEnd = rowStart + rowsPerThread;
		if (i == mThreadNum - 1)
		{
			rowEnd += leftOver;
		}

		
		std::thread t([this, &w, &cv, &completedThreads, rowStart, rowEnd]
		{
			CalculateMultiThread(w, mtx, cv, completedThreads, rowStart, rowEnd);
		});

		threads.push_back(std::move(t));
	}

	//wait that completed threads num equal thread num.
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [&completedThreads, this] {
			return completedThreads == mThreadNum;
		});
	}

	//join
	for (auto& t : threads)
	{
		t.join();
	}
}

void Pinhole::RenderStereo(World& w, float x, int offset)
{
	ViewPlane vp(w.mViewPlane);
	Ray ray;
	int depth = 0; //recursion depth

	Point2D sp;
	Point2D pp;
	RGBColor L;

	vp.mPixelSize /= mZoom;
	ray.mOrigin = mEye;

	for (int r = 0; r < vp.mVRes; r++)
	{
		for (int c = 0; c < vp.mHRes; c++)
		{
			L = black;

			for (int j = 0; j < vp.mNumSamples; j++)
			{
				sp = vp.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = vp.mPixelSize * (c - 0.5 * vp.mHRes + sp.mPosX) + x;
				pp.mPosY = vp.mPixelSize * (r - 0.5 * vp.mVRes + sp.mPosY);
				ray.mDirection = GetDirection(pp);
				// TraceRay output black pixel now
				// so if you run any programs, image is all black.
				// if you use TraceRay(ray);, you can output ideal images. 
				L += w.mTracerPtr->TraceRay(ray, depth);
			}
			L /= vp.mNumSamples;
			L *= mExposureTime;
			w.DisplayPixel(r, c + offset, L);
		}
	}
}

void Pinhole::CalculateMultiThread(World& w, std::mutex& mtx, std::condition_variable& cv, std::atomic<int>& completed,int start,int end)
{
	ViewPlane vp(w.mViewPlane);
	Ray ray;

	Point2D sp;
	Point2D pp;
	RGBColor L;

	vp.mPixelSize /= mZoom;
	ray.mOrigin = mEye;

	for (int r = start; r < end; r++)
	{
		for (int c = 0; c < vp.mHRes; c++)
		{
			L = black;

			for (int j = 0; j < vp.mNumSamples; j++)
			{
				sp = vp.mSamplerPtr->SampleUnitSquare();
				pp.mPosX = vp.mPixelSize * (c - 0.5 * vp.mHRes + sp.mPosX);
				pp.mPosY = vp.mPixelSize * (r - 0.5 * vp.mVRes + sp.mPosY);
				ray.mDirection = GetDirection(pp);
				{
					std::lock_guard lock(mtx);
					L += w.mTracerPtr->TraceRay(ray, 0); //depth = 0
				}
			}
			L /= vp.mNumSamples;
			L *= mExposureTime;
			{
				// Ç¢ÇÁÇ»Ç¢Ç©Ç‡ÅAmmdÇÃéûÇÃèàóùÇ≈ÇÕÇ‚ÇÁÇ»Ç≠ÇƒÇ‡ìÆÇ¢ÇΩÇÃÇ≈
				// draw pixelç¸ÇÈÇ∆Ç´ÇÃÇ›std::lock_guardÇóßÇƒÇÈ
				std::lock_guard lock(mtx);
				w.DisplayPixel(r, c, L);
			}
		}
	}

	{
		std::lock_guard lock(mtx);
		completed++;
		cv.notify_one();
	}
}

void Pinhole::SetViewDistance(float d)
{
	mDistance = d;
}

void Pinhole::SetZoom(float zoomFactor)
{
	mZoom = zoomFactor;
}

Vector3D Pinhole::GetDirection(const Point2D& p) const
{
	Vector3D dir = p.mPosX * mU + p.mPosY * mV - mDistance * mW;
	dir.Normalize();
	return dir;
}