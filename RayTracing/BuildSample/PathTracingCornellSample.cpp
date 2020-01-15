void World::Build()
{
	int numSamples = 100;

	//set View Plane
	mViewPlane.SetHRes(300);
	mViewPlane.SetVRes(300);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(10);

	//set Tracer
	//mTracerPtr = std::make_shared<PathTrace>(this);
	mTracerPtr = std::make_shared<GlobalTrace>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(27.6, 27.4, -80.0);
	pinholePtr->SetLookAt(27.6, 27.4, 0.0);
	pinholePtr->SetViewDistance(400);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	Point3D p0;
	Vector3D a, b;
	Normal normal;

	// box dimension
	double width = 55.28;
	double height = 54.88;
	double depth = 55.92;

	// ceiling light
	std::shared_ptr<Emissive> emissive_ptr = std::make_shared<Emissive>();
	emissive_ptr->SetCe(1.0, 0.73, 0.4);
	emissive_ptr->SetLadiance(100);

	p0 = Point3D(21.3, height - 0.001, 22.7);
	a = Vector3D(0.0, 0.0, 10.5);
	b = Vector3D(13.0, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	std::shared_ptr<Rectangler> light_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	light_ptr->SetMaterial(emissive_ptr);
	light_ptr->SetSampler(std::make_shared<MultiJittered>(numSamples));
	light_ptr->SetIsShadow(false);
	AddObject(light_ptr);

	std::shared_ptr<AreaLight> ceiling_light_ptr = std::make_shared<AreaLight>();
	ceiling_light_ptr->SetObject(light_ptr);
	ceiling_light_ptr->SetIsShadow(true);
	AddLight(ceiling_light_ptr);

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
	std::shared_ptr<Rectangler> floor_ptr = std::make_shared<Rectangler>(p0, a, b, normal);
	floor_ptr->SetMaterial(matte_ptr3);
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