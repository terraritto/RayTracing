#include "Grid.h"
#include "Triangle.h"

Grid::Grid()
	: Compound()
	, mNx(0), mNy(0), mNz(0)
{
}

Grid::Grid(const Grid& rg)
	: Compound(rg)
	, mNx(rg.mNx), mNy(rg.mNy), mNz(rg.mNz)
	, mBBox(rg.mBBox)
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
			if (object_ptr && object_ptr->hit(ray, t, s) && t < tx_next)
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
				if (object_ptr && object_ptr->hit(ray, t, s) && t < ty_next)
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
				if (object_ptr && object_ptr->hit(ray, t, s) && t < tz_next)
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
