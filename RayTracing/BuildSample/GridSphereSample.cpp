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

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<Directional> light_ptr = std::make_shared<Directional>();
	light_ptr->SetDirection(0, 0, 1);
	light_ptr->SetScaleRadiance(3.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(0.0, 0.0, 0.9);
	pinholePtr->SetLookAt(0, 0, -100);
	pinholePtr->SetViewDistance(150);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	int numSpheres = 1000;
	float volume = 0.1 / numSpheres;
	float radius = std::pow(0.75 * volume / 3.14159, 1.0 / 3.0);

	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();

	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);
	for (int j = 0; j < numSpheres; j++)
	{
		std::shared_ptr<Matte> matte_ptr = std::make_shared<Matte>();
		matte_ptr->SetKa(0.25);
		matte_ptr->SetKd(0.75);
		matte_ptr->SetCd(RGBColor(floatRand(mt), floatRand(mt), floatRand(mt)));

		std::shared_ptr<Sphere> sphere_ptr = std::make_shared <Sphere>();
		sphere_ptr->SetRadius(radius);
		sphere_ptr->SetCenter(
			1.0 - 2.0 * floatRand(mt),
			1.0 - 2.0 * floatRand(mt),
			1.0 - 2.0 * floatRand(mt)
		);
		sphere_ptr->SetMaterial(matte_ptr);
		grid_ptr->AddObject(sphere_ptr);
	}

	grid_ptr->SetupCells();
	AddObject(grid_ptr);
}