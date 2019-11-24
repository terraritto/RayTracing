void World::Build()
{
	int numSamples = 100;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.5);

	//set Tracer
	mTracerPtr = std::make_shared<AreaLights>(this);

	//Main Light
	std::shared_ptr<MultiJittered> samplePtr = std::make_shared<MultiJittered>(numSamples);

	/*
	std::shared_ptr<AmbientOccluder> ambientPtr = std::make_shared<AmbientOccluder>();
	ambientPtr->SetRadiance(1.0);
	ambientPtr->SetColor(white);
	ambientPtr->SetMinAmount(0.0);
	ambientPtr->SetSampler(samplePtr);
	SetAmbientLight(ambientPtr);
	*/
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0);
	SetAmbientLight(ambientPtr);
	//Add Light
	float width = 4.0;
	float height = 4.0;
	Point3D center(0.0, 7.0, -7.0);
	Point3D p0(-0.5 * width, center.mPosY - 0.5 * height, center.mPosZ);
	Vector3D a(width, 0.0, 0.0);
	Vector3D b(0.0, height, 0.0);
	Normal normal(0, 0, 1);

	std::shared_ptr<Emissive> emissivePtr = std::make_shared<Emissive>();
	emissivePtr->SetLadiance(40.0);
	emissivePtr->SetCe(white);

	std::shared_ptr<Rectangler> rectanglePtr = std::make_shared<Rectangler>(p0, a, b, normal);
	rectanglePtr->SetMaterial(emissivePtr);
	rectanglePtr->SetSampler(samplePtr);
	rectanglePtr->SetIsShadow(false);
	AddObject(rectanglePtr);

	std::shared_ptr<AreaLight> areaLightPtr = std::make_shared<AreaLight>();
	areaLightPtr->SetObject(rectanglePtr);
	areaLightPtr->SetIsShadow(true);
	AddLight(areaLightPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(-20, 10, 20);
	pinholePtr->SetLookAt(0, 2, 0);
	pinholePtr->SetViewDistance(1080);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	float box_width = 1.0; 		// x dimension
	float box_depth = 1.0; 		// z dimension
	float box_height = 4.5; 		// y dimension
	float gap = 3.0;

	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.25);
	matte_ptr1->SetKd(0.75);
	matte_ptr1->SetCd(0.4, 0.7, 0.4);     // green

	std::shared_ptr<Box> box_ptr0 = std::make_shared<Box>(
		Point3D(-1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth),
		Point3D(-1.5 * gap - box_width, box_height, 0.5 * box_depth));
	box_ptr0->SetMaterial(matte_ptr1);
	AddObject(box_ptr0);

	std::shared_ptr<Box> box_ptr1 = std::make_shared<Box>(
		Point3D(-0.5 * gap - box_width, 0.0, -0.5 * box_depth),
		Point3D(-0.5 * gap, box_height, 0.5 * box_depth));
	box_ptr1->SetMaterial(matte_ptr1->Clone());
	AddObject(box_ptr1);

	std::shared_ptr<Box> box_ptr2 = std::make_shared<Box>(
		Point3D(0.5 * gap, 0.0, -0.5 * box_depth),
		Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->SetMaterial(matte_ptr1->Clone());
	AddObject(box_ptr2);

	std::shared_ptr<Box> box_ptr3 = std::make_shared<Box>(
		Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth),
		Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->SetMaterial(matte_ptr1->Clone());
	AddObject(box_ptr3);

	// ground plane

	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.1);
	matte_ptr2->SetKd(0.9);
	matte_ptr2->SetCd(white);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr2);
	AddObject(plane_ptr);

}