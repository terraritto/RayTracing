void World::Build()
{
	int numSamples = 100;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(5);

	//set Tracer
	mTracerPtr = std::make_shared<PathTrace>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Add Object
	std::shared_ptr<Emissive> emissivePtr = std::make_shared<Emissive>();
	emissivePtr->SetLadiance(1.5);
	emissivePtr->SetCe(white);

	std::shared_ptr<ConcaveSphere> sphere_ptr = std::make_shared<ConcaveSphere>();
	sphere_ptr->SetRadius(1000000.0);
	sphere_ptr->SetMaterial(emissivePtr);
	sphere_ptr->SetIsShadow(false);
	AddObject(sphere_ptr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(100, 45, 100);
	pinholePtr->SetLookAt(-10, 40, 0);
	pinholePtr->SetViewDistance(400);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	float ka = 0.2;

	//large sphere
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(ka);
	matte_ptr1->SetKd(0.60);
	matte_ptr1->SetCd(white);
	matte_ptr1->SetSamples(numSamples);

	std::shared_ptr<Sphere> sphere_ptr1 = std::make_shared<Sphere>(Point3D(38, 20, -24), 20);
	sphere_ptr1->SetMaterial(matte_ptr1);
	AddObject(sphere_ptr1);

	//small sphere
	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(ka);
	matte_ptr2->SetKd(0.5);
	matte_ptr2->SetCd(0.85);
	matte_ptr2->SetSamples(numSamples);

	std::shared_ptr<Sphere> sphere_ptr2 = std::make_shared<Sphere>(Point3D(34, 12, 13), 12);
	sphere_ptr2->SetMaterial(matte_ptr2);
	AddObject(sphere_ptr2);

	//medium sphere
	std::shared_ptr<Reflective> reflective_ptr2 = std::make_shared<Reflective>();
	reflective_ptr2->SetKa(0.35);
	reflective_ptr2->SetKd(0.75);
	reflective_ptr2->SetCd(black);
	reflective_ptr2->SetKs(0.0);
	reflective_ptr2->SetExp(1.0);
	reflective_ptr2->SetKr(0.75);
	reflective_ptr2->SetCr(white);

	std::shared_ptr<Sphere> sphere_ptr3 = std::make_shared<Sphere>(Point3D(-7, 15, 42), 16);
	sphere_ptr3->SetMaterial(reflective_ptr2);
	AddObject(sphere_ptr3);

	//cylinder
	std::shared_ptr<Matte> matte_ptr4 = std::make_shared<Matte>();
	matte_ptr4->SetKa(ka);
	matte_ptr4->SetKd(0.75);
	matte_ptr4->SetCd(0.60);
	matte_ptr4->SetSamples(numSamples);

	float bottom = 0.0;
	float top = 85;
	float radius = 22;
	std::shared_ptr<SolidCylinder> cylinder_ptr = std::make_shared<SolidCylinder>(bottom, top, radius);
	cylinder_ptr->SetMaterial(matte_ptr4);
	AddObject(cylinder_ptr);

	// box
	std::shared_ptr<Matte> matte_ptr5 = std::make_shared<Matte>();
	matte_ptr5->SetKa(ka);
	matte_ptr5->SetKd(0.75);
	matte_ptr5->SetCd(0.95);
	matte_ptr5->SetSamples(numSamples);

	std::shared_ptr<Box> box_ptr = std::make_shared<Box>(Point3D(-55, 0, -110), Point3D(-25, 60, 65));
	box_ptr->SetMaterial(matte_ptr5);
	AddObject(box_ptr);

	// ground plane
	std::shared_ptr<Matte> matte_ptr6 = std::make_shared<Matte>();
	matte_ptr6->SetKa(0.15);
	matte_ptr6->SetKd(0.95);
	matte_ptr6->SetCd(0.37, 0.43, 0.08);
	matte_ptr6->SetSampler(std::make_shared<MultiJittered>(numSamples));

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr6);
	AddObject(plane_ptr);
}