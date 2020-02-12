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
	mBackGroundColor = black;

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(1.0);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinhole_ptr = std::make_shared<Pinhole>();
	pinhole_ptr->SetEye(11, 5, 9);
	pinhole_ptr->SetLookAt(0, -0.5, 0);
	pinhole_ptr->SetViewDistance(1600.0);
	pinhole_ptr->ComputeUVW();
	SetCamera(pinhole_ptr);


	//sub light
	std::shared_ptr<Directional> light_ptr1 = std::make_shared<Directional>();
	light_ptr1->SetDirection(0.75, 1, -0.15);
	light_ptr1->SetScaleRadiance(4.5);
	light_ptr1->SetIsShadow(true);
	AddLight(light_ptr1);

	//image
	std::shared_ptr<Image> image_ptr = std::make_shared<Image>();
	image_ptr->ReadPpmFile("Additional_Texture/TextureFiles/jpg/BlueGlass.jpg");

	// image texture
	std::shared_ptr<ImageTexture> texture_ptr = std::make_shared<ImageTexture>();
	texture_ptr->SetImage(image_ptr);

	//set object
	std::shared_ptr<SV_Matte> sv_matte_ptr = std::make_shared<SV_Matte>();
	sv_matte_ptr->SetKa(0.1);
	sv_matte_ptr->SetKd(0.75);
	sv_matte_ptr->SetCd(texture_ptr);

	const std::string fileName = "./Additional_File/PLYFiles/TwoUVTriangles.ply";
	std::shared_ptr<Grid> grid_ptr = std::make_shared<Grid>();
	grid_ptr->ReadUVTriangles(fileName, Grid::ETriangleType::smooth);
	grid_ptr->SetMaterial(sv_matte_ptr);
	grid_ptr->SetupCells();
	AddObject(grid_ptr);

	std::shared_ptr<Matte> matte_ptr = std::make_shared<Matte>();
	matte_ptr->SetCd(1, 0.9, 0.6);
	matte_ptr->SetKa(0.25);
	matte_ptr->SetKd(0.4);

	std::shared_ptr<Plane> plane_ptr1 = std::make_shared<Plane>(Point3D(0, -2.0, 0), Normal(0, 1, 0));
	plane_ptr1->SetMaterial(matte_ptr);
	AddObject(plane_ptr1);
}