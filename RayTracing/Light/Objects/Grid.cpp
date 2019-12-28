#include "Grid.h"

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

void Grid::SetupCells()
{
}

bool Grid::hit(const Ray& ray, double& t, ShadeRec& s)
{
	return false;
}

bool Grid::Shadow_hit(const Ray& ray, float& tmin) const
{
	return false;
}

Point3D Grid::MinCoordinates()
{
	return Point3D();
}

Point3D Grid::MaxCoordinates()
{
	return Point3D();
}
