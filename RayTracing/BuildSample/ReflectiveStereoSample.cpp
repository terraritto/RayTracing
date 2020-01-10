void World::Build()
{
	int numSamples = 25;

	//set View Plane
	mViewPlane.SetHRes(400);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(10);

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<Whitted>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.25);
	SetAmbientLight(ambientPtr);

	//Set Camera
	float vpd = 2400.0f;

	std::shared_ptr<Pinhole> left_pinholePtr = std::make_shared<Pinhole>();
	left_pinholePtr->SetViewDistance(vpd);

	std::shared_ptr<Pinhole> right_pinholePtr = std::make_shared<Pinhole>();
	right_pinholePtr->SetViewDistance(vpd);

	std::shared_ptr<StereoCamera> stereo_ptr = std::make_shared<StereoCamera>();
	stereo_ptr->SetRightCamera(right_pinholePtr);
	stereo_ptr->SetLeftCamera(left_pinholePtr);
	stereo_ptr->UseParallelViewing();
	stereo_ptr->SetPixelGap(5);
	stereo_ptr->SetEye(-8, 20, 40);
	stereo_ptr->SetLookAt(0, 4.5, 0);
	stereo_ptr->ComputeUVW();
	stereo_ptr->SetStereoAngle(1.5);
	stereo_ptr->SetupCameras();
	SetCamera(stereo_ptr);

	//Add Light
	std::shared_ptr<PointLight> light_ptr = std::make_shared<PointLight>();
	light_ptr->SetLocation(40, 50, 0);
	light_ptr->SetScaleRadiance(5.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	std::shared_ptr<PointLight> light_ptr_2 = std::make_shared<PointLight>();
	light_ptr_2->SetLocation(-10, 20, 10);
	light_ptr_2->SetScaleRadiance(4.0);
	light_ptr_2->SetIsShadow(true);
	AddLight(light_ptr_2);

	std::shared_ptr<Directional> light_ptr_3 = std::make_shared<Directional>();
	light_ptr_3->SetDirection(-1, 0, 0);
	light_ptr_3->SetScaleRadiance(4.0);
	light_ptr_3->SetIsShadow(true);
	AddLight(light_ptr_3);

	//set object
	//---
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.45);
	matte_ptr1->SetKd(0.75);
	matte_ptr1->SetCd(0.75, 0.25, 0);

	std::shared_ptr<Sphere> sphere_ptr2 = std::make_shared<Sphere>();
	sphere_ptr2->SetMaterial(matte_ptr1);

	std::shared_ptr<Instance> instance_ptr1 = std::make_shared<Instance>(sphere_ptr2);
	instance_ptr1->Scale(30);
	instance_ptr1->Translate(0, 50, 45);
	AddObject(instance_ptr1);
	//---
	//---
	std::shared_ptr<Reflective> reflective_ptr1 = std::make_shared<Reflective>();
	reflective_ptr1->SetKa(0.0);
	reflective_ptr1->SetKd(0.0);
	reflective_ptr1->SetCd(1.0);
	reflective_ptr1->SetKs(0.15);
	reflective_ptr1->SetExp(300.0);
	reflective_ptr1->SetKr(0.9);
	reflective_ptr1->SetCr(RGBColor(1.0, 0.75, 0.25));

	std::shared_ptr<Sphere> sphere_ptr = std::make_shared<Sphere>();
	sphere_ptr->SetMaterial(reflective_ptr1);

	std::shared_ptr<Instance> instance_ptr2 = std::make_shared<Instance>(sphere_ptr);
	instance_ptr2->Scale(3.0);
	instance_ptr2->Translate(0, 4.5, 0);
	AddObject(instance_ptr2);

	//---
	//---
	std::shared_ptr<Matte> matte_ptr3 = std::make_shared<Matte>();
	matte_ptr3->SetKa(0.30);
	matte_ptr3->SetKd(0.9);
	matte_ptr3->SetCd(white);

	std::shared_ptr<Rectangler> plane_ptr = std::make_shared<Rectangler>(
		Point3D(-20, -0.001, -100),
		Vector3D(0, 0, 120),
		Vector3D(40, 0, 0),
		Normal(0, 1, 0)
		);
	plane_ptr->SetMaterial(matte_ptr3);
	AddObject(plane_ptr);
	//---
}