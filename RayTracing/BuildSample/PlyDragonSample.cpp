void World::Build()
{
	int numSamples = 1;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<MultiJittered> sample_ptr = std::make_shared<MultiJittered>(numSamples);
	std::shared_ptr<AmbientOccluder> ambientPtr = std::make_shared<AmbientOccluder>();
	ambientPtr->SetMinAmount(0.25);
	ambientPtr->SetSampler(sample_ptr);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<Directional> light_ptr = std::make_shared<Directional>();
	light_ptr->SetDirection(0.5, 1, 0.75);
	light_ptr->SetScaleRadiance(1.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(-6, 5, 11);
	pinholePtr->SetLookAt(-0.009, 0.11, 0);
	pinholePtr->SetViewDistance(37500);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	std::shared_ptr<Phong> phong_ptr1 = std::make_shared<Phong>();
	phong_ptr1->SetKa(0.2);
	phong_ptr1->SetKd(0.95);
	phong_ptr1->SetCd(1, 0.6, 0);
	phong_ptr1->SetKs(0.5);
	phong_ptr1->SetExp(20);
	phong_ptr1->SetCs(1, 0.6, 0);

	const std::string fileName = "./Additional_File/PLYFiles/dragon_recon/dragon_vrip_res2.ply";
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	grid_ptr->ReadTriangles(fileName, Grid::ETriangleType::smooth);
	grid_ptr->SetMaterial(phong_ptr1);
	grid_ptr->SetupCells();
	AddObject(grid_ptr);

	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.2);
	matte_ptr2->SetKd(0.75);
	matte_ptr2->SetCd(0.5);

	std::shared_ptr<Plane> plane_ptr1 = std::make_shared<Plane>(Point3D(0, 0.055, 0), Normal(0, 1, 0));
	plane_ptr1->SetMaterial(matte_ptr2);
	AddObject(plane_ptr1);
}