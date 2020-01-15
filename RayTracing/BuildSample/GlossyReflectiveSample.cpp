void World::Build()
{
	int numSamples = 256;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(10);

	//set Tracer
	mTracerPtr = std::make_shared<AreaLights>(this);

	//Main Light
	std::shared_ptr<MultiJittered> samplePtr = std::make_shared<MultiJittered>(numSamples);


	std::shared_ptr<AmbientOccluder> ambientPtr = std::make_shared<AmbientOccluder>();
	ambientPtr->SetRadiance(1.0);
	ambientPtr->SetColor(white);
	ambientPtr->SetMinAmount(0.5);
	ambientPtr->SetSampler(samplePtr);
	SetAmbientLight(ambientPtr);

	//Add Light
	std::shared_ptr<Directional> light_ptr = std::make_shared<Directional>();
	light_ptr->SetDirection(150, 250, -150);
	light_ptr->SetScaleRadiance(1.5);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	std::shared_ptr<Emissive> emissivePtr = std::make_shared<Emissive>();
	emissivePtr->SetLadiance(0.85);
	emissivePtr->SetCe(1.0, 1.0, 0.5);

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
	pinholePtr->SetLookAt(-10, 35, 0);
	pinholePtr->SetViewDistance(400);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//set object
	std::shared_ptr<GlossyReflector> glossy_ptr1 = std::make_shared<GlossyReflector>();
	glossy_ptr1->SetSamples(numSamples, 100.0);
	glossy_ptr1->SetKa(0.0);
	glossy_ptr1->SetKd(0.0);
	glossy_ptr1->SetKs(0.3);
	glossy_ptr1->SetExp(100.0);
	glossy_ptr1->SetCd(1.0, 1.0, 0.3);
	glossy_ptr1->SetKr(0.9);
	glossy_ptr1->SetExponent(100.0);
	glossy_ptr1->SetCr(1.0, 0.75, 0.5);

	//large sphere
	std::shared_ptr<Sphere> sphere_ptr1 = std::make_shared<Sphere>(Point3D(38, 20, -24), 20);
	sphere_ptr1->SetMaterial(glossy_ptr1);
	AddObject(sphere_ptr1);

	//small sphere
	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.4);
	matte_ptr2->SetKd(0.4);
	matte_ptr2->SetCd(0.75, 0.0, 0.0);

	std::shared_ptr<Sphere> sphere_ptr2 = std::make_shared<Sphere>(Point3D(34, 12, 13), 12);
	sphere_ptr2->SetMaterial(matte_ptr2);
	AddObject(sphere_ptr2);

	//medium sphere
	std::shared_ptr<Reflective> reflective_ptr1 = std::make_shared<Reflective>();
	reflective_ptr1->SetKa(0.0);
	reflective_ptr1->SetKd(0.0);
	reflective_ptr1->SetCd(0.75);
	reflective_ptr1->SetKs(0.0);
	reflective_ptr1->SetExp(20);
	reflective_ptr1->SetKr(0.9);
	reflective_ptr1->SetCr(1.0, 0.75, 0.5);


	std::shared_ptr<Sphere> sphere_ptr3 = std::make_shared<Sphere>(Point3D(-7, 15, 42), 16);
	sphere_ptr3->SetMaterial(reflective_ptr1);
	AddObject(sphere_ptr3);

	//cylinder
	std::shared_ptr<GlossyReflector> glossy_ptr2 = std::make_shared<GlossyReflector>();
	glossy_ptr2->SetSamples(numSamples, 10.0);
	glossy_ptr2->SetKa(0.0);
	glossy_ptr2->SetKd(0.0);
	glossy_ptr2->SetKs(0.75);
	glossy_ptr2->SetCs(0.35, 0.75, 0.55);
	glossy_ptr2->SetExp(10.0);
	glossy_ptr2->SetCd(1.0, 1.0, 0.3);
	glossy_ptr2->SetKr(0.9);
	glossy_ptr2->SetExponent(10.0);
	glossy_ptr2->SetCr(0.35, 0.75, 0.55);


	float bottom = 0.0;
	float top = 85;
	float radius = 22;
	std::shared_ptr<OpenCylinder> cylinder_ptr = std::make_shared<OpenCylinder>(bottom, top, radius);
	cylinder_ptr->SetMaterial(glossy_ptr2);
	AddObject(cylinder_ptr);

	// box
	std::shared_ptr<GlossyReflector> glossy_ptr3 = std::make_shared<GlossyReflector>();
	glossy_ptr3->SetSamples(numSamples, 1000.0);
	glossy_ptr3->SetKa(0.2);
	glossy_ptr3->SetKd(0.3);
	glossy_ptr3->SetKs(0.0);
	glossy_ptr3->SetExp(1000.0);
	glossy_ptr3->SetCd(0.4, 0.5, 1.0);
	glossy_ptr3->SetKr(0.9);
	glossy_ptr3->SetExponent(1000.0);
	glossy_ptr3->SetCr(0.4, 0.5, 1.0);


	std::shared_ptr<Box> box_ptr = std::make_shared<Box>(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->SetMaterial(glossy_ptr3);
	AddObject(box_ptr);

	// ground plane
	std::shared_ptr<GlossyReflector> glossy_ptr4 = std::make_shared<GlossyReflector>();
	glossy_ptr4->SetSamples(numSamples, 1.0);
	glossy_ptr4->SetKa(0.0);
	glossy_ptr4->SetKd(0.0);
	glossy_ptr4->SetKs(0.0);
	glossy_ptr4->SetExp(1.0);
	glossy_ptr4->SetCd(1.0, 1.0, 0.3);
	glossy_ptr4->SetKr(0.75);
	glossy_ptr4->SetExponent(1.0);
	glossy_ptr4->SetCr(1.0, 0.75, 0.5);


	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(glossy_ptr4);
	AddObject(plane_ptr);
}