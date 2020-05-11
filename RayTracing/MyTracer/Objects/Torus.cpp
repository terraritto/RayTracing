#include "Torus.h"
#include "..\Maths\Constants.h"

Torus::Torus(double a, double b)
	: GeometricObject()
	, mA(a)
	, mB(b)
{
}

Torus::Torus(const Torus& torus)
	: GeometricObject(torus)
	, mA(torus.mA)
	, mB(torus.mB)
{
}

std::shared_ptr<Torus> Torus::Clone() const
{
	return std::make_shared<Torus>(*this);
}

Torus& Torus::operator=(Torus& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);
	mA = rhs.mA;
	mB = rhs.mB;

	return *this;
}

bool Torus::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	double x1 = ray.mOrigin.mPosX; double y1 = ray.mOrigin.mPosY; double z1 = ray.mOrigin.mPosZ;
	double d1 = ray.mDirection.mPosX; double d2 = ray.mDirection.mPosY; double d3 = ray.mDirection.mPosZ;
	std::array<double, 5> coeffs;
	std::array<double, 4> roots;
	
	//define the coefficients
	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - mA * mA - mB * mB;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd = 4.0 * mA * mA;

	coeffs[0] = e * e - four_a_sqrd * (mB * mB - y1 * y1);
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;

	//find the roots
	int num_real_roots = SolveQuartic(coeffs, roots);

	bool intersected = false;
	double t = kHugeValue;

	if (num_real_roots == 0) { //ray misses the torus
		return false;
	}

	// find the smallest root greater than kEpsilon if any
	for (int j = 0; j < num_real_roots; j++)
	{
		if (roots[j] > kEpsilon)
		{
			intersected = true;
			if (roots[j] < t)
			{
				t = roots[j];
			}
		}
	}

	if (!intersected)
	{
		return false;
	}

	tMin = t;
	sr.mLocalHitPoint = ray.mOrigin + t * ray.mDirection;
	sr.mNormal = ComputeNormal(sr.mLocalHitPoint);

	return true;
}

bool Torus::Shadow_hit(const Ray& ray, float& tMin) const
{
	double x1 = ray.mOrigin.mPosX; double y1 = ray.mOrigin.mPosY; double z1 = ray.mOrigin.mPosZ;
	double d1 = ray.mDirection.mPosX; double d2 = ray.mDirection.mPosY; double d3 = ray.mDirection.mPosZ;
	std::array<double, 5> coeffs;
	std::array<double, 4> roots;

	//define the coefficients
	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - mA * mA - mB * mB;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd = 4.0 * mA * mA;

	coeffs[0] = e * e - four_a_sqrd * (mB * mB - y1 * y1);
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;

	//find the roots
	int num_real_roots = SolveQuartic(coeffs, roots);

	bool intersected = false;
	double t = kHugeValue;

	if (num_real_roots == 0) { //ray misses the torus
		return false;
	}

	// find the smallest root greater than kEpsilon if any
	for (int j = 0; j < num_real_roots; j++)
	{
		if (roots[j] > kEpsilon)
		{
			intersected = true;
				if (roots[j] < t)
				{
					t = roots[j];
				}
		}
	}

	if (!intersected)
	{
		return false;
	}

	tMin = t;

	return true;
}


Normal Torus::ComputeNormal(Point3D p) const
{
	Normal n;
	n.mPosX = 4.0 * p.mPosX * (std::pow(p.mPosX, 2) + std::pow(p.mPosY, 2) + std::pow(p.mPosZ, 2)
		- std::pow(mA, 2) - std::pow(mB, 2));
	n.mPosY = 4.0 * p.mPosY * (std::pow(p.mPosX, 2) + std::pow(p.mPosY, 2) + std::pow(p.mPosZ, 2)
		- std::pow(mA, 2) - std::pow(mB, 2) + 2 * std::pow(mA,2));
	n.mPosZ = 4.0 * p.mPosZ * (std::pow(p.mPosX, 2) + std::pow(p.mPosY, 2) + std::pow(p.mPosZ, 2)
		- std::pow(mA, 2) - std::pow(mB, 2));
	n.Normalize();

	return n;
}
