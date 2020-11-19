void World::Build()
{
	int numSamples = 30;

	//set View Plane
	mViewPlane.SetHRes(1920);
	mViewPlane.SetVRes(1080);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(10);

	mResult.resize(mViewPlane.mHRes);
	for (auto& res : mResult)
	{
		res.resize(mViewPlane.mVRes);
	}


	//set Tracer
	mTracerPtr = std::make_shared<AreaLights>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(77.6, 40.4, -80.0);
	pinholePtr->SetLookAt(77.6, 40.4, 0.0);
	pinholePtr->SetViewDistance(1000);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	Point3D p0;
	Vector3D a, b;
	Normal normal;

	// box dimension
	double width = 155.28;
	double height = 80.88;
	double depth = 55.92;

	// ceiling light
	std::shared_ptr<Emissive> emissive_ptr = std::make_shared<Emissive>();
	//emissive_ptr->SetCe(1.0, 1.0, 1.0);
	emissive_ptr->SetCe(1.0, 0.73, 0.4);
	emissive_ptr->SetLadiance(10);

	p0 = Point3D(width / 4, height - 0.001, depth / 4);
	a = Vector3D(0.0, 0.0, depth / 2);
	b = Vector3D(width / 2, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);

	//p0 = Point3D(0.0, 0.0, -depth * 2);
	//a = Vector3D(width, 0.0, 0.0);
	//b = Vector3D(0.0, height, 0.0);
	//normal = Normal(0.0, 0.0, 1.0);

	std::shared_ptr<Rectangler> light_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	light_ptr->SetMaterial(emissive_ptr);
	light_ptr->SetSampler(std::make_shared<MultiJittered>(numSamples));
	light_ptr->SetIsShadow(false);
	AddObject(light_ptr);

	std::shared_ptr<AreaLight> ceiling_light_ptr = std::make_shared<AreaLight>();
	ceiling_light_ptr->SetObject(light_ptr);
	ceiling_light_ptr->SetIsShadow(true);
	AddLight(ceiling_light_ptr);

	//front light
	p0 = Point3D(0.0, 0.0, -depth * 2);
	a = Vector3D(width, 0.0, 0.0);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(0.0, 0.0, 1.0);

	std::shared_ptr<Rectangler> light_ptr2 = std::make_shared<Rectangler>(p0, a, b, normal);
	light_ptr2->SetMaterial(emissive_ptr);
	light_ptr2->SetSampler(std::make_shared<MultiJittered>(numSamples));
	light_ptr2->SetIsShadow(false);
	AddObject(light_ptr);

	std::shared_ptr<AreaLight> front_light_ptr = std::make_shared<AreaLight>();
	front_light_ptr->SetObject(light_ptr2);
	front_light_ptr->SetIsShadow(true);
	AddLight(front_light_ptr);

	//point light
	auto light_ptr3 = std::make_shared<Directional>();
	light_ptr3->SetScaleRadiance(2.0);
	light_ptr3->SetColor(1.0, 0.73, 0.4);
	light_ptr3->SetDirection(0.0f, 0.0f, 1.0f);
	AddLight(light_ptr3);

	//object
	/*
	int modelHandle;
	std::string fileName = "Additional_File/MMD/Tda式初音ミクV4X_Ver1.00/Tda式初音ミク.pmx";
	//load and set model
	modelHandle = MV1LoadModel(fileName.c_str());
	MV1SetPosition(modelHandle, VGet(-width + width / 2, 0.0, depth / 4));
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
	int attachIndex = MV1AttachAnim(modelHandle, 0, -1, FALSE);
	MV1SetAttachAnimTime(modelHandle, attachIndex, 0.0f);
	*/

	std::shared_ptr<Matte> matte_ptr = std::make_shared<Matte>();
	matte_ptr->SetKa(0.0);
	matte_ptr->SetKd(0.6);
	matte_ptr->SetCd(1.0, 1.0, 0.0);
	matte_ptr->SetSamples(numSamples);

	//const std::string fileName = "./Additional_File/PLYFiles/dragon_recon/dragon_vrip_res2.ply";
	const std::string fileName = "./Additional_File/PLYFiles/icon_no_aitsu.ply";
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	grid_ptr->ReadTriangles(fileName, Grid::ETriangleType::smooth);
	grid_ptr->SetMaterial(matte_ptr);
	grid_ptr->SetupCells();

	std::shared_ptr<Instance> instance_ptr = std::make_shared<Instance>();
	instance_ptr->SetObject(grid_ptr);
	instance_ptr->SetMaterial(matte_ptr);
	instance_ptr->Scale(10.0, 10.0, 10.0);
	instance_ptr->RotateX(-90.0f);
	instance_ptr->RotateY(180.0f);
	instance_ptr->Translate(+width - width / 2, 10.0, depth / 2);
	instance_ptr->ComputeBoundingBox();
	//std::shared_ptr<Grid> instance_grid_ptr = std::make_shared<Grid>();
	//instance_grid_ptr->AddObject(instance_ptr);
	//instance_grid_ptr->SetupCells();


	AddObject(instance_ptr);

	//AddObject(grid_ptr);


	/*
	std::shared_ptr<Matte> mmd_matte = std::make_shared<Matte>();
	mmd_matte->SetKa(0.1);
	mmd_matte->SetKd(0.75);
	mmd_matte->SetCd(0.1, 0.5, 1.0);

	std::shared_ptr<Grid> mmd_ptr = std::make_shared<Grid>();
	mmd_ptr->SetShadowAlpha(*this); //for alpha shadow
	mmd_ptr->ReadMMDTriangles(modelHandle);
	//mmd_ptr->SetMaterial(mmd_matte);
	mmd_ptr->SetupCells();
	AddObject(mmd_ptr);

	MV1DeleteModel(modelHandle);
	*/

	//left wall
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.0);
	matte_ptr1->SetKd(0.6);
	matte_ptr1->SetCd(0.57, 0.025, 0.025);
	matte_ptr1->SetSamples(numSamples);

	p0 = Point3D(width, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(-1.0, 0.0, 0.0);
	std::shared_ptr<Rectangler> left_wall_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	left_wall_ptr->SetMaterial(matte_ptr1);
	AddObject(left_wall_ptr);

	//right wall
	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.0);
	matte_ptr2->SetKd(0.6);
	matte_ptr2->SetCd(0.37, 0.59, 0.2);
	matte_ptr2->SetSamples(numSamples);

	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(1.0, 0.0, 0.0);
	std::shared_ptr<Rectangler> right_wall_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	right_wall_ptr->SetMaterial(matte_ptr2);
	AddObject(right_wall_ptr);

	//back wall
	std::shared_ptr<Matte> matte_ptr3 = std::make_shared<Matte>();
	matte_ptr3->SetKa(0.0);
	matte_ptr3->SetKd(0.6);
	matte_ptr3->SetCd(1.0);
	matte_ptr3->SetSamples(numSamples);

	std::shared_ptr<Reflective> reflective_ptr = std::make_shared<Reflective>();
	reflective_ptr->SetKa(0);
	reflective_ptr->SetKd(0);
	reflective_ptr->SetCd(black);
	reflective_ptr->SetKs(0);
	reflective_ptr->SetKr(0.9);
	reflective_ptr->SetCr(0.9, 1.0, 0.9);

	p0 = Point3D(0.0, 0.0, depth);
	a = Vector3D(width, 0.0, 0.0);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(0.0, 0.0, -1.0);
	std::shared_ptr<Rectangler> back_wall_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	back_wall_ptr->SetMaterial(matte_ptr3);
	AddObject(back_wall_ptr);

	//floor
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, 1.0, 0.0);

	std::shared_ptr<MicforasetReflective> reflective_ptr2 = std::make_shared<MicforasetReflective>();
	reflective_ptr2->SetKa(0);
	reflective_ptr2->SetKd(0);
	reflective_ptr2->SetCd(black);
	reflective_ptr2->SetKs(0);
	reflective_ptr2->SetKr(0.9);
	reflective_ptr2->SetCr(0.9, 1.0, 0.9);
	reflective_ptr2->SetAlpha(0.9);
	reflective_ptr2->SetFresnel(0.5);

	std::shared_ptr<Rectangler> floor_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	floor_ptr->SetMaterial(reflective_ptr2);
	AddObject(floor_ptr);

	//ceiling
	p0 = Point3D(0.0, height, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	std::shared_ptr<Rectangler> ceiling_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	ceiling_ptr->SetMaterial(matte_ptr3);
	AddObject(ceiling_ptr);

	//short box
	//top
	p0 = Point3D(13.0, 16.5, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(16.0, 0.0, 4.9);
	normal = Normal(0.0, 1.0, 0.0);
	std::shared_ptr<Rectangler> short_top_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	short_top_ptr->SetMaterial(matte_ptr3);
	AddObject(short_top_ptr);

	//side1
	p0 = Point3D(13.0, 0.0, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(0.0, 16.5, 0.0);
	std::shared_ptr<Rectangler> short_side_ptr1 = std::make_shared<Rectangler>(p0, a, b);
	short_side_ptr1->SetMaterial(matte_ptr3);
	AddObject(short_side_ptr1);

	//side2
	p0 = Point3D(8.2, 0.0, 22.5);
	a = Vector3D(15.8, 0.0, 4.7);
	std::shared_ptr<Rectangler> short_side_ptr2 = std::make_shared<Rectangler>(p0, a, b);
	short_side_ptr2->SetMaterial(matte_ptr3);
	AddObject(short_side_ptr2);

	//side3
	p0 = Point3D(24.2, 0.0, 27.4);
	a = Vector3D(4.8, 0.0, -16.0);
	std::shared_ptr<Rectangler> short_side_ptr3 = std::make_shared<Rectangler>(p0, a, b);
	short_side_ptr3->SetMaterial(matte_ptr3);
	AddObject(short_side_ptr3);

	//side4
	p0 = Point3D(29.0, 0.0, 11.4);
	a = Vector3D(-16.0, 0.0, -4.9);
	std::shared_ptr<Rectangler> short_side_ptr4 = std::make_shared<Rectangler>(p0, a, b);
	short_side_ptr4->SetMaterial(matte_ptr3);
	AddObject(short_side_ptr4);

	//tall
	//top
	p0 = Point3D(42.3, 33.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(4.9, 0.0, 15.9);
	normal = Normal(0.0, 1.0, 0.0);
	std::shared_ptr<Rectangler> tall_top_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	tall_top_ptr->SetMaterial(matte_ptr3);
	AddObject(tall_top_ptr);

	//side1
	p0 = Point3D(42.3, 0.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(0.0, 33.0, 0.0);
	std::shared_ptr<Rectangler> tall_side_ptr1 = std::make_shared<Rectangler>(p0, a, b);
	tall_side_ptr1->SetMaterial(matte_ptr3);
	AddObject(tall_side_ptr1);

	//side2
	p0 = Point3D(26.5, 0.0, 29.6);
	a = Vector3D(4.9, 0.0, 15.9);
	std::shared_ptr<Rectangler> tall_side_ptr2 = std::make_shared<Rectangler>(p0, a, b);
	tall_side_ptr2->SetMaterial(matte_ptr3);
	AddObject(tall_side_ptr2);

	//side3
	p0 = Point3D(31.4, 0.0, 45.5);
	a = Vector3D(15.8, 0.0, -4.9);
	std::shared_ptr<Rectangler> tall_side_ptr3 = std::make_shared<Rectangler>(p0, a, b);
	tall_side_ptr3->SetMaterial(matte_ptr3);
	AddObject(tall_side_ptr3);

	//side4
	p0 = Point3D(47.2, 0.0, 40.6);
	a = Vector3D(-4.9, 0.0, -15.9);
	std::shared_ptr<Rectangler> tall_side_ptr4 = std::make_shared<Rectangler>(p0, a, b);
	tall_side_ptr4->SetMaterial(matte_ptr3);
	AddObject(tall_side_ptr4);

}