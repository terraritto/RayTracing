void World::Build()
{
	int numSamples = 1;

	//set View Plane
	mViewPlane.SetHRes(500);
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
	light_ptr->SetDirection(20, 40, 20);
	light_ptr->SetScaleRadiance(3.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//set object
	const std::string fileName = "./Additional_File/PLYFiles/bunny/reconstruction/bun_zipper_res2.ply";
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	grid_ptr->ReadTriangles(fileName, Grid::ETriangleType::flat);
	grid_ptr->SetupCells();

	int num_levels = 6;
	int instances_grid_res = 10;
	int delta = 0.1;
	int gap = 0.08;
	double size = 0.1;
	double mcx = 0.5;

	std::shared_ptr<Grid> current_grid_ptr = grid_ptr;

	//random
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	for (int level = 0; level < num_levels; level++)
	{
		std::shared_ptr<Grid> instance_grid_ptr = std::make_shared<Grid>();

		for (int i = 0; i < instances_grid_res; i++)
		{
			for (int k = 0; k < instances_grid_res; k++)
			{
				//set object
				std::shared_ptr<Phong> phong_ptr1 = std::make_shared<Phong>();
				phong_ptr1->SetKa(0.2);
				phong_ptr1->SetKd(0.5);
				phong_ptr1->SetCd(floatRand(mt), floatRand(mt), floatRand(mt));
				phong_ptr1->SetKs(0.4);
				phong_ptr1->SetExp(20);

				std::shared_ptr<Instance> instance_ptr = std::make_shared<Instance>();
				instance_ptr->SetObject(current_grid_ptr);
				instance_ptr->SetMaterial(phong_ptr1);
				instance_ptr->Translate(i * (size + gap), 0.0, k * (size + gap));
				instance_ptr->ComputeBoundingBox();
				instance_grid_ptr->AddObject(instance_ptr);
			}
		}
		size = instances_grid_res * size + (instances_grid_res - 1) * gap;
		gap = delta * size;
		instance_grid_ptr->SetupCells();
		current_grid_ptr = instance_grid_ptr;
	}
	AddObject(current_grid_ptr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(7 * mcx * size, 4 * mcx * size, 5 * mcx * size);
	pinholePtr->SetLookAt(mcx * size, 0.0, mcx * size);
	pinholePtr->SetViewDistance(300000000);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

}