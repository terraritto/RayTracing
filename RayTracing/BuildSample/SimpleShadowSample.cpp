void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.0, 0.3 * 0.75, 0.25 * 0.75);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.5);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(0, 7, 10);
	pinholePtr->SetLookAt(0, -1.5, 0);
	pinholePtr->SetViewDistance(1200);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Light
	std::shared_ptr<PointLight> lightPtr1 = std::make_shared<PointLight>();
	lightPtr1->SetLocation(3, 10, 2);
	lightPtr1->SetScaleRadiance(12.0);
	lightPtr1->SetColor(1, 0, 0);
	lightPtr1->SetIsShadow(true);
	AddLight(lightPtr1);

	std::shared_ptr<PointLight> lightPtr2 = std::make_shared<PointLight>();
	lightPtr2->SetLocation(-3, 10, 2);
	lightPtr2->SetScaleRadiance(12.0);
	lightPtr2->SetColor(0, 1, 0);
	lightPtr2->SetIsShadow(true);
	AddLight(lightPtr2);

	std::shared_ptr<PointLight> lightPtr3 = std::make_shared<PointLight>();
	lightPtr3->SetLocation(0, 10, 3);
	lightPtr3->SetScaleRadiance(12.0);
	lightPtr3->SetColor(0, 0, 1);
	lightPtr3->SetIsShadow(true);
	AddLight(lightPtr3);
	/*
	std::shared_ptr<Directional> lightPtr = std::make_shared<Directional>();
	lightPtr->SetDirection(0, 0, 1);
	lightPtr->SetScaleRadiance(4.0);
	AddLight(lightPtr);
	*/
	//set object
	std::shared_ptr<Matte> mattePtr1 = std::make_shared<Matte>();
	mattePtr1->SetKa(0.6);
	mattePtr1->SetKd(0.2);
	mattePtr1->SetCd(0.5);
	std::shared_ptr<Sphere> spherePtr1 = std::make_shared<Sphere>();
	spherePtr1->SetMaterial(mattePtr1);
	AddObject(spherePtr1);

	std::shared_ptr<Matte> mattePtr3 = std::make_shared<Matte>();
	mattePtr3->SetKa(0.0);
	mattePtr3->SetKd(0.35);
	mattePtr3->SetCd(0.7);
	std::shared_ptr<Plane> planePtr = std::make_shared<Plane>(Point3D(0, -3, 0), Normal(0, 1, 0));
	planePtr->SetMaterial(mattePtr3);
	AddObject(planePtr);
}