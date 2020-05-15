void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.0, 0.6588, 1.0);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.5);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(7.5, 4, 10);
	pinholePtr->SetLookAt(-1, 3.7, 0);
	pinholePtr->SetViewDistance(340);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Light
	std::shared_ptr<Directional> lightPtr = std::make_shared<Directional>();
	lightPtr->SetDirection(15, 15, 2.5);
	lightPtr->SetScaleRadiance(3.0);
	lightPtr->SetIsShadow(true);
	AddLight(lightPtr);

	/*
	std::shared_ptr<PointLight> lightPtr2 = std::make_shared<PointLight>();
	lightPtr2->SetLocation(15, 15, 2.5);
	lightPtr2->SetScaleRadiance(2.0);
	lightPtr2->SetIsShadow(true);
	AddLight(lightPtr2);

	//std::shared_ptr<Directional> lightPtr3 = std::make_shared<Directional>();
	//lightPtr3->SetDirection(1, 1, 0);
	//lightPtr3->SetScaleRadiance(4.0);
	//AddLight(lightPtr3);
	*/

	//set object
	std::shared_ptr<CookTorrance> mattePtr1 = std::make_shared<CookTorrance>();
	mattePtr1->SetKa(0.25);
	mattePtr1->SetKd(0.75);
	mattePtr1->SetKs(0.25);
	mattePtr1->SetAlpha(0.4);
	mattePtr1->SetFresnel(0.5);
	mattePtr1->SetCd(1, 1, 0);
	mattePtr1->SetCs(0.2);

	mattePtr1->SetType(MicrofaseType::Beckmann);
	//mattePtr1->SetType(MicrofaseType::GGX);

	std::shared_ptr<Sphere> spherePtr1 = std::make_shared<Sphere>(Point3D(3.85, 2.3, -2.55), 2.3);
	spherePtr1->SetMaterial(mattePtr1);
	AddObject(spherePtr1);

	std::shared_ptr<CookTorrance> mattePtr2 = std::make_shared<CookTorrance>();
	mattePtr2->SetKa(0.45);
	mattePtr2->SetKd(0.75);
	mattePtr2->SetKs(0.25);
	mattePtr2->SetFresnel(0.5);
	mattePtr2->SetAlpha(0.2);
	mattePtr2->SetCd(0.75, 0.25, 0);
	mattePtr2->SetCs(0.2);

	mattePtr2->SetType(MicrofaseType::Beckmann);
	//mattePtr2->SetType(MicrofaseType::GGX);

	std::shared_ptr<Sphere> spherePtr2 = std::make_shared<Sphere>(Point3D(-0.7, 1, 4.2), 2);
	spherePtr2->SetMaterial(mattePtr2);
	AddObject(spherePtr2);

	std::shared_ptr<Matte> mattePtr3 = std::make_shared<Matte>();
	mattePtr3->SetKa(0.15);
	mattePtr3->SetKd(0.5);
	mattePtr3->SetCd(0, 0.4, 0.2);
	std::shared_ptr<Plane> planePtr = std::make_shared<Plane>(Point3D(0, 0, 0), Normal(0, 1, 0));
	planePtr->SetMaterial(mattePtr3);
	AddObject(planePtr);

}