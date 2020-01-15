void World::Build()
{
	int numSamples = 100;

	//set View Plane
	mViewPlane.SetHRes(400);
	mViewPlane.SetVRes(300);
	mViewPlane.SetPixelSize(0.05);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(0);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);
	mBackGroundColor = white;

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.5);
	SetAmbientLight(ambientPtr);

	//sub Light
	std::shared_ptr<Directional> light_ptr = std::make_shared<Directional>();
	light_ptr->SetDirection(1, 1, 1);
	light_ptr->SetScaleRadiance(7.5);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	//Set Camera
	std::shared_ptr<ThinLens> thin_lens_ptr = std::make_shared<ThinLens>();
	thin_lens_ptr->SetSampler(std::make_shared<MultiJittered>(numSamples));
	thin_lens_ptr->SetEye(0, 6, 50);
	thin_lens_ptr->SetLookAt(0, 6, 0);
	thin_lens_ptr->SetViewDistance(40.0);
	thin_lens_ptr->SetFocalLength(50.0);
	thin_lens_ptr->SetLensRadius(1.0);
	thin_lens_ptr->ComputeUVW();
	SetCamera(thin_lens_ptr);

	//set object
	//box 1
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.5);
	matte_ptr1->SetKd(0.35);
	matte_ptr1->SetCd(1, 1, 0.33);

	std::shared_ptr<Box> box_ptr1 = std::make_shared<Box>(Point3D(-9, 0, -1), Point3D(-3, 12, 0));
	box_ptr1->SetMaterial(matte_ptr1);
	AddObject(box_ptr1);

	//box 2
	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.5);
	matte_ptr2->SetKd(0.35);
	matte_ptr2->SetCd(0.1, 1, 0.5);

	std::shared_ptr<Box> box_ptr2 = std::make_shared<Box>(Point3D(-3.25, 0, -25), Point3D(4.75, 14, -24));
	box_ptr2->SetMaterial(matte_ptr2);
	AddObject(box_ptr2);

	//box 3
	std::shared_ptr<Matte> matte_ptr3 = std::make_shared<Matte>();
	matte_ptr3->SetKa(0.5);
	matte_ptr3->SetKd(0.35);
	matte_ptr3->SetCd(1, 0.6, 0.15);

	std::shared_ptr<Box> box_ptr3 = std::make_shared<Box>(Point3D(8, 0, -49), Point3D(18, 15, -48));
	box_ptr3->SetMaterial(matte_ptr3);
	AddObject(box_ptr3);

	// ground plane
	std::shared_ptr<Matte> matte_ptr4 = std::make_shared<Matte>();
	matte_ptr4->SetKa(0.5);
	matte_ptr4->SetKd(0.35);
	matte_ptr4->SetCd(white);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr4);
	AddObject(plane_ptr);
}
