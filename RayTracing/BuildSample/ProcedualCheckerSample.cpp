void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(880);
	mViewPlane.SetVRes(300);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(0);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);
	mBackGroundColor = RGBColor(0.5);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinhole_ptr = std::make_shared<Pinhole>();
	pinhole_ptr->SetEye(100, 100, 300);
	pinhole_ptr->SetLookAt(-0.2, 1.0, 0);
	pinhole_ptr->SetViewDistance(12000.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);


	//sub light
	std::shared_ptr<Directional> light_ptr1 = std::make_shared<Directional>();
	light_ptr1->SetDirection(0, 0, 1);
	light_ptr1->SetScaleRadiance(1.5);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);


	//set object

	//sphere
	std::shared_ptr<Checker3D> checker_ptr1 = std::make_shared<Checker3D>();

	std::shared_ptr<SV_Matte> sv_matte_ptr1 = std::make_shared<SV_Matte>();
	sv_matte_ptr1->SetKa(0.75);
	sv_matte_ptr1->SetKd(0.75);
	sv_matte_ptr1->SetCd(checker_ptr1);

	std::shared_ptr<Sphere> sphere_ptr = std::make_shared<Sphere>(Point3D(-9.5, -1, 0), 2.5);
	sphere_ptr->SetMaterial(sv_matte_ptr1);
	AddObject(sphere_ptr);

	//box
	std::shared_ptr<Checker3D> checker_ptr2 = std::make_shared<Checker3D>();

	std::shared_ptr<SV_Matte> sv_matte_ptr2 = std::make_shared<SV_Matte>();
	sv_matte_ptr2->SetKa(0.75);
	sv_matte_ptr2->SetKd(0.75);
	sv_matte_ptr2->SetCd(checker_ptr2);

	std::shared_ptr<Box> box_ptr = std::make_shared<Box>(Point3D(7, -1.0, -2), Point3D(11, 3, 2));
	box_ptr->SetMaterial(sv_matte_ptr2);
	AddObject(box_ptr);

	//plane
	std::shared_ptr<Checker3D> checker_ptr3 = std::make_shared<Checker3D>();
	checker_ptr3->SetSize(1.5);
	checker_ptr3->SetColor1(RGBColor(0.35));
	checker_ptr3->SetColor2(RGBColor(0.5));

	std::shared_ptr<SV_Matte> sv_matte_ptr3 = std::make_shared<SV_Matte>();
	sv_matte_ptr3->SetKa(0.75);
	sv_matte_ptr3->SetKd(0.75);
	sv_matte_ptr3->SetCd(checker_ptr3);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0, -4.5, 0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(sv_matte_ptr3);
	AddObject(plane_ptr);
}