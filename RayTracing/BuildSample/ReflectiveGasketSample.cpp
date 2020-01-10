void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(800);
	mViewPlane.SetVRes(800);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(12);

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<Whitted>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.5);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	//four sphere
	/*
	pinholePtr->SetEye(-35, 25, 35);
	pinholePtr->SetLookAt(0.0, 0.4, -0.2);
	pinholePtr->SetViewDistance(5500.0);
	*/

	// sierpinski gasket
	pinholePtr->SetEye(0.0, 0.05, 0.0);
	pinholePtr->SetLookAt(0.0, 1.0, 0.0);
	pinholePtr->SetViewDistance(600.0);

	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Add Light
	// if four sphere render,it's light add.
	/*
	std::shared_ptr<PointLight> light_ptr = std::make_shared<PointLight>();
	light_ptr->SetLocation(0, 20, 20);
	light_ptr->SetScaleRadiance(5.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);
	*/

	//set object
	//sphere
	float ka = 0.75f;
	float kd = 0.75f;
	float ks = 0.1f;
	float e = 20.0f;
	float kr = 1.0f;

	std::shared_ptr<Reflective> reflective_ptr1 = std::make_shared<Reflective>();
	reflective_ptr1->SetKa(ka);
	reflective_ptr1->SetKd(kd);
	reflective_ptr1->SetCd(0.168, 0.171, 0.009);
	reflective_ptr1->SetKs(ks);
	reflective_ptr1->SetExp(e);
	reflective_ptr1->SetKr(kr);

	std::shared_ptr<Sphere> sphere_ptr1 = std::make_shared<Sphere>(Point3D(0.0, 1.414, 0.0), 0.866);
	sphere_ptr1->SetMaterial(reflective_ptr1);
	AddObject(sphere_ptr1);

	std::shared_ptr<Reflective> reflective_ptr2 = std::make_shared<Reflective>();
	reflective_ptr2->SetKa(ka);
	reflective_ptr2->SetKd(kd);
	reflective_ptr2->SetCd(0.094, 0.243, 0.029);
	reflective_ptr2->SetKs(ks);
	reflective_ptr2->SetExp(e);
	reflective_ptr2->SetKr(kr);

	std::shared_ptr<Sphere> sphere_ptr2 = std::make_shared<Sphere>(Point3D(0.0, 0.0, 1.0), 0.866);
	sphere_ptr2->SetMaterial(reflective_ptr2);
	AddObject(sphere_ptr2);

	std::shared_ptr<Reflective> reflective_ptr3 = std::make_shared<Reflective>();
	reflective_ptr3->SetKa(ka);
	reflective_ptr3->SetKd(kd);
	reflective_ptr3->SetCd(0.243, 0.018, 0.164);
	reflective_ptr3->SetKs(ks);
	reflective_ptr3->SetExp(e);
	reflective_ptr3->SetKr(kr);

	std::shared_ptr<Sphere> sphere_ptr3 = std::make_shared<Sphere>(Point3D(0.866, 0.0, -0.5), 0.866);
	sphere_ptr3->SetMaterial(reflective_ptr3);
	AddObject(sphere_ptr3);

	std::shared_ptr<Reflective> reflective_ptr4 = std::make_shared<Reflective>();
	reflective_ptr4->SetKa(ka);
	reflective_ptr4->SetKd(kd);
	reflective_ptr4->SetCd(0.094, 0.100, 0.243);
	reflective_ptr4->SetKs(ks);
	reflective_ptr4->SetExp(e);
	reflective_ptr4->SetKr(kr);

	std::shared_ptr<Sphere> sphere_ptr4 = std::make_shared<Sphere>(Point3D(-0.866, 0.0, -0.5), 0.866);
	sphere_ptr4->SetMaterial(reflective_ptr4);
	AddObject(sphere_ptr4);
}