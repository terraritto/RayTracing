#pragma once
#include "Sampler.h"

class Regular : public Sampler
{
public:
	Regular();
	Regular(const int num);
	Regular(const Regular& u);
	~Regular();

	Regular& operator=(const Regular& rhs);
	std::shared_ptr<Sampler> Clone() const override;

	void GenerateSamples() override;
};