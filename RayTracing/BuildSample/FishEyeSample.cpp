void World::Build()
{
	int numSamples = 10;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(0);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);
	mBackGroundColor = white;

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//sub Light
	std::shared_ptr<PointLight> light_ptr = std::make_shared<PointLight>();
	light_ptr->SetLocation(150, 200, 65);
	light_ptr->SetScaleRadiance(5.25);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//Set Camera
	std::shared_ptr<FishEye> fisheye_ptr = std::make_shared<FishEye>();
	fisheye_ptr->SetEye(250, 300, 150);
	fisheye_ptr->SetLookAt(-20, 300, -110);
	fisheye_ptr->SetPsiMax(120);
	fisheye_ptr->ComputeUVW();
	SetCamera(fisheye_ptr);

	//set object
	//box materials
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.4);
	matte_ptr1->SetKd(0.5);
	matte_ptr1->SetCd(0, 0.5, 0.5);

	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.4);
	matte_ptr2->SetKd(0.5);
	matte_ptr2->SetCd(1, 0, 0);

	std::shared_ptr<Matte> matte_ptr3 = std::make_shared<Matte>();
	matte_ptr3->SetKa(0.4);
	matte_ptr3->SetKd(0.5);
	matte_ptr3->SetCd(0.5, 0.6, 0);

	// grid
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();

	//first row
	int num_boxes = 40;
	float wx = 50;
	float wz = 50;
	float h = 150;
	float s = 100;

	for (int j = 0; j < num_boxes; j++)
	{
		std::shared_ptr<Box> box_ptr = std::make_shared<Box>(
			Point3D(-wx, 0, -(j + 1) * wz - j * s),
			Point3D(0, h, -j * wz - j * s)
			);
		box_ptr->SetMaterial(matte_ptr1);
		grid_ptr->AddObject(box_ptr);
	}

	//second row
	h = 300;
	for (int j = 0; j < num_boxes; j++)
	{
		std::shared_ptr<Box> box_ptr = std::make_shared<Box>(
			Point3D(-wx - wx - s, 0, -(j + 1) * wz - j * s),
			Point3D(-wx - s, h, -j * wz - j * s)
			);
		box_ptr->SetMaterial(matte_ptr2);
		grid_ptr->AddObject(box_ptr);
	}

	//third row
	h = 850;

	for (int j = 0; j < num_boxes; j++)
	{
		std::shared_ptr<Box> box_ptr = std::make_shared<Box>(
			Point3D(-wx - 2 * wx - 2 * s, 0, -(j + 1) * wz - j * s),
			Point3D(-2 * wx - 2 * s, h, -j * wz - j * s)
			);
		box_ptr->SetMaterial(matte_ptr3);
		grid_ptr->AddObject(box_ptr);
	}

	// a column
	h = 150;
	for (int j = 0; j < num_boxes; j++)
	{
		std::shared_ptr<Box> box_ptr = std::make_shared<Box>(
			Point3D(-3 * (wx + s) - (j + 1) * wz - j * s, 0, -wx),
			Point3D(-3 * (wx + s) - j * wz - j * s, h, 0)
			);
		box_ptr->SetMaterial(matte_ptr1);
		grid_ptr->AddObject(box_ptr);
	}

	grid_ptr->SetupCells();
	AddObject(grid_ptr);

	// ground plane
	std::shared_ptr<Matte> matte_ptr4 = std::make_shared<Matte>();
	matte_ptr4->SetKa(0.2);
	matte_ptr4->SetKd(0.5);
	matte_ptr4->SetCd(white);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0, 1, 0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr4);
	AddObject(plane_ptr);
}
