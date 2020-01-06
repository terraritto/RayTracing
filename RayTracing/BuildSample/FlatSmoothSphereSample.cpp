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
	mBackGroundColor = RGBColor(0.9);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<Directional> light_ptr = std::make_shared<Directional>();
	light_ptr->SetDirection(20, 25, 5);
	light_ptr->SetScaleRadiance(3.0);
	light_ptr->SetIsShadow(false);
	AddLight(light_ptr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(10, 12, 18);
	pinholePtr->SetLookAt(0);
	pinholePtr->SetViewDistance(4000);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	std::shared_ptr<Phong> phong_ptr = std::make_shared<Phong>();
	phong_ptr->SetKa(0.25);
	phong_ptr->SetKd(0.75);
	phong_ptr->SetCs(0.5);
	phong_ptr->SetCd(0.2, 0.5, 0.4);
	phong_ptr->SetKs(0.2);
	phong_ptr->SetExp(20.0);

	int num_horizontal_steps = 100;
	int num_vertical_steps = 50;

	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	// flat sphere
	//grid_ptr->TessellateFlatSphere(num_horizontal_steps, num_vertical_steps);
	// smooth sphere
	grid_ptr->TessellateSmoothSphere(num_horizontal_steps, num_vertical_steps);
	grid_ptr->SetMaterial(phong_ptr);
	grid_ptr->SetupCells();
	AddObject(grid_ptr);
}