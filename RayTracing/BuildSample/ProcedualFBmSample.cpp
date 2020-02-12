void World::Build()
{
	int numSamples = 1;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(600);
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
	pinhole_ptr->SetEye(0, 0, 100);
	pinhole_ptr->SetLookAt(0.0);
	pinhole_ptr->SetViewDistance(4750.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);


	//sub light
	std::shared_ptr<PointLight> light_ptr1 = std::make_shared<PointLight>();
	light_ptr1->SetLocation(10, 10, 20);
	light_ptr1->SetScaleRadiance(2.5);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);


	//set object
	// noise
	std::shared_ptr<CubicNoise> noise_ptr = std::make_shared<CubicNoise>();
	noise_ptr->SetOctaves(2);
	noise_ptr->SetGain(0.25);
	noise_ptr->SetLacunarity(4);

	//texture
	std::shared_ptr<WrappedTexture> texture_ptr = std::make_shared<WrappedTexture>();
	texture_ptr->SetNoise(noise_ptr);
	texture_ptr->SetColor(RGBColor(0.7, 1.0, 0.5));
	texture_ptr->SetExpansionNumber(2);

	// material
	std::shared_ptr<SV_Matte> matte_ptr = std::make_shared<SV_Matte>();
	matte_ptr->SetKa(0.25);
	matte_ptr->SetKd(0.85);
	matte_ptr->SetCd(texture_ptr);

	// sphere
	std::shared_ptr<Sphere> sphere_ptr = std::make_shared<Sphere>(Point3D(0.0), 6.0);
	sphere_ptr->SetMaterial(matte_ptr);
	AddObject(sphere_ptr);
}
