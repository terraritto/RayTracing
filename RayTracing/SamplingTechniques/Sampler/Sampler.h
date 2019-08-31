#pragma once
#include "../Maths/Point2D.h"
#include <vector>
#include <memory>

class Sampler
{
public:
	Sampler();
	Sampler(const int num);
	Sampler(const int num, const int numSets);
	Sampler(const Sampler& s);
	virtual ~Sampler();

	Sampler& operator=(const Sampler& rhs);
	virtual std::shared_ptr<Sampler> Clone() const { return std::move(std::make_shared<Sampler>(*this)); };

	virtual void GenerateSamples(){};
	void SetupShuffledIndices();
	void SetNumSets(const int np);
	int GetNumSamples();
	void ShuffleXCoordinates();
	void ShuffleYCoordinates();

	//convert disk from square
	void MapSamplesToUnitDisk();

	Point2D SampleUnitSquare();
	Point2D SampleUnitDisk();
protected:
	int mNumSamples;
	int mNumSets;
	std::vector<Point2D> mSamples;
	std::vector<Point2D> mDiskSamples;
	std::vector<int> mShuffledIndices;
	unsigned long mCount;
	int mJump;
};