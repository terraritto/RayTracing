#pragma once
#include "Compound.h"

class Grid : public Compound
{
public:
	Grid();
	Grid(const Grid& rg);
	~Grid();
	Grid& operator=(const Grid& rhs);

	std::shared_ptr<Grid> Clone();
	BBox GetBoundingBox() const override;

	//for mesh sphere
	void TessellateFlatSphere(const int horizontalSteps, const int verticalSteps);

	void SetupCells();
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) override;
	virtual bool Shadow_hit(const Ray& ray, float& tmin) const override;
private:
	std::vector<std::shared_ptr<GeometricObject>> mCells;
	BBox mBBox;
	int mNx, mNy, mNz; // number of cells in the x,y and z directions

	Point3D MinCoordinates(); //compute minimum grid coordinates
	Point3D MaxCoordinates(); //compute maximum grid coordinates
};