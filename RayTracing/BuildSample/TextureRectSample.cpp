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
	mBackGroundColor = RGBColor(0.0);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinhole_ptr = std::make_shared<Pinhole>();
	pinhole_ptr->SetEye(5, 1.5, 8);
	pinhole_ptr->SetLookAt(0.25, 0.0, 0.0);
	pinhole_ptr->SetViewDistance(1000.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);

	//sub light
	std::shared_ptr<Directional> light_ptr1 = std::make_shared<Directional>();
	light_ptr1->SetDirection(-15, 20, 25);
	light_ptr1->SetScaleRadiance(2.5);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);

	//image
	std::shared_ptr<Image> image_ptr = std::make_shared<Image>();
	image_ptr->ReadPpmFile("Additional_Texture/TextureFiles/jpg/Lightlace.jpg");

	//mapping
	std::shared_ptr<RectangularMap> map_ptr = std::make_shared<RectangularMap>();

	// image texture
	std::shared_ptr<ImageTexture> texture_ptr = std::make_shared<ImageTexture>();
	texture_ptr->SetImage(image_ptr);
	texture_ptr->SetMapping(map_ptr);

	//set object
	std::shared_ptr<SV_Matte> sv_matte_ptr = std::make_shared<SV_Matte>();
	sv_matte_ptr->SetKa(0.40);
	sv_matte_ptr->SetKd(0.95);
	sv_matte_ptr->SetCd(texture_ptr);

	std::shared_ptr<Rectangler> rectangule_ptr = std::make_shared<Rectangler>();
	rectangule_ptr->SetMaterial(sv_matte_ptr);

	std::shared_ptr<Instance> lightlace_ptr = std::make_shared<Instance>(rectangule_ptr);
	lightlace_ptr->Scale(1.0, 1.0, 1.5);
	lightlace_ptr->RotateZ(90);
	lightlace_ptr->RotateY(90);
	AddObject(lightlace_ptr);

	//ground plane
	std::shared_ptr<Matte> matte_ptr = std::make_shared<Matte>();
	matte_ptr->SetKa(0.25);
	matte_ptr->SetKd(0.5);
	matte_ptr->SetCd(1.0);

	std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0.0, -1.0, 0.0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr);
	AddObject(plane_ptr);
}