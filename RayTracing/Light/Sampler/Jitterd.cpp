#include "Jittered.h"
#include "../Maths/Point2D.h"
#include <random>
#include <cmath>

Jittered::Jittered()
	:Sampler()
{

}

Jittered::Jittered(const int numSamples)
	: Sampler(numSamples)
{
	GenerateSamples();
}

Jittered::Jittered(const int numSamples, const int m)
	: Sampler(numSamples, m)
{
	GenerateSamples();
}

Jittered::Jittered(const Jittered& js)
	: Sampler(js)
{
	GenerateSamples();
}

Jittered::~Jittered()
{

}

Jittered& Jittered::operator=(const Jittered& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Sampler::operator=(rhs);

	return *this;
}

std::shared_ptr<Sampler> Jittered::Clone() const
{
	return std::move(std::make_shared<Jittered>(*this));
}

void Jittered::GenerateSamples()
{
	int n = std::sqrt(mNumSamples);

	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	for (int p = 0; p < mNumSets; p++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				Point2D sp((k + floatRand(mt)) / n, (j + floatRand(mt)) / n);
				mSamples.emplace_back(sp);
			}
		}
	}
}