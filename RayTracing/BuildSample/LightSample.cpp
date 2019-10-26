void World::Build()
{
	int numSamples = 10;

	//set View Plane
	mViewPlane.SetHRes(500);
	mViewPlane.SetVRes(500);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(0, 0, 200);
	pinholePtr->SetLookAt(-5, 0, 0);
	pinholePtr->SetViewDistance(850.0);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Light
	std::shared_ptr<PointLight> lightPtr = std::make_shared<PointLight>();
	lightPtr->SetLocation(100, 50, 150);
	lightPtr->SetScaleRadiance(5.0);
	AddLight(lightPtr);

	/*
	std::shared_ptr<Directional> lightPtr = std::make_shared<Directional>();
	lightPtr->SetDirection(1, 1, 0);
	lightPtr->SetScaleRadiance(4.0);
	AddLight(lightPtr);
	*/
	//set object
	std::shared_ptr<Matte> mattePtr1 = std::make_shared<Matte>();
	mattePtr1->SetKa(0.25);
	mattePtr1->SetKd(0.65);
	mattePtr1->SetCd(1, 1, 0);
	std::shared_ptr<Sphere> spherePtr1 = std::make_shared<Sphere>(Point3D(10, -5, 0), 27);
	spherePtr1->SetMaterial(mattePtr1);
	AddObject(spherePtr1);

	std::shared_ptr<Matte> mattePtr2 = std::make_shared<Matte>();
	mattePtr2->SetKa(0.15);
	mattePtr2->SetKd(0.85);
	mattePtr2->SetCd(0.71, 0.40, 0.16);
	std::shared_ptr<Sphere> spherePtr2 = std::make_shared<Sphere>(Point3D(-25, 10, -35), 27);
	spherePtr2->SetMaterial(mattePtr2);
	AddObject(spherePtr2);

	std::shared_ptr<Matte> mattePtr3 = std::make_shared<Matte>();
	mattePtr3->SetKa(0.15);
	mattePtr3->SetKd(0.5);
	mattePtr3->SetCd(0, 0.4, 0.2);
	std::shared_ptr<Plane> planePtr = std::make_shared<Plane>(Point3D(0, 0, -50), Normal(0, 0, 1));
	planePtr->SetMaterial(mattePtr3);
	AddObject(planePtr);
}