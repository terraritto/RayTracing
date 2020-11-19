#include "Grid.h"
#include "Triangle.h"
#include "SmoothTriangle.h"

//triangle
#include "FlatMeshTriangle.h"
#include "FlatUVMeshTriangle.h"
#include "SmoothMeshTriangle.h"
#include "SmoothUVMeshTriangle.h"

//ply
#include "../../Additional_Code/ReadPLY.h"

//texture
#include "../Texture/ImageTexture.h"
#include "../Texture//AlphaImageTexture.h"

//material
#include "../Material/Matte.h"
#include "../Material/SV_Matte.h"
#include "../Material/MMD_Matte.h"
#include "../Material/MMD_Dielectric.h"

#include "DxLib.h"

#include <unordered_map>

Grid::Grid()
	: Compound()
	, mNx(0), mNy(0), mNz(0)
	, mMesh(std::make_shared<Mesh>())
	, mReverseNormal(false)
{
}

Grid::Grid(const Grid& rg)
	: Compound(rg)
	, mNx(rg.mNx), mNy(rg.mNy), mNz(rg.mNz)
	, mBBox(rg.mBBox)
	, mMesh(rg.mMesh) // maybe change
	, mReverseNormal(rg.mReverseNormal)
{
}

Grid::~Grid()
{
}

Grid& Grid::operator=(const Grid& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Compound::operator=(rhs);

	mNx = rhs.mNx;
	mNy = rhs.mNy;
	mNz = rhs.mNz;
	mBBox = rhs.mBBox;
	mMesh = rhs.mMesh; //maybe change
	mReverseNormal = rhs.mReverseNormal;

	return *this;
}

std::shared_ptr<Grid> Grid::Clone()
{
	return std::make_shared<Grid>(*this);
}

BBox Grid::GetBoundingBox() const
{
	return mBBox;
}

void Grid::TessellateFlatSphere(const int horizontalSteps, const int verticalSteps)
{
	// define the top triangles which all touch the north pole
	int k = 1;

	for (int j = 0; j <= horizontalSteps - 1; j++)
	{
		//define vertices
		Point3D v0(0, 1, 0);
		Point3D v1(
			std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps),
			std::cos(PI * k / verticalSteps),
			std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps)
		);
		Point3D v2(
			std::sin(2.0 * PI * (j+1) / horizontalSteps) * std::sin(PI * k / verticalSteps),
			std::cos(PI * k / verticalSteps),
			std::cos(2.0 * PI * (j+1) / horizontalSteps) * std::sin(PI * k / verticalSteps)
		);

		std::shared_ptr<Triangle> triangle_ptr = std::make_shared<Triangle>(v0, v1, v2);
		mObjects.push_back(triangle_ptr);
	}

	// define the buttom triangles which all touch the south pole
	k = verticalSteps - 1;
	for (int j = 0; j <= horizontalSteps - 1; j++)
	{
		//define vertices
		Point3D v0(
			std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps),
			std::cos(PI * k / verticalSteps),
			std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps)
		);
		Point3D v1(0, -1, 0);

		Point3D v2(
			std::sin(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * k / verticalSteps),
			std::cos(PI * k / verticalSteps),
			std::cos(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * k / verticalSteps)
		);

		std::shared_ptr<Triangle> triangle_ptr = std::make_shared<Triangle>(v0, v1, v2);
		mObjects.push_back(triangle_ptr);
	}

	//define the other triangles

	for (int k = 1; k <= verticalSteps - 2; k++)
	{
		for (int j = 0; j <= horizontalSteps - 1; j++)
		{
			//define the first triangle
			Point3D v0(
				std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * (k+1) / verticalSteps),
				std::cos(PI * (k+1) / verticalSteps),
				std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * (k+1) / verticalSteps)
			);
			Point3D v1(
				std::sin(2.0 * PI * (j+1) / horizontalSteps) * std::sin(PI * (k + 1) / verticalSteps),
				std::cos(PI * (k + 1) / verticalSteps),
				std::cos(2.0 * PI * (j+1) / horizontalSteps) * std::sin(PI * (k + 1) / verticalSteps)
			);

			Point3D v2(
				std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps),
				std::cos(PI * k / verticalSteps),
				std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps)
			);

			std::shared_ptr<Triangle> triangle_ptr1 = std::make_shared<Triangle>(v0, v1, v2);
			mObjects.push_back(triangle_ptr1);

			//define the second triangle
			v0 = Point3D(
				std::sin(2.0 * PI * (j+1) / horizontalSteps) * std::sin(PI * k / verticalSteps),
				std::cos(PI * k / verticalSteps),
				std::cos(2.0 * PI * (j+1) / horizontalSteps) * std::sin(PI * k / verticalSteps)
			);
			v1 = Point3D(
				std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps),
				std::cos(PI * k / verticalSteps),
				std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps)
			);

			v2 = Point3D(
				std::sin(2.0 * PI * (j+1) / horizontalSteps) * std::sin(PI * (k+1) / verticalSteps),
				std::cos(PI * (k+1) / verticalSteps),
				std::cos(2.0 * PI * (j+1) / horizontalSteps) * std::sin(PI * (k+1) / verticalSteps)
			);

			std::shared_ptr<Triangle> triangle_ptr2 = std::make_shared<Triangle>(v0, v1, v2);
			mObjects.push_back(triangle_ptr2);

		}
	}
}

