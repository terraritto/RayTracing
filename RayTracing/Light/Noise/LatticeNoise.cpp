#include "LatticeNoise.h"
#include <random>
#include <numeric>

LatticeNoise::LatticeNoise()
	: mFsMin(0.0f)
	, mFsMax(1.0f)
	, mNumOctaves(1)
	, mfBmMin(0.0f)
	, mfBmMax(1.0f)
	, mGain(0.5f)
	, mLacunarity(8)
{
	//init permutation table
	std::iota(mPermutationTable.begin(), mPermutationTable.end(), 0);
	std::random_device seed;
	std::mt19937 engine(seed());
	std::shuffle(mPermutationTable.begin(), mPermutationTable.end(), engine);

	//init value table
	InitValueTable();
}

float LatticeNoise::Perm(int index) const
{
	return mPermutationTable[index & tableMask];
}

int LatticeNoise::Index(int ix, int iy, int iz) const
{
	return Perm(ix + Perm(iy + Perm(iz)));
}

float LatticeNoise::ValueFractalSum(const Point3D& p) const
{
	float amplitude = 1.0f;
	float frequency = 1.0f;
	float fractalSum = 0.0f;

	for (int j = 0; j < mNumOctaves; j++)
	{
		fractalSum += amplitude * ValueNoise(p);
		amplitude *= 0.5;
		frequency *= 2.0;
	}

	fractalSum = (fractalSum - mFsMin) / (mFsMax - mFsMin);

	return fractalSum;
}

float LatticeNoise::ValueTurblence(const Point3D& p) const
{
	float amplitude = 1.0f;
	float frequency = 1.0f;
	float turbulence = 0.0f;

	for (int j = 0; j < mNumOctaves; j++)
	{
		turbulence += amplitude * std::fabs(ValueNoise(frequency * p));
		amplitude *= 0.5f;
		frequency *= 2.0f;
	}

	turbulence /= mFsMax;

	return turbulence;
}

float LatticeNoise::ValuefBm(const Point3D& p) const
{
	float amplitude = 1.0f;
	float frequency = 1.0f;
	float fBm = 0.0f;

	for (int j = 0; j < mNumOctaves; j++)
	{
		fBm += amplitude * ValueNoise(frequency * p);
		amplitude *= mGain;
		frequency *= mLacunarity;
	}

	fBm = (fBm - mfBmMin) / (mfBmMax - mfBmMin);

	return fBm;
}

void LatticeNoise::SetFsMin(const float fs)
{
	mFsMin = fs;
}

void LatticeNoise::SetFsMax(const float fs)
{
	mFsMax = fs;
}

void LatticeNoise::SetOctaves(const int octave)
{
	mNumOctaves = octave;
}

void LatticeNoise::SetfBmMin(const float fbm)
{
	mfBmMin = fbm;
}

void LatticeNoise::SetfBmMax(const float fbm)
{
	mfBmMax = fbm;
}

void LatticeNoise::SetGain(const float g)
{
	mGain = g;
}

void LatticeNoise::SetLacunarity(const float l)
{
	mLacunarity = l;
}

void LatticeNoise::InitValueTable()
{
	//random device
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	for (int i = 0; i < tableSize; i++)
	{
		mValueTable[i] = 1.0 - 2.0 * floatRand(mt);
	}
}
