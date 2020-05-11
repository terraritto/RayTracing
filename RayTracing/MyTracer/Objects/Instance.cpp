#include "Instance.h"

Matrix Instance::mForwardMatrix;

Instance::Instance()
	: GeometricObject()
	, mObjectPtr(nullptr)
	, mInvMatrix()
	, mTransformTheTexture(true)
{
	mInvMatrix.SetIdentity();
	mForwardMatrix.SetIdentity();
}

Instance::Instance(std::shared_ptr<GeometricObject> obj_ptr)
	: GeometricObject()
	, mObjectPtr(obj_ptr)
	, mInvMatrix()
	, mTransformTheTexture(true)
{
	mInvMatrix.SetIdentity();
	mForwardMatrix.SetIdentity();
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

void Instance::ComputeBoundingBox()
{
	//first get the untransformed box
	BBox object_bbox = mObjectPtr->GetBoundingBox();

	//construct 8 vertices as 3D points
	std::array<Point3D, 8> vertices;

	vertices[0].mPosX = object_bbox.mP0.mPosX;
	vertices[0].mPosY = object_bbox.mP0.mPosY;
	vertices[0].mPosZ = object_bbox.mP0.mPosZ;
	vertices[1].mPosX = object_bbox.mP1.mPosX;
	vertices[1].mPosY = object_bbox.mP0.mPosY;
	vertices[1].mPosZ = object_bbox.mP0.mPosZ;
	vertices[2].mPosX = object_bbox.mP1.mPosX;
	vertices[2].mPosY = object_bbox.mP1.mPosY;
	vertices[2].mPosZ = object_bbox.mP0.mPosZ;
	vertices[3].mPosX = object_bbox.mP0.mPosX;
	vertices[3].mPosY = object_bbox.mP1.mPosY;
	vertices[3].mPosZ = object_bbox.mP0.mPosZ;

	vertices[4].mPosX = object_bbox.mP0.mPosX;
	vertices[4].mPosY = object_bbox.mP0.mPosY;
	vertices[4].mPosZ = object_bbox.mP1.mPosZ;
	vertices[5].mPosX = object_bbox.mP1.mPosX;
	vertices[5].mPosY = object_bbox.mP0.mPosY;
	vertices[5].mPosZ = object_bbox.mP1.mPosZ;
	vertices[6].mPosX = object_bbox.mP1.mPosX;
	vertices[6].mPosY = object_bbox.mP1.mPosY;
	vertices[6].mPosZ = object_bbox.mP1.mPosZ;
	vertices[7].mPosX = object_bbox.mP0.mPosX;
	vertices[7].mPosY = object_bbox.mP1.mPosY;
	vertices[7].mPosZ = object_bbox.mP1.mPosZ;

	//transform vertices

	vertices[0] = mForwardMatrix * vertices[0];
	vertices[1] = mForwardMatrix * vertices[1];
	vertices[2] = mForwardMatrix * vertices[2];
	vertices[3] = mForwardMatrix * vertices[3];
	vertices[4] = mForwardMatrix * vertices[4];
	vertices[5] = mForwardMatrix * vertices[5];
	vertices[6] = mForwardMatrix * vertices[6];
	vertices[7] = mForwardMatrix * vertices[7];

	// init forward matrix
	mForwardMatrix.SetIdentity();

	// copute minimum values
	double x0 = kHugeValue;
	double y0 = kHugeValue;
	double z0 = kHugeValue;
	double x1 = -kHugeValue;
	double y1 = -kHugeValue;
	double z1 = -kHugeValue;

	auto compareValueMin = [](auto pos, auto v) { return pos < v ? pos : v; };
	auto compareValueMax = [](auto pos, auto v) { return pos > v ? pos : v; };

	for (auto& value : vertices)
	{
		x0 = compareValueMin(value.mPosX, x0);
		y0 = compareValueMin(value.mPosY, y0);
		z0 = compareValueMin(value.mPosZ, z0);
		x1 = compareValueMax(value.mPosX, x1);
		y1 = compareValueMax(value.mPosY, y1);
		z1 = compareValueMax(value.mPosZ, z1);
	}

	mBbox.mP0.mPosX = x0;
	mBbox.mP0.mPosY = y0;
	mBbox.mP0.mPosZ = z0;
	mBbox.mP1.mPosX = x1;
	mBbox.mP1.mPosY = y1;
	mBbox.mP1.mPosZ = z1;
}

BBox Instance::GetBoundingBox() const
{
	return mBbox;
}

void Instance::Translate(const Vector3D& trans)
{
	Matrix invTranslationMatrix;
	invTranslationMatrix.SetIdentity();

	invTranslationMatrix.mMatrix[0][3] = -trans.mPosX;
	invTranslationMatrix.mMatrix[1][3] = -trans.mPosY;
	invTranslationMatrix.mMatrix[2][3] = -trans.mPosZ;

	mInvMatrix = mInvMatrix * invTranslationMatrix;

	Matrix translationMatrix;
	translationMatrix.SetIdentity();

	translationMatrix.mMatrix[0][3] = trans.mPosX;
	translationMatrix.mMatrix[1][3] = trans.mPosY;
	translationMatrix.mMatrix[2][3] = trans.mPosZ;

	mForwardMatrix = translationMatrix * mForwardMatrix;
}

void Instance::Translate(const double dx, const double dy, const double dz)
{
	Matrix invTranslationMatrix;
	invTranslationMatrix.SetIdentity();

	invTranslationMatrix.mMatrix[0][3] = -dx;
	invTranslationMatrix.mMatrix[1][3] = -dy;
	invTranslationMatrix.mMatrix[2][3] = -dz;

	mInvMatrix = mInvMatrix * invTranslationMatrix;

	Matrix translationMatrix;
	translationMatrix.SetIdentity();

	translationMatrix.mMatrix[0][3] = dx;
	translationMatrix.mMatrix[1][3] = dy;
	translationMatrix.mMatrix[2][3] = dz;

	mForwardMatrix = translationMatrix * mForwardMatrix;

}

void Instance::Scale(const Vector3D& s)
{
	Matrix invScaleMatrix;
	invScaleMatrix.SetIdentity();

	invScaleMatrix.mMatrix[0][0] = 1.0 / s.mPosX;
	invScaleMatrix.mMatrix[1][1] = 1.0 / s.mPosY;
	invScaleMatrix.mMatrix[2][2] = 1.0 / s.mPosZ;

	mInvMatrix = mInvMatrix * invScaleMatrix;

	Matrix scaleMatrix;
	scaleMatrix.SetIdentity();

	scaleMatrix.mMatrix[0][0] = s.mPosX;
	scaleMatrix.mMatrix[1][1] = s.mPosY;
	scaleMatrix.mMatrix[2][2] = s.mPosZ;

	mForwardMatrix = scaleMatrix * mForwardMatrix;
}

void Instance::Scale(const double a, const double b, const double c)
{
	Matrix invScaleMatrix;
	invScaleMatrix.SetIdentity();

	invScaleMatrix.mMatrix[0][0] = 1.0 / a;
	invScaleMatrix.mMatrix[1][1] = 1.0 / b;
	invScaleMatrix.mMatrix[2][2] = 1.0 / c;

	mInvMatrix = mInvMatrix * invScaleMatrix;

	Matrix scaleMatrix;
	scaleMatrix.SetIdentity();

	scaleMatrix.mMatrix[0][0] = a;
	scaleMatrix.mMatrix[1][1] = b;
	scaleMatrix.mMatrix[2][2] = c;

	mForwardMatrix = scaleMatrix * mForwardMatrix;
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

	Matrix rotationMatrix;
	rotationMatrix.SetIdentity();

	rotationMatrix.mMatrix[1][1] = cos_theta;
	rotationMatrix.mMatrix[1][2] = -sin_theta;
	rotationMatrix.mMatrix[2][1] = sin_theta;
	rotationMatrix.mMatrix[2][2] = cos_theta;

	mForwardMatrix = rotationMatrix * mForwardMatrix;
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

	Matrix rotationMatrix;
	rotationMatrix.SetIdentity();

	rotationMatrix.mMatrix[0][0] = cos_theta;
	rotationMatrix.mMatrix[0][2] = sin_theta;
	rotationMatrix.mMatrix[2][0] = -sin_theta;
	rotationMatrix.mMatrix[2][2] = cos_theta;

	mForwardMatrix = rotationMatrix * mForwardMatrix;

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

	Matrix rotationMatrix;
	rotationMatrix.SetIdentity();

	rotationMatrix.mMatrix[0][0] = cos_theta;
	rotationMatrix.mMatrix[0][1] = -sin_theta;
	rotationMatrix.mMatrix[1][0] = sin_theta;
	rotationMatrix.mMatrix[1][1] = cos_theta;

	mForwardMatrix = rotationMatrix * mForwardMatrix;
}