void Grid::TessellateSmoothSphere(const int horizontalSteps, const int verticalSteps)
{
	// define the top triangles which all touch the north pole
	int k = 1;

	for (int j = 0; j <= horizontalSteps - 1; j++)
	{
		//define vertices
		Point3D v0(0, 1, 0);
		Point3D v1(
			std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps),
			std::cos(PI * k / verticalSteps),
			std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps)
		);
		Point3D v2(
			std::sin(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * k / verticalSteps),
			std::cos(PI * k / verticalSteps),
			std::cos(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * k / verticalSteps)
		);

		std::shared_ptr<SmoothTriangle> triangle_ptr = std::make_shared<SmoothTriangle>(v0, v1, v2);
		triangle_ptr->mN0 = v0;
		triangle_ptr->mN1 = v1;
		triangle_ptr->mN2 = v2;
		mObjects.push_back(triangle_ptr);
	}

	// define the buttom triangles which all touch the south pole
	k = verticalSteps - 1;
	for (int j = 0; j <= horizontalSteps - 1; j++)
	{
		//define vertices
		Point3D v0(
			std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps),
			std::cos(PI * k / verticalSteps),
			std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps)
		);
		Point3D v1(0, -1, 0);

		Point3D v2(
			std::sin(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * k / verticalSteps),
			std::cos(PI * k / verticalSteps),
			std::cos(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * k / verticalSteps)
		);

		std::shared_ptr<SmoothTriangle> triangle_ptr = std::make_shared<SmoothTriangle>(v0, v1, v2);
		triangle_ptr->mN0 = v0;
		triangle_ptr->mN1 = v1;
		triangle_ptr->mN2 = v2;
		mObjects.push_back(triangle_ptr);
	}

	//define the other triangles

	for (int k = 1; k <= verticalSteps - 2; k++)
	{
		for (int j = 0; j <= horizontalSteps - 1; j++)
		{
			//define the first triangle
			Point3D v0(
				std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * (k + 1) / verticalSteps),
				std::cos(PI * (k + 1) / verticalSteps),
				std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * (k + 1) / verticalSteps)
			);
			Point3D v1(
				std::sin(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * (k + 1) / verticalSteps),
				std::cos(PI * (k + 1) / verticalSteps),
				std::cos(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * (k + 1) / verticalSteps)
			);

			Point3D v2(
				std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps),
				std::cos(PI * k / verticalSteps),
				std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps)
			);

			std::shared_ptr<SmoothTriangle> triangle_ptr1 = std::make_shared<SmoothTriangle>(v0, v1, v2);
			triangle_ptr1->mN0 = v0;
			triangle_ptr1->mN1 = v1;
			triangle_ptr1->mN2 = v2;
			mObjects.push_back(triangle_ptr1);

			//define the second triangle
			v0 = Point3D(
				std::sin(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * k / verticalSteps),
				std::cos(PI * k / verticalSteps),
				std::cos(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * k / verticalSteps)
			);
			v1 = Point3D(
				std::sin(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps),
				std::cos(PI * k / verticalSteps),
				std::cos(2.0 * PI * j / horizontalSteps) * std::sin(PI * k / verticalSteps)
			);

			v2 = Point3D(
				std::sin(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * (k + 1) / verticalSteps),
				std::cos(PI * (k + 1) / verticalSteps),
				std::cos(2.0 * PI * (j + 1) / horizontalSteps) * std::sin(PI * (k + 1) / verticalSteps)
			);

			std::shared_ptr<SmoothTriangle> triangle_ptr2 = std::make_shared<SmoothTriangle>(v0, v1, v2);
			triangle_ptr2->mN0 = v0;
			triangle_ptr2->mN1 = v1;
			triangle_ptr2->mN2 = v2;
			mObjects.push_back(triangle_ptr2);
		}
	}
}

void Grid::ReadTriangles(std::string fileName, ETriangleType type)
{
	ReadPlyFile(fileName, type);
}

void Grid::ReadNormTriangles(std::string fileName, ETriangleType type)
{
	ReadNormPlyFile(fileName, type);
}

void Grid::ReadUVTriangles(std::string fileName, ETriangleType type)
{
	ReadUVPlyFile(fileName, type);
}

