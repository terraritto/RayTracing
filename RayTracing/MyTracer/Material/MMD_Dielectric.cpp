#include "MMD_Dielectric.h"

MMD_Dielectric::MMD_Dielectric()
	: MMD_Matte()
{
	mFresnelBRDF = std::make_shared<FresnelReflector>();
	mFresnelBTDF = std::make_shared<FresnelTransmitter>();
}

MMD_Dielectric::MMD_Dielectric(const MMD_Dielectric& tp)
	: MMD_Matte(tp)
{
	if (tp.mFresnelBRDF)
	{
		mFresnelBRDF = tp.mFresnelBRDF->Clone();
	}
	else
	{
		mFresnelBRDF = std::make_shared<FresnelReflector>();
	}

	if (tp.mFresnelBTDF)
	{
		mFresnelBTDF = tp.mFresnelBTDF->Clone();
	}
	else
	{
		mFresnelBTDF = std::make_shared<FresnelTransmitter>();
	}

}

MMD_Dielectric::~MMD_Dielectric()
{
}

MMD_Dielectric& MMD_Dielectric::operator=(const MMD_Dielectric& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	MMD_Matte::operator=(rhs);

	if (rhs.mFresnelBRDF)
	{
		mFresnelBRDF = rhs.mFresnelBRDF->Clone();
	}

	if (rhs.mFresnelBTDF)
	{
		mFresnelBTDF = rhs.mFresnelBTDF->Clone();
	}

	mCfIn = rhs.mCfIn;
	mCfOut = rhs.mCfOut;

	return *this;

}

std::shared_ptr<MMD_Dielectric> MMD_Dielectric::Clone() const
{
	return std::make_shared<MMD_Dielectric>();
}

RGBColor MMD_Dielectric::Shade(ShadeRec& sr)
{
	if (mSVDiffuseBRDF->GetAlpha(sr) != 0.0f)
	{
		RGBColor L(MMD_Matte::Shade(sr));
		return L;
	}

	//transparent
	RGBColor L = black;
	Vector3D wi;
	Vector3D wo(-sr.mRay.mDirection);
	RGBColor fr = mFresnelBRDF->SampleFunc(sr, wo, wi);
	Ray reflected_ray(sr.mHitPoint, wi);
	float t;
	RGBColor Lr, Lt;
	float ndotwi = sr.mNormal * wi;

	if (mFresnelBTDF->tir(sr)) //total internal reflection
	{
		if (ndotwi < 0.0) {
			//reflected ray is inside
			Lr = sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1);
			L += mCfIn.PowColor(t) * Lr;
		}
		else
		{
			//reflected ray is outside
			Lr = sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1);
			L += mCfOut.PowColor(t) * Lr;
		}
	}
	else
	{
		Vector3D wt;
		RGBColor ft = mFresnelBTDF->SampleFunc(sr, wo, wt);
		Ray transmitted_ray(sr.mHitPoint, wt);
		float ndotwt = sr.mNormal * wt;

		if (ndotwi < 0.0)
		{
			//reflected ray is inside
			Lr = fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1) * std::fabs(ndotwi);
			L += mCfIn.PowColor(t) * Lr;

			// transmitted ray is outside
			Lt = ft * sr.mWorld.mTracerPtr->TraceRay(transmitted_ray, t, sr.mDepth + 1) * std::fabs(ndotwt);
			L += mCfOut.PowColor(t) * Lt;
		}
		else
		{
			//reflected ray is outside
			Lr = fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1) * std::fabs(ndotwi);
			L += mCfOut.PowColor(t) * Lr;

			//transmitted ray is inside
			Lt = ft * sr.mWorld.mTracerPtr->TraceRay(transmitted_ray, t, sr.mDepth + 1) * std::fabs(ndotwt);
			L += mCfIn.PowColor(t) * Lt;
		}
	}

	return L;
}

RGBColor MMD_Dielectric::AreaLightShade(ShadeRec& sr)
{
	//if not black, It's not transparent,
	//so return color for mmd_matte output.
	/*
	if (mSVDiffuseBRDF->GetAlpha(sr) != 0.0f)
	{
		RGBColor L(MMD_Matte::Shade(sr));
		return L;
	}
	*/
	RGBColor L(MMD_Matte::Shade(sr));

	//transparent
	//if enter this process,
	//it means transparent object.
	//RGBColor L = black;
	Vector3D wi;
	Vector3D wo(-sr.mRay.mDirection);
	RGBColor fr = mFresnelBRDF->SampleFunc(sr, wo, wi);
	Ray reflected_ray(sr.mHitPoint, wi);
	float t;
	RGBColor Lr, Lt;
	float ndotwi = sr.mNormal * wi;

	if (mFresnelBTDF->tir(sr)) //total internal reflection
	{
		if (ndotwi < 0.0) {
			//reflected ray is inside
			Lr = sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1);
			L += mCfIn.PowColor(t) * Lr;
		}
		else
		{
			//reflected ray is outside
			Lr = sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1);
			L += mCfOut.PowColor(t) * Lr;
		}
	}
	else
	{
		Vector3D wt;
		RGBColor ft = mFresnelBTDF->SampleFunc(sr, wo, wt);
		Ray transmitted_ray(sr.mHitPoint, wt);
		float ndotwt = sr.mNormal * wt;

		if (ndotwi < 0.0)
		{
			//reflected ray is inside
			Lr = fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1) * std::fabs(ndotwi);
			L += mCfIn.PowColor(t) * Lr;

			// transmitted ray is outside
			Lt = ft * sr.mWorld.mTracerPtr->TraceRay(transmitted_ray, t, sr.mDepth + 1) * std::fabs(ndotwt);
			L += mCfOut.PowColor(t) * Lt;
		}
		else
		{
			//reflected ray is outside
			Lr = fr * sr.mWorld.mTracerPtr->TraceRay(reflected_ray, t, sr.mDepth + 1) * std::fabs(ndotwi);
			L += mCfOut.PowColor(t) * Lr;

			//transmitted ray is inside
			Lt = ft * sr.mWorld.mTracerPtr->TraceRay(transmitted_ray, t, sr.mDepth + 1) * std::fabs(ndotwt);
			L += mCfIn.PowColor(t) * Lt;
		}
	}

	return L;
}

void MMD_Dielectric::SetEtaIn(float eta)
{
	mFresnelBRDF->SetEtaIn(eta);
	mFresnelBTDF->SetEtaIn(eta);
}

void MMD_Dielectric::SetEtaOut(float eta)
{
	mFresnelBRDF->SetEtaOut(eta);
	mFresnelBTDF->SetEtaOut(eta);
}

void MMD_Dielectric::SetCfIn(const RGBColor& color)
{
	mCfIn = color;
}

void MMD_Dielectric::SetCfIn(const float color)
{
	mCfIn = RGBColor(color);
}

void MMD_Dielectric::SetCfIn(const float r, const float g, const float b)
{
	mCfOut = RGBColor(r,g,b);
}

void MMD_Dielectric::SetCfOut(const RGBColor& color)
{
	mCfOut = color;
}

void MMD_Dielectric::SetCfOut(const float color)
{
	mCfOut = RGBColor(color);
}

void MMD_Dielectric::SetCfOut(const float r, const float g, const float b)
{
	mCfOut = RGBColor(r, g, b);
}
