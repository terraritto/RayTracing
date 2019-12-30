void World::Build()
{
	int numSamples = 25;

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
	light_ptr->SetDirection(1, 0, 0);
	light_ptr->SetScaleRadiance(1.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	std::shared_ptr<Directional> light_ptr2 = std::make_shared<Directional>();
	light_ptr2->SetDirection(0, 1, 0);
	light_ptr2->SetScaleRadiance(2.0);
	light_ptr2->SetIsShadow(true);
	AddLight(light_ptr2);

	std::shared_ptr<Directional> light_ptr3 = std::make_shared<Directional>();
	light_ptr3->SetDirection(0, 0, 1);
	light_ptr3->SetScaleRadiance(1.5);
	light_ptr3->SetIsShadow(true);
	AddLight(light_ptr3);
	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(7, 5, 4.5);
	pinholePtr->SetLookAt(0, 0.5, -0.25);
	pinholePtr->SetViewDistance(1305);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	int numSpheres = 25;
	float volume = 0.1 / numSpheres;
	float radius = 2.5 * std::pow(0.75 * volume / 3.14159, 1.0 / 3.0);

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
		sphere_ptr->SetMaterial(matte_ptr);

		std::shared_ptr<Instance> sphere_ptr2 = std::make_shared<Instance>(sphere_ptr);
		sphere_ptr2->Scale(radius);
		sphere_ptr2->Scale(1, 0.25, 1);
		sphere_ptr2->Translate(
			1.0 - 2.0 * floatRand(mt),
			1.0 - 2.0 * floatRand(mt),
			1.0 - 2.0 * floatRand(mt)
		);
		sphere_ptr2->ComputeBoundingBox();

		grid_ptr->AddObject(sphere_ptr2);
	}

	grid_ptr->SetupCells();
	AddObject(grid_ptr);

	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.15);
	matte_ptr1->SetKd(0.6);
	matte_ptr1->SetCd(0.5);

	std::shared_ptr<Plane> plane_ptr1 = std::make_shared<Plane>(Point3D(-2, 0, 0), Normal(1, 0, 0));
	plane_ptr1->SetMaterial(matte_ptr1);
	AddObject(plane_ptr1);

	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.15);
	matte_ptr2->SetKd(0.6);
	matte_ptr2->SetCd(0.5);

	std::shared_ptr<Plane> plane_ptr2 = std::make_shared<Plane>(Point3D(0, -2, 0), Normal(0, 1, 0));
	plane_ptr2->SetMaterial(matte_ptr2);
	AddObject(plane_ptr2);

	std::shared_ptr<Matte> matte_ptr3 = std::make_shared<Matte>();
	matte_ptr3->SetKa(0.15);
	matte_ptr3->SetKd(0.6);
	matte_ptr3->SetCd(0.5);

	std::shared_ptr<Plane> plane_ptr3 = std::make_shared<Plane>(Point3D(0, 0, -2), Normal(0, 0, 1));
	plane_ptr3->SetMaterial(matte_ptr3);
	AddObject(plane_ptr3);

}