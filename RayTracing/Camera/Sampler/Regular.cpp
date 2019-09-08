#include "Regular.h"
#include "../Maths/Point2D.h"
#include <cmath>


Regular::Regular()
	:Sampler()
{

}

Regular::Regular(const int num)
	: Sampler(num)
{
	GenerateSamples();
}

Regular::Regular(const Regular& u)
	: Sampler(u)
{
	GenerateSamples();
}

Regular::~Regular()
{

}

Regular& Regular::operator=(const Regular& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Sampler::operator=(rhs);

	return *this;
}

std::shared_ptr<Sampler> Regular::Clone() const
{
	return std::move((std::make_shared<Regular>(*this)));
}

void Regular::GenerateSamples()
{
	int n = std::sqrt(mNumSamples);

	for (int j = 0; j < mNumSets; j++)
	{
		for (int p = 0; p < n; p++)
		{
			for (int q = 0; q < n; q++)
			{
				mSamples.push_back(Point2D((q + 0.5) / n, (p + 0.5) / n));
			}
		}
	}
}