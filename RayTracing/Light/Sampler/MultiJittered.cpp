#include "MultiJittered.h"
#include <random>
#include <cmath>

MultiJittered::MultiJittered()
	: Sampler()
{

}

MultiJittered::MultiJittered(const int numSamples)
	:Sampler(numSamples)
{
	GenerateSamples();
}

MultiJittered::MultiJittered(const int numSamples, const int m)
	: Sampler(numSamples, m)
{
	GenerateSamples();
}

MultiJittered::MultiJittered(const MultiJittered& mjs)
	:Sampler(mjs)
{
}

MultiJittered::~MultiJittered()
{
}

MultiJittered& MultiJittered::operator=(const MultiJittered& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Sampler::operator=(rhs);

	return *this;
}

std::shared_ptr<Sampler> MultiJittered::Clone() const
{
	return std::move(std::make_shared<Sampler>(*this));
}

void MultiJittered::GenerateSamples()
{
	int n = std::sqrt(mNumSamples);
	float subCellWidth = 1.0 / mNumSamples;

	//fill ths sample array
	Point2D fillPoint;
	for (int j = 0; j < mNumSamples * mNumSets; j++)
	{
		mSamples.emplace_back(fillPoint);
	}

	//initialize
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, subCellWidth);

	for (int p = 0; p < mNumSets; p++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				mSamples[i * n + j + p * mNumSamples].mPosX = (i * n + j) * subCellWidth + floatRand(mt);
				mSamples[i * n + j + p * mNumSamples].mPosY = (j * n + i) * subCellWidth + floatRand(mt);
			}
		}
	}

	// shuffle x coordinates
	for (int p = 0; p < mNumSets; p++) 
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::uniform_int_distribution<int> intRand(j, n - 1);
				int k = intRand(mt);
				float t = mSamples[i * n + j + p * mNumSamples].mPosX;
				mSamples[i * n + j + p * mNumSamples].mPosX = mSamples[i * n + k + p * mNumSamples].mPosX;
				mSamples[i * n + k + p * mNumSamples].mPosX = t;
			}
		}
	}

	// shuffle y coordinates
	for (int p = 0; p < mNumSets; p++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::uniform_int_distribution<int> intRand(j, n - 1);
				int k = intRand(mt);
				float t = mSamples[j * n + i + p * mNumSamples].mPosY;
				mSamples[j * n + i + p * mNumSamples].mPosX = mSamples[j * n + k + p * mNumSamples].mPosY;
				mSamples[j * n + k + p * mNumSamples].mPosY = t;
			}
		}
	}
}
