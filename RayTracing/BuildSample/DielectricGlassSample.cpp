void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(4);

	//set Tracer
	mTracerPtr = std::make_shared<Whitted>(this);
	mBackGroundColor = RGBColor(0.75);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinhole_ptr = std::make_shared<Pinhole>();
	pinhole_ptr->SetEye(10, 12, 20);
	pinhole_ptr->SetLookAt(-3.75, 3, 0);
	pinhole_ptr->SetViewDistance(1500.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);

	//sub light
	std::shared_ptr<PointLight> light_ptr1 = std::make_shared<PointLight>();
	light_ptr1->SetLocation(20, 25, -20);
	light_ptr1->SetScaleRadiance(3.0);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);

	//set object
	RGBColor glass_color(1.0, 1.0, 0.0);

	std::shared_ptr<Dielectric> glass_ptr = std::make_shared<Dielectric>();
	glass_ptr->SetEtaIn(1.5);
	glass_ptr->SetEtaOut(1.0);
	glass_ptr->SetCfIn(glass_color);
	glass_ptr->SetCfOut(white);
	glass_ptr->SetCs(1.0);

	double thickness = 0.25;
	double height = 4.0;
	double delta = 1.0;

	int num_boxes = 10;
	double x_min = -10.0;
	double gap = 0.5;

	for (int j = 0; j < num_boxes; j++)
	{
		double length = thickness + j * delta;
		Point3D p0(x_min + j * (thickness + gap), 0.0, -length);
		Point3D p1(x_min + j * (thickness + gap) + thickness, height, 0.0);

		std::shared_ptr<Box> box_ptr = std::make_shared<Box>(p0, p1);
		box_ptr->SetMaterial(glass_ptr);
		AddObject(box_ptr);
	}

	std::shared_ptr<Matte> matte_ptr = std::make_shared<Matte>();
	matte_ptr->SetKa(0.5);
	matte_ptr->SetKd(0.65);
	matte_ptr->SetCd(0.75);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr);
	AddObject(plane_ptr);
}
