void World::Build()
{
	int numSamples = 100;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.5);

	//set Tracer
	mTracerPtr = std::make_shared<AreaLights>(this);

	//Main Light
	std::shared_ptr<MultiJittered> samplePtr = std::make_shared<MultiJittered>(numSamples);


	std::shared_ptr<AmbientOccluder> ambientPtr = std::make_shared<AmbientOccluder>();
	ambientPtr->SetRadiance(1.0);
	ambientPtr->SetColor(white);
	ambientPtr->SetMinAmount(0.5);
	ambientPtr->SetSampler(samplePtr);
	SetAmbientLight(ambientPtr); //for(A) & (C)


	/*
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);
	*/

	//Add Light
	std::shared_ptr<Emissive> emissivePtr = std::make_shared<Emissive>();
	emissivePtr->SetLadiance(0.9);
	emissivePtr->SetCe(white);

	std::shared_ptr<ConcaveSphere> sphere_ptr = std::make_shared<ConcaveSphere>();
	sphere_ptr->SetRadius(1000000.0);
	sphere_ptr->SetMaterial(emissivePtr);
	sphere_ptr->SetIsShadow(false);
	AddObject(sphere_ptr);

	std::shared_ptr<EnvironmentLight> environmentLightPtr = std::make_shared<EnvironmentLight>();
	environmentLightPtr->SetMaterial(emissivePtr);
	environmentLightPtr->SetSampler(samplePtr->Clone());
	environmentLightPtr->SetIsShadow(true);
	AddLight(environmentLightPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(100, 45, 100);
	pinholePtr->SetLookAt(-10, 40, 0);
	pinholePtr->SetViewDistance(400);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	float ka = 0.2;
	float ks = 1.0;
	float exp = 10.0;
	RGBColor cs(1, 0, 0);
	//large sphere
	std::shared_ptr<Phong> phong_ptr1 = std::make_shared<Phong>();
	phong_ptr1->SetKa(ka);
	phong_ptr1->SetKd(0.60);
	phong_ptr1->SetCd(0.75);
	phong_ptr1->SetKs(ks);
	phong_ptr1->SetExp(exp);
	phong_ptr1->SetCs(cs);

	std::shared_ptr<Sphere> sphere_ptr1 = std::make_shared<Sphere>(Point3D(38, 20, -24), 20);
	sphere_ptr1->SetMaterial(phong_ptr1);
	AddObject(sphere_ptr1);

	//small sphere
	std::shared_ptr<Phong> phong_ptr2 = std::make_shared<Phong>();
	phong_ptr2->SetKa(ka);
	phong_ptr2->SetKd(0.50);
	phong_ptr2->SetCd(0.95);
	phong_ptr2->SetKs(ks);
	phong_ptr2->SetExp(exp);
	phong_ptr2->SetCs(cs);

	std::shared_ptr<Sphere> sphere_ptr2 = std::make_shared<Sphere>(Point3D(34, 12, 13), 12);
	sphere_ptr2->SetMaterial(phong_ptr2);
	AddObject(sphere_ptr2);

	//medium sphere
	std::shared_ptr<Phong> phong_ptr3 = std::make_shared<Phong>();
	phong_ptr3->SetKa(ka);
	phong_ptr3->SetKd(0.50);
	phong_ptr3->SetCd(0.75);
	phong_ptr3->SetKs(ks);
	phong_ptr3->SetExp(exp);
	phong_ptr3->SetCs(cs);

	std::shared_ptr<Sphere> sphere_ptr3 = std::make_shared<Sphere>(Point3D(-7, 15, 42), 16);
	sphere_ptr3->SetMaterial(phong_ptr3);
	AddObject(sphere_ptr3);

	// box
	std::shared_ptr<Phong> phong_ptr5 = std::make_shared<Phong>();
	phong_ptr5->SetKa(ka);
	phong_ptr5->SetKd(0.50);
	phong_ptr5->SetCd(0.95);
	phong_ptr5->SetKs(ks);
	phong_ptr5->SetExp(exp);
	phong_ptr5->SetCs(cs);

	std::shared_ptr<Box> box_ptr = std::make_shared<Box>(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->SetMaterial(phong_ptr5);
	AddObject(box_ptr);

	// ground plane
	std::shared_ptr<Matte> matte_ptr6 = std::make_shared<Matte>();
	matte_ptr6->SetKa(0.15);
	matte_ptr6->SetKd(0.5);
	matte_ptr6->SetCd(0.7);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr6);
	AddObject(plane_ptr);
}
