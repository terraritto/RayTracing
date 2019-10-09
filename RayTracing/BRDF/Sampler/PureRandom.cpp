#include "PureRandom.h"
#include "../Maths/Point2D.h"
#include <random>

PureRandom::PureRandom()
	: Sampler()
{

}

PureRandom::PureRandom(const int num)
	: Sampler(num)
{
	GenerateSamples();
}

PureRandom::PureRandom(const PureRandom& r)
	: Sampler(r)
{
	GenerateSamples();
}

PureRandom::~PureRandom()
{

}

PureRandom& PureRandom::operator=(const PureRandom& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Sampler::operator=(rhs);

	return *this;
}

std::shared_ptr<Sampler> PureRandom::Clone() const
{
	return std::move(std::make_shared<PureRandom>(*this));
}

void PureRandom::GenerateSamples()
{
	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);


	for (int p = 0; p < mNumSets; p++)
	{
		for (int q = 0; q < mNumSamples; q++)
		{
			mSamples.emplace_back(Point2D(floatRand(mt), floatRand(mt)));
		}
	}
}