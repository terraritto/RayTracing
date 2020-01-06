void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(400);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<Directional> light_ptr = std::make_shared<Directional>();
	light_ptr->SetDirection(0.75, 1, -0.15);
	light_ptr->SetScaleRadiance(4.5);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(100, 50, 90);
	pinholePtr->SetLookAt(0, -0.5, 0);
	pinholePtr->SetViewDistance(16000);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.1);
	matte_ptr1->SetKd(0.75);
	matte_ptr1->SetCd(0.1, 0.5, 1.0);

	const std::string fileName = "./Additional_File/PLYFiles/TwoTriangles.ply";
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	grid_ptr->ReadTriangles(fileName, Grid::ETriangleType::smooth);
	grid_ptr->SetMaterial(matte_ptr1);
	grid_ptr->SetupCells();
	AddObject(grid_ptr);

	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.25);
	matte_ptr2->SetKd(0.4);
	matte_ptr2->SetCd(1, 0.9, 0.6);

	std::shared_ptr<Plane> plane_ptr1 = std::make_shared<Plane>(Point3D(0, -2.0, 0), Normal(0, 1, 0));
	plane_ptr1->SetMaterial(matte_ptr2);
	AddObject(plane_ptr1);
}