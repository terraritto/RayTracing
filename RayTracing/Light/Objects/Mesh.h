#pragma once
#include <vector>
#include "../Maths/Point3D.h"
#include "../Maths/Normal.h"

class Mesh
{
public:
	std::vector<Point3D> mVertices;
	std::vector<Normal> mNormals;
	std::vector<float> mU;
	std::vector<float> mV;
	std::vector<std::vector<int>> mVertexFaces;
	int mNumVertices;
	int mNumTriangles;

	Mesh() = default;
	Mesh(const Mesh& m);
	~Mesh() = default;
	Mesh& operator=(const Mesh& rhs);
};