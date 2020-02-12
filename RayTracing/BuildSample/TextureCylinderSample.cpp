void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(400);
	mViewPlane.SetVRes(400);
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
	pinhole_ptr->SetEye(2, 3.5, 5);
	pinhole_ptr->SetLookAt(0);
	pinhole_ptr->SetViewDistance(800.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);

	//sub light
	std::shared_ptr<Directional> light_ptr1 = std::make_shared<Directional>();
	light_ptr1->SetDirection(14, 20, 25);
	light_ptr1->SetScaleRadiance(1.75);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);

	//image
	std::shared_ptr<Image> image_ptr = std::make_shared<Image>();
	image_ptr->ReadPpmFile("Additional_Texture/TextureFiles/jpg/CountryScene.jpg");

	//mapping
	std::shared_ptr<CylindricalMap> map_ptr = std::make_shared<CylindricalMap>();

	// image texture
	std::shared_ptr<ImageTexture> texture_ptr = std::make_shared<ImageTexture>();
	texture_ptr->SetImage(image_ptr);
	texture_ptr->SetMapping(map_ptr);

	//set object
	std::shared_ptr<SV_Matte> sv_matte_ptr = std::make_shared<SV_Matte>();
	sv_matte_ptr->SetKa(0.40);
	sv_matte_ptr->SetKd(0.95);
	sv_matte_ptr->SetCd(texture_ptr);

	std::shared_ptr<OpenCylinder> cylinder_ptr = std::make_shared<OpenCylinder>();
	cylinder_ptr->SetMaterial(sv_matte_ptr);
	AddObject(cylinder_ptr);
}