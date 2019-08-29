#pragma once
#include "Sampler.h"

class Jittered : public Sampler
{
public:
	Jittered();
	Jittered(const int numSamples);
	Jittered(const int numSamples, const int m);
	Jittered(const Jittered& u);
	~Jittered();

	Jittered& operator=(const Jittered& rhs);
	std::shared_ptr<Sampler> Clone() const;

	void GenerateSamples() override;
};