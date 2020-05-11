#include "Mesh.h"

//this don't handle mVertexFaces
Mesh::Mesh(const Mesh& m)
	: mVertices(m.mVertices)
	, mNormals(m.mNormals)
	, mU(m.mU)
	, mV(m.mV)
	, mNumVertices(m.mNumVertices)
	, mNumTriangles(m.mNumTriangles)
{
}

//this don't handle mVertexFaces
Mesh& Mesh::operator=(const Mesh& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mVertices = rhs.mVertices;
	mNormals = rhs.mNormals;
	mU = rhs.mU;
	mV = rhs.mV;
	mNumVertices = rhs.mNumVertices;
	mNumTriangles = rhs.mNumTriangles;

	return *this;
}
