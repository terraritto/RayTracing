void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(10);

	//set backgroundColor
	mBackGroundColor = RGBColor(0.15);

	//set Tracer
	mTracerPtr = std::make_shared<Whitted>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.5);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(75, 40, 100);
	pinholePtr->SetLookAt(-10, 39, 0);
	pinholePtr->SetViewDistance(360);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Add Light
	std::shared_ptr<PointLight> light_ptr = std::make_shared<PointLight>();
	light_ptr->SetLocation(150, 150, 0);
	light_ptr->SetScaleRadiance(3.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//set object
	std::shared_ptr<Reflective> reflective_ptr1 = std::make_shared<Reflective>();
	reflective_ptr1->SetKa(0.25);
	reflective_ptr1->SetKd(0.5);
	reflective_ptr1->SetCd(0.75, 0.75, 0);
	reflective_ptr1->SetKs(0.15);
	reflective_ptr1->SetExp(100.0);
	reflective_ptr1->SetKr(0.75);
	reflective_ptr1->SetCr(white);

	float radius = 23.0;
	std::shared_ptr<Sphere> sphere_ptr1 = std::make_shared<Sphere>(Point3D(38, radius, -25), radius);
	sphere_ptr1->SetMaterial(reflective_ptr1);
	AddObject(sphere_ptr1);

	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.45);
	matte_ptr1->SetKd(0.75);
	matte_ptr1->SetCd(0.75, 0.25, 0);

	std::shared_ptr<Sphere> sphere_ptr2 = std::make_shared<Sphere>(Point3D(-7, 10, 42), 20);
	sphere_ptr2->SetMaterial(matte_ptr1);
	AddObject(sphere_ptr2);

	std::shared_ptr<Reflective> reflective_ptr2 = std::make_shared<Reflective>();
	reflective_ptr2->SetKa(0.35);
	reflective_ptr2->SetKd(0.75);
	reflective_ptr2->SetCd(black);
	reflective_ptr2->SetKs(0.0);
	reflective_ptr2->SetExp(1.0);
	reflective_ptr2->SetKr(0.75);
	reflective_ptr2->SetCr(white);

	std::shared_ptr<Sphere> sphere_ptr3 = std::make_shared<Sphere>(Point3D(-30, 59, 35), 20);
	sphere_ptr3->SetMaterial(reflective_ptr2);
	AddObject(sphere_ptr3);

	std::shared_ptr<Reflective> reflective_ptr3 = std::make_shared<Reflective>();
	reflective_ptr3->SetKa(0.35);
	reflective_ptr3->SetKd(0.5);
	reflective_ptr3->SetCd(0, 0.5, 0.75);
	reflective_ptr3->SetKs(0.2);
	reflective_ptr3->SetExp(100.0);
	reflective_ptr3->SetKr(0.75);
	reflective_ptr3->SetCr(white);

	double bottom = 0.0;
	double top = 85;
	double cylinder_radius = 22;
	std::shared_ptr<SolidCylinder> cylinder_ptr = std::make_shared<SolidCylinder>(bottom, top, cylinder_radius);
	cylinder_ptr->SetMaterial(reflective_ptr3);
	AddObject(cylinder_ptr);

	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.15);
	matte_ptr2->SetKd(0.5);
	matte_ptr2->SetCd(0.75, 1.0, 0.75);

	std::shared_ptr<Box> box_ptr = std::make_shared<Box>(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->SetMaterial(matte_ptr2);
	AddObject(box_ptr);

	std::shared_ptr<Matte> matte_ptr3 = std::make_shared<Matte>();
	matte_ptr3->SetKa(0.30);
	matte_ptr3->SetKd(0.9);
	matte_ptr3->SetCd(white);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr3);
	AddObject(plane_ptr);
}