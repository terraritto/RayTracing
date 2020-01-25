void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(5);

	//set Tracer
	mTracerPtr = std::make_shared<Whitted>(this);
	mBackGroundColor = RGBColor(0.0, 0.3, 0.25);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.25);
	SetAmbientLight(ambientPtr);

	//sub Light
	std::shared_ptr<PointLight> light_ptr = std::make_shared<PointLight>();
	light_ptr->SetLocation(40, 50, 0);
	light_ptr->SetScaleRadiance(4.0);
	light_ptr->SetIsShadow(true);
	AddLight(light_ptr);

	std::shared_ptr<PointLight> light_ptr2 = std::make_shared<PointLight>();
	light_ptr2->SetLocation(-10, 20, 10);
	light_ptr2->SetScaleRadiance(4.0);
	light_ptr2->SetIsShadow(true);
	AddLight(light_ptr2);

	std::shared_ptr<Directional> light_ptr3 = std::make_shared<Directional>();
	light_ptr3->SetDirection(-1, 0, 0);
	light_ptr3->SetScaleRadiance(4.0);
	light_ptr3->SetIsShadow(true);
	AddLight(light_ptr3);

	//Set Camera
	std::shared_ptr<Pinhole> pinhole_ptr = std::make_shared<Pinhole>();
	pinhole_ptr->SetEye(-5, 5.5, 35);
	pinhole_ptr->SetLookAt(1.25, 3.5, 0);
	pinhole_ptr->SetViewDistance(2400.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);

	//set object
	//transparent bunny
	std::shared_ptr<Transparent> glass_ptr = std::make_shared<Transparent>();
	glass_ptr->SetKs(0.2);
	glass_ptr->SetExp(2000.0);
	glass_ptr->SetIor(1.5);
	glass_ptr->SetKr(0.1);
	glass_ptr->SetKt(0.9);
	glass_ptr->SetCs(1.0);

	const std::string fileName = "./Additional_File/PLYFiles/bunny/reconstruction/bun_zipper_res4.ply";
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	grid_ptr->ReadTriangles(fileName, Grid::ETriangleType::smooth);
	grid_ptr->SetMaterial(glass_ptr);
	grid_ptr->SetupCells();

	std::shared_ptr<Instance> big_bunny_ptr = std::make_shared<Instance>(grid_ptr);
	big_bunny_ptr->Scale(45.0);
	big_bunny_ptr->Translate(1.7, -1.5, 0.0);
	AddObject(big_bunny_ptr);

	// red sphere
	std::shared_ptr<Reflective> reflective_ptr = std::make_shared<Reflective>();
	reflective_ptr->SetKa(0.3);
	reflective_ptr->SetKd(0.3);
	reflective_ptr->SetCd(1.0, 0.0, 0.0);
	reflective_ptr->SetKs(0.2);
	reflective_ptr->SetExp(2000.0);
	reflective_ptr->SetKr(0.25);
	reflective_ptr->SetCs(1.0);

	std::shared_ptr<Sphere> sphere_ptr2 = std::make_shared<Sphere>(Point3D(4, 4, -6), 3);
	sphere_ptr2->SetMaterial(reflective_ptr);
	AddObject(sphere_ptr2);

	//rectangle
	std::shared_ptr<Matte> matte_ptr = std::make_shared<Matte>();
	matte_ptr->SetKa(0.5);
	matte_ptr->SetKd(0.35);
	matte_ptr->SetCd(white);

	Point3D p0(-20, 0, -100);
	Vector3D a(0, 0, 120);
	Vector3D b(40, 0, 0);

	std::shared_ptr<Rectangler> rectangle_ptr = std::make_shared<Rectangler>(p0, a, b);
	rectangle_ptr->SetMaterial(matte_ptr);
	AddObject(rectangle_ptr);
}
