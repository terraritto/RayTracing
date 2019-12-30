void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(400);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.5);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<MultiJittered> samplePtr = std::make_shared<MultiJittered>(numSamples);


	std::shared_ptr<AmbientOccluder> ambientPtr = std::make_shared<AmbientOccluder>();
	ambientPtr->SetRadiance(1.0);
	ambientPtr->SetColor(white);
	ambientPtr->SetMinAmount(0.5);
	ambientPtr->SetSampler(samplePtr);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<PointLight> light_ptr = std::make_shared<PointLight>();
	light_ptr->SetLocation(50, 50, 1);
	light_ptr->SetScaleRadiance(3.0);
	AddLight(light_ptr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(100, 0, 100);
	pinholePtr->SetLookAt(0, 1, 0);
	pinholePtr->SetViewDistance(8000);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	std::shared_ptr<Phong> phong_ptr = std::make_shared<Phong>();
	phong_ptr->SetCd(0.75);
	phong_ptr->SetKa(0.25);
	phong_ptr->SetKd(0.8);
	phong_ptr->SetKs(0.15);
	phong_ptr->SetExp(50);

	std::shared_ptr<Instance> ellipsoid_ptr = std::make_shared<Instance>(std::make_shared<Sphere>());
	ellipsoid_ptr->SetMaterial(phong_ptr);
	ellipsoid_ptr->Scale(2, 3, 1);
	ellipsoid_ptr->RotateX(-45);
	ellipsoid_ptr->Translate(0, 1, 0);
	AddObject(ellipsoid_ptr);
}