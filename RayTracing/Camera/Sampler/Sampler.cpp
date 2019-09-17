#include "Sampler.h"
#include "..//Maths//Constants.h"
#include "..//Maths//Point3D.h"
#include <random>
#include <numeric>
#include <algorithm>
#include <cmath>

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

Point2D Sampler::SampleUnitDisk()
{
	//random
	std::random_device rd;
	std::mt19937 mt(rd());

	if (mCount % mNumSamples == 0)
	{
		mJump = (mt() % mNumSets) * mNumSamples;
	}

	return mDiskSamples[mJump + mShuffledIndices[mJump + mCount++ % mNumSamples]];

}

Point3D Sampler::SampleHemisphere()
{
	//random
	std::random_device rd;
	std::mt19937 mt(rd());

	if (mCount % mNumSamples == 0)
	{
		mJump = (mt() % mNumSets) * mNumSamples;
	}

	return mHemisphereSamples[mJump + mShuffledIndices[mJump + mCount++ % mNumSamples]];

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

void Sampler::MapSamplesToUnitDisk()
{
	int size = mSamples.size();
	float r, phi;
	Point2D sp;
	
	mDiskSamples.resize(size);

	for (int j = 0; j < size; j++)
	{
		sp.mPosX = 2.0 * mSamples[j].mPosX - 1.0;
		sp.mPosY = 2.0 * mSamples[j].mPosY - 1.0;

		if (sp.mPosX > -sp.mPosY)
		{
			if (sp.mPosX > sp.mPosY)
			{
				//section 1
				r = sp.mPosX;
				phi = sp.mPosY / sp.mPosX;
			}
			else
			{
				//section 2
				r = sp.mPosY;
				phi = 2 - sp.mPosX / sp.mPosY;
			}
		}
		else
		{
			if (sp.mPosX < sp.mPosY)
			{
				//section 3
				r = -sp.mPosX;
				phi = 4 + sp.mPosY / sp.mPosX;
			}
			else
			{
				//section 4
				r = -sp.mPosY;

				if (sp.mPosY != 0.0)
				{
					phi = 6 - sp.mPosX / sp.mPosY;
				}
				else
				{
					phi = 0.0;
				}
			}
		}

		phi *= PI / 4.0;

		mDiskSamples[j].mPosX = r * std::cos(phi);
		mDiskSamples[j].mPosY = r * std::sin(phi);
	}

	mSamples.erase(mSamples.begin(), mSamples.end());
}

void Sampler::MapSamplesToHemisphere(const float e)
{
	int size = mSamples.size();
	mHemisphereSamples.reserve(mNumSamples * mNumSets);

	for (int j = 0; j < size; j++)
	{
		float cosPhi = std::cos(2.0 * PI * mSamples[j].mPosX);
		float sinPhi = std::sin(2.0 * PI * mSamples[j].mPosX);
		float cosTheta = std::pow((1.0 - mSamples[j].mPosY), 1.0 / (e + 1.0));
		float sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
		float pu = sinTheta * cosPhi;
		float pv = sinTheta * sinPhi;
		float pw = cosTheta;

		mHemisphereSamples.emplace_back(Point3D(pu, pv, pw));
	}
}