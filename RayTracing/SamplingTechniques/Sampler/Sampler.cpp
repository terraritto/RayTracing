#include "Sampler.h"
#include <random>
#include <numeric>
#include <algorithm>

Sampler::Sampler()
	: mNumSamples(1)
	, mNumSets(83)
	, mCount(0)
	, mJump(0)
{
	mSamples.reserve(mNumSamples * mNumSets);
	SetupShuffledIndices();
}

Sampler::Sampler(const int ns)
	: mNumSamples(ns)
	, mNumSets(83)
	, mCount(0)
	, mJump(0)
{
	mSamples.reserve(mNumSamples * mNumSets);
	SetupShuffledIndices();
}

Sampler::Sampler(const int ns, const int nSets)
	: mNumSamples(ns)
	, mNumSets(nSets)
	, mCount(0)
	, mJump(0)
{
	mSamples.reserve(mNumSamples * mNumSets);
	SetupShuffledIndices();
}

Sampler::Sampler(const Sampler& s)
	: mNumSamples(s.mNumSamples)
	, mNumSets(s.mNumSets)
	, mSamples(s.mSamples)
	, mShuffledIndices(s.mShuffledIndices)
	, mCount(s.mCount)
	, mJump(s.mJump)
{

}

Sampler& Sampler::operator=(const Sampler& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mNumSamples = rhs.mNumSamples;
	mNumSets = rhs.mNumSets;
	mSamples = rhs.mSamples; 
	mShuffledIndices = rhs.mShuffledIndices;
	mCount = rhs.mCount;
	mJump = rhs.mJump;

	return *this;
}

Sampler::~Sampler()
{

}

void Sampler::SetupShuffledIndices()
{
	//reserve vector
	mShuffledIndices.reserve(mNumSamples * mNumSets);
	
	//make indices
	std::vector<int> indices(mNumSamples);
	std::iota(indices.begin(), indices.end(), 0);

	//make random device
	std::random_device seed;
	std::mt19937 engine(seed());

	for (int p = 0; p < mNumSets; p++)
	{
		std::shuffle(indices.begin(), indices.end(),engine);

		for (int j = 0; j < mNumSamples; j++)
		{
			mShuffledIndices.emplace_back(indices[j]);
		}
	}
}

void Sampler::SetNumSets(const int np)
{
	mNumSets = np;
}

int Sampler::GetNumSamples()
{
	return mNumSamples;
}


Point2D Sampler::SampleUnitSquare()
{
	//random
	std::random_device rd;
	std::mt19937 mt(rd());

	if (mCount % mNumSamples == 0)
	{
		mJump = (mt() % mNumSets) * mNumSamples;
	}

	return mSamples[mJump + mShuffledIndices[mJump + mCount++ % mNumSamples]];

}

void Sampler::ShuffleXCoordinates()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	for (int p = 0; p < mNumSets; p++)
	{
		for (int i = 0; i < mNumSamples - 1; i++)
		{
			int target = mt() % mNumSamples + p * mNumSamples;
			float temp = mSamples[i + p * mNumSamples + 1].mPosX;
			mSamples[i + p * mNumSamples + 1].mPosX = mSamples[target].mPosX;
			mSamples[target].mPosX = temp;
		}
	}
}

void Sampler::ShuffleYCoordinates()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	for (int p = 0; p < mNumSets; p++)
	{
		for (int i = 0; i < mNumSamples - 1; i++)
		{
			int target = mt() % mNumSamples + p * mNumSamples;
			float temp = mSamples[i + p * mNumSamples + 1].mPosY;
			mSamples[i + p * mNumSamples + 1].mPosY = mSamples[target].mPosY;
			mSamples[target].mPosY = temp;
		}
	}
}