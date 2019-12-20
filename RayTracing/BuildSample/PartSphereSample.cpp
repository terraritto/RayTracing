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
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<Directional> lightPtr1 = std::make_shared<Directional>();
	lightPtr1->SetDirection(200, 75, 100);
	lightPtr1->SetScaleRadiance(4.0);
	lightPtr1->SetIsShadow(true);
	AddLight(lightPtr1);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(5, 25, 20);
	pinholePtr->SetLookAt(0, 0, 0);
	pinholePtr->SetViewDistance(1500);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Set Object
	std::shared_ptr<Phong> phong_ptr1 = std::make_shared<Phong>();
	phong_ptr1->SetKa(0.25);
	phong_ptr1->SetKd(0.5);
	phong_ptr1->SetCd(1, 0, 0);
	phong_ptr1->SetKs(0.05);
	phong_ptr1->SetExp(5);

	std::shared_ptr<PartSphere> sphere_ptr1 = std::make_shared<PartSphere>();
	sphere_ptr1->SetMaterial(phong_ptr1);
	sphere_ptr1->SetPhi(0.0, PI);
	sphere_ptr1->SetTheta(0.0, PI / 2);
	AddObject(sphere_ptr1);

	//plane
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.15);
	matte_ptr1->SetKd(0.5);
	matte_ptr1->SetCd(1.0);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0, -2, 0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr1);
	AddObject(plane_ptr);
}