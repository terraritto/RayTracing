void World::Build()
{
	int numSamples = 1;

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
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<PointLight> lightPtr1 = std::make_shared<PointLight>();
	lightPtr1->SetLocation(1, 5, 0);
	lightPtr1->SetScaleRadiance(3.0);
	lightPtr1->SetIsShadow(true);
	AddLight(lightPtr1);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(25, 200, 100);
	pinholePtr->SetLookAt(-0.5, 0, 0);
	pinholePtr->SetViewDistance(8000);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Set Object
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.25);
	matte_ptr1->SetKd(0.75);
	matte_ptr1->SetCd(1, 1, 0);

	std::shared_ptr<Disk> disk_ptr1 = std::make_shared<Disk>(Point3D(-0.5, 0.0, 0.0), Normal(0, 1, 0), 3);
	disk_ptr1->SetMaterial(matte_ptr1);
	AddObject(disk_ptr1);
}