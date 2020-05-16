void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(2);

	//set backgroundColor
	mBackGroundColor = black;

	//set Tracer
	mTracerPtr = std::make_shared<Whitted>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.25);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(7.5, 3, 9.5);
	pinholePtr->SetLookAt(0);
	pinholePtr->SetViewDistance(300.0);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Add Light
	std::shared_ptr<PointLight> light_ptr = std::make_shared<PointLight>();
	light_ptr->SetLocation(10, 10, 0);
	light_ptr->SetScaleRadiance(2.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	std::shared_ptr<PointLight> light_ptr_2 = std::make_shared<PointLight>();
	light_ptr_2->SetLocation(0, 10, 10);
	light_ptr_2->SetScaleRadiance(2.0);
	light_ptr_2->SetIsShadow(true);
	AddLight(light_ptr_2);

	std::shared_ptr<PointLight> light_ptr_3 = std::make_shared<PointLight>();
	light_ptr_3->SetLocation(-10, 10, 0);
	light_ptr_3->SetScaleRadiance(2.0);
	light_ptr_3->SetIsShadow(true);
	AddLight(light_ptr_3);

	std::shared_ptr<PointLight> light_ptr_4 = std::make_shared<PointLight>();
	light_ptr_4->SetLocation(0, 10, -10);
	light_ptr_4->SetScaleRadiance(2.0);
	light_ptr_4->SetIsShadow(true);
	AddLight(light_ptr_4);

	//set object
	//sphere
	std::shared_ptr<MicforasetReflective> reflective_ptr1 = std::make_shared<MicforasetReflective>();
	reflective_ptr1->SetKa(0.1);
	reflective_ptr1->SetKd(0.4);
	reflective_ptr1->SetCd(0, 0, 1);
	reflective_ptr1->SetKs(0.25);
	reflective_ptr1->SetKr(0.85);
	reflective_ptr1->SetCr(0.75, 0.75, 1);
	reflective_ptr1->SetAlpha(0.5);
	reflective_ptr1->SetFresnel(0.5);
	reflective_ptr1->SetCs(0.2, 0.2, 0.2);

	std::shared_ptr<Sphere> sphere_ptr1 = std::make_shared<Sphere>(Point3D(0, 0.5, 0), 4);
	sphere_ptr1->SetMaterial(reflective_ptr1);
	AddObject(sphere_ptr1);

	//room
	double room_size = 11.0;

	//floor
	std::shared_ptr<Matte> matte_ptr1 = std::make_shared<Matte>();
	matte_ptr1->SetKa(0.1);
	matte_ptr1->SetKd(0.50);
	matte_ptr1->SetCd(0.25);

	std::shared_ptr<Plane> floor_ptr = std::make_shared<Plane>(Point3D(0, -room_size, 0), Normal(0, 1, 0));
	floor_ptr->SetMaterial(matte_ptr1);
	AddObject(floor_ptr);

	//ceiling
	std::shared_ptr<Matte> matte_ptr2 = std::make_shared<Matte>();
	matte_ptr2->SetKa(0.35);
	matte_ptr2->SetKd(0.50);
	matte_ptr2->SetCd(white);

	std::shared_ptr<Plane> ceiling_ptr = std::make_shared<Plane>(Point3D(0, room_size, 0), Normal(0, -1, 0));
	ceiling_ptr->SetMaterial(matte_ptr2);
	AddObject(ceiling_ptr);

	//back wall
	std::shared_ptr<Matte> matte_ptr3 = std::make_shared<Matte>();
	matte_ptr3->SetKa(0.15);
	matte_ptr3->SetKd(0.60);
	matte_ptr3->SetCd(0.5, 0.75, 0.75);

	std::shared_ptr<Plane> backWall_ptr = std::make_shared<Plane>(Point3D(0, 0, -room_size), Normal(0, 0, 1));
	backWall_ptr->SetMaterial(matte_ptr3);
	AddObject(backWall_ptr);

	//front wall
	std::shared_ptr<Plane> frontWall_ptr = std::make_shared<Plane>(Point3D(0, 0, -room_size), Normal(0, 0, 1));
	frontWall_ptr->SetMaterial(matte_ptr3);
	AddObject(frontWall_ptr);

	//left wall
	std::shared_ptr<Matte> matte_ptr4 = std::make_shared<Matte>();
	matte_ptr4->SetKa(0.15);
	matte_ptr4->SetKd(0.60);
	matte_ptr4->SetCd(0.71, 0.40, 0.20);

	std::shared_ptr<Plane> leftWall_ptr = std::make_shared<Plane>(Point3D(-room_size, 0, 0), Normal(1, 0, 0));
	leftWall_ptr->SetMaterial(matte_ptr4);
	AddObject(leftWall_ptr);

	//right wall
	std::shared_ptr<Plane> rightWall_ptr = std::make_shared<Plane>(Point3D(room_size, 0, 0), Normal(-1, 0, 0));
	rightWall_ptr->SetMaterial(matte_ptr4);
	AddObject(rightWall_ptr);

	//mirror wall
	double mirror_size = 8.0;
	double offset = 1.0;

	std::shared_ptr<MicforasetReflective> reflective_ptr2 = std::make_shared<MicforasetReflective>();
	reflective_ptr2->SetKa(0);
	reflective_ptr2->SetKd(0);
	reflective_ptr2->SetCd(black);
	reflective_ptr2->SetKs(0);
	reflective_ptr2->SetKr(0.9);
	reflective_ptr2->SetCr(0.9, 1.0, 0.9);
	reflective_ptr2->SetAlpha(0.9);
	reflective_ptr2->SetFresnel(0.5);

	//back wall mirror
	Point3D p0;
	Vector3D a, b;

	p0 = Point3D(-mirror_size, -mirror_size, -(room_size - offset));
	a = Vector3D(2.0 * mirror_size, 0, 0);
	b = Vector3D(0, 2.0 * mirror_size, 0);
	Normal n(0, 0, 1);

	std::shared_ptr<Rectangler> rectangle_ptr1 = std::make_shared<Rectangler>(p0, a, b, n);
	rectangle_ptr1->SetMaterial(reflective_ptr2);
	AddObject(rectangle_ptr1);

	//front wall mirror
	p0 = Point3D(-mirror_size, -mirror_size, +(room_size - offset));
	n = Normal(0, 0, -1);

	std::shared_ptr<Rectangler> rectangle_ptr2 = std::make_shared<Rectangler>(p0, a, b, n);
	rectangle_ptr2->SetMaterial(reflective_ptr2);
	AddObject(rectangle_ptr2);

	//left wall mirror
	p0 = Point3D(-(room_size - offset), -mirror_size, +mirror_size);
	a = Vector3D(0, 0, -2.0 * mirror_size);
	n = Normal(1, 0, 0);

	std::shared_ptr<Rectangler> rectangle_ptr3 = std::make_shared<Rectangler>(p0, a, b, n);
	rectangle_ptr3->SetMaterial(reflective_ptr2);
	AddObject(rectangle_ptr3);

	//horizontal mirror
	std::shared_ptr<MicforasetReflective> reflective_ptr3 = std::make_shared<MicforasetReflective>();
	reflective_ptr3->SetKa(0);
	reflective_ptr3->SetKd(0);
	reflective_ptr3->SetCd(black);
	reflective_ptr3->SetKs(0);
	reflective_ptr3->SetKr(1);
	reflective_ptr3->SetCr(1, 1, 0.5);
	reflective_ptr3->SetAlpha(0.9);
	reflective_ptr3->SetFresnel(0.5);

	double yw = -4.0;

	p0 = Point3D(-mirror_size, yw, -mirror_size);
	a = Vector3D(0, 0, 2.0 * mirror_size);
	b = Vector3D(2.0 * mirror_size, 0, 0);
	n = Normal(0, 1, 0);

	std::shared_ptr<Rectangler> rectangle_ptr4 = std::make_shared<Rectangler>(p0, a, b, n);
	rectangle_ptr4->SetMaterial(reflective_ptr3);
	AddObject(rectangle_ptr4);
}