void Grid::SetupCells()
{
	Point3D p0 = MinCoordinates();
	Point3D p1 = MaxCoordinates();

	mBBox.mP0 = p0;
	mBBox.mP1 = p1;

	//dimensions of the grid in the x,y, and z directions
	double wx = p1.mPosX - p0.mPosX;
	double wy = p1.mPosY - p0.mPosY;
	double wz = p1.mPosZ - p0.mPosZ;

	//multiplayer scales
	double multiplier = 2.0;

	double s = std::pow(wx * wy * wz / mObjects.size(), 1.0/3.0);
	
	mNx = multiplier * wx / s + 1;
	mNy = multiplier * wy / s + 1;
	mNz = multiplier * wz / s + 1;

	//set up the array of cells
	mCells.resize(mNx * mNy * mNz, nullptr);

	//set up a temorary array for counting object
	std::vector<int> counts;
	counts.resize(mNx * mNy * mNz, 0);

	// put the objects into the cells
	BBox obj_bbox; //objects bounding box
	int index;
	for (auto& obj : mObjects)
	{
		obj_bbox = obj->GetBoundingBox();

		//compute the cell indices
		int ixMin = std::clamp((obj_bbox.mP0.mPosX - p0.mPosX) * mNx / (p1.mPosX - p0.mPosX), 0.0, mNx - 1.0);
		int iyMin = std::clamp((obj_bbox.mP0.mPosY - p0.mPosY) * mNy / (p1.mPosY - p0.mPosY), 0.0, mNy - 1.0);
		int izMin = std::clamp((obj_bbox.mP0.mPosZ - p0.mPosZ) * mNz / (p1.mPosZ - p0.mPosZ), 0.0, mNz - 1.0);
		int ixMax = std::clamp((obj_bbox.mP1.mPosX - p0.mPosX) * mNx / (p1.mPosX - p0.mPosX), 0.0, mNx - 1.0);
		int iyMax = std::clamp((obj_bbox.mP1.mPosY - p0.mPosY) * mNy / (p1.mPosY - p0.mPosY), 0.0, mNy - 1.0);
		int izMax = std::clamp((obj_bbox.mP1.mPosZ - p0.mPosZ) * mNz / (p1.mPosZ - p0.mPosZ), 0.0, mNz - 1.0);

		// add the object to the cells
		for (int iz = izMin; iz <= izMax; iz++)
		{
			for (int iy = iyMin; iy <= iyMax; iy++)
			{
				for (int ix = ixMin; ix <= ixMax; ix++)
				{
					index = ix + mNx * iy + mNx * mNy * iz;

					if (counts[index] == 0)
					{
						mCells[index] = obj;
						counts[index] += 1;
					}
					else
					{
						if (counts[index] == 1)
						{
							std::shared_ptr<Compound> compound_ptr = std::make_shared<Compound>();
							compound_ptr->AddObject(mCells[index]);
							compound_ptr->AddObject(obj);
							mCells[index] = compound_ptr;
							counts[index] += 1;
						}
						else
						{
							mCells[index]->AddObject(obj);
							counts[index] += 1;
						}
					}
				}
			}
		}
	}
	// erase Compound::Objects
	mObjects.erase(mObjects.begin(), mObjects.end());

	//erase count
	counts.erase(counts.begin(), counts.end());
}

