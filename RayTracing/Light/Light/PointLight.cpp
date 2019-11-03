#include "PointLight.h"

PointLight::PointLight()
	: Light()
	, mLs(1.0)
	, mColor(1.0)
	, mLocation(0, 0, 0)
{

}

PointLight::PointLight(const PointLight& pl)
	: Light(pl)
	, mLs(pl.mLs)
	, mColor(pl.mColor)
	, mLocation(pl.mLocation)
{

}

PointLight::~PointLight()
{

}

PointLight& PointLight::operator=(const PointLight& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Light::operator=(rhs);

	mLs = rhs.mLs;
	mColor = rhs.mColor;
	mLocation = rhs.mLocation;

	return *this;
}

std::shared_ptr<PointLight> PointLight::Clone() const
{
	return std::make_shared<PointLight>(*this);
}

void PointLight::SetScaleRadiance(const float b)
{
	mLs = b;
}

void PointLight::SetColor(const float c)
{
	mColor.mRed = c;
	mColor.mBlue = c;
	mColor.mGreen = c;
}

void PointLight::SetColor(const RGBColor& c)
{
	mColor = c;
}

void PointLight::SetColor(const float r, const float g, const float b)
{
	mColor.mRed = r;
	mColor.mGreen = g;
	mColor.mBlue = b;
}

void PointLight::SetLocation(Vector3D d)
{
	mLocation = d;
}

void PointLight::SetLocation(float dx, float dy, float dz)
{
	mLocation.mPosX = dx;
	mLocation.mPosY = dy;
	mLocation.mPosZ = dz;
}

Vector3D PointLight::GetDirection(ShadeRec& sr)
{
	return (mLocation - sr.mHitPoint).hat();
}

RGBColor PointLight::L(ShadeRec& sr)
{
	return mLs * mColor;
}

bool PointLight::InShadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int numObjects = sr.mWorld.mObjects.size();
	float d = Point3D(mLocation.mPosX, mLocation.mPosY, mLocation.mPosZ).Length(ray.mOrigin);

	for (int j = 0; j < numObjects; j++)
	{
		if (sr.mWorld.mObjects[j]->Shadow_hit(ray, t) && t < d)
		{
			return true;
		}
	}
	return false;
}
