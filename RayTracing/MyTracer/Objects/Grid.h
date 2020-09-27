#pragma once
#include "Compound.h"
#include "Mesh.h"

class Grid : public Compound
{
public:
	// triangle type
	enum class ETriangleType
	{
		flat,
		smooth
	};

	Grid();
	Grid(const Grid& rg);
	~Grid();
	Grid& operator=(const Grid& rhs);

	std::shared_ptr<Grid> Clone();
	BBox GetBoundingBox() const override;

	//for mesh sphere
	void TessellateFlatSphere(const int horizontalSteps, const int verticalSteps);
	void TessellateSmoothSphere(const int horizontalSteps, const int verticalSteps);

	//to read ply files
	void ReadTriangles(std::string fileName, ETriangleType type);
	void ReadUVTriangles(std::string fileName, ETriangleType type);

	// to read mmd object
	void ReadMMDTriangles(int modelHandle);

	void SetupCells();
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) override;
	virtual bool Shadow_hit(const Ray& ray, float& tmin) const override;
private:
	std::vector<std::shared_ptr<GeometricObject>> mCells;
	BBox mBBox;
	int mNx, mNy, mNz; // number of cells in the x,y and z directions
	bool mReverseNormal;
	Point3D MinCoordinates(); //compute minimum grid coordinates
	Point3D MaxCoordinates(); //compute maximum grid coordinates

	void ReadPlyFile(std::string fileName, ETriangleType type);
	void ReadUVPlyFile(std::string fileName, ETriangleType type);
	void ComputeMeshNormals();
public:
	std::shared_ptr<Mesh> mMesh; // for triangle
	void SetShadowAlpha(World& w); //for alpha
};