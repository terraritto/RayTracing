#pragma once

#include "Sampler.h"

class PureRandom : public Sampler
{
public:
	PureRandom();
	PureRandom(const int num);
	PureRandom(const PureRandom& r);
	~PureRandom();

	PureRandom& operator=(const PureRandom& rhs);
	std::shared_ptr<Sampler> Clone() const override;

	void GenerateSamples() override;
};