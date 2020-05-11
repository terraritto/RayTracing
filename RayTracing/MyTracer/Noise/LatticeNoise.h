#pragma once
#include "../Maths/Point3D.h"
#include <array>

constexpr int tableSize = 256;
constexpr int tableMask = tableSize - 1;

class LatticeNoise
{
public:
	LatticeNoise();
	~LatticeNoise() = default;

	virtual float ValueNoise(const Point3D& p) const = 0;

	float Perm(int index) const;
	int Index(int ix, int iy, int iz) const;

	float ValueFractalSum(const Point3D& p) const;
	float ValueTurblence(const Point3D& p) const;
	float ValuefBm(const Point3D& p) const;

	void SetFsMin(const float fs);
	void SetFsMax(const float fs);
	void SetOctaves(const int octave);

	void SetfBmMin(const float fbm);
	void SetfBmMax(const float fbm);
	void SetGain(const float g);
	void SetLacunarity(const float l);
protected:
	std::array<float, tableSize> mValueTable;
	std::array<int, tableSize> mPermutationTable;
private:
	void InitValueTable();

	float mFsMin;
	float mFsMax;
	int mNumOctaves;

	float mfBmMin;
	float mfBmMax;
	float mGain;
	float mLacunarity;

};