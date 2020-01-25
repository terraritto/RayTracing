void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(10);

	//set Tracer
	mTracerPtr = std::make_shared<Whitted>(this);
	mBackGroundColor = white;

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.25);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinhole_ptr = std::make_shared<Pinhole>();
	pinhole_ptr->SetEye(0, 0, 100);
	pinhole_ptr->SetLookAt(-0.4, 0.6, 0);
	pinhole_ptr->SetViewDistance(15000.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);

	//set object
	//transparent bunny
	std::shared_ptr<Dielectric> glass_ptr = std::make_shared<Dielectric>();
	glass_ptr->SetKa(0.0);
	glass_ptr->SetKd(0.0);
	glass_ptr->SetKs(0.2);
	glass_ptr->SetExp(2000.0);
	glass_ptr->SetEtaIn(1.5);
	glass_ptr->SetEtaOut(1.0);
	glass_ptr->SetCfIn(0.65, 0.45, 0);
	glass_ptr->SetCfOut(white);
	glass_ptr->SetCs(1.0);

	const std::string fileName = "./Additional_File/PLYFiles/bunny/reconstruction/bun_zipper_res4.ply";
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	grid_ptr->ReadTriangles(fileName, Grid::ETriangleType::smooth);
	grid_ptr->SetMaterial(glass_ptr);
	grid_ptr->SetupCells();

	std::shared_ptr<Instance> big_bunny_ptr = std::make_shared<Instance>(grid_ptr);
	big_bunny_ptr->Scale(20.0);
	big_bunny_ptr->Translate(0.0, -1.5, 0.0);
	AddObject(big_bunny_ptr);
}