bool Grid::hit(const Ray& ray, double& t, ShadeRec& s)
{
	//for alpha shadow about mesh
	mShadowSr = std::make_shared<ShadeRec>(s);


	double ox = ray.mOrigin.mPosX;
	double oy = ray.mOrigin.mPosY;
	double oz = ray.mOrigin.mPosZ;
	double dx = ray.mDirection.mPosX;
	double dy = ray.mDirection.mPosY;
	double dz = ray.mDirection.mPosZ;

	double x0 = mBBox.mP0.mPosX;
	double y0 = mBBox.mP0.mPosY;
	double z0 = mBBox.mP0.mPosZ;
	double x1 = mBBox.mP1.mPosX;
	double y1 = mBBox.mP1.mPosY;
	double z1 = mBBox.mP1.mPosZ;

	//BBox hit function can't return t value
	//so we define here.
	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0)
	{
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else
	{
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else
	{
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0)
	{
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else
	{
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;
	if (tx_min > ty_min)
	{
		t0 = tx_min;
	}
	else
	{
		t0 = ty_min;
	}

	if (tz_min > t0)
	{
		t0 = tz_min;
	}

	if (tx_max < ty_max)
	{
		t1 = tx_max;
	}
	else
	{
		t1 = ty_max;
	}

	if (tz_max < t1)
	{
		t1 = tz_max;
	}

	if (t0 > t1)
	{
		return false;
	}

	//initial cell coordinates
	int ix, iy, iz;
	int i = 0;
	if (mBBox.Inside(ray.mOrigin))
	{
		//inside
		ix = std::clamp((ox - x0) * mNx / (x1 - x0), 0.0, mNx - 1.0);
		iy = std::clamp((oy - y0) * mNy / (y1 - y0), 0.0, mNy - 1.0);
		iz = std::clamp((oz - z0) * mNz / (z1 - z0), 0.0, mNz - 1.0);
		i = 1;
	}
	else
	{
		//outside
		if (isnan(t0))
		{
			// I don't know why nan is stored.
			return false;
		}
		Point3D p = ray.mOrigin + t0 * ray.mDirection;
		ix = std::clamp((p.mPosX - x0) * mNx / (x1 - x0), 0.0, mNx - 1.0);
		iy = std::clamp((p.mPosY - y0) * mNy / (y1 - y0), 0.0, mNy - 1.0);
		iz = std::clamp((p.mPosZ - z0) * mNz / (z1 - z0), 0.0, mNz - 1.0);
		i = 2;
	}

	//ray parameter per cell in x,y,z dir
	double dtx = (tx_max - tx_min) / mNx;
	double dty = (ty_max - ty_min) / mNy;
	double dtz = (tz_max - tz_min) / mNz;

	double tx_next, ty_next, tz_next;
	int ix_step, iy_step, iz_step;
	int ix_stop, iy_stop, iz_stop;

	if (dx > 0)
	{
		tx_next = tx_min + (ix + 1) * dtx;
		ix_step = 1;
		ix_stop = mNx;
	}
	else
	{
		tx_next = tx_min + (mNx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}
	
	if (dx == 0.0)
	{
		tx_next = kHugeValue;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dy > 0)
	{
		ty_next = ty_min + (iy + 1) * dty;
		iy_step = 1;
		iy_stop = mNy;
	}
	else
	{
		ty_next = ty_min + (mNy - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dy == 0.0)
	{
		ty_next = kHugeValue;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dz > 0)
	{
		tz_next = tz_min + (iz + 1) * dtz;
		iz_step = 1;
		iz_stop = mNz;
	}
	else
	{
		tz_next = tz_min + (mNz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}

	if (dz == 0.0)
	{
		tz_next = kHugeValue;
		iz_step = -1;
		iz_stop = -1;
	}

	while (true)
	{
		std::shared_ptr<GeometricObject> object_ptr = mCells[ix + mNx * iy + mNx * mNy * iz];

		if (tx_next < ty_next && tx_next < tz_next)
		{
			if (object_ptr && object_ptr->hit(ray, t, s) 
				&& t < tx_next)
			{
				mMaterial = object_ptr->GetMaterial();
				return true;
			}

			tx_next += dtx;
			ix += ix_step;
			if (ix == ix_stop)
			{
				return false;
			}
		}
		else
		{
			if (ty_next < tz_next)
			{
				if (object_ptr && object_ptr->hit(ray, t, s) 
					&& t < ty_next)
				{
					mMaterial = object_ptr->GetMaterial();
					return true;
				}

				ty_next += dty;
				iy += iy_step;

				if (iy == iy_stop)
				{
					return false;
				}
			}
			else
			{
				if (object_ptr && object_ptr->hit(ray, t, s)
					&& t < tz_next)
				{
					mMaterial = object_ptr->GetMaterial();
					return true;
				}

				tz_next += dtz;
				iz += iz_step;

				if (iz == iz_stop)
				{
					return false;
				}
			}
		}
	}
}

bool Grid::Shadow_hit(const Ray& ray, float& t) const
{
	if (!mIsShadow)
	{
		return false;
	}

	double ox = ray.mOrigin.mPosX;
	double oy = ray.mOrigin.mPosY;
	double oz = ray.mOrigin.mPosZ;
	double dx = ray.mDirection.mPosX;
	double dy = ray.mDirection.mPosY;
	double dz = ray.mDirection.mPosZ;

	double x0 = mBBox.mP0.mPosX;
	double y0 = mBBox.mP0.mPosY;
	double z0 = mBBox.mP0.mPosZ;
	double x1 = mBBox.mP1.mPosX;
	double y1 = mBBox.mP1.mPosY;
	double z1 = mBBox.mP1.mPosZ;

	//BBox hit function can't return t value
	//so we define here.
	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0)
	{
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else
	{
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else
	{
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0)
	{
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else
	{
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;
	if (tx_min > ty_min)
	{
		t0 = tx_min;
	}
	else
	{
		t0 = ty_min;
	}

	if (tz_min > t0)
	{
		t0 = tz_min;
	}

	if (tx_max < ty_max)
	{
		t1 = tx_max;
	}
	else
	{
		t1 = ty_max;
	}

	if (tz_max < t1)
	{
		t1 = tz_max;
	}

	if (t0 > t1)
	{
		return false;
	}

	//initial cell coordinates
	int ix, iy, iz;

	if (mBBox.Inside(ray.mOrigin))
	{
		//inside
		ix = std::clamp((ox - x0) * mNx / (x1 - x0), 0.0, mNx - 1.0);
		iy = std::clamp((oy - y0) * mNy / (y1 - y0), 0.0, mNy - 1.0);
		iz = std::clamp((oz - z0) * mNz / (z1 - z0), 0.0, mNz - 1.0);
	}
	else
	{
		//outside
		Point3D p = ray.mOrigin + t0 * ray.mDirection;
		ix = std::clamp((p.mPosX - x0) * mNx / (x1 - x0), 0.0, mNx - 1.0);
		iy = std::clamp((p.mPosY - y0) * mNy / (y1 - y0), 0.0, mNy - 1.0);
		iz = std::clamp((p.mPosZ - z0) * mNz / (z1 - z0), 0.0, mNz - 1.0);
	}

	//ray parameter per cell in x,y,z dir
	double dtx = (tx_max - tx_min) / mNx;
	double dty = (ty_max - ty_min) / mNy;
	double dtz = (tz_max - tz_min) / mNz;

	double tx_next, ty_next, tz_next;
	int ix_step, iy_step, iz_step;
	int ix_stop, iy_stop, iz_stop;

	if (dx > 0)
	{
		tx_next = tx_min + (ix + 1) * dtx;
		ix_step = 1;
		ix_stop = mNx;
	}
	else
	{
		tx_next = tx_min + (mNx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dx == 0.0)
	{
		tx_next = kHugeValue;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dy > 0)
	{
		ty_next = ty_min + (iy + 1) * dty;
		iy_step = 1;
		iy_stop = mNy;
	}
	else
	{
		ty_next = ty_min + (mNy - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dy == 0.0)
	{
		ty_next = kHugeValue;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dz > 0)
	{
		tz_next = tz_min + (iz + 1) * dtz;
		iz_step = 1;
		iz_stop = mNz;
	}
	else
	{
		tz_next = tz_min + (mNz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}

	if (dz == 0.0)
	{
		tz_next = kHugeValue;
		iz_step = -1;
		iz_stop = -1;
	}

	while (true)
	{
		std::shared_ptr<GeometricObject> object_ptr = mCells[ix + mNx * iy + mNx * mNy * iz];

		if (tx_next < ty_next && tx_next < tz_next)
		{
			if (object_ptr && object_ptr->Shadow_hit(ray, t) && t < tx_next)
			{
				return true;
			}

			tx_next += dtx;
			ix += ix_step;
			if (ix == ix_stop)
			{
				return false;
			}
		}
		else
		{
			if (ty_next < tz_next)
			{
				if (object_ptr && object_ptr->Shadow_hit(ray, t) && t < ty_next)
				{
					return true;
				}

				ty_next += dty;
				iy += iy_step;

				if (iy == iy_stop)
				{
					return false;
				}
			}
			else
			{
				if (object_ptr && object_ptr->Shadow_hit(ray, t) && t < tz_next)
				{
					return true;
				}

				tz_next += dtz;
				iz += iz_step;

				if (iz == iz_stop)
				{
					return false;
				}
			}
		}
	}
}

Point3D Grid::MinCoordinates()
{
	BBox box;
	Point3D p0(kHugeValue);

	for (auto& obj : mObjects)
	{
		box = obj->GetBoundingBox();

		if (box.mP0.mPosX < p0.mPosX)
		{
			p0.mPosX = box.mP0.mPosX;
		}

		if (box.mP0.mPosY < p0.mPosY)
		{
			p0.mPosY = box.mP0.mPosY;
		}

		if (box.mP0.mPosZ < p0.mPosZ)
		{
			p0.mPosZ = box.mP0.mPosZ;
		}
	}

	p0.mPosX -= kEpsilon;
	p0.mPosY -= kEpsilon;
	p0.mPosZ -= kEpsilon;

	return p0;
}

Point3D Grid::MaxCoordinates()
{
	BBox box;
	Point3D p1(-kHugeValue);

	for (auto& obj : mObjects)
	{
		box = obj->GetBoundingBox();

		if (box.mP1.mPosX > p1.mPosX)
		{
			p1.mPosX = box.mP1.mPosX;
		}

		if (box.mP1.mPosY > p1.mPosY)
		{
			p1.mPosY = box.mP1.mPosY;
		}

		if (box.mP1.mPosZ > p1.mPosZ)
		{
			p1.mPosZ = box.mP1.mPosZ;
		}
	}

	p1.mPosX += kEpsilon;
	p1.mPosY += kEpsilon;
	p1.mPosZ += kEpsilon;

	return p1;
}

void Grid::ReadPlyFile(std::string fileName, ETriangleType type)
{
	//read file
	happly::PLYData plyIn(fileName);

	// exception
	try
	{
		plyIn.validate();
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}

	//---objects---
	//vertex
	const std::vector<float> vertex_x = plyIn.getElement("vertex").getProperty<float>("x");
	const std::vector<float> vertex_y = plyIn.getElement("vertex").getProperty<float>("y");
	const std::vector<float> vertex_z = plyIn.getElement("vertex").getProperty<float>("z");
	
	//face
	std::vector<std::vector<int>> face = plyIn.getElement("face").getListProperty<int>("vertex_indices");

	// num
	int vertexNum = vertex_x.size();
	int faceNum = face.size();
	//---------

	//---set---
	// objects
	mObjects.reserve(faceNum);
	//vertex
	for (int i = 0; i < vertexNum; i++)
	{
		Point3D p(vertex_x[i], vertex_y[i], vertex_z[i]);
		mMesh->mVertices.push_back(p);
	}

	mMesh->mNumVertices = vertexNum;
	mMesh->mNumTriangles = faceNum;

	// face
	mMesh->mVertexFaces.resize(vertexNum); // vertex size
	//---------

	//--- make triangle ---
	if (type == ETriangleType::flat)
	{
		for (auto& f : face) {
			std::shared_ptr<FlatMeshTriangle> triangle_ptr = std::make_shared<FlatMeshTriangle>(mMesh, f[0], f[1], f[2]);
			triangle_ptr->ComputeNormal(mReverseNormal);
			mObjects.push_back(triangle_ptr);
		}

		mMesh->mVertexFaces.erase(mMesh->mVertexFaces.begin(), mMesh->mVertexFaces.end());
	}

	if (type == ETriangleType::smooth)
	{
		int count = 0; //number of feces
		for (auto& f : face)
		{
			std::shared_ptr<SmoothMeshTriangle> triangle_ptr = std::make_shared<SmoothMeshTriangle>(mMesh, f[0], f[1], f[2]);
			triangle_ptr->ComputeNormal(mReverseNormal);
			mObjects.push_back(triangle_ptr);

			mMesh->mVertexFaces[f[0]].push_back(count);
			mMesh->mVertexFaces[f[1]].push_back(count);
			mMesh->mVertexFaces[f[2]].push_back(count);
			count++;
			

			//for rectangle
			if (f.size() == 4) {
				std::shared_ptr<SmoothMeshTriangle> triangle_ptr2 = std::make_shared<SmoothMeshTriangle>(mMesh, f[0], f[2], f[3]);
				triangle_ptr2->ComputeNormal(mReverseNormal);
				mObjects.push_back(triangle_ptr2);

				mMesh->mVertexFaces[f[3]].push_back(count);
				mMesh->mVertexFaces[f[2]].push_back(count);
				mMesh->mVertexFaces[f[0]].push_back(count);
				count++;
			}
			
			
		}
		ComputeMeshNormals();
	}
	//---------------------
}

void Grid::ReadNormPlyFile(std::string fileName, ETriangleType type)
{
	//read file
	happly::PLYData plyIn(fileName);

	// exception
	try
	{
		plyIn.validate();
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}

	//---objects---
	//vertex
	const std::vector<float> vertex_x = plyIn.getElement("vertex").getProperty<float>("x");
	const std::vector<float> vertex_y = plyIn.getElement("vertex").getProperty<float>("y");
	const std::vector<float> vertex_z = plyIn.getElement("vertex").getProperty<float>("z");
	const std::vector<float> norm_x = plyIn.getElement("vertex").getProperty<float>("nx");
	const std::vector<float> norm_y = plyIn.getElement("vertex").getProperty<float>("ny");
	const std::vector<float> norm_z = plyIn.getElement("vertex").getProperty<float>("nz");


	//face
	std::vector<std::vector<int>> face = plyIn.getElement("face").getListProperty<int>("vertex_indices");

	// num
	int vertexNum = vertex_x.size();
	int faceNum = face.size();
	//---------

	//---set---
	// objects
	mObjects.reserve(faceNum);
	//vertex
	for (int i = 0; i < vertexNum; i++)
	{
		Point3D p(vertex_x[i], vertex_y[i], vertex_z[i]);
		mMesh->mVertices.push_back(p);
	}

	mMesh->mNumVertices = vertexNum;
	mMesh->mNumTriangles = faceNum;

	// face
	mMesh->mVertexFaces.resize(vertexNum); // vertex size
	//---------

	//--- make triangle ---
	if (type == ETriangleType::flat)
	{
		for (auto& f : face) {
			std::shared_ptr<FlatMeshTriangle> triangle_ptr = std::make_shared<FlatMeshTriangle>(mMesh, f[0], f[1], f[2]);
			/*
			Normal sumNorm;

			for (int i = 0; i < 3; i++)
			{

				Normal p(
					norm_x[f[i]],
					norm_y[f[i]],
					norm_z[f[i]]
				);
				sumNorm += p;
			}*/

			auto norm0 = Vector3D(norm_x[f[0]],norm_y[f[0]],norm_z[f[0]]);
			auto norm1 = Vector3D(norm_x[f[1]],norm_y[f[1]],norm_z[f[1]]);
			auto norm2 = Vector3D(norm_x[f[2]],norm_y[f[2]],norm_z[f[2]]);

			auto vv1 = norm1 - norm0;
			auto vv2 = norm2 - norm1;
			auto val = (vv1 ^ vv2);
			val.Normalize();
			Normal sumNorm(val);

			triangle_ptr->SetNormal(sumNorm);

			mObjects.push_back(triangle_ptr);
		}

		mMesh->mVertexFaces.erase(mMesh->mVertexFaces.begin(), mMesh->mVertexFaces.end());

	}

	if (type == ETriangleType::smooth)
	{
		int count = 0; //number of feces
		for (auto& f : face)
		{
			std::shared_ptr<SmoothMeshTriangle> triangle_ptr = std::make_shared<SmoothMeshTriangle>(mMesh, f[0], f[1], f[2]);
			
			Normal sumNorm;

			auto NormIndex = [f](int i) { return f[i]; };

			int index = NormIndex(0);
			sumNorm += Normal(norm_x[index], norm_y[index], norm_z[index]);
			index = NormIndex(1);
			sumNorm += Normal(norm_x[index], norm_y[index], norm_z[index]);
			index = NormIndex(2);
			sumNorm += Normal(norm_x[index], norm_y[index], norm_z[index]);


			if (sumNorm.mPosX == 0.0 && sumNorm.mPosY == 0.0 && sumNorm.mPosZ == 0.0)
			{
				sumNorm.mPosY = 1.0;
			}
			else
			{
				sumNorm.Normalize();
			}
			
			triangle_ptr->SetNormal(sumNorm);
			
			//triangle_ptr->ComputeNormal(mReverseNormal);
			mObjects.push_back(triangle_ptr);


			mMesh->mVertexFaces[f[0]].push_back(count);
			mMesh->mVertexFaces[f[1]].push_back(count);
			mMesh->mVertexFaces[f[2]].push_back(count);
			count++;

			//for triangle
			if (f.size() == 4) {
				std::shared_ptr<SmoothMeshTriangle> triangle_ptr2 = std::make_shared<SmoothMeshTriangle>(mMesh, f[1], f[2], f[3]);
				triangle_ptr2->ComputeNormal(mReverseNormal);
				mObjects.push_back(triangle_ptr2);

				sumNorm = Normal(0);

				index = NormIndex(3);
				sumNorm += Normal(norm_x[index], norm_y[index], norm_z[index]);
				index = NormIndex(0);
				sumNorm += Normal(norm_x[index], norm_y[index], norm_z[index]);
				index = NormIndex(1);
				sumNorm += Normal(norm_x[index], norm_y[index], norm_z[index]);

				if (sumNorm.mPosX == 0.0 && sumNorm.mPosY == 0.0 && sumNorm.mPosZ == 0.0)
				{
					sumNorm.mPosY = 1.0;
				}
				else
				{
					sumNorm.Normalize();
				}

				triangle_ptr->SetNormal(sumNorm);

				//triangle_ptr->ComputeNormal(mReverseNormal);
				mObjects.push_back(triangle_ptr);

				mMesh->mVertexFaces[f[3]].push_back(count);
				mMesh->mVertexFaces[f[0]].push_back(count);
				mMesh->mVertexFaces[f[1]].push_back(count);
				count++;

			}

		}
		ComputeMeshNormals();
	}
	//---------------------
}

void Grid::ReadUVPlyFile(std::string fileName, ETriangleType type)
{
	//read file
	happly::PLYData plyIn(fileName);

	// exception
	try
	{
		plyIn.validate();
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}

	//---objects---
	//vertex
	const std::vector<float> vertex_x = plyIn.getElement("vertex").getProperty<float>("x");
	const std::vector<float> vertex_y = plyIn.getElement("vertex").getProperty<float>("y");
	const std::vector<float> vertex_z = plyIn.getElement("vertex").getProperty<float>("z");
	const std::vector<float> vertex_u = plyIn.getElement("vertex").getProperty<float>("u");
	const std::vector<float> vertex_v = plyIn.getElement("vertex").getProperty<float>("v");
	//face
	std::vector<std::vector<int>> face = plyIn.getElement("face").getListProperty<int>("vertex_indices");

	// num
	int vertexNum = vertex_x.size();
	int faceNum = face.size();
	//---------

	//---set---
	// objects
	mObjects.reserve(faceNum);
	//vertex
	for (int i = 0; i < vertexNum; i++)
	{
		Point3D p(vertex_x[i], vertex_y[i], vertex_z[i]);
		mMesh->mVertices.push_back(p);
		mMesh->mU.push_back(vertex_u[i]);
		mMesh->mV.push_back(vertex_v[i]);
	}

	mMesh->mNumVertices = vertexNum;
	mMesh->mNumTriangles = faceNum;

	// face
	mMesh->mVertexFaces.resize(vertexNum); // vertex size
	//---------

	//--- make triangle ---
	if (type == ETriangleType::flat)
	{
		for (auto& f : face) {
			std::shared_ptr<FlatUVMeshTriangle> triangle_ptr = std::make_shared<FlatUVMeshTriangle>(mMesh, f[0], f[1], f[2]);
			triangle_ptr->ComputeNormal(mReverseNormal);
			mObjects.push_back(triangle_ptr);
		}

		mMesh->mVertexFaces.erase(mMesh->mVertexFaces.begin(), mMesh->mVertexFaces.end());
	}

	if (type == ETriangleType::smooth)
	{
		int count = 0; //number of feces
		for (auto& f : face)
		{
			std::shared_ptr<SmoothUVMeshTriangle> triangle_ptr = std::make_shared<SmoothUVMeshTriangle>(mMesh, f[0], f[1], f[2]);
			triangle_ptr->ComputeNormal(mReverseNormal);
			mObjects.push_back(triangle_ptr);

			mMesh->mVertexFaces[f[0]].push_back(count);
			mMesh->mVertexFaces[f[1]].push_back(count);
			mMesh->mVertexFaces[f[2]].push_back(count);
			count++;
		}
		ComputeMeshNormals();
	}
	//---------------------
}

void Grid::ReadMMDTriangles(int modelHandle)
{
	//setup mesh data and get it.
	MV1SetupReferenceMesh(modelHandle, -1, TRUE);
	auto refPoly = MV1GetReferenceMesh(modelHandle, -1, TRUE);

	//set up image
	std::string pass = "Additional_File/MMD/TdaéÆèââπÉ~ÉNV4X_Ver1.00/";
	std::unordered_map<std::string, std::shared_ptr<AlphaImageTexture>> image_map;

	//not shadow
	std::vector<std::string> not_testure = 
	{ 
		"hairshadow",
		"body_cloth_yellowgreen",
		"cheek",
		"megane",
		"lens"
	};

	//transparent shadow
	std::vector<std::string> transparent = { "body_decal","eye_hi","eye_hi2" };

	int textureNum = MV1GetTextureNum(modelHandle);
	for (int i = 0; i < textureNum; i++)
	{
		//name
		std::string name = MV1GetTextureName(modelHandle, i);
		
		//image
		std::shared_ptr<AlphaImage> image = std::make_shared<AlphaImage>();
		image->ReadPpmFile(pass + name);

		//texture
		std::shared_ptr<AlphaImageTexture> texture_ptr = std::make_shared<AlphaImageTexture>();
		texture_ptr->SetImage(image);


		image_map[name] = texture_ptr;
	}

	//set num
	mMesh->mNumVertices = refPoly.VertexNum;
	mMesh->mNumTriangles = refPoly.PolygonNum;

	//---set---
	// objects
	mObjects.reserve(mMesh->mNumTriangles);

	//vertex
	mMesh->mVertices.reserve(mMesh->mNumVertices);
	for (int i = 0; i < mMesh->mNumVertices; i++)
	{
		Point3D p(-refPoly.Vertexs[i].Position.x, //right coordinate -> left coordinate
			refPoly.Vertexs[i].Position.y,
			refPoly.Vertexs[i].Position.z);
		//vertices
		mMesh->mVertices.push_back(p);
		//uv
		mMesh->mU.push_back(refPoly.Vertexs[i].TexCoord[0].u);
		mMesh->mV.push_back(1.0f -refPoly.Vertexs[i].TexCoord[0].v);
	}

	//normal
	mMesh->mNormals.reserve(mMesh->mNumVertices);
	for (int i = 0; i < mMesh->mNumVertices; i++)
	{
		Normal p(-refPoly.Vertexs[i].Normal.x,
			refPoly.Vertexs[i].Normal.y,
			refPoly.Vertexs[i].Normal.z);
		//normal
		mMesh->mNormals.push_back(p);
	}

	//mesh
	for (int i = 0; i < mMesh->mNumTriangles; i++)
	{
		bool is_skip = false;
		//material name
		std::string material_name = MV1GetMaterialName(modelHandle, refPoly.Polygons[i].MaterialIndex);

		// skip shadow textuer
		for (auto& name : not_testure)
		{
			if (material_name == name)
			{
				is_skip = true;
			}
		}

		if (is_skip) { continue; }

		//polygon
		std::shared_ptr<SmoothUVMeshTriangle> triangle_ptr = 
			std::make_shared<SmoothUVMeshTriangle>(
				mMesh, 
				refPoly.Polygons[i].VIndex[0], 
				refPoly.Polygons[i].VIndex[1], 
				refPoly.Polygons[i].VIndex[2]);
		triangle_ptr->ComputeNormal(mReverseNormal);
		
		//material
		/*
		std::shared_ptr<Matte> sv_matte_ptr = std::make_shared<Matte>();
		sv_matte_ptr->SetKa(0.8);
		sv_matte_ptr->SetKd(0.2);

		auto ambient = MV1GetMaterialAmbColor(modelHandle, refPoly.Polygons[i].MaterialIndex);
		RGBColor am = RGBColor(ambient.r, ambient.g, ambient.b);
		auto diffuse = MV1GetMaterialDifColor(modelHandle, refPoly.Polygons[i].MaterialIndex);
		RGBColor diff = RGBColor(diffuse.r, diffuse.g, diffuse.b);
		
		sv_matte_ptr->setCdd(diff);
		sv_matte_ptr->SetCda(am);
		triangle_ptr->SetMaterial(sv_matte_ptr);
		*/
		/*
		std::shared_ptr<SV_Matte> sv_matte_ptr = std::make_shared<SV_Matte>();
		sv_matte_ptr->SetKa(0.2);
		sv_matte_ptr->SetKd(0.8);

		std::string material_texture_name = MV1GetTextureName(modelHandle,MV1GetMaterialDifMapTexture(modelHandle, refPoly.Polygons[i].MaterialIndex));
		sv_matte_ptr->SetCd(image_map.at(material_texture_name));
		*/

		//dieletric
		/*
		if (std::find(std::begin(transparent), std::end(transparent), material_name) != std::end(transparent))
		{
			std::shared_ptr<MMD_Dielectric> dielectric_ptr = std::make_shared<MMD_Dielectric>();
			
			//matte settings
			dielectric_ptr->SetKa(0.5);
			dielectric_ptr->SetKd(0.5);
			auto ambient = MV1GetMaterialAmbColor(modelHandle, refPoly.Polygons[i].MaterialIndex);
			RGBColor am = RGBColor(ambient.r, ambient.g, ambient.b);
			auto diffuse = MV1GetMaterialDifColor(modelHandle, refPoly.Polygons[i].MaterialIndex);
			RGBColor diff = RGBColor(diffuse.r, diffuse.g, diffuse.b);
			//texture name
			std::string material_texture_name = MV1GetTextureName(modelHandle, MV1GetMaterialDifMapTexture(modelHandle, refPoly.Polygons[i].MaterialIndex));

			dielectric_ptr->setCdd(diff);
			dielectric_ptr->SetCda(am);
			dielectric_ptr->setCddc(image_map.at(material_texture_name));

			//dielectric settings
			dielectric_ptr->SetEtaIn(1.5);
			dielectric_ptr->SetEtaOut(1.0);
			dielectric_ptr->SetCfIn(white);
			dielectric_ptr->SetCfOut(white);

			//push triangle
			triangle_ptr->SetMaterial(dielectric_ptr);
			mObjects.push_back(triangle_ptr);
			continue;
		}
		*/

		//matte
		std::shared_ptr<MMD_Matte> sv_matte_ptr = std::make_shared<MMD_Matte>();
		sv_matte_ptr->SetKa(0.0);
		sv_matte_ptr->SetKd(0.7);

		auto ambient = MV1GetMaterialAmbColor(modelHandle, refPoly.Polygons[i].MaterialIndex);
		RGBColor am = RGBColor(ambient.r, ambient.g, ambient.b);
		auto diffuse = MV1GetMaterialDifColor(modelHandle, refPoly.Polygons[i].MaterialIndex);
		RGBColor diff = RGBColor(diffuse.r, diffuse.g, diffuse.b);
		//texture name
		std::string material_texture_name = MV1GetTextureName(modelHandle, MV1GetMaterialDifMapTexture(modelHandle, refPoly.Polygons[i].MaterialIndex));
		//toon texture name
		int is_toon_texture = MV1GetMaterialDifGradTexture(modelHandle, refPoly.Polygons[i].MaterialIndex);
		std::string toon_texture_name;
		//if is_toon_texture == -1, this material don't have toon texture.
		if (is_toon_texture != -1) {
			toon_texture_name = MV1GetTextureName(modelHandle, is_toon_texture);
		}

		sv_matte_ptr->setCdd(diff);
		sv_matte_ptr->SetCda(am);
		sv_matte_ptr->setCddc(image_map.at(material_texture_name));
		if (is_toon_texture != -1) {
			sv_matte_ptr->SetToon(image_map.at(toon_texture_name));
		}

		triangle_ptr->SetMaterial(sv_matte_ptr);
		triangle_ptr->mShadowSr = mShadowSr; //set alpha shadow for mesh object

		mObjects.push_back(triangle_ptr);
	}
	//---------------------

}

void Grid::ComputeMeshNormals()
{
	mMesh->mNormals.reserve(mMesh->mNumVertices);

	for (int index = 0; index < mMesh->mNumVertices; index++)
	{
		Normal normal;

		// face index for vertex
		for (int j = 0; j < mMesh->mVertexFaces[index].size(); j++)
		{
			normal += mObjects[mMesh->mVertexFaces[index][j]]->GetNormal();
		}

		if (normal.mPosX == 0.0 && normal.mPosY == 0.0 && normal.mPosZ == 0.0)
		{
			normal.mPosY = 1.0;
		}
		else
		{
			normal.Normalize();
		}

		mMesh->mNormals.push_back(normal);
	}

	for (int index = 0; index < mMesh->mNumVertices; index++)
	{
		mMesh->mVertexFaces[index].erase(mMesh->mVertexFaces[index].begin(), mMesh->mVertexFaces[index].end());
	}

	mMesh->mVertexFaces.erase(mMesh->mVertexFaces.begin(), mMesh->mVertexFaces.end());
}

void Grid::SetShadowAlpha(World& w)
{
	mShadowSr = std::make_shared<ShadeRec>(w);
}
