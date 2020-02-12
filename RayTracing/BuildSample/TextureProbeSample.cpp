void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(900);
	mViewPlane.SetVRes(900);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));
	mViewPlane.SetMaxDepth(0);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);
	mBackGroundColor = black;

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<FishEye> fisheye_ptr = std::make_shared<FishEye>();
	fisheye_ptr->SetEye(0);
	fisheye_ptr->SetLookAt(0, 0, -100);
	fisheye_ptr->SetPsiMax(360);
	fisheye_ptr->ComputeUVW();
	SetCamera(fisheye_ptr);

	//sub light
	/*
	std::shared_ptr<Directional> light_ptr1 = std::make_shared<Directional>();
	light_ptr1->SetDirection(-0.25, 0.4, 1);
	light_ptr1->SetScaleRadiance(2.5);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);
	*/

	//image
	std::shared_ptr<Image> image_ptr = std::make_shared<Image>();
	image_ptr->ReadPpmFile("Additional_Texture/TextureFiles/jpg/EarthHighRes.jpg");

	//mapping
	std::shared_ptr<LightProbeMap> map_ptr = std::make_shared<LightProbeMap>();
	map_ptr->SetMapType(LightProbeMap::MapType::EPanoramic);

	// image texture
	std::shared_ptr<ImageTexture> texture_ptr = std::make_shared<ImageTexture>();
	texture_ptr->SetImage(image_ptr);
	texture_ptr->SetMapping(map_ptr);

	//set object
	std::shared_ptr<SV_Matte> sv_matte_ptr = std::make_shared<SV_Matte>();
	sv_matte_ptr->SetKa(1.0);
	sv_matte_ptr->SetKd(0.85);
	sv_matte_ptr->SetCd(texture_ptr);

	std::shared_ptr<Sphere> sphere_ptr = std::make_shared<Sphere>();

	std::shared_ptr<Instance> instance_ptr = std::make_shared<Instance>(sphere_ptr);
	instance_ptr->Scale(1000000.0);
	instance_ptr->SetMaterial(sv_matte_ptr);
	AddObject(instance_ptr);
}
