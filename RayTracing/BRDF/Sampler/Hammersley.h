#pragma once
#include "Sampler.h"

class Hammersley : public Sampler
{
public:
	Hammersley();
	Hammersley(const int num);
	Hammersley(const Hammersley& h);
	~Hammersley();

	Hammersley& operator=(const Hammersley& rhs);
	std::shared_ptr<Sampler> Clone() const override;

	double phi(int j);
	void GenerateSamples() override;

};