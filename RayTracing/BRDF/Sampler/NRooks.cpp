#include "NRooks.h"
#include <random>

NRooks::NRooks()
	: Sampler()
{

}

NRooks::NRooks(const int numSample)
	: Sampler(numSample)
{
	GenerateSamples();
}

NRooks::NRooks(const int numSamples, const int m)
	: Sampler(numSamples, m)
{
	GenerateSamples();
}

NRooks::~NRooks()
{

}

NRooks::NRooks(const NRooks& nr)
	: Sampler(nr)
{
	GenerateSamples();
}

std::shared_ptr<Sampler> NRooks::Clone() const
{
	return std::move(std::make_shared<NRooks>(*this));
}

void NRooks::GenerateSamples()
{
	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	for (int p = 0; p < mNumSets; p++)
	{
		for (int j = 0; j < mNumSamples; j++)
		{
			Point2D sp((j + floatRand(mt)) / mNumSamples, (j + floatRand(mt)) / mNumSamples);
			mSamples.push_back(sp);
		}
	}

	ShuffleXCoordinates();
	ShuffleYCoordinates();
}