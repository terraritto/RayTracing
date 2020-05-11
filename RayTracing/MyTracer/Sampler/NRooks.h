#pragma once
#include "Sampler.h"

class NRooks : public Sampler
{
public:
	NRooks();
	NRooks(const int numSamples);
	NRooks(const int numSamples, const int m);
	NRooks(const NRooks& nr);
	~NRooks();

	NRooks& operator=(const NRooks& rhs);
	std::shared_ptr<Sampler> Clone() const override;
	
	void GenerateSamples() override;
};