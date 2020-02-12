void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(700);
	mViewPlane.SetVRes(700);
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
	std::shared_ptr<Pinhole> pinhole_ptr = std::make_shared<Pinhole>();
	pinhole_ptr->SetEye(0, 0, 65);
	pinhole_ptr->SetLookAt(0);
	pinhole_ptr->SetViewDistance(21000.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);

	//sub light
	std::shared_ptr<Directional> light_ptr1 = std::make_shared<Directional>();
	light_ptr1->SetDirection(-0.25, 0.4, 1);
	light_ptr1->SetScaleRadiance(2.5);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);

	//image
	std::shared_ptr<Image> image_ptr = std::make_shared<Image>();
	image_ptr->ReadPpmFile("Additional_Texture/TextureFiles/jpg/EarthHighRes.jpg");

	//mapping
	std::shared_ptr<SphericalMap> map_ptr = std::make_shared<SphericalMap>();

	// image texture
	std::shared_ptr<ImageTexture> texture_ptr = std::make_shared<ImageTexture>();
	texture_ptr->SetImage(image_ptr);
	texture_ptr->SetMapping(map_ptr);

	//set object
	std::shared_ptr<SV_Matte> sv_matte_ptr = std::make_shared<SV_Matte>();
	sv_matte_ptr->SetKa(0.20);
	sv_matte_ptr->SetKd(0.80);
	sv_matte_ptr->SetCd(texture_ptr);

	std::shared_ptr<Sphere> sphere_ptr = std::make_shared<Sphere>();
	sphere_ptr->SetMaterial(sv_matte_ptr);

	std::shared_ptr<Instance> earth_ptr = std::make_shared<Instance>(sphere_ptr);
	earth_ptr->RotateY(60);
	AddObject(earth_ptr);
}