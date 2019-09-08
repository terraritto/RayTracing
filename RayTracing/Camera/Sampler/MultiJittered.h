#pragma once
#include "Sampler.h"

class MultiJittered :public Sampler
{
public:
	MultiJittered();
	MultiJittered(const int numSamples);
	MultiJittered(const int numSamples, const int m);
	MultiJittered(const MultiJittered& mjs);
	~MultiJittered();

	MultiJittered& operator=(const MultiJittered& rhs);
	std::shared_ptr<Sampler> Clone() const override;

	void GenerateSamples();
};