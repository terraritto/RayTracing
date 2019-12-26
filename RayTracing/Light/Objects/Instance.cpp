#include "Instance.h"

Instance::Instance()
	: GeometricObject()
	, mObjectPtr(nullptr)
	, mInvMatrix()
	, mTransformTheTexture(true)
{
	mInvMatrix.SetIdentity();
}

Instance::Instance(std::shared_ptr<GeometricObject> obj_ptr)
	: GeometricObject()
	, mObjectPtr(obj_ptr)
	, mInvMatrix()
	, mTransformTheTexture(true)
{
	mInvMatrix.SetIdentity();
}

Instance::Instance(const Instance& instance)
	: GeometricObject(instance)
	, mInvMatrix(instance.mInvMatrix)
	, mTransformTheTexture(instance.mTransformTheTexture)
{
	if (instance.mObjectPtr)
	{
		mObjectPtr = instance.mObjectPtr->Clone();
	}
	else
	{
		mObjectPtr = nullptr;
	}
}

Instance::~Instance()
{
}

Instance& Instance::operator=(const Instance& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	GeometricObject::operator=(rhs);

	if (rhs.mObjectPtr)
	{
		mObjectPtr = rhs.mObjectPtr->Clone();
	}
	else
	{
		mObjectPtr = nullptr;
	}

	mInvMatrix = rhs.mInvMatrix;
	mTransformTheTexture = rhs.mTransformTheTexture;

	return *this;
}

std::shared_ptr<Instance> Instance::Clone() const
{
	return std::make_shared<Instance>(*this);
}

bool Instance::hit(const Ray& ray, double& tMin, ShadeRec& sr)
{
	Ray inv_ray(ray);
	inv_ray.mOrigin = mInvMatrix * inv_ray.mOrigin;
	inv_ray.mDirection = mInvMatrix * inv_ray.mDirection;

	if (mObjectPtr->hit(inv_ray, tMin, sr))
	{
		sr.mNormal = mInvMatrix * sr.mNormal;
		sr.mNormal.Normalize();
		
		if (mObjectPtr->GetMaterial())
		{
			mMaterial = mObjectPtr->GetMaterial();
		}

		if (!mTransformTheTexture) {
			sr.mLocalHitPoint = ray.mOrigin + tMin * ray.mDirection;
		}

		return true;
	}
	return false;
}

bool Instance::Shadow_hit(const Ray& ray, float& tmin) const
{
	Ray inv_ray(ray);
	inv_ray.mOrigin = mInvMatrix * inv_ray.mOrigin;
	inv_ray.mDirection = mInvMatrix * inv_ray.mDirection;

	if (mObjectPtr->Shadow_hit(inv_ray, tmin))
	{
		return true;
	}
	return false;
}

void Instance::SetObject(std::shared_ptr<GeometricObject> obj_ptr)
{
	mObjectPtr = obj_ptr;
}

void Instance::SetMaterial(std::shared_ptr<Material> material_ptr)
{
	mMaterial = material_ptr;
}

void Instance::Translate(const Vector3D& trans)
{
	Matrix invTranslationMatrix;
	invTranslationMatrix.SetIdentity();

	invTranslationMatrix.mMatrix[0][3] = -trans.mPosX;
	invTranslationMatrix.mMatrix[1][3] = -trans.mPosY;
	invTranslationMatrix.mMatrix[2][3] = -trans.mPosZ;

	mInvMatrix = mInvMatrix * invTranslationMatrix;

}

void Instance::Translate(const double dx, const double dy, const double dz)
{
	Matrix invTranslationMatrix;
	invTranslationMatrix.SetIdentity();

	invTranslationMatrix.mMatrix[0][3] = -dx;
	invTranslationMatrix.mMatrix[1][3] = -dy;
	invTranslationMatrix.mMatrix[2][3] = -dz;

	mInvMatrix = mInvMatrix * invTranslationMatrix;

}

void Instance::Scale(const Vector3D& s)
{
	Matrix invScaleMatrix;
	invScaleMatrix.SetIdentity();

	invScaleMatrix.mMatrix[0][0] = 1.0 / s.mPosX;
	invScaleMatrix.mMatrix[1][1] = 1.0 / s.mPosY;
	invScaleMatrix.mMatrix[2][2] = 1.0 / s.mPosZ;

	mInvMatrix = mInvMatrix * invScaleMatrix;
}

void Instance::Scale(const double a, const double b, const double c)
{
	Matrix invScaleMatrix;
	invScaleMatrix.SetIdentity();

	invScaleMatrix.mMatrix[0][0] = 1.0 / a;
	invScaleMatrix.mMatrix[1][1] = 1.0 / b;
	invScaleMatrix.mMatrix[2][2] = 1.0 / c;

	mInvMatrix = mInvMatrix * invScaleMatrix;
}

void Instance::RotateX(const double r)
{
	double sin_theta = std::sin(r * PI_ON_180);
	double cos_theta = std::cos(r * PI_ON_180);

	Matrix inv_rotation_matrix;
	inv_rotation_matrix.SetIdentity();

	inv_rotation_matrix.mMatrix[1][1] = cos_theta;
	inv_rotation_matrix.mMatrix[1][2] = sin_theta;
	inv_rotation_matrix.mMatrix[2][1] = -sin_theta;
	inv_rotation_matrix.mMatrix[2][2] = cos_theta;

	mInvMatrix = mInvMatrix * inv_rotation_matrix;
}

void Instance::RotateY(const double r)
{
	double sin_theta = std::sin(r * PI_ON_180);
	double cos_theta = std::cos(r * PI_ON_180);

	Matrix inv_rotation_matrix;
	inv_rotation_matrix.SetIdentity();

	inv_rotation_matrix.mMatrix[0][0] = cos_theta;
	inv_rotation_matrix.mMatrix[0][2] = -sin_theta;
	inv_rotation_matrix.mMatrix[2][0] = sin_theta;
	inv_rotation_matrix.mMatrix[2][2] = cos_theta;

	mInvMatrix = mInvMatrix * inv_rotation_matrix;
}

void Instance::RotateZ(const double r)
{

	double sin_theta = std::sin(r * PI_ON_180);
	double cos_theta = std::cos(r * PI_ON_180);

	Matrix inv_rotation_matrix;
	inv_rotation_matrix.SetIdentity();

	inv_rotation_matrix.mMatrix[0][0] = cos_theta;
	inv_rotation_matrix.mMatrix[0][1] = sin_theta;
	inv_rotation_matrix.mMatrix[1][0] = -sin_theta;
	inv_rotation_matrix.mMatrix[1][1] = cos_theta;

	mInvMatrix = mInvMatrix * inv_rotation_matrix;
}
