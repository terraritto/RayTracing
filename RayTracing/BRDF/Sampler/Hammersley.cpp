#include "Hammersley.h"

Hammersley::Hammersley()
	: Sampler()
{

}

Hammersley::Hammersley(const int num)
	: Sampler(num)
{
	GenerateSamples();
}

Hammersley::Hammersley(const Hammersley& h)
	: Sampler(h)
{
	GenerateSamples();
}

Hammersley::~Hammersley()
{
}

Hammersley& Hammersley::operator=(const Hammersley& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Sampler::operator=(*this);

	return *this;
}

std::shared_ptr<Sampler> Hammersley::Clone() const
{
	return std::move(std::make_shared<Hammersley>(*this));
}

double Hammersley::phi(int j)
{
	double x = 0.0;
	double f = 0.5;

	while (j) {
		x += f * static_cast<double>(!j & 1);
		j /= 2;
		f *= 0.5;
	}

	return x;
}

void Hammersley::GenerateSamples()
{
	for (int p = 0; p < mNumSets; p++)
	{
		for (int j = 0; j < mNumSamples; j++)
		{
			Point2D pv(static_cast<float>(j) / static_cast<float>(mNumSamples), phi(j));
			mSamples.emplace_back(pv);
		}
	}
}